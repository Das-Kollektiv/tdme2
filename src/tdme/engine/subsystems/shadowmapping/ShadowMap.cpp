// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMap.java
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/ObjectParticleSystemEntity.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_ArrayList.h>

using tdme::engine::subsystems::shadowmapping::ShadowMap;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::ObjectParticleSystemEntity;
using tdme::engine::Partition;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

ShadowMap::ShadowMap(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ShadowMap::ShadowMap(ShadowMapping* shadowMapping, int32_t width, int32_t height) 
	: ShadowMap(*static_cast< ::default_init_tag* >(0))
{
	ctor(shadowMapping,width,height);
}

constexpr int32_t ShadowMap::TEXTUREUNIT;

void ShadowMap::ctor(ShadowMapping* shadowMapping, int32_t width, int32_t height)
{
	super::ctor();
	visibleObjects = new _ArrayList();
	this->shadowMapping = shadowMapping;
	lightCamera = new Camera(shadowMapping->renderer);
	frameBuffer = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER);
	biasMatrix = new Matrix4x4(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f);
	depthBiasMVPMatrix = (new Matrix4x4())->identity();
	lightDirection = new Vector3();
	lightLookAt = new Vector3();
	lightLookFrom = new Vector3();
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

void ShadowMap::render(Light* light, _ArrayList* objects)
{
	visibleObjects->clear();
	auto camera = shadowMapping->engine->getCamera();
	auto lightEyeDistance = lightDirection->set(camera->getLookAt())->sub(camera->getLookFrom())->computeLength() * shadowMapping->lightEyeDistanceScale;
	lightDirection->set(light->getSpotDirection())->normalize();
	lightLookAt->set(camera->getLookAt());
	lightLookFrom->set(lightLookAt)->sub(lightDirection->scale(lightEyeDistance));
	auto lightCameraZFar = lightEyeDistance * 2.0f;
	if (camera->getZFar() > lightCameraZFar)
		lightCameraZFar = camera->getZFar();

	lightCamera->setZNear(camera->getZNear());
	lightCamera->setZFar(lightCameraZFar);
	lightCamera->getLookFrom()->set(lightLookFrom);
	lightCamera->getLookAt()->set(lightLookAt);
	lightCamera->computeUpVector(lightCamera->getLookFrom(), lightCamera->getLookAt(), lightCamera->getUpVector());
	lightCamera->update(frameBuffer->getWidth(), frameBuffer->getHeight());
	frameBuffer->enableFrameBuffer();
	shadowMapping->renderer->clear(shadowMapping->renderer->CLEAR_DEPTH_BUFFER_BIT);
	for (auto _i = shadowMapping->engine->getPartition()->getVisibleEntities(lightCamera->getFrustum())->iterator(); _i->hasNext(); ) {
		Entity* entity = java_cast< Entity* >(_i->next());
		{
			if (dynamic_cast< Object3D* >(entity) != nullptr) {
				auto object = java_cast< Object3D* >(entity);
				if (object->isDynamicShadowingEnabled() == false)
					continue;

				visibleObjects->add(object);
			} else if (dynamic_cast< ObjectParticleSystemEntity* >(entity) != nullptr) {
				auto opse = java_cast< ObjectParticleSystemEntity* >(entity);
				if (opse->isDynamicShadowingEnabled() == false)
					continue;

				visibleObjects->addAll(opse->getEnabledObjects());
			}
		}
	}
	computeDepthBiasMVPMatrix();
	shadowMapping->object3DVBORenderer->render(visibleObjects, false);
}

void ShadowMap::computeDepthBiasMVPMatrix()
{
	auto modelViewMatrix = shadowMapping->renderer->getModelViewMatrix();
	auto projectionMatrix = shadowMapping->renderer->getProjectionMatrix();
	depthBiasMVPMatrix->set(modelViewMatrix)->multiply(projectionMatrix)->multiply(biasMatrix);
}

void ShadowMap::updateDepthBiasMVPMatrix()
{
	shadowMapping->updateDepthBiasMVPMatrix(depthBiasMVPMatrix);
}

String* ShadowMap::toString()
{
	return ::java::lang::StringBuilder().append(u"ShadowMap [frameBuffer="_j)->append(static_cast< Object* >(frameBuffer))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ShadowMap::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.shadowmapping.ShadowMap", 46);
    return c;
}

java::lang::Class* ShadowMap::getClass0()
{
	return class_();
}

