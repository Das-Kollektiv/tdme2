#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/Renderer_Light.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/Console.h>

using std::to_string;
using std::string;

using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
using tdme::engine::subsystems::renderer::Renderer_Light;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::utils::Console;

LightingShaderPBRBaseImplementation::LightingShaderPBRBaseImplementation(Renderer* renderer)
{
	this->renderer = renderer;
	initialized = false;
}

bool LightingShaderPBRBaseImplementation::isInitialized()
{
	return initialized;
}

void LightingShaderPBRBaseImplementation::initialize()
{

	// link program
	if (renderer->linkProgram(renderLightingProgramId) == false) return;

	//
	initialized = true;
}

void LightingShaderPBRBaseImplementation::useProgram(Engine* engine, void* context)
{
	renderer->useProgram(context, renderLightingProgramId);
}

void LightingShaderPBRBaseImplementation::unUseProgram(void* context)
{
}

void LightingShaderPBRBaseImplementation::updateEffect(Renderer* renderer, void* context)
{
}

void LightingShaderPBRBaseImplementation::updateMaterial(Renderer* renderer, void* context)
{
}

void LightingShaderPBRBaseImplementation::updateLight(Renderer* renderer, void* context, int32_t lightId)
{
}

void LightingShaderPBRBaseImplementation::updateMatrices(Renderer* renderer, void* context)
{
}

void LightingShaderPBRBaseImplementation::updateTextureMatrix(Renderer* renderer, void* context) {
}

void LightingShaderPBRBaseImplementation::bindTexture(Renderer* renderer, void* context, int32_t textureId)
{
}
