#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShader.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderFoliageImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderTreeImplementation.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderBaseImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderDefaultImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderFoliageImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderTreeImplementation;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;
using tdme::utilities::StringTools;

ShadowMapCreationShader::ShadowMapCreationShader(Renderer* renderer): renderer(renderer)
{
	if (ShadowMapCreationShaderDefaultImplementation::isSupported(renderer) == true) shader["default"] = new ShadowMapCreationShaderDefaultImplementation(renderer);
	if (ShadowMapCreationShaderFoliageImplementation::isSupported(renderer) == true) shader["foliage"] = new ShadowMapCreationShaderFoliageImplementation(renderer);
	if (ShadowMapCreationShaderTreeImplementation::isSupported(renderer) == true) shader["tree"] = new ShadowMapCreationShaderTreeImplementation(renderer);
	auto threadCount = renderer->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
}

ShadowMapCreationShader::~ShadowMapCreationShader() {
	for (auto shaderIt: shader) {
		delete shaderIt.second;
	}
}

bool ShadowMapCreationShader::isInitialized()
{
	bool initialized = true;
	for (auto shaderIt: shader) {
		initialized&= shaderIt.second->isInitialized();
	}
	return initialized;
}

void ShadowMapCreationShader::initialize()
{
	for (auto shaderIt: shader) {
		shaderIt.second->initialize();
	}
}

void ShadowMapCreationShader::useProgram(Engine* engine)
{
	running = true;
	this->engine = engine;
}

void ShadowMapCreationShader::unUseProgram()
{
	running = false;
	auto i = 0;
	for (auto& shadowMappingShaderPreContext: contexts) {
		if (shadowMappingShaderPreContext.implementation != nullptr) {
			shadowMappingShaderPreContext.implementation->unUseProgram(i);
		}
		shadowMappingShaderPreContext.implementation = nullptr;
		i++;
	}
	engine = nullptr;
}

void ShadowMapCreationShader::updateMatrices(int contextIdx)
{
	auto& shadowMappingShaderPreContext = contexts[contextIdx];
	if (shadowMappingShaderPreContext.implementation == nullptr) return;
	shadowMappingShaderPreContext.implementation->updateMatrices(contextIdx);
}

void ShadowMapCreationShader::updateTextureMatrix(int contextIdx) {
	auto& shadowMappingShaderPreContext = contexts[contextIdx];
	if (shadowMappingShaderPreContext.implementation == nullptr) return;
	shadowMappingShaderPreContext.implementation->updateTextureMatrix(renderer, contextIdx);
}

void ShadowMapCreationShader::updateMaterial(int contextIdx)
{
	auto& shadowMappingShaderPreContext = contexts[contextIdx];
	if (shadowMappingShaderPreContext.implementation == nullptr) return;
	shadowMappingShaderPreContext.implementation->updateMaterial(renderer, contextIdx);
}

void ShadowMapCreationShader::updateShaderParameters(int contextIdx) {
	auto& shadowMappingShaderPreContext = contexts[contextIdx];
	if (shadowMappingShaderPreContext.implementation == nullptr) return;
	shadowMappingShaderPreContext.implementation->updateShaderParameters(renderer, contextIdx);
}

void ShadowMapCreationShader::bindTexture(int contextIdx, int32_t textureId)
{
	auto& shadowMappingShaderPreContext = contexts[contextIdx];
	if (shadowMappingShaderPreContext.implementation == nullptr) return;
	shadowMappingShaderPreContext.implementation->bindTexture(renderer, contextIdx, textureId);
}

void ShadowMapCreationShader::setShader(int contextIdx, const string& id) {
	// TODO: find a better solution for removing PBR- lighing prefix
	string shaderId;
	if (StringTools::startsWith(id, string("pbr-")) == true) {
		shaderId = StringTools::substring(id, 4);
	} else {
		shaderId = id;
	}

	//
	auto& shadowMappingShaderPreContext = contexts[contextIdx];
	auto currentImplementation = shadowMappingShaderPreContext.implementation;
	auto shaderIt = shader.find(shaderId);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	auto nextImplementation = shaderIt->second;
	if (currentImplementation != nextImplementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram(contextIdx);
		shadowMappingShaderPreContext.implementation = nextImplementation;
		shadowMappingShaderPreContext.implementation->useProgram(engine, contextIdx);
	}
}

void ShadowMapCreationShader::loadTextures(const string& pathName) {
	for (auto shaderIt: shader) {
		shaderIt.second->loadTextures(pathName);
	}
}
