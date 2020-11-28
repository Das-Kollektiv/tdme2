#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>

#include <vector>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DRenderGroup.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/ObjectParticleSystem.h>
#include <tdme/engine/ParticleSystemGroup.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::LODObject3D;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::Partition;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

ShadowMap::ShadowMap(ShadowMapping* shadowMapping, int32_t width, int32_t height)
{
	this->shadowMapping = shadowMapping;
	lightCamera = new Camera(shadowMapping->renderer);
	lightCamera->setCameraMode(Camera::CAMERAMODE_NONE);
	frameBuffer = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER);
	#if defined(VULKAN)
		biasMatrix.set(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, -0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f
		);
	#else
		biasMatrix.set(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f
		);
	#endif
	depthBiasMVPMatrix.identity();
}

ShadowMap::~ShadowMap() {
	delete lightCamera;
	delete frameBuffer;
}

int32_t ShadowMap::getWidth()
{
	return frameBuffer->getWidth();
}

int32_t ShadowMap::getHeight()
{
	return frameBuffer->getHeight();
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

void ShadowMap::bindDepthBufferTexture(void* context)
{
	frameBuffer->bindDepthBufferTexture(context);
}

Camera* ShadowMap::getCamera()
{
	return lightCamera;
}

void ShadowMap::render(Light* light)
{
	// use default context
	// TODO: object->preRender only uses default context, lets see how to make this multithreaded
	auto context = shadowMapping->renderer->getDefaultContext();

	// clear visible objects
	visibleObjects.clear();

	// determine visible objects and objects that should generate a shadow
	Entity* orgEntity = nullptr;
	Object3D* object = nullptr;
	LODObject3D* lodObject = nullptr;
	Object3DRenderGroup* org = nullptr;
	ObjectParticleSystem* opse = nullptr;
	ParticleSystemGroup* psg = nullptr;
	EntityHierarchy* eh = nullptr;
	for (auto entity: shadowMapping->engine->getPartition()->getVisibleEntities(shadowMapping->engine->getCamera()->getFrustum())) {
		if ((org = dynamic_cast<Object3DRenderGroup*>(entity)) != nullptr) {
			if ((orgEntity = org->getEntity()) != nullptr) {
				if (orgEntity->isContributesShadows() == false) continue;
				if ((object = dynamic_cast<Object3D*>(orgEntity)) != nullptr) {
					object->preRender(context);
					visibleObjects.push_back(object);
				} else
				if ((lodObject = dynamic_cast<LODObject3D*>(orgEntity)) != nullptr) {
					if (lodObject->isContributesShadows() == false) continue;
					auto object = lodObject->getLODObject();
					if (object != nullptr) {
						object->preRender(context);
						visibleObjects.push_back(object);
					}
				}
			}
		} else
		if ((object = dynamic_cast<Object3D*>(entity)) != nullptr) {
			if (object->isContributesShadows() == false) continue;
			object->preRender(context);
			visibleObjects.push_back(object);
		} else
		if ((lodObject = dynamic_cast<LODObject3D*>(entity)) != nullptr) {
			if (lodObject->isContributesShadows() == false) continue;
			auto object = lodObject->getLODObject();
			if (object != nullptr) {
				object->preRender(context);
				visibleObjects.push_back(object);
			}
		} else
		if ((opse = dynamic_cast<ObjectParticleSystem*>(entity)) != nullptr) {
			if (opse->isContributesShadows() == false) continue;
			for (auto object: opse->getEnabledObjects()) {
				object->preRender(context);
				visibleObjects.push_back(object);
			}
		} else
		if ((psg = dynamic_cast<ParticleSystemGroup*>(entity)) != nullptr) {
			for (auto ps: psg->getParticleSystems()) {
				opse = dynamic_cast<ObjectParticleSystem*>(ps);
				if (opse == nullptr) continue;
				if (opse->isContributesShadows() == false) continue;
				for (auto object: opse->getEnabledObjects()) {
					object->preRender(context);
					visibleObjects.push_back(object);
				}
			}
		} else
		if ((eh = dynamic_cast<EntityHierarchy*>(entity)) != nullptr) {
			if (eh->isContributesShadows() == false) continue;
			for (auto entity: eh->getEntities()) {
				auto object = dynamic_cast<Object3D*>(entity);
				if (object == nullptr || object->isEnabled() == false) continue;
				object->preRender(context);
				visibleObjects.push_back(object);
			}
		}
	}

	//
	auto camera = shadowMapping->engine->getCamera();

	// try to determine light position

	// 	left
	Vector4 left;
	camera->getModelViewProjectionInvertedMatrix().multiply(
		Vector4(
			(2.0f * 0.0f) - 1.0f,
			1.0f - (2.0f * 0.5f),
			2.0f * 0.997f - 1.0f,
			1.0f
		),
		left
	);
	left.scale(1.0f / left.getW());

	//	right
	Vector4 right;
	camera->getModelViewProjectionInvertedMatrix().multiply(
		Vector4(
			(2.0f * 1.0f) - 1.0f,
			1.0f - (2.0f * 0.5f),
			2.0f * 0.997f - 1.0f,
			1.0f
		),
		right
	);
	right.scale(1.0f / right.getW());

	//	center
	Vector4 center4;
	camera->getModelViewProjectionInvertedMatrix().multiply(
		Vector4(
			(2.0f * 0.5f) - 1.0f,
			1.0f - (2.0f * 1.0f),
			2.0f * 0.5f - 1.0f,
			1.0f
		),
		center4
	);
	center4.scale(1.0f / center4.getW());

	// so we get some contraints for the shadow map camera, TODO: improve me
	Vector3 center(Vector3(center4.getX(), center4.getY(), center4.getZ()));
	auto width = Vector3(right.getX(), right.getY(), right.getZ()).sub(Vector3(left.getX(), left.getY(), left.getZ())).computeLength() * shadowMapping->engine->getShadowMapLightEyeDistanceScale();

	// viewers camera
	Vector3 lightDirection;
	Vector3 lightLookFrom;
	// compute camera from view of light
	lightDirection.set(light->getSpotDirection()).normalize();
	lightLookFrom
		.set(center)
		.sub(lightDirection.clone().scale(width * 1.25f));
	// set up light camera from view of light
	Vector3 lightCameraUpVector;
	Vector3 lightCameraSideVector;
	lightCamera->setZNear(camera->getZNear());
	lightCamera->setZFar(150.0f);
	lightCamera->setLookFrom(lightLookFrom);
	lightCamera->setForwardVector(lightDirection);
	lightCamera->setSideVector(Vector3(1.0f, 0.0f, 0.0f));
	// TODO: fix cross product NaN if side vector == forward vector
	Vector3::computeCrossProduct(lightCamera->getForwardVector(), lightCamera->getSideVector(), lightCameraUpVector);
	lightCamera->setUpVector(lightCameraUpVector);
	Vector3::computeCrossProduct(lightCamera->getForwardVector(), lightCamera->getUpVector(), lightCameraSideVector);
	lightCamera->setSideVector(lightCameraSideVector);
	lightCamera->setUpVector(lightCameraUpVector);
	lightCamera->update(context, frameBuffer->getWidth(), frameBuffer->getHeight());
	// bind frame buffer
	frameBuffer->enableFrameBuffer();
	// clear depth buffer
	shadowMapping->renderer->clear(shadowMapping->renderer->CLEAR_DEPTH_BUFFER_BIT);
	// generate shadow map texture matrix
	computeDepthBiasMVPMatrix();
	// only draw opaque face entities as shadows will not be produced from transparent objects
	shadowMapping->object3DRenderer->render(
		visibleObjects,
		false,
		EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
		EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY
	);
}

void ShadowMap::computeDepthBiasMVPMatrix()
{
	// matrices
	auto modelViewMatrix = shadowMapping->renderer->getModelViewMatrix();
	auto projectionMatrix = shadowMapping->renderer->getProjectionMatrix();
	// compute shadow texture matrix
	depthBiasMVPMatrix.set(modelViewMatrix).multiply(projectionMatrix).multiply(biasMatrix);
}

void ShadowMap::updateDepthBiasMVPMatrix(void* context)
{
	shadowMapping->updateDepthBiasMVPMatrix(context, depthBiasMVPMatrix);
}

FrameBuffer* ShadowMap::getFrameBuffer() {
	return frameBuffer;
}
