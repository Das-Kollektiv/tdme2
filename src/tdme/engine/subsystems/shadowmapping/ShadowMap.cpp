#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/ImposterObject.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/LODObject.h>
#include <tdme/engine/LODObjectImposter.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/ObjectParticleSystem.h>
#include <tdme/engine/ObjectRenderGroup.h>
#include <tdme/engine/ParticleSystemGroup.h>
#include <tdme/engine/Partition.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::make_unique;
using std::unique_ptr;
using std::vector;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::LineSegment;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::FrameBuffer;
using tdme::engine::ImposterObject;
using tdme::engine::Light;
using tdme::engine::LODObject;
using tdme::engine::LODObjectImposter;
using tdme::engine::Object;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::ObjectRenderGroup;
using tdme::engine::Partition;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

ShadowMap::ShadowMap(ShadowMapping* shadowMapping, int32_t width, int32_t height)
{
	this->shadowMapping = shadowMapping;
	lightCamera = make_unique<Camera>(shadowMapping->renderer);
	lightCamera->setCameraMode(Camera::CAMERAMODE_NONE);
	frameBuffer = make_unique<FrameBuffer>(width, height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER);
	if (shadowMapping->renderer->getRendererType() == Renderer::RENDERERTYPE_VULKAN) {
		biasMatrix.set(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, -0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f
		);
	} else {
		biasMatrix.set(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f
		);
	}
	depthBiasMVPMatrix.identity();
}

ShadowMap::~ShadowMap() {
}

void ShadowMap::initialize()
{
	frameBuffer->initialize();
}

void ShadowMap::reshape(int32_t width, int32_t height)
{
}

void ShadowMap::dispose()
{
	frameBuffer->dispose();
}

void ShadowMap::bindDepthBufferTexture(int contextIdx)
{
	frameBuffer->bindDepthBufferTexture(contextIdx);
}

Camera* ShadowMap::getCamera()
{
	return lightCamera.get();
}

