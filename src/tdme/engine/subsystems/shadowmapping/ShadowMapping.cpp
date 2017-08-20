// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMapping.java
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>

#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utils/_Console.h>

using std::vector;
using std::wstring;
using std::to_wstring;

using tdme::engine::subsystems::shadowmapping::ShadowMapping;
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

int32_t ShadowMapping::shadowMapWidth = 2048;
int32_t ShadowMapping::shadowMapHeight = 2048;

ShadowMapping::ShadowMapping(Engine* engine, GLRenderer* renderer, Object3DVBORenderer* object3DVBORenderer) 
{
	width = shadowMapWidth;
	height = shadowMapHeight;
	this->engine = engine;
	this->renderer = renderer;
	this->object3DVBORenderer = object3DVBORenderer;
	this->lightEyeDistanceScale = 4.0f;
	shadowMaps.resize(engine->getLightCount());
	for (auto i = 0; i < shadowMaps.size(); i++) {
		shadowMaps[i] = nullptr;
	}
	shadowTransformationsMatrix = new Matrix4x4();
	depthBiasMVPMatrix.identity();
	mvMatrix.identity();
	mvpMatrix.identity();
	normalMatrix.identity();
	runState = ShadowMapping_RunState::NONE;
}

void ShadowMapping::setShadowMapSize(int32_t width, int32_t height)
{
	shadowMapWidth = width;
	shadowMapHeight = height;
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
	for (auto i = 0; i < engine->getLightCount(); i++) {
		auto light = engine->getLightAt(i);
		if (light->isEnabled()) {
			if (shadowMaps[i] == nullptr) {
				auto shadowMap = new ShadowMap(this, width, height);
				shadowMap->initialize();
				shadowMaps[i] = shadowMap;
			}
			shadowMaps[i]->render(light, objects);
		} else {
			if (shadowMaps[i] != nullptr) {
				shadowMaps[i]->dispose();
				delete shadowMaps[i];
				shadowMaps[i] = nullptr;
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
	Vector3 tmpVector3;
	Vector4 lightPosition4Transformed {  };
	Vector3 lightPosition3Transformed {  };
	Vector4 spotDirection4 {  };
	Vector4 spotDirection4Transformed {  };
	Vector3 spotDirection3Transformed {  };
	runState = ShadowMapping_RunState::RENDER;
	auto shader = Engine::getShadowMappingShaderRender();
	shader->useProgram();
	shader->setProgramTextureUnit(ShadowMap::TEXTUREUNIT);
	renderer->disableDepthBuffer();
	renderer->setDepthFunction(renderer->DEPTHFUNCTION_EQUAL);
	for (auto i = 0; i < shadowMaps.size(); i++) {
		if (shadowMaps[i] == nullptr)
			continue;

		auto shadowMap = shadowMaps[i];
		auto light = engine->getLightAt(i);
		shader->setProgramLightPosition(lightPosition3Transformed.set(tmpVector3.set(renderer->getCameraMatrix()->multiply(light->getPosition(), &lightPosition4Transformed)->scale(1.0f / lightPosition4Transformed.getW()))));
		shader->setProgramLightDirection(spotDirection3Transformed.set(tmpVector3.set(renderer->getCameraMatrix()->multiply(spotDirection4.set(light->getSpotDirection(), 0.0f), &spotDirection4Transformed))));
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
	for (auto i = 0; i < shadowMaps.size(); i++) {
		if (shadowMaps[i] != nullptr) {
			shadowMaps[i]->dispose();
			delete shadowMaps[i];
			shadowMaps[i] = nullptr;
		}
	}
}

void ShadowMapping::startObjectTransformations(Matrix4x4* transformationsMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	Matrix4x4 tmpMatrix;
	shadowTransformationsMatrix.set(&depthBiasMVPMatrix);
	tmpMatrix.set(&depthBiasMVPMatrix);
	depthBiasMVPMatrix.set(transformationsMatrix)->multiply(&tmpMatrix);
	updateDepthBiasMVPMatrix();
}

void ShadowMapping::endObjectTransformations()
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	depthBiasMVPMatrix.set(&shadowTransformationsMatrix);
}

void ShadowMapping::updateMVPMatrices(GLRenderer* renderer)
{
	if (runState == ShadowMapping_RunState::NONE)
		return;

	mvMatrix.set(renderer->getModelViewMatrix());
	mvpMatrix.set(&mvMatrix)->multiply(renderer->getProjectionMatrix());
	normalMatrix.set(&mvMatrix)->invert()->transpose();
	{
		auto v = runState;
		if ((v == ShadowMapping_RunState::PRE)) {
			{
				Engine::getShadowMappingShaderPre()->setProgramMVPMatrix(&mvpMatrix);
				goto end_switch0;;
			}
		}
		if ((v == ShadowMapping_RunState::PRE) || (v == ShadowMapping_RunState::RENDER)) {
			{
				auto shader = Engine::getShadowMappingShaderRender();
				shader->setProgramMVMatrix(&mvMatrix);
				shader->setProgramMVPMatrix(&mvpMatrix);
				shader->setProgramNormalMatrix(&normalMatrix);
				goto end_switch0;;
			}
		}
		if (((v == ShadowMapping_RunState::PRE) || (v == ShadowMapping_RunState::RENDER) || ((v != ShadowMapping_RunState::PRE) && (v != ShadowMapping_RunState::RENDER)))) {
			{
				_Console::println(wstring(L"ShadowMapping::updateMVPMatrices(): unsupported run state '" + to_wstring(runState)));
				goto end_switch0;;
			}
		}
		end_switch0:;
	}

}

void ShadowMapping::updateDepthBiasMVPMatrix(Matrix4x4* depthBiasMVPMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	this->depthBiasMVPMatrix.set(depthBiasMVPMatrix);
	Engine::getShadowMappingShaderRender()->setProgramDepthBiasMVPMatrix(depthBiasMVPMatrix);
}

void ShadowMapping::updateDepthBiasMVPMatrix()
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	Engine::getShadowMappingShaderRender()->setProgramDepthBiasMVPMatrix(&depthBiasMVPMatrix);
}
