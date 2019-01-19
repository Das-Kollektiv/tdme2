#include <tdme/engine/subsystems/lighting/LightingShader.h>

#include <tdme/engine/subsystems/lighting/LightingShaderBackImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderFoliageImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderFrontImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderSkyImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderSolidImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTerrainImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderImplementation.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/utils/Console.h>

using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderBackImplementation;
using tdme::engine::subsystems::lighting::LightingShaderDefaultImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFoliageImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFrontImplementation;
using tdme::engine::subsystems::lighting::LightingShaderSkyImplementation;
using tdme::engine::subsystems::lighting::LightingShaderSolidImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTerrainImplementation;
using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::Console;

LightingShader::LightingShader(GLRenderer* renderer) 
{
	if (LightingShaderBackImplementation::isSupported(renderer) == true) shader["back"] = new LightingShaderBackImplementation(renderer);
	if (LightingShaderDefaultImplementation::isSupported(renderer) == true) shader["default"] = new LightingShaderDefaultImplementation(renderer);
	if (LightingShaderFoliageImplementation::isSupported(renderer) == true) shader["foliage"] = new LightingShaderFoliageImplementation(renderer);
	if (LightingShaderFrontImplementation::isSupported(renderer) == true) shader["front"] = new LightingShaderFrontImplementation(renderer);
	if (LightingShaderSkyImplementation::isSupported(renderer) == true) shader["sky"] = new LightingShaderSkyImplementation(renderer);
	if (LightingShaderSolidImplementation::isSupported(renderer) == true) shader["solid"] = new LightingShaderSolidImplementation(renderer);
	if (LightingShaderTerrainImplementation::isSupported(renderer) == true) shader["terrain"] = new LightingShaderTerrainImplementation(renderer);
	implementation = nullptr;
}

LightingShader::~LightingShader() {
	for (auto shaderIt: shader) {
		delete shaderIt.second;
	}
}

bool LightingShader::isInitialized()
{
	bool initialized = true;
	for (auto shaderIt: shader) {
		if (shaderIt.second->isInitialized() == false) {
			Console::println("LightingShader::isInitialized(): " + shaderIt.first + ": not initialized!");
		}
		initialized&= shaderIt.second->isInitialized();
	}
	return initialized;
}

void LightingShader::initialize()
{
	for (auto shaderIt: shader) {
		shaderIt.second->initialize();
	}
}

void LightingShader::useProgram(Engine* engine)
{
	running = true;
	this->engine = engine;
}

void LightingShader::unUseProgram()
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram();;
	}
	implementation = nullptr;
	engine = nullptr;
}

void LightingShader::updateEffect(GLRenderer* renderer)
{
	if (implementation == nullptr) return;
	implementation->updateEffect(renderer);
}

void LightingShader::updateMaterial(GLRenderer* renderer)
{
	if (implementation == nullptr) return;
	implementation->updateMaterial(renderer);
}

void LightingShader::updateLight(GLRenderer* renderer, int32_t lightId)
{
	if (implementation == nullptr) return;
	implementation->updateLight(renderer, lightId);
}

void LightingShader::updateMatrices(GLRenderer* renderer)
{
	if (implementation == nullptr) return;
	implementation->updateMatrices(renderer);
}

void LightingShader::updateTextureMatrix(GLRenderer* renderer) {
	if (implementation == nullptr) return;
	implementation->updateTextureMatrix(renderer);
}

void LightingShader::setShader(const string& id) {
	if (running == false) return;

	auto currentImplementation = implementation;
	auto shaderIt = shader.find(id);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	implementation = shaderIt->second;

	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram();
		implementation->useProgram(engine);
	}
}

void LightingShader::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	if (implementation == nullptr) return;
	implementation->bindTexture(renderer, textureId);
}