void ShadowMap::createCascades(Light* light) {
	// use default context
	auto contextIdx = shadowMapping->renderer->CONTEXTINDEX_DEFAULT;
	auto engine = shadowMapping->getEngine();

	// https://ahbejarano.gitbook.io/lwjglgamedev/chapter-17
	auto camera = engine->getCamera();
	auto viewMatrix = camera->getCameraMatrix();
	auto projMatrix = camera->getProjectionMatrix();
	auto lightDir = light->getSpotDirection().clone().normalize();

	auto cascadeSplitLambda = 0.95f;

	auto nearClip = camera->getZNear();
	auto farClip = camera->getZFar();
	auto clipRange = farClip - nearClip;

	auto minZ = nearClip;
	auto maxZ = nearClip + clipRange;

	auto range = maxZ - minZ;
	auto ratio = maxZ / minZ;

	// Calculate split depths based on view camera frustum
	// Based on method presented in https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch10.html
	array<float, CASCADE_COUNT> cascadeSplits;
	for (auto i = 0; i < CASCADE_COUNT; i++) {
		auto p = static_cast<float>(i + 1) / static_cast<float>(CASCADE_COUNT);
		auto log = minZ * Math::pow(ratio, p);
		auto uniform = minZ + range * p;
		auto d = cascadeSplitLambda * (log - uniform) + uniform;
		cascadeSplits[i] = (d - nearClip) / clipRange;
	}
	array<Vector3, 8> frustumCorners = {
		Vector3(-1.0f, 1.0f, -1.0f), // left, top, znear
		Vector3(1.0f, 1.0f, -1.0f), // right, top, znear
		Vector3(1.0f, -1.0f, -1.0f), // right, bottom, znear
		Vector3(-1.0f, -1.0f, -1.0f), // left, bottom, znear
		Vector3(-1.0f, 1.0f, 1.0f), // left, top, zfar
		Vector3(1.0f, 1.0f, 1.0f), // right, top, zfar
		Vector3(1.0f, -1.0f, 1.0f), // right, bottom, zfar
		Vector3(-1.0f, -1.0f, 1.0f), // left, bottom, zfar
	};

	Console::printLine("FC");
	for (const auto& frustomCorner: frustumCorners) {
		Console::printLine(
			"\t" +
			to_string(frustomCorner.getX()) + ", " +
			to_string(frustomCorner.getY()) + ", " +
			to_string(frustomCorner.getZ()) + "; "
		);
	}
	Console::printLine();

	// Project frustum corners into world space
	auto invCam = viewMatrix.clone().multiply(projMatrix).invert();
	for (int j = 0; j < frustumCorners.size(); j++) {
		auto invCorner = invCam.multiply(Vector4(frustumCorners[j], 1.0f));
		frustumCorners[j].set(
			invCorner.getX() / invCorner.getW(),
			invCorner.getY() / invCorner.getW(),
			invCorner.getZ() / invCorner.getW()
		);
	}

	//
	Console::printLine("FC@");
	for (const auto& frustomCorner: frustumCorners) {
		Console::printLine(
			"\t" +
			to_string(frustomCorner.getX()) + ", " +
			to_string(frustomCorner.getY()) + ", " +
			to_string(frustomCorner.getZ()) + "; "
		);
	}
	Console::printLine();

	// Calculate orthographic projection matrix for each cascade
	float lastSplitDist = 0.0f;
	for (auto i = 0; i < CASCADE_COUNT; i++) {
		Console::printLine("Cascade@" + to_string(i));

		float splitDist = cascadeSplits[i];

		/*
		Console::printLine("FC@" + to_string(i) + "@2");
		for (const auto& frustomCorner: frustumCorners) {
			Console::printLine(
				"\t" +
				to_string(frustomCorner.getX()) + ", " +
				to_string(frustomCorner.getY()) + ", " +
				to_string(frustomCorner.getZ()) + "; "
			);
		}
		Console::printLine();
		*/

		//
		Console::printLine("FC@" + to_string(i));
		for (const auto& frustomCorner: frustumCorners) {
			Console::printLine(
				"\t" +
				to_string(frustomCorner.getX()) + ", " +
				to_string(frustomCorner.getY()) + ", " +
				to_string(frustomCorner.getZ()) + "; "
			);
		}
		Console::printLine();

		// Get frustum center
		Vector3 frustumCenter;
		for (auto j = 0; j < frustumCorners.size(); j++) {
			frustumCenter.add(frustumCorners[j]);
		}
		frustumCenter.scale(1.0f / static_cast<float>(frustumCorners.size()));

		//
		Console::printLine("Center");
		Console::print(
			to_string(frustumCenter.getX()) + ", " +
			to_string(frustumCenter.getY()) + ", " +
			to_string(frustumCenter.getZ()) + "; "
		);
		Console::printLine();

		//
		float radius = 0.0f;
		for (auto j = 0; j < frustumCorners.size(); j++) {
			auto distance = frustumCorners[j].clone().sub(frustumCenter).computeLength();
			radius = Math::max(radius, distance);
		}
		radius = Math::ceil(radius * 16.0f) / 16.0f;

		//
		auto maxExtents = Vector3(radius, radius, radius);
		auto minExtents = maxExtents.clone().scale(-1.0f);

		Console::printLine("Max@" + to_string(i));
		Console::print(
			to_string(maxExtents.getX()) + ", " +
			to_string(maxExtents.getY()) + ", " +
			to_string(maxExtents.getZ()) + "; "
		);
		Console::printLine();

		Console::printLine("Min@" + to_string(i));
		Console::print(
			to_string(minExtents.getX()) + ", " +
			to_string(minExtents.getY()) + ", " +
			to_string(minExtents.getZ()) + "; "
		);
		Console::printLine();

		auto eye = frustumCenter.clone().sub(lightDir.clone().scale(-minExtents.getZ()));
		auto up = Camera::computeUpVector(eye, frustumCenter);


		Console::printLine("lightDir@" + to_string(i));
		Console::print(
			to_string(lightDir.getX()) + ", " +
			to_string(lightDir.getY()) + ", " +
			to_string(lightDir.getZ()) + "; "
		);
		Console::printLine();

		Console::printLine("eye@" + to_string(i));
		Console::print(
			to_string(eye.getX()) + ", " +
			to_string(eye.getY()) + ", " +
			to_string(eye.getZ()) + "; "
		);
		Console::printLine();

		Console::printLine("up@" + to_string(i));
		Console::print(
			to_string(up.getX()) + ", " +
			to_string(up.getY()) + ", " +
			to_string(up.getZ()) + "; "
		);
		Console::printLine();

		//
		Matrix4x4 lightOrthoMatrix;
		{
			auto leftPlane = minExtents.getX();
			auto rightPlane = maxExtents.getX();
			auto topPlane = minExtents.getY();
			auto bottomPlane = maxExtents.getY();
			auto nearPlane = 0.0f;
			auto farPlane = maxExtents.getZ() - minExtents.getZ();
			lightOrthoMatrix.set(
				2.0f / (rightPlane - leftPlane),
				0.0f,
				0.0f,
				0.0f,
				0.0f,
				2.0f / (topPlane - bottomPlane),
				0.0f,
				0.0f,
				0.0f,
				0.0f,
				-2.0f / (farPlane - nearPlane),
				0.0f,
				-(rightPlane + leftPlane) / (rightPlane - leftPlane),
				-(topPlane + bottomPlane) / (topPlane - bottomPlane),
				-(farPlane + nearPlane) / (farPlane - nearPlane),
				1.0f
			);
		}

		//
		Matrix4x4 lightViewMatrix;
		{
			//
			auto forwardVector = lightDir;
			auto upVector = up;
			auto sideVector = Vector3::computeCrossProduct(forwardVector, upVector).normalize();

			Console::printLine("forward@" + to_string(i));
			Console::print(
				to_string(forwardVector.getX()) + ", " +
				to_string(forwardVector.getY()) + ", " +
				to_string(forwardVector.getZ()) + "; "
			);
			Console::printLine();

			Console::printLine("side@" + to_string(i));
			Console::print(
				to_string(sideVector.getX()) + ", " +
				to_string(sideVector.getY()) + ", " +
				to_string(sideVector.getZ()) + "; "
			);
			Console::printLine();

			Console::printLine("up@" + to_string(i));
			Console::print(
				to_string(upVector.getX()) + ", " +
				to_string(upVector.getY()) + ", " +
				to_string(upVector.getZ()) + "; "
			);
			Console::printLine();

			//
			lightViewMatrix.
				identity().
				setTranslation(
					eye.clone().scale(-1.0f)
				).
				multiply(
					Matrix4x4(
						sideVector[0],
						upVector[0],
						-forwardVector[0],
						0.0f,
						sideVector[1],
						upVector[1],
						-forwardVector[1],
						0.0f,
						sideVector[2],
						upVector[2],
						-forwardVector[2],
						0.0f,
						0.0f,
						0.0f,
						0.0f,
						1.0f
					)
				);
		}

		//
		for (auto j = 0; j < frustumCorners.size() / 2; j++) {
			auto dist = frustumCorners[j + 4].clone().sub(frustumCorners[j]);
			frustumCorners[j + 4].add(dist.clone().scale(splitDist));
			frustumCorners[j].add(dist.clone().scale(lastSplitDist));
		}

		// Store split distance and matrix in cascade
		auto& cascadeShadow = cascadeShadows[i];
		cascadeShadow.splitDistance = (nearClip + splitDist * clipRange) * -1.0f;
		cascadeShadow.projViewMatrix = lightViewMatrix.clone().multiply(lightOrthoMatrix);
		lastSplitDist = cascadeSplits[i];

		Console::printLine("Matrix@" + to_string(i));
		for (auto v: lightOrthoMatrix.getArray()) Console::print(to_string(v) + " ");
		Console::printLine();
		for (auto v: lightViewMatrix.getArray()) Console::print(to_string(v) + " ");
		Console::printLine();
		for (auto v: cascadeShadow.projViewMatrix.getArray()) Console::print(to_string(v) + " ");
		Console::printLine();

		if (i == 0) {
			//
			lightCamera->setLookFrom(eye);
			lightCamera->setLookAt(frustumCenter);
			lightCamera->setUpVector(up);
			lightCamera->setZFar(250.0f);
			lightCamera->updateCustom(contextIdx, frameBuffer->getWidth(), frameBuffer->getHeight(), eye, frustumCenter, up, lightOrthoMatrix, lightViewMatrix);
			lightCamera->getFrustum()->update();

			// clear visible objects
			visibleObjects.clear();

			// determine visible objects and objects that should generate a shadow
			for (auto entity: shadowMapping->engine->getPartition()->getVisibleEntities(lightCamera->getFrustum())) {
				switch (entity->getEntityType()) {
					case Entity::ENTITYTYPE_OBJECTRENDERGROUP:
						{
							auto org = static_cast<ObjectRenderGroup*>(entity);
							auto orgEntity = org->getEntity();
							if (orgEntity != nullptr) {
								if (orgEntity->isContributesShadows() == false) continue;
								switch(orgEntity->getEntityType()) {
									case Entity::ENTITYTYPE_OBJECT:
										{
											auto object = static_cast<Object*>(orgEntity);
											visibleObjects.push_back(object);
										}
										break;
									case Entity::ENTITYTYPE_LODOBJECT:
										{
											auto lodObject = static_cast<LODObject*>(orgEntity);
											if (lodObject->isContributesShadows() == false) continue;
											auto object = lodObject->getLODObject();
											if (object != nullptr) {
												visibleObjects.push_back(object);
											}
										}
										break;
									default:
										break;
								}
							}
						}
						break;
					case Entity::ENTITYTYPE_OBJECT:
						{
							auto object = static_cast<Object*>(entity);
							if (object->isContributesShadows() == false) continue;
							visibleObjects.push_back(object);
						}
						break;
					case Entity::ENTITYTYPE_LODOBJECT:
						{
							auto lodObject = static_cast<LODObject*>(entity);
							if (lodObject->isContributesShadows() == false) continue;
							auto object = lodObject->getLODObject();
							if (object != nullptr) visibleObjects.push_back(object);
						}
						break;
					case Entity::ENTITYTYPE_IMPOSTEROBJECT:
						{
							auto object = static_cast<ImposterObject*>(entity);
							if (object->isContributesShadows() == false) continue;
							visibleObjects.push_back(object->getBillboardObject());
						}
						break;
					case Entity::ENTITYTYPE_LODOBJECTIMPOSTER:
						{
							auto lodObjectImposter = static_cast<LODObjectImposter*>(entity);
							if (lodObjectImposter->isContributesShadows() == false) continue;
							auto object = lodObjectImposter->getLODObject();
							if (object != nullptr) visibleObjects.push_back(object);
						}
						break;
					case Entity::ENTITYTYPE_OBJECTPARTICLESYSTEM:
						{
							auto opse = static_cast<ObjectParticleSystem*>(entity);
							if (opse->isContributesShadows() == false) continue;
							for (auto object: opse->getEnabledObjects()) visibleObjects.push_back(object);
						}
						break;
					case Entity::ENTITYTYPE_PARTICLESYSTEMGROUP:
						{
							auto psg = static_cast<ParticleSystemGroup*>(entity);
							for (auto ps: psg->getParticleSystems()) {
								if (ps->getEntityType() != Entity::ENTITYTYPE_OBJECTPARTICLESYSTEM) continue;
								auto opse = static_cast<ObjectParticleSystem*>(ps);
								if (opse->isContributesShadows() == false) continue;
								for (auto object: opse->getEnabledObjects()) visibleObjects.push_back(object);
							}
						}
						break;
					case Entity::ENTITYTYPE_ENTITYHIERARCHY:
						{
							auto eh = static_cast<EntityHierarchy*>(entity);
							if (eh->isContributesShadows() == false) continue;
							for (auto entity: eh->getEntities()) {
								if (entity->getEntityType() != Entity::ENTITYTYPE_OBJECT) continue;
								auto object = static_cast<Object*>(entity);
								if (object->isEnabled() == false) continue;
								visibleObjects.push_back(object);
							}
						}
						break;
					default:
						break;
				}
			}

			// bind frame buffer
			frameBuffer->enableFrameBuffer();
			// clear depth buffer
			shadowMapping->renderer->clear(shadowMapping->renderer->CLEAR_DEPTH_BUFFER_BIT);
			// generate shadow map texture matrix
			computeDepthBiasMVPMatrix();
			// only draw opaque face entities as shadows will not be produced from transparent objects
			for (auto i = 0; i < Entity::RENDERPASS_MAX; i++) {
				auto renderPass = static_cast<Entity::RenderPass>(Math::pow(2, i));
				shadowMapping->entityRenderer->render(
					renderPass,
					visibleObjects,
					false,
					EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
					EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY
				);
			}
		}
	}
}

