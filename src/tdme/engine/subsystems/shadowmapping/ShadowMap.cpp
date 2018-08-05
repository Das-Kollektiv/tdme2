#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>

#include <vector>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DRenderGroup.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/ObjectParticleSystemEntity.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/subsystems/rendering/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::LODObject3D;
using tdme::engine::ObjectParticleSystemEntity;
using tdme::engine::Partition;
using tdme::engine::subsystems::rendering::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

constexpr int32_t ShadowMap::TEXTUREUNIT;

ShadowMap::ShadowMap(ShadowMapping* shadowMapping, int32_t width, int32_t height)
{
	this->shadowMapping = shadowMapping;
	lightCamera = new Camera(shadowMapping->renderer);
	frameBuffer = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER);
	biasMatrix.set(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f);
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

void ShadowMap::bindDepthBufferTexture()
{
	frameBuffer->bindDepthBufferTexture();
}

Camera* ShadowMap::getCamera()
{
	return lightCamera;
}

void ShadowMap::render(Light* light)
{
	// clear visible objects
	visibleObjects.clear();
	// viewers camera
	auto camera = shadowMapping->engine->getCamera();
	Vector3 lightDirection;
	Vector3 lightLookAt;
	Vector3 lightLookFrom;
	auto lightEyeDistance = lightDirection.set(camera->getLookAt()).sub(camera->getLookFrom()).computeLength() * shadowMapping->lightEyeDistanceScale;
	// compute camera from view of light
	lightDirection.set(light->getSpotDirection()).normalize();
	lightLookAt.set(camera->getLookAt());
	lightLookFrom.set(lightLookAt).sub(lightDirection.scale(lightEyeDistance));
	// determine light camera z far
	auto lightCameraZFar = lightEyeDistance * 2.0f;
	if (camera->getZFar() > lightCameraZFar)
		lightCameraZFar = camera->getZFar();
	// set up light camera from view of light
	lightCamera->setZNear(camera->getZNear());
	lightCamera->setZFar(lightCameraZFar);
	lightCamera->setLookFrom(lightLookFrom);
	lightCamera->setLookAt(lightLookAt);
	lightCamera->setUpVector(lightCamera->computeUpVector(lightCamera->getLookFrom(), lightCamera->getLookAt()));
	lightCamera->update(frameBuffer->getWidth(), frameBuffer->getHeight());
	// Bind frame buffer to shadow map fbo id
	frameBuffer->enableFrameBuffer();
	// clear depth buffer
	shadowMapping->renderer->clear(shadowMapping->renderer->CLEAR_DEPTH_BUFFER_BIT);
	// determine visible objects and objects that should generate a shadow
	Object3D* object = nullptr;
	LODObject3D* lodObject = nullptr;
	Object3DRenderGroup* org = nullptr;
	ObjectParticleSystemEntity* opse = nullptr;
	for (auto entity: *shadowMapping->engine->getPartition()->getVisibleEntities(lightCamera->getFrustum())) {
		if ((org = dynamic_cast< Object3DRenderGroup* >(entity)) != nullptr) {
			if ((object = org->getObject()) != nullptr) {
				if (object->isDynamicShadowingEnabled() == false) continue;
				object->preRender();
				visibleObjects.push_back(object);
			}
		} else
		if ((object = dynamic_cast< Object3D* >(entity)) != nullptr) {
			if (object->isDynamicShadowingEnabled() == false) continue;
			object->preRender();
			visibleObjects.push_back(object);
		} else
		if ((lodObject = dynamic_cast< LODObject3D* >(entity)) != nullptr) {
			if (lodObject->isDynamicShadowingEnabled() == false) continue;
			auto object = lodObject->getLODObject();
			if (object != nullptr) {
				object->preRender();
				visibleObjects.push_back(object);
			}
		} else
		if ((opse = dynamic_cast< ObjectParticleSystemEntity* >(entity)) != nullptr) {
			if (opse->isDynamicShadowingEnabled() == false) continue;
			for (auto object: *opse->getEnabledObjects()) {
				object->preRender();
				visibleObjects.push_back(object);
			}
		}
	}
	// generate shadow map texture matrix
	computeDepthBiasMVPMatrix();
	// only draw opaque face entities as shadows will not be produced from transparent objects
	shadowMapping->object3DVBORenderer->render(
		visibleObjects,
		false,
		Object3DVBORenderer::RENDERTYPE_NORMALS | // TODO: actually this is not required, but GL2 currently needs this
		Object3DVBORenderer::RENDERTYPE_TEXTUREARRAYS | // TODO: actually this is not required, but GL2 currently needs this
		Object3DVBORenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
		Object3DVBORenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY
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

void ShadowMap::updateDepthBiasMVPMatrix()
{
	shadowMapping->updateDepthBiasMVPMatrix(depthBiasMVPMatrix);
}
