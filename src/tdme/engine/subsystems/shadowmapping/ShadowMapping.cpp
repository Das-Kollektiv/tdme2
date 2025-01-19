#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
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

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using tdme::engine::subsystems::renderer::RendererBackend;
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

ShadowMapping::ShadowMapping(Engine* engine, RendererBackend* rendererBackend, EntityRenderer* entityRenderer)
{
	this->engine = engine;
	this->rendererBackend = rendererBackend;
	this->entityRenderer = entityRenderer;
	shadowMaps.resize(engine->getLightCount());
	depthBiasMVPMatrix.identity();
	runState = ShadowMapping_RunState::NONE;
}

ShadowMapping::~ShadowMapping() {
}

void ShadowMapping::reshape(int32_t width, int32_t height)
{
}

void ShadowMapping::createShadowMaps()
{
	runState = ShadowMapping_RunState::CREATE;
	// disable color rendering, we only want to write to the Z-Buffer
	rendererBackend->setColorMask(false, false, false, false);
	// render backfaces only, avoid self-shadowing
	rendererBackend->setCullFace(rendererBackend->CULLFACE_FRONT);
	// render to shadow maps
	for (auto i = 0; i < engine->getLightCount(); i++) {
		auto light = engine->getLightAt(i);
		if (light->isEnabled() == true &&
			light->getSpotDirection().computeLengthSquared() > Math::square(Math::EPSILON)) {
			// create shadow map for light, if required
			if (shadowMaps[i] == nullptr) {
				shadowMaps[i] = make_unique<ShadowMap>(this, Engine::getShadowMapWidth(), Engine::getShadowMapHeight());
				shadowMaps[i]->initialize();
			}
			// render
			Engine::getShadowMapCreationShader()->useProgram(engine);
			shadowMaps[i]->createShadowMap(light);
			Engine::getShadowMapCreationShader()->unUseProgram();
		} else {
			if (shadowMaps[i] != nullptr) {
				// dispose shadow map
				shadowMaps[i]->dispose();
				shadowMaps[i] = nullptr;
			}
		}
	}
	// restore disable color rendering
	rendererBackend->setColorMask(true, true, true, true);
	// restore render backfaces only
	rendererBackend->setCullFace(rendererBackend->CULLFACE_BACK);
	//
	runState = ShadowMapping_RunState::NONE;
}

void ShadowMapping::renderShadowMaps(const vector<Object*>& visibleObjects)
{
	// only render for objects that receives shadows
	for (auto object: visibleObjects) {
		if (object->isReceivesShadows() == false) continue;
		visibleObjectsReceivingShadows.push_back(object);
	}

	//
	auto contextCount = rendererBackend->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	//
	runState = ShadowMapping_RunState::RENDER;
	// render using shadow mapping program
	auto shader = Engine::getShadowMapRenderShader();
	//	do not allow writing to depth buffer
	rendererBackend->disableDepthBufferWriting();
	// user shader program
	shader->useProgram(engine);
	// render each shadow map
	rendererBackend->enableBlending();

	for (auto i = 0; i < shadowMaps.size(); i++) {
		// skip on unused shadow mapping
		if (shadowMaps[i] == nullptr) continue;

		//
		auto shadowMap = shadowMaps[i].get();
		// set light to render
		shader->setRenderLightId(i);

		// setup depth textures to contexts
		for (auto j = 0; j < contextCount; j++) {
			// use default context
			auto contextIdx = j;
			// set up light shader uniforms
			shadowMap->updateDepthBiasMVPMatrix(contextIdx);
			//
			// bind shadow map texture on shadow map texture unit
			auto textureUnit = rendererBackend->getTextureUnit(contextIdx);
			rendererBackend->setTextureUnit(contextIdx, ShadowMap::TEXTUREUNIT);
			shadowMap->bindDepthBufferTexture(contextIdx);
			// switch back to texture last unit
			rendererBackend->setTextureUnit(contextIdx, textureUnit);
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
	rendererBackend->disableBlending();

	// unuse shader program
	shader->unUseProgram();

	// restore depth textures of contexts
	for (auto j = 0; j < contextCount; j++) {
		// use default context
		auto contextIdx = j;
		auto textureUnit = rendererBackend->getTextureUnit(contextIdx);
		rendererBackend->setTextureUnit(contextIdx, ShadowMap::TEXTUREUNIT);
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		rendererBackend->setTextureUnit(contextIdx, textureUnit);
	}

	// restore render defaults
	rendererBackend->disableBlending();
	rendererBackend->enableDepthBufferWriting();

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
			shadowMaps[i] = nullptr;
		}
	}
}

