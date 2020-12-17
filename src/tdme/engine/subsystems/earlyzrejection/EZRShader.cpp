#include <tdme/engine/subsystems/earlyzrejection/EZRShader.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderImplementation.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::earlyzrejection::EZRShader;

using tdme::engine::Engine;
using tdme::engine::subsystems::earlyzrejection::EZRShaderBaseImplementation;
using tdme::engine::subsystems::earlyzrejection::EZRShaderDefaultImplementation;
using tdme::engine::subsystems::earlyzrejection::EZRShaderImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::utilities::Console;

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
	for (auto& ezrShaderPreContext: contexts) {
		if (ezrShaderPreContext.implementation != nullptr) {
			ezrShaderPreContext.implementation->unUseProgram(renderer->getContext(i));
		}
		ezrShaderPreContext.implementation = nullptr;
		i++;
	}
	engine = nullptr;
}

void EZRShader::updateMatrices(void* context)
{
	auto& ezrShaderPreContext = contexts[renderer->getContextIndex(context)];
	if (ezrShaderPreContext.implementation == nullptr) return;
	ezrShaderPreContext.implementation->updateMatrices(renderer, context);
}

void EZRShader::updateTextureMatrix(void* context) {
	auto& ezrShaderPreContext = contexts[renderer->getContextIndex(context)];
	if (ezrShaderPreContext.implementation == nullptr) return;
	ezrShaderPreContext.implementation->updateTextureMatrix(renderer, context);
}

void EZRShader::updateMaterial(void* context)
{
	auto& ezrShaderPreContext = contexts[renderer->getContextIndex(context)];
	if (ezrShaderPreContext.implementation == nullptr) return;
	ezrShaderPreContext.implementation->updateMaterial(renderer, context);
}

void EZRShader::bindTexture(void* context, int32_t textureId)
{
	auto& ezrShaderPreContext = contexts[renderer->getContextIndex(context)];
	if (ezrShaderPreContext.implementation == nullptr) return;
	ezrShaderPreContext.implementation->bindTexture(renderer, context, textureId);
}

void EZRShader::setShader(void* context, const string& id) {
	if (running == false) return;

	auto& ezrShaderPreContext = contexts[renderer->getContextIndex(context)];
	auto currentImplementation = ezrShaderPreContext.implementation;

	auto shaderIt = shader.find(id);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	ezrShaderPreContext.implementation = shaderIt->second;

	if (currentImplementation != ezrShaderPreContext.implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram(context);
		ezrShaderPreContext.implementation->useProgram(engine, context);
	}
}
