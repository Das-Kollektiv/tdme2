#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShader.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderFoliageImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderTreeImplementation.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderDefaultImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderFoliageImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderTreeImplementation;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Matrix4x4;
using tdme::utilities::StringTools;

ShadowMapRenderShader::ShadowMapRenderShader(RendererBackend* rendererBackend): rendererBackend(rendererBackend)
{
	if (ShadowMapRenderShaderDefaultImplementation::isSupported(rendererBackend) == true) shaders["default"] = new ShadowMapRenderShaderDefaultImplementation(rendererBackend);
	if (ShadowMapRenderShaderFoliageImplementation::isSupported(rendererBackend) == true) shaders["foliage"] = new ShadowMapRenderShaderFoliageImplementation(rendererBackend);
	if (ShadowMapRenderShaderTreeImplementation::isSupported(rendererBackend) == true) shaders["tree"] = new ShadowMapRenderShaderTreeImplementation(rendererBackend);
	auto threadCount = rendererBackend->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
}

ShadowMapRenderShader::~ShadowMapRenderShader()
{
	for (const auto& [shaderId, shader]: shaders) {
		shader->unloadTextures();
		delete shader;
	}
}

bool ShadowMapRenderShader::isInitialized()
{
	bool initialized = true;
	for (const auto& [shaderId, shader]: shaders) {
		initialized&= shader->isInitialized();
	}
	return initialized;
}

void ShadowMapRenderShader::initialize()
{
	for (const auto& [shaderId, shader]: shaders) {
		shader->initialize();
	}
}

void ShadowMapRenderShader::useProgram(Engine* engine)
{
	running = true;
	this->engine = engine;
}

void ShadowMapRenderShader::unUseProgram()
{
	running = false;
	auto i = 0;
	for (auto& shadowMappingShaderRenderContext: contexts) {
		if (shadowMappingShaderRenderContext.implementation != nullptr) {
			shadowMappingShaderRenderContext.implementation->unUseProgram(i);
		}
		shadowMappingShaderRenderContext.implementation = nullptr;
		i++;
	}
	engine = nullptr;
}

void ShadowMapRenderShader::updateMatrices(int contextIdx)
{
	auto& shadowMappingShaderRenderContext = contexts[contextIdx];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->updateMatrices(contextIdx);
}

void ShadowMapRenderShader::updateTextureMatrix(int contextIdx) {
	auto& shadowMappingShaderRenderContext = contexts[contextIdx];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->updateTextureMatrix(rendererBackend, contextIdx);
}

void ShadowMapRenderShader::updateMaterial(int contextIdx)
{
	auto& shadowMappingShaderRenderContext = contexts[contextIdx];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->updateMaterial(rendererBackend, contextIdx);
}

void ShadowMapRenderShader::updateLight(int contextIdx, int32_t lightId) {
	auto& shadowMappingShaderRenderContext = contexts[contextIdx];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->updateLight(rendererBackend, contextIdx, lightId);
}

void ShadowMapRenderShader::updateShaderParameters(int contextIdx) {
	auto& shadowMappingShaderRenderContext = contexts[contextIdx];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->updateShaderParameters(rendererBackend, contextIdx);
}

void ShadowMapRenderShader::bindTexture(int contextIdx, int32_t textureId)
{
	auto& shadowMappingShaderRenderContext = contexts[contextIdx];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->bindTexture(rendererBackend, contextIdx, textureId);
}

void ShadowMapRenderShader::setDepthBiasMVPMatrix(int contextIdx, const Matrix4x4& depthBiasMVPMatrix)
{
	this->depthBiasMVPMatrix = depthBiasMVPMatrix;
	auto& shadowMappingShaderRenderContext = contexts[contextIdx];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->setDepthBiasMVPMatrix(contextIdx, this->depthBiasMVPMatrix);
}

void ShadowMapRenderShader::setRenderLightId(int32_t lightId) {
	this->lightId = lightId;
}

void ShadowMapRenderShader::setShader(int contextIdx, const string& id) {
	// TODO: find a better solution for removing PBR- lighing prefix
	string shaderId;
	if (StringTools::startsWith(id, string("pbr-")) == true) {
		shaderId = StringTools::substring(id, 4);
	} else {
		shaderId = id;
	}

	//
	auto& shadowMappingShaderRenderContext = contexts[contextIdx];
	auto currentImplementation = shadowMappingShaderRenderContext.implementation;
	auto shaderIt = shaders.find(shaderId);
	if (shaderIt == shaders.end()) {
		shaderIt = shaders.find("default");
	}
	auto nextImplementation = shaderIt->second;
	if (currentImplementation != nextImplementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram(contextIdx);
		shadowMappingShaderRenderContext.implementation = nextImplementation;
		shadowMappingShaderRenderContext.implementation->useProgram(engine, contextIdx);
	}

	shadowMappingShaderRenderContext.implementation->setDepthBiasMVPMatrix(contextIdx, depthBiasMVPMatrix);
	shadowMappingShaderRenderContext.implementation->setRenderLightId(lightId);
}

void ShadowMapRenderShader::loadTextures(const string& pathName) {
	for (const auto& [shaderId, shader]: shaders) {
		shader->unloadTextures();
		shader->loadTextures(pathName);
	}
}
