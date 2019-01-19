#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>

#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/subsystems/rendering/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utils/Console.h>

using std::vector;
using std::string;
using std::to_string;

using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::subsystems::rendering::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::Console;

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
	depthBiasMVPMatrix.identity();
	mvMatrix.identity();
	mvpMatrix.identity();
	normalMatrix.identity();
	runState = ShadowMapping_RunState::NONE;
}

ShadowMapping::~ShadowMapping() {
	for (auto i = 0; i < shadowMaps.size(); i++) {
		if (shadowMaps[i] != nullptr) delete shadowMaps[i];
	}
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

void ShadowMapping::createShadowMaps()
{
	runState = ShadowMapping_RunState::PRE;
	// disable color rendering, we only want to write to the Z-Buffer
	renderer->setColorMask(false, false, false, false);
	// render backfaces only, avoid self-shadowing
	renderer->setCullFace(renderer->CULLFACE_FRONT);
	// render to shadow maps
	for (auto i = 0; i < engine->getLightCount(); i++) {
		auto light = engine->getLightAt(i);
		if (light->isEnabled() == true) {
			// create shadow map for light, if required
			if (shadowMaps[i] == nullptr) {
				auto shadowMap = new ShadowMap(this, width, height);
				shadowMap->initialize();
				shadowMaps[i] = shadowMap;
			}
			// render
			Engine::getShadowMappingShaderPre()->useProgram(engine);
			shadowMaps[i]->render(light);
			Engine::getShadowMappingShaderPre()->unUseProgram();
		} else {
			if (shadowMaps[i] != nullptr) {
				// dispose shadow map
				shadowMaps[i]->dispose();
				delete shadowMaps[i];
				shadowMaps[i] = nullptr;
			}
		}
	}
	// restore disable color rendering
	renderer->setColorMask(true, true, true, true);
	// restore render backfaces only
	renderer->setCullFace(renderer->CULLFACE_BACK);
	//
	runState = ShadowMapping_RunState::NONE;
}

void ShadowMapping::renderShadowMaps(const vector<Object3D*>& visibleObjects)
{
	runState = ShadowMapping_RunState::RENDER;
	// render using shadow mapping program
	auto shader = Engine::getShadowMappingShaderRender();
	//	do not allow writing to depth buffer
	renderer->disableDepthBufferWriting();
	//	only process nearest fragments
	renderer->setDepthFunction(renderer->DEPTHFUNCTION_LESSEQUAL);
	// user shader program
	shader->useProgram(engine);
	// render each shadow map
	for (auto i = 0; i < shadowMaps.size(); i++) {
		// skip on unused shadow mapping
		if (shadowMaps[i] == nullptr) continue;

		//
		auto shadowMap = shadowMaps[i];
		auto light = engine->getLightAt(i);
		// set light to render
		shader->setRenderLightId(i);
		// set up light shader uniforms
		shadowMap->updateDepthBiasMVPMatrix();
		// bind shadow map texture on shadow map texture unit
		auto textureUnit = renderer->getTextureUnit();
		renderer->setTextureUnit(ShadowMap::TEXTUREUNIT);
		shadowMap->bindDepthBufferTexture();
		// switch back to texture last unit
		renderer->setTextureUnit(textureUnit);
		// render objects, enable blending
		//	will be disabled after rendering transparent faces
		renderer->enableBlending();
		// 	only opaque face entities as shadows will not be produced on transparent faces
		object3DVBORenderer->render(
			visibleObjects,
			false,
			Object3DVBORenderer::RENDERTYPE_NORMALS |
			Object3DVBORenderer::RENDERTYPE_TEXTUREARRAYS | // TODO: actually this is not required, but GL2 currently needs this
			Object3DVBORenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
			Object3DVBORenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY |
			Object3DVBORenderer::RENDERTYPE_SHADOWMAPPING
		);
		//	disable blending
		renderer->disableBlending();
	}
	// unuse shader program
	shader->unUseProgram();

	// restore texture unit
	auto textureUnit = renderer->getTextureUnit();
	renderer->setTextureUnit(ShadowMap::TEXTUREUNIT);
	renderer->bindTexture(renderer->ID_NONE);
	renderer->setTextureUnit(textureUnit);
	// restore render defaults
	renderer->disableBlending();
	renderer->enableDepthBufferWriting();
	renderer->setDepthFunction(renderer->DEPTHFUNCTION_LESSEQUAL);
	//
	runState = ShadowMapping_RunState::NONE;
}

void ShadowMapping::dispose()
{
	// dispose shadow mappings
	for (auto i = 0; i < shadowMaps.size(); i++) {
		if (shadowMaps[i] != nullptr) {
			shadowMaps[i]->dispose();
			delete shadowMaps[i];
			shadowMaps[i] = nullptr;
		}
	}
}

void ShadowMapping::startObjectTransformations(Matrix4x4& transformationsMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

    // retrieve current model view matrix and put it on stack
	Matrix4x4 tmpMatrix;
	shadowTransformationsMatrix.set(depthBiasMVPMatrix);
	// set up new model view matrix
	tmpMatrix.set(depthBiasMVPMatrix);
	depthBiasMVPMatrix.set(transformationsMatrix).multiply(tmpMatrix);

	//
	updateDepthBiasMVPMatrix();
}

void ShadowMapping::endObjectTransformations()
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;
	// set up new model view matrix
	depthBiasMVPMatrix.set(shadowTransformationsMatrix);
}

