#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBlurImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderDesaturationImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderLightScatteringImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOMapImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderVignetteImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>

using std::string;
using std::unordered_map;

using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderBlurImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderDefaultImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderDesaturationImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderLightScatteringImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOMapImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderVignetteImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

PostProcessingShader::PostProcessingShader(Renderer* renderer)
{
	if (PostProcessingShaderBlurImplementation::isSupported(renderer) == true) shader["depth_blur"] = new PostProcessingShaderBlurImplementation(renderer);
	if (PostProcessingShaderDefaultImplementation::isSupported(renderer) == true) shader["default"] = new PostProcessingShaderDefaultImplementation(renderer);
	if (PostProcessingShaderDesaturationImplementation::isSupported(renderer) == true) shader["desaturation"] = new PostProcessingShaderDesaturationImplementation(renderer);
	if (PostProcessingShaderLightScatteringImplementation::isSupported(renderer) == true) shader["light_scattering"] = new PostProcessingShaderLightScatteringImplementation(renderer);
	if (PostProcessingShaderSSAOMapImplementation::isSupported(renderer) == true) shader["ssao_map"] = new PostProcessingShaderSSAOMapImplementation(renderer);
	if (PostProcessingShaderSSAOImplementation::isSupported(renderer) == true) shader["ssao"] = new PostProcessingShaderSSAOImplementation(renderer);
	if (PostProcessingShaderVignetteImplementation::isSupported(renderer) == true) shader["vignette"] = new PostProcessingShaderVignetteImplementation(renderer);
	implementation = nullptr;
}

PostProcessingShader::~PostProcessingShader()
{
	for (auto shaderIt: shader) {
		delete shaderIt.second;
	}
}

bool PostProcessingShader::isInitialized()
{
	auto initialized = true;
	for (auto shaderIt: shader) {
		initialized&= shaderIt.second->isInitialized();
	}
	return initialized;
}

void PostProcessingShader::initialize()
{
	for (auto shaderIt: shader) {
		shaderIt.second->initialize();
	}
}

void PostProcessingShader::useProgram()
{
	running = true;
}

void PostProcessingShader::unUseProgram()
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram();;
	}
	implementation = nullptr;
}

bool PostProcessingShader::hasShader(const string& id) {
	return shader.find(id) != shader.end();
}

void PostProcessingShader::setShader(int contextIdx, const string& id) {
	if (running == false) return;

	auto currentImplementation = implementation;
	auto shaderIt = shader.find(id);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	implementation = shaderIt->second;

	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram();
		implementation->useProgram(contextIdx);
	}
}

void PostProcessingShader::setBufferPixelWidth(int contextIdx, float pixelWidth) {
	if (implementation == nullptr) return;
	implementation->setBufferPixelWidth(contextIdx, pixelWidth);
}

void PostProcessingShader::setBufferPixelHeight(int contextIdx, float pixelHeight) {
	if (implementation == nullptr) return;
	implementation->setBufferPixelHeight(contextIdx, pixelHeight);
}

void PostProcessingShader::setShaderParameters(int contextIdx, Engine* engine) {
	if (implementation == nullptr) return;
	implementation->setShaderParameters(contextIdx, engine);
}

void PostProcessingShader::loadTextures(const string& pathName) {
	for (auto shaderIt: shader) {
		shaderIt.second->loadTextures(pathName);
	}
}
