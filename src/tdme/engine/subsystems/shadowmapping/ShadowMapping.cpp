// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMapping.java
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>

#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping_RunState.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utils/_Console.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::vector;

using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
typedef ::SubArray< ::tdme::engine::Light, ::java::lang::ObjectArray > LightArray;

namespace subsystems {
namespace shadowmapping {
typedef ::SubArray< ::tdme::engine::subsystems::shadowmapping::ShadowMap, ::java::lang::ObjectArray > ShadowMapArray;
}  // namespace shadowmapping
}  // namespace subsystems
}  // namespace engine
}  // namespace tdme

ShadowMapping::ShadowMapping(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ShadowMapping::ShadowMapping(Engine* engine, GLRenderer* renderer, Object3DVBORenderer* object3DVBORenderer) 
	: ShadowMapping(*static_cast< ::default_init_tag* >(0))
{
	ctor(engine,renderer,object3DVBORenderer);
}

int32_t ShadowMapping::shadowMapWidth;

int32_t ShadowMapping::shadowMapHeight;

void ShadowMapping::setShadowMapSize(int32_t width, int32_t height)
{
	clinit();
	shadowMapWidth = width;
	shadowMapHeight = height;
}

void ShadowMapping::ctor(Engine* engine, GLRenderer* renderer, Object3DVBORenderer* object3DVBORenderer)
{
	super::ctor();
	width = shadowMapWidth;
	height = shadowMapHeight;
	this->engine = engine;
	this->renderer = renderer;
	this->object3DVBORenderer = object3DVBORenderer;
	this->lightEyeDistanceScale = 4.0f;
	shadowMaps = new ShadowMapArray(engine->getLights()->length);
	for (auto i = 0; i < shadowMaps->length; i++) {
		shadowMaps->set(i, nullptr);
	}
	shadowTransformationsMatrix = new Matrix4x4();
	depthBiasMVPMatrix = (new Matrix4x4())->identity();
	tmpMatrix = (new Matrix4x4())->identity();
	mvMatrix = (new Matrix4x4())->identity();
	mvpMatrix = (new Matrix4x4())->identity();
	normalMatrix = (new Matrix4x4())->identity();
	lightPosition4Transformed = new Vector4();
	lightPosition3Transformed = new Vector3();
	spotDirection4 = new Vector4();
	spotDirection4Transformed = new Vector4();
	spotDirection3Transformed = new Vector3();
	tmpVector3 = new Vector3();
	runState = ShadowMapping_RunState::NONE;
}

Engine* ShadowMapping::getEngine()
{
	return engine;
}

float ShadowMapping::getLightEyeDistanceScale()
{
	return lightEyeDistanceScale;
}

void ShadowMapping::setLightEyeDistanceScale(float lightEyeDistanceScale)
{
	this->lightEyeDistanceScale = lightEyeDistanceScale;
}

void ShadowMapping::reshape(int32_t width, int32_t height)
{
}

void ShadowMapping::createShadowMaps(const vector<Object3D*>& objects)
{
	runState = ShadowMapping_RunState::PRE;
	renderer->setColorMask(false, false, false, false);
	renderer->setCullFace(renderer->CULLFACE_FRONT);
	Engine::getShadowMappingShaderPre()->useProgram();
	for (auto i = 0; i < engine->getLights()->length; i++) {
		auto light = engine->getLightAt(i);
		if (light->isEnabled()) {
			if ((*shadowMaps)[i] == nullptr) {
				auto shadowMap = new ShadowMap(this, width, height);
				shadowMap->initialize();
				shadowMaps->set(i, shadowMap);
			}
			(*shadowMaps)[i]->render(light, objects);
		} else {
			if ((*shadowMaps)[i] != nullptr) {
				(*shadowMaps)[i]->dispose();
				shadowMaps->set(i, nullptr);
			}
		}
	}
	Engine::getShadowMappingShaderPre()->unUseProgram();
	renderer->setColorMask(true, true, true, true);
	renderer->setCullFace(renderer->CULLFACE_BACK);
	runState = ShadowMapping_RunState::NONE;
}

void ShadowMapping::renderShadowMaps(const vector<Object3D*>& visibleObjects)
{
	runState = ShadowMapping_RunState::RENDER;
	auto shader = Engine::getShadowMappingShaderRender();
	shader->useProgram();
	shader->setProgramTextureUnit(ShadowMap::TEXTUREUNIT);
	renderer->disableDepthBuffer();
	renderer->setDepthFunction(renderer->DEPTHFUNCTION_EQUAL);
	for (auto i = 0; i < shadowMaps->length; i++) {
		if ((*shadowMaps)[i] == nullptr)
			continue;

		auto shadowMap = (*shadowMaps)[i];
		auto light = engine->getLightAt(i);
		shader->setProgramLightPosition(lightPosition3Transformed->set(tmpVector3->set(renderer->getCameraMatrix()->multiply(light->getPosition(), lightPosition4Transformed)->scale(1.0f / lightPosition4Transformed->getW()))));
		shader->setProgramLightDirection(spotDirection3Transformed->set(tmpVector3->set(renderer->getCameraMatrix()->multiply(spotDirection4->set(light->getSpotDirection(), 0.0f), spotDirection4Transformed))));
		shader->setProgramLightSpotExponent(light->getSpotExponent());
		shader->setProgramLightSpotCosCutOff(light->getSpotCutOff());
		shader->setProgramLightConstantAttenuation(light->getConstantAttenuation());
		shader->setProgramLightLinearAttenuation(light->getLinearAttenuation());
		shader->setProgramLightQuadraticAttenuation(light->getQuadraticAttenuation());
		shader->setProgramTexturePixelDimensions(1.0f / static_cast< float >(shadowMap->getWidth()), 1.0f / static_cast< float >(shadowMap->getHeight()));
		shadowMap->updateDepthBiasMVPMatrix();
		auto textureUnit = renderer->getTextureUnit();
		renderer->setTextureUnit(ShadowMap::TEXTUREUNIT);
		shadowMap->bindDepthBufferTexture();
		renderer->setTextureUnit(textureUnit);
		renderer->enableBlending();
		object3DVBORenderer->render(visibleObjects, false);
		renderer->disableBlending();
	}
	auto textureUnit = renderer->getTextureUnit();
	renderer->setTextureUnit(ShadowMap::TEXTUREUNIT);
	renderer->bindTexture(renderer->ID_NONE);
	renderer->setTextureUnit(textureUnit);
	renderer->disableBlending();
	renderer->enableDepthBuffer();
	renderer->setDepthFunction(renderer->DEPTHFUNCTION_LESSEQUAL);
	runState = ShadowMapping_RunState::NONE;
}

void ShadowMapping::dispose()
{
	for (auto i = 0; i < shadowMaps->length; i++) {
		if ((*shadowMaps)[i] != nullptr) {
			(*shadowMaps)[i]->dispose();
			shadowMaps->set(i, nullptr);
		}
	}
}

void ShadowMapping::startObjectTransformations(Matrix4x4* transformationsMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	shadowTransformationsMatrix->set(depthBiasMVPMatrix);
	tmpMatrix->set(depthBiasMVPMatrix);
	depthBiasMVPMatrix->set(transformationsMatrix)->multiply(tmpMatrix);
	updateDepthBiasMVPMatrix();
}

void ShadowMapping::endObjectTransformations()
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	depthBiasMVPMatrix->set(shadowTransformationsMatrix);
}

