#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBlurImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOMapImplementation.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderBlurImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderDefaultImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOMapImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::Engine;

PostProcessingShader::PostProcessingShader(GLRenderer* renderer)
{
	if (PostProcessingShaderBlurImplementation::isSupported(renderer) == true) shader["depth_blur"] = new PostProcessingShaderBlurImplementation(renderer);
	if (PostProcessingShaderDefaultImplementation::isSupported(renderer) == true) shader["default"] = new PostProcessingShaderDefaultImplementation(renderer);
	if (PostProcessingShaderSSAOMapImplementation::isSupported(renderer) == true) shader["ssao_map"] = new PostProcessingShaderSSAOMapImplementation(renderer);
	if (PostProcessingShaderSSAOImplementation::isSupported(renderer) == true) shader["ssao"] = new PostProcessingShaderSSAOImplementation(renderer);
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

void PostProcessingShader::setShader(const string& id) {
	if (running == false) return;

	auto currentImplementation = implementation;
	auto shaderIt = shader.find(id);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	implementation = shaderIt->second;

	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram();
		implementation->useProgram();
	}
}

void PostProcessingShader::setBufferPixelWidth(float pixelWidth) {
	if (implementation == nullptr) return;
	implementation->setBufferPixelWidth(pixelWidth);
}

void PostProcessingShader::setBufferPixelHeight(float pixelHeight) {
	if (implementation == nullptr) return;
	implementation->setBufferPixelHeight(pixelHeight);
}