void ShadowMap::createShadowMap(Light* light)
{
	createCascades(light);
	return;
	//

	// use default context
	auto contextIdx = shadowMapping->renderer->CONTEXTINDEX_DEFAULT;

	//
	auto camera = shadowMapping->engine->getCamera();

	//
	auto lightDirection = light->getSpotDirection().clone().normalize();

	// directional lights
	if (light->isDirectional() == true) {
		// try to determine light position
		// 	left
		auto left = camera->getModelViewProjectionInvertedMatrix().multiply(
			Vector4(
				(2.0f * 0.0f) - 1.0f,
				1.0f - (2.0f * 0.5f),
				2.0f * 0.997f - 1.0f,
				1.0f
			)
		);
		left.scale(1.0f / left.getW());

		//	right
		auto right = camera->getModelViewProjectionInvertedMatrix().multiply(
			Vector4(
				(2.0f * 1.0f) - 1.0f,
				1.0f - (2.0f * 0.5f),
				2.0f * 0.997f - 1.0f,
				1.0f
			)
		);
		right.scale(1.0f / right.getW());

		//	center
		auto center4 = camera->getModelViewProjectionInvertedMatrix().multiply(
			Vector4(
				(2.0f * 0.5f) - 1.0f,
				1.0f - (2.0f * 1.0f),
				2.0f * 0.5f - 1.0f,
				1.0f
			)
		);
		center4.scale(1.0f / center4.getW());

		// so we get some contraints for the shadow map camera, TODO: improve me
		Vector3 center(Vector3(center4.getX(), center4.getY(), center4.getZ()));
		auto width = Vector3(right.getX(), right.getY(), right.getZ()).sub(Vector3(left.getX(), left.getY(), left.getZ())).computeLength() * shadowMapping->engine->getShadowMapLightEyeDistanceScale();

		// light camera
		// compute camera from view of light
		auto lightLookFrom = center.clone().sub(lightDirection.clone().scale(width * 0.5f));

		// set up light camera from view of light
		Vector3 lightCameraUpVector;
		Vector3 lightCameraSideVector;
		lightCamera->setFrustumMode(Camera::FRUSTUMMODE_ORTHOGRAPHIC);
		lightCamera->setOrthographicFrustumScale((width / frameBuffer->getWidth()) / 1.25f);
		lightCamera->setZNear(camera->getZNear());
		lightCamera->setZFar(250.0f);
		lightCamera->setLookFrom(lightLookFrom);
	} else {
		auto lightPosition = light->getPosition();
		lightPosition.scale(1.0f / lightPosition.getW());
		auto lightPosition3 = Vector3(lightPosition.getX(), lightPosition.getY(), lightPosition.getZ());
		lightCamera->setFrustumMode(Camera::FRUSTUMMODE_PERSPECTIVE);
		lightCamera->setZNear(camera->getZNear());
		lightCamera->setZFar(150.0f);
		lightCamera->setLookFrom(lightPosition3);
	}

	//
	lightCamera->setForwardVector(lightDirection);
	lightCamera->setSideVector(Vector3(1.0f, 0.0f, 0.0f));
	// TODO: fix cross product NaN if side vector == forward vector
	auto lightCameraUpVector = Vector3::computeCrossProduct(lightCamera->getForwardVector(), lightCamera->getSideVector());
	lightCamera->setUpVector(lightCameraUpVector);
	auto lightCameraSideVector = Vector3::computeCrossProduct(lightCamera->getForwardVector(), lightCamera->getUpVector());
	lightCamera->setSideVector(lightCameraSideVector);
	lightCamera->setUpVector(lightCameraUpVector);
	lightCamera->update(contextIdx, frameBuffer->getWidth(), frameBuffer->getHeight());
	lightCamera->getFrustum()->update();

	// clear visible objects
	visibleObjects.clear();

	// determine visible objects and objects that should generate a shadow
	for (auto entity: shadowMapping->engine->getPartition()->getVisibleEntities(lightCamera->getFrustum())) {
		switch (entity->getEntityType()) {
			case Entity::ENTITYTYPE_OBJECTRENDERGROUP:
				{
					auto org = static_cast<ObjectRenderGroup*>(entity);
					auto orgEntity = org->getEntity();
					if (orgEntity != nullptr) {
						if (orgEntity->isContributesShadows() == false) continue;
						switch(orgEntity->getEntityType()) {
							case Entity::ENTITYTYPE_OBJECT:
								{
									auto object = static_cast<Object*>(orgEntity);
									visibleObjects.push_back(object);
								}
								break;
							case Entity::ENTITYTYPE_LODOBJECT:
								{
									auto lodObject = static_cast<LODObject*>(orgEntity);
									if (lodObject->isContributesShadows() == false) continue;
									auto object = lodObject->getLODObject();
									if (object != nullptr) {
										visibleObjects.push_back(object);
									}
								}
								break;
							default:
								break;
						}
					}
				}
				break;
			case Entity::ENTITYTYPE_OBJECT:
				{
					auto object = static_cast<Object*>(entity);
					if (object->isContributesShadows() == false) continue;
					visibleObjects.push_back(object);
				}
				break;
			case Entity::ENTITYTYPE_LODOBJECT:
				{
					auto lodObject = static_cast<LODObject*>(entity);
					if (lodObject->isContributesShadows() == false) continue;
					auto object = lodObject->getLODObject();
					if (object != nullptr) visibleObjects.push_back(object);
				}
				break;
			case Entity::ENTITYTYPE_IMPOSTEROBJECT:
				{
					auto object = static_cast<ImposterObject*>(entity);
					if (object->isContributesShadows() == false) continue;
					visibleObjects.push_back(object->getBillboardObject());
				}
				break;
			case Entity::ENTITYTYPE_LODOBJECTIMPOSTER:
				{
					auto lodObjectImposter = static_cast<LODObjectImposter*>(entity);
					if (lodObjectImposter->isContributesShadows() == false) continue;
					auto object = lodObjectImposter->getLODObject();
					if (object != nullptr) visibleObjects.push_back(object);
				}
				break;
			case Entity::ENTITYTYPE_OBJECTPARTICLESYSTEM:
				{
					auto opse = static_cast<ObjectParticleSystem*>(entity);
					if (opse->isContributesShadows() == false) continue;
					for (auto object: opse->getEnabledObjects()) visibleObjects.push_back(object);
				}
				break;
			case Entity::ENTITYTYPE_PARTICLESYSTEMGROUP:
				{
					auto psg = static_cast<ParticleSystemGroup*>(entity);
					for (auto ps: psg->getParticleSystems()) {
						if (ps->getEntityType() != Entity::ENTITYTYPE_OBJECTPARTICLESYSTEM) continue;
						auto opse = static_cast<ObjectParticleSystem*>(ps);
						if (opse->isContributesShadows() == false) continue;
						for (auto object: opse->getEnabledObjects()) visibleObjects.push_back(object);
					}
				}
				break;
			case Entity::ENTITYTYPE_ENTITYHIERARCHY:
				{
					auto eh = static_cast<EntityHierarchy*>(entity);
					if (eh->isContributesShadows() == false) continue;
					for (auto entity: eh->getEntities()) {
						if (entity->getEntityType() != Entity::ENTITYTYPE_OBJECT) continue;
						auto object = static_cast<Object*>(entity);
						if (object->isEnabled() == false) continue;
						visibleObjects.push_back(object);
					}
				}
				break;
			default:
				break;
		}
	}

	// bind frame buffer
	frameBuffer->enableFrameBuffer();
	// clear depth buffer
	shadowMapping->renderer->clear(shadowMapping->renderer->CLEAR_DEPTH_BUFFER_BIT);
	// generate shadow map texture matrix
	computeDepthBiasMVPMatrix();
	// only draw opaque face entities as shadows will not be produced from transparent objects
	for (auto i = 0; i < Entity::RENDERPASS_MAX; i++) {
		auto renderPass = static_cast<Entity::RenderPass>(Math::pow(2, i));
		shadowMapping->entityRenderer->render(
			renderPass,
			visibleObjects,
			false,
			EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
			EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY
		);
	}
}

void ShadowMap::computeDepthBiasMVPMatrix()
{
	// matrices
	auto modelViewMatrix = shadowMapping->renderer->getModelViewMatrix();
	auto projectionMatrix = shadowMapping->renderer->getProjectionMatrix();
	// compute shadow texture matrix
	depthBiasMVPMatrix.set(modelViewMatrix).multiply(projectionMatrix).multiply(biasMatrix);
}

void ShadowMap::updateDepthBiasMVPMatrix(int contextIdx)
{
	shadowMapping->updateDepthBiasMVPMatrix(contextIdx, depthBiasMVPMatrix);
}
