#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>

#include <string>
#include <vector>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShader.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShader.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShader;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Console;

ShadowMapping::ShadowMapping(Engine* engine, Renderer* renderer, EntityRenderer* entityRenderer)
{
	this->engine = engine;
	this->renderer = renderer;
	this->entityRenderer = entityRenderer;
	shadowMaps.resize(engine->getLightCount());
	for (auto i = 0; i < shadowMaps.size(); i++) {
		shadowMaps[i] = nullptr;
	}
	depthBiasMVPMatrix.identity();
	runState = ShadowMapping_RunState::NONE;
}

ShadowMapping::~ShadowMapping() {
	for (auto i = 0; i < shadowMaps.size(); i++) {
		if (shadowMaps[i] != nullptr) delete shadowMaps[i];
	}
}

Engine* ShadowMapping::getEngine()
{
	return engine;
}

void ShadowMapping::reshape(int32_t width, int32_t height)
{
}

void ShadowMapping::createShadowMaps()
{
	runState = ShadowMapping_RunState::CREATE;
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
				auto shadowMap = new ShadowMap(this, Engine::getShadowMapWidth(), Engine::getShadowMapHeight());
				shadowMap->initialize();
				shadowMaps[i] = shadowMap;
			}
			// render
			Engine::getShadowMapCreationShader()->useProgram(engine);
			shadowMaps[i]->createShadowMap(light);
			Engine::getShadowMapCreationShader()->unUseProgram();
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

ShadowMap* ShadowMapping::getShadowMap(int idx) {
	return shadowMaps[idx];
}

void ShadowMapping::renderShadowMaps(const vector<Object3D*>& visibleObjects)
{
	// only render for objects that receives shadows
	for (auto object: visibleObjects) {
		if (object->isReceivesShadows() == false) continue;
		visibleObjectsReceivingShadows.push_back(object);
	}

	//
	auto contextCount = renderer->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	//
	runState = ShadowMapping_RunState::RENDER;
	// render using shadow mapping program
	auto shader = Engine::getShadowMapRenderShader();
	//	do not allow writing to depth buffer
	renderer->disableDepthBufferWriting();
	// user shader program
	shader->useProgram(engine);
	// render each shadow map
	renderer->enableBlending();

	for (auto i = 0; i < shadowMaps.size(); i++) {
		// skip on unused shadow mapping
		if (shadowMaps[i] == nullptr) continue;

		//
		auto shadowMap = shadowMaps[i];
		// set light to render
		shader->setRenderLightId(i);

		// setup depth textures to contexts
		for (auto j = 0; j < contextCount; j++) {
			// use default context
			auto context = renderer->getContext(j);
			// set up light shader uniforms
			shadowMap->updateDepthBiasMVPMatrix(context);
			//
			// bind shadow map texture on shadow map texture unit
			auto textureUnit = renderer->getTextureUnit(context);
			renderer->setTextureUnit(context, ShadowMap::TEXTUREUNIT);
			shadowMap->bindDepthBufferTexture(context);
			// switch back to texture last unit
			renderer->setTextureUnit(context, textureUnit);
		}

		// 	only opaque face entities as shadows will not be produced on transparent faces
		for (auto i = 0; i < Entity::RENDERPASS_MAX; i++) {
			auto renderPass = static_cast<Entity::RenderPass>(Math::pow(2, i));
			entityRenderer->render(
				renderPass,
				visibleObjectsReceivingShadows,
				false,
				EntityRenderer::RENDERTYPE_NORMALS |
				EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
				EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY |
				EntityRenderer::RENDERTYPE_SHADOWMAPPING
			);
		}
	}

	//
	renderer->disableBlending();

	// unuse shader program
	shader->unUseProgram();

	// restore depth textures of contexts
	for (auto j = 0; j < contextCount; j++) {
		// use default context
		auto context = renderer->getContext(j);
		auto textureUnit = renderer->getTextureUnit(context);
		renderer->setTextureUnit(context, ShadowMap::TEXTUREUNIT);
		renderer->bindTexture(context, renderer->ID_NONE);
		renderer->setTextureUnit(context, textureUnit);
	}

	// restore render defaults
	renderer->disableBlending();
	renderer->enableDepthBufferWriting();

	//
	visibleObjectsReceivingShadows.clear();

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

void ShadowMapping::startObjectTransformations(void* context, Matrix4x4& transformationsMatrix)
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
	updateDepthBiasMVPMatrix(context);
}

void ShadowMapping::endObjectTransformations()
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;
	// set up new model view matrix
	depthBiasMVPMatrix.set(shadowTransformationsMatrix);
}

void ShadowMapping::updateTextureMatrix(void* context)
{
	if (runState == ShadowMapping_RunState::NONE) return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->updateTextureMatrix(context);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->updateTextureMatrix(context);
			break;
		default:
			Console::println(string("ShadowMapping::updateTextureMatrix(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateMatrices(void* context)
{
	if (runState == ShadowMapping_RunState::NONE) return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->updateMatrices(context);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->updateMatrices(context);
			break;
		default:
			Console::println(string("ShadowMapping::updateMatrices(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateMaterial(void* context) {
	if (runState == ShadowMapping_RunState::NONE)
		return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->updateMaterial(context);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->updateMaterial(context);
			break;
		default:
			Console::println(string("ShadowMapping::updateMaterial(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateLight(void* context, int32_t lightId) {
	if (runState == ShadowMapping_RunState::RENDER) {
		Engine::getShadowMapRenderShader()->updateLight(context, lightId);
	}
}

void ShadowMapping::bindTexture(void* context, int32_t textureId) {
	if (runState == ShadowMapping_RunState::NONE)
		return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->bindTexture(context, textureId);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->bindTexture(context, textureId);
			break;
		default:
			Console::println(string("ShadowMapping::bindTexture(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateDepthBiasMVPMatrix(void* context, Matrix4x4& depthBiasMVPMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	// copy matrix
	this->depthBiasMVPMatrix.set(depthBiasMVPMatrix);
	// upload
	Engine::getShadowMapRenderShader()->setDepthBiasMVPMatrix(context, depthBiasMVPMatrix);
}

void ShadowMapping::updateDepthBiasMVPMatrix(void* context)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	// upload
	Engine::getShadowMapRenderShader()->setDepthBiasMVPMatrix(context, depthBiasMVPMatrix);
}

void ShadowMapping::setShader(void* context, const string& id) {
	if (runState == ShadowMapping_RunState::NONE)
		return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->setShader(context, id);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->setShader(context, id);
			break;
		default:
			Console::println(string("ShadowMapping::setShader(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateShaderParameters(void* context) {
	if (runState == ShadowMapping_RunState::NONE)
		return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->updateShaderParameters(context);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->updateShaderParameters(context);
			break;
		default:
			Console::println(string("ShadowMapping::updateShaderParameters(): unsupported run state '" + to_string(runState)));
	}
}