void ShadowMapping::startObjectTransform(int contextIdx, Matrix4x4& transformMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

    // retrieve current model view matrix and put it on stack
	Matrix4x4 tmpMatrix;
	shadowTransformMatrix.set(depthBiasMVPMatrix);
	// set up new model view matrix
	tmpMatrix.set(depthBiasMVPMatrix);
	depthBiasMVPMatrix.set(transformMatrix).multiply(tmpMatrix);

	//
	updateDepthBiasMVPMatrix(contextIdx);
}

void ShadowMapping::endObjectTransform()
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;
	// set up new model view matrix
	depthBiasMVPMatrix.set(shadowTransformMatrix);
}

void ShadowMapping::updateTextureMatrix(int contextIdx)
{
	if (runState == ShadowMapping_RunState::NONE) return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->updateTextureMatrix(contextIdx);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->updateTextureMatrix(contextIdx);
			break;
		default:
			Console::printLine(string("ShadowMapping::updateTextureMatrix(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateMatrices(int contextIdx)
{
	if (runState == ShadowMapping_RunState::NONE) return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->updateMatrices(contextIdx);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->updateMatrices(contextIdx);
			break;
		default:
			Console::printLine(string("ShadowMapping::updateMatrices(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateMaterial(int contextIdx) {
	if (runState == ShadowMapping_RunState::NONE)
		return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->updateMaterial(contextIdx);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->updateMaterial(contextIdx);
			break;
		default:
			Console::printLine(string("ShadowMapping::updateMaterial(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateLight(int contextIdx, int32_t lightId) {
	if (runState == ShadowMapping_RunState::RENDER) {
		Engine::getShadowMapRenderShader()->updateLight(contextIdx, lightId);
	}
}

void ShadowMapping::bindTexture(int contextIdx, int32_t textureId) {
	if (runState == ShadowMapping_RunState::NONE)
		return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->bindTexture(contextIdx, textureId);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->bindTexture(contextIdx, textureId);
			break;
		default:
			Console::printLine(string("ShadowMapping::bindTexture(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateDepthBiasMVPMatrix(int contextIdx, Matrix4x4& depthBiasMVPMatrix)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	// copy matrix
	this->depthBiasMVPMatrix.set(depthBiasMVPMatrix);
	// upload
	Engine::getShadowMapRenderShader()->setDepthBiasMVPMatrix(contextIdx, depthBiasMVPMatrix);
}

void ShadowMapping::updateDepthBiasMVPMatrix(int contextIdx)
{
	if (runState != ShadowMapping_RunState::RENDER)
		return;

	// upload
	Engine::getShadowMapRenderShader()->setDepthBiasMVPMatrix(contextIdx, depthBiasMVPMatrix);
}

void ShadowMapping::setShader(int contextIdx, const string& id) {
	if (runState == ShadowMapping_RunState::NONE)
		return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->setShader(contextIdx, id);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->setShader(contextIdx, id);
			break;
		default:
			Console::printLine(string("ShadowMapping::setShader(): unsupported run state '" + to_string(runState)));
	}
}

void ShadowMapping::updateShaderParameters(int contextIdx) {
	if (runState == ShadowMapping_RunState::NONE)
		return;

	//
	switch(runState) {
		case ShadowMapping_RunState::CREATE:
			Engine::getShadowMapCreationShader()->updateShaderParameters(contextIdx);
			break;
		case ShadowMapping_RunState::RENDER:
			Engine::getShadowMapRenderShader()->updateShaderParameters(contextIdx);
			break;
		default:
			Console::printLine(string("ShadowMapping::updateShaderParameters(): unsupported run state '" + to_string(runState)));
	}
}

