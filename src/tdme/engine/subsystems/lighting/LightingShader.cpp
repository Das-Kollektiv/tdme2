#include <tdme/engine/subsystems/lighting/LightingShader.h>

#include <tdme/engine/subsystems/lighting/LightingShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderFoliageImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderImplementation.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/utils/Console.h>

using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderDefaultImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFoliageImplementation;
using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::Console;

LightingShader::LightingShader(GLRenderer* renderer) 
{
	defaultImplementation = new LightingShaderDefaultImplementation(renderer);
	foliageImplementation = new LightingShaderFoliageImplementation(renderer);
	implementation = nullptr;
}

LightingShader::~LightingShader() {
	delete defaultImplementation;
	delete foliageImplementation;
}

bool LightingShader::isInitialized()
{
	return defaultImplementation->isInitialized() == true && foliageImplementation->isInitialized() == true;
}

void LightingShader::initialize()
{
	defaultImplementation->initialize();
	foliageImplementation->initialize();
}

void LightingShader::useProgram()
{
	running = true;
}

void LightingShader::unUseProgram()
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram();;
	}
	implementation = nullptr;
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

void LightingShader::updateApplyFoliageAnimation(GLRenderer* renderer) {
	if (running == false) return;

	auto currentImplementation = implementation;
	implementation = renderer->applyFoliageAnimation == true?foliageImplementation:defaultImplementation;
	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram();
		implementation->useProgram();
	}
}

void LightingShader::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	if (implementation == nullptr) return;
	implementation->bindTexture(renderer, textureId);
}