void ShadowMapping::updateMVPMatrices(GLRenderer* renderer)
{
	if (runState == ShadowMapping_RunState::NONE)
		return;

	mvMatrix->set(renderer->getModelViewMatrix());
	mvpMatrix->set(mvMatrix)->multiply(renderer->getProjectionMatrix());
	normalMatrix->set(mvMatrix)->invert()->transpose();
	{
		auto v = runState;
		if ((v == ShadowMapping_RunState::PRE)) {
{
				Engine::getShadowMappingShaderPre()->setProgramMVPMatrix(mvpMatrix);
				goto end_switch0;;
			}		}
		if ((v == ShadowMapping_RunState::PRE) || (v == ShadowMapping_RunState::RENDER)) {
{
				auto shader = Engine::getShadowMappingShaderRender();
				shader->setProgramMVMatrix(mvMatrix);
				shader->setProgramMVPMatrix(mvpMatrix);
				shader->setProgramNormalMatrix(normalMatrix);
				goto end_switch0;;
			}		}
		if (((v == ShadowMapping_RunState::PRE) || (v == ShadowMapping_RunState::RENDER) || ((v != ShadowMapping_RunState::PRE) && (v != ShadowMapping_RunState::RENDER)))) {
{
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ShadowMapping::updateMVPMatrices(): unsupported run state '"_j)->append(static_cast< Object* >(runState))
					->append(u"'"_j)->toString()));
				goto end_switch0;;
			}		}
end_switch0:;
	}

}

void ShadowMapping::updateDepthBiasMVPMatrix(Matrix4x4* depthBiasMVPMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	this->depthBiasMVPMatrix->set(depthBiasMVPMatrix);
	Engine::getShadowMappingShaderRender()->setProgramDepthBiasMVPMatrix(depthBiasMVPMatrix);
}

void ShadowMapping::updateDepthBiasMVPMatrix()
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	Engine::getShadowMappingShaderRender()->setProgramDepthBiasMVPMatrix(depthBiasMVPMatrix);
}

String* ShadowMapping::toString()
{
	return ::java::lang::StringBuilder().append(u"ShadowMapping [shadowMaps="_j)->append(Arrays::toString(static_cast< ObjectArray* >(shadowMaps)))
		->append(u", width="_j)
		->append(width)
		->append(u", height="_j)
		->append(height)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ShadowMapping::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.shadowmapping.ShadowMapping", 50);
    return c;
}

void ShadowMapping::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		shadowMapWidth = 2048;
		shadowMapHeight = 2048;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* ShadowMapping::getClass0()
{
	return class_();
}

