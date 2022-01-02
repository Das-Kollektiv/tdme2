#include <tdme/engine/subsystems/earlyzrejection/EZRShader.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/StringTools.h>

using tdme::engine::subsystems::earlyzrejection::EZRShader;

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::subsystems::earlyzrejection::EZRShaderBaseImplementation;
using tdme::engine::subsystems::earlyzrejection::EZRShaderDefaultImplementation;
using tdme::engine::subsystems::earlyzrejection::EZRShaderImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;
using tdme::utilities::Console;
using tdme::utilities::StringTools;

EZRShader::EZRShader(Renderer* renderer): renderer(renderer)
{
	if (EZRShaderDefaultImplementation::isSupported(renderer) == true) { auto shaderProgram = new EZRShaderDefaultImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	auto threadCount = renderer->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
}

EZRShader::~EZRShader() {
	for (auto shaderIt: shader) {
		delete shaderIt.second;
	}
}

bool EZRShader::isInitialized()
{
	bool initialized = true;
	for (auto shaderIt: shader) {
		initialized&= shaderIt.second->isInitialized();
	}
	return initialized;
}

void EZRShader::initialize()
{
	for (auto shaderIt: shader) {
		shaderIt.second->initialize();
	}
}

void EZRShader::useProgram(Engine* engine)
{
	running = true;
	this->engine = engine;
}

void EZRShader::unUseProgram()
{
	running = false;
	auto i = 0;
	for (auto& ezrShaderContext: contexts) {
		if (ezrShaderContext.implementation != nullptr) {
			ezrShaderContext.implementation->unUseProgram(i);
		}
		ezrShaderContext.implementation = nullptr;
		i++;
	}
	engine = nullptr;
}

void EZRShader::updateMatrices(int contextIdx)
{
	auto& ezrShaderContext = contexts[contextIdx];
	if (ezrShaderContext.implementation == nullptr) return;
	ezrShaderContext.implementation->updateMatrices(renderer, contextIdx);
}

void EZRShader::updateTextureMatrix(int contextIdx) {
	auto& ezrShaderContext = contexts[contextIdx];
	if (ezrShaderContext.implementation == nullptr) return;
	ezrShaderContext.implementation->updateTextureMatrix(renderer, contextIdx);
}

void EZRShader::updateMaterial(int contextIdx)
{
	auto& ezrShaderContext = contexts[contextIdx];
	if (ezrShaderContext.implementation == nullptr) return;
	ezrShaderContext.implementation->updateMaterial(renderer, contextIdx);
}

void EZRShader::bindTexture(int contextIdx, int32_t textureId)
{
	auto& ezrShaderContext = contexts[contextIdx];
	if (ezrShaderContext.implementation == nullptr) return;
	ezrShaderContext.implementation->bindTexture(renderer, contextIdx, textureId);
}

void EZRShader::updateShaderParameters(int contextIdx) {
	auto& ezrShaderContext = contexts[contextIdx];
	if (ezrShaderContext.implementation == nullptr) return;
	ezrShaderContext.implementation->updateShaderParameters(renderer, contextIdx);
}

void EZRShader::setShader(int contextIdx, const string& id) {
	if (running == false) return;

	// TODO: find a better solution for removing PBR- lighing prefix
	string shaderId;
	if (StringTools::startsWith(id, string("pbr-")) == true) {
		shaderId = StringTools::substring(id, 4);
	} else {
		shaderId = id;
	}

	//
	auto& ezrShaderContext = contexts[contextIdx];
	auto currentImplementation = ezrShaderContext.implementation;
	auto shaderIt = shader.find(shaderId);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	auto nextImplementation = shaderIt->second;
	if (currentImplementation != nextImplementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram(contextIdx);
		ezrShaderContext.implementation = nextImplementation;
		ezrShaderContext.implementation->useProgram(engine, contextIdx);
	}
}
