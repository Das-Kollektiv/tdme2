#include <tdme/engine/subsystems/lighting/LightingShader.h>

#include <tdme/engine/subsystems/lighting/LightingShaderBackImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderFoliageImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderFrontImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderSkyImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderSolidImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTerrainImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderWaterImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/utils/Console.h>

using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderBackImplementation;
using tdme::engine::subsystems::lighting::LightingShaderDefaultImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFoliageImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFrontImplementation;
using tdme::engine::subsystems::lighting::LightingShaderSkyImplementation;
using tdme::engine::subsystems::lighting::LightingShaderSolidImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTerrainImplementation;
using tdme::engine::subsystems::lighting::LightingShaderWaterImplementation;
using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::utils::Console;

LightingShader::LightingShader(Renderer* renderer) 
{
	if (LightingShaderBackImplementation::isSupported(renderer) == true) shader["back"] = new LightingShaderBackImplementation(renderer);
	if (LightingShaderDefaultImplementation::isSupported(renderer) == true) shader["default"] = new LightingShaderDefaultImplementation(renderer);
	if (LightingShaderFoliageImplementation::isSupported(renderer) == true) shader["foliage"] = new LightingShaderFoliageImplementation(renderer);
	if (LightingShaderFrontImplementation::isSupported(renderer) == true) shader["front"] = new LightingShaderFrontImplementation(renderer);
	if (LightingShaderSkyImplementation::isSupported(renderer) == true) shader["sky"] = new LightingShaderSkyImplementation(renderer);
	if (LightingShaderSolidImplementation::isSupported(renderer) == true) shader["solid"] = new LightingShaderSolidImplementation(renderer);
	if (LightingShaderTerrainImplementation::isSupported(renderer) == true) shader["terrain"] = new LightingShaderTerrainImplementation(renderer);
	if (LightingShaderWaterImplementation::isSupported(renderer) == true) shader["water"] = new LightingShaderWaterImplementation(renderer);
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

void LightingShader::unUseProgram(void* context)
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram(context);
	}
	implementation = nullptr;
	engine = nullptr;
}

void LightingShader::updateEffect(Renderer* renderer, void* context)
{
	if (implementation == nullptr) return;
	implementation->updateEffect(renderer, context);
}

void LightingShader::updateMaterial(Renderer* renderer, void* context)
{
	if (implementation == nullptr) return;
	implementation->updateMaterial(renderer, context);
}

void LightingShader::updateLight(Renderer* renderer, void* context, int32_t lightId)
{
	if (implementation == nullptr) return;
	implementation->updateLight(renderer, context, lightId);
}

void LightingShader::updateMatrices(Renderer* renderer, void* context)
{
	if (implementation == nullptr) return;
	implementation->updateMatrices(renderer, context);
}

void LightingShader::updateTextureMatrix(Renderer* renderer, void* context) {
	if (implementation == nullptr) return;
	implementation->updateTextureMatrix(renderer, context);
}

void LightingShader::setShader(void* context, const string& id) {
	if (running == false) return;

	auto currentImplementation = implementation;
	auto shaderIt = shader.find(id);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	implementation = shaderIt->second;

	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram(context);
		implementation->useProgram(engine, context);
	}
}

void LightingShader::bindTexture(Renderer* renderer, void* context, int32_t textureId)
{
	if (implementation == nullptr) return;
	implementation->bindTexture(renderer, context, textureId);
}