void ShadowMapping::updateTextureMatrix(GLRenderer* renderer)
{
	if (runState == ShadowMapping_RunState::NONE) return;

	// upload
	{
		auto v = runState;
		if (v == ShadowMapping_RunState::PRE) {
			{
				Engine::getShadowMappingShaderPre()->updateTextureMatrix(renderer);
				goto end_switch0;
			}
		} else
		if (v == ShadowMapping_RunState::RENDER) {
			{
				Engine::getShadowMappingShaderRender()->updateTextureMatrix(renderer);
				goto end_switch0;
			}
		} else {
			{
				Console::println(string("ShadowMapping::updateTextureMatrix(): unsupported run state '" + to_string(runState)));
				goto end_switch0;;
			}
		}
		end_switch0:;
	}
}

void ShadowMapping::updateMatrices(GLRenderer* renderer)
{
	if (runState == ShadowMapping_RunState::NONE) return;

	// model view matrix
	mvMatrix.set(renderer->getModelViewMatrix());
	// object to screen matrix
	mvpMatrix.set(mvMatrix).multiply(renderer->getProjectionMatrix());
	// normal matrix
	normalMatrix.set(mvMatrix).invert().transpose();
	// upload
	{
		auto v = runState;
		if (v == ShadowMapping_RunState::PRE) {
			{
				Engine::getShadowMappingShaderPre()->updateMatrices(mvpMatrix);
				goto end_switch0;;
			}
		} else
		if (v == ShadowMapping_RunState::RENDER) {
			{
				auto shader = Engine::getShadowMappingShaderRender();
				shader->setProgramMVMatrix(mvMatrix);
				shader->setProgramMVPMatrix(mvpMatrix);
				shader->setProgramNormalMatrix(normalMatrix);
				goto end_switch0;;
			}
		} else {
			{
				Console::println(string("ShadowMapping::updateMatrices(): unsupported run state '" + to_string(runState)));
				goto end_switch0;;
			}
		}
		end_switch0:;
	}
}

void ShadowMapping::updateMaterial(GLRenderer* renderer) {
	if (runState == ShadowMapping_RunState::NONE)
		return;
	{
		auto v = runState;
		if (v == ShadowMapping_RunState::PRE) {
			{
				Engine::getShadowMappingShaderPre()->updateMaterial(renderer);
				goto end_switch0;;
			}
		} else
		if (v == ShadowMapping_RunState::RENDER) {
			{
				Engine::getShadowMappingShaderRender()->updateMaterial(renderer);
				goto end_switch0;;
			}
		}
		end_switch0:;
	}
}

void ShadowMapping::updateLight(GLRenderer* renderer, int32_t lightId) {
	if (runState == ShadowMapping_RunState::RENDER) {
		Engine::getShadowMappingShaderRender()->updateLight(renderer, lightId);
	}
}

void ShadowMapping::bindTexture(GLRenderer* renderer, int32_t textureId) {
	if (runState == ShadowMapping_RunState::NONE)
		return;
	{
		auto v = runState;
		if (v == ShadowMapping_RunState::PRE) {
			{
				Engine::getShadowMappingShaderPre()->bindTexture(renderer, textureId);
				goto end_switch0;;
			}
		} else
		if (v == ShadowMapping_RunState::RENDER) {
			{
				Engine::getShadowMappingShaderRender()->bindTexture(renderer, textureId);
				goto end_switch0;;
			}
		}
		end_switch0:;
	}
}

void ShadowMapping::updateDepthBiasMVPMatrix(Matrix4x4& depthBiasMVPMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;
	// copy matrix
	this->depthBiasMVPMatrix.set(depthBiasMVPMatrix);
	// upload
	Engine::getShadowMappingShaderRender()->setProgramDepthBiasMVPMatrix(depthBiasMVPMatrix);
}

void ShadowMapping::updateDepthBiasMVPMatrix()
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	// upload
	Engine::getShadowMappingShaderRender()->setProgramDepthBiasMVPMatrix(depthBiasMVPMatrix);
}

void ShadowMapping::setShader(const string& id) {
	{
		if (runState == ShadowMapping_RunState::NONE) {
			// no op
		} else
		if (runState == ShadowMapping_RunState::PRE) {
			Engine::getShadowMappingShaderPre()->setShader(id);
		} else
		if (runState == ShadowMapping_RunState::RENDER) {
			Engine::getShadowMappingShaderRender()->setShader(id);
		} else {
			Console::println(string("ShadowMapping::setShader(): unsupported run state '" + to_string(runState)));
		}
	}
}
