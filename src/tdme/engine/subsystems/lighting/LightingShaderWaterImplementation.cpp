// @see https://jayconrod.com/posts/34/water-simulation-in-glsl

#include <tdme/engine/subsystems/lighting/LightingShaderWaterImplementation.h>

#include <array>
#include <string>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::array;
using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderWaterImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::ShaderParameter;
using tdme::engine::Timing;
using tdme::math::Math;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderWaterImplementation::isSupported(Renderer* renderer) {
	return true;
}

LightingShaderWaterImplementation::LightingShaderWaterImplementation(Renderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

const string LightingShaderWaterImplementation::getId() {
	return "water";
}

void LightingShaderWaterImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	fragment shader
	renderLightingFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_fragmentshader.frag",
		"#define HAVE_WATER_SHADER\n#define HAVE_DEPTH_FOG"
	);
	if (renderLightingFragmentShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.vert",
		"#define HAVE_WATER_SHADER\n#define HAVE_DEPTH_FOG",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"render_water.inc.glsl"
		)
	);
	if (renderLightingVertexShaderId == 0) return;

	// create, attach and link program
	renderLightingProgramId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingVertexShaderId);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingFragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();

	//
	initialized = false;

	//
	uniformWaterHeight = renderer->getProgramUniformLocation(renderLightingProgramId, "waterHeight");
	if (uniformWaterHeight == -1) return;
	uniformTime = renderer->getProgramUniformLocation(renderLightingProgramId, "time");
	if (uniformTime == -1) return;
	uniformWaterWaves = renderer->getProgramUniformLocation(renderLightingProgramId, "waterWaves");
	if (uniformWaterWaves == -1) return;
	for (auto i = 0; i < WAVES_MAX; i++) {
		uniformWaterAmplitude[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "waterAmplitude[" + to_string(i) + "]");
		if (uniformWaterAmplitude[i] == -1) return;
	}
	for (auto i = 0; i < WAVES_MAX; i++) {
		uniformWaterWaveLength[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "waterWavelength[" + to_string(i) + "]");
		if (uniformWaterWaveLength[i] == -1) return;
	}
	for (auto i = 0; i < WAVES_MAX; i++) {
		uniformWaterSpeed[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "waterSpeed[" + to_string(i) + "]");
		if (uniformWaterSpeed[i] == -1) return;
	}
	for (auto i = 0; i < WAVES_MAX; i++) {
		uniformWaterDirection[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "waterDirection[" + to_string(i) + "]");
		if (uniformWaterDirection[i] == -1) return;
	}
	uniformModelMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, "modelMatrix");

	//
	initialized = true;

	//
	for (auto i = 0; i < 4; i++) angle[i] = -Math::PI / 3.0f + Math::random() * Math::PI * 2.0f / 3.0f;

	// register shader
	if (initialized == true) {
		Engine::registerShader(
			Engine::ShaderType::SHADERTYPE_OBJECT3D,
			getId(),
			{{ "speed", ShaderParameter(1.0f) }}
		);
	}
}

void LightingShaderWaterImplementation::useProgram(Engine* engine, void* context) {
	LightingShaderBaseImplementation::useProgram(engine, context);

	//
	renderer->setProgramUniformFloat(context, uniformWaterHeight, 0.25f);
	renderer->setProgramUniformFloat(context, uniformTime, time / 10.0f);
	renderer->setProgramUniformInteger(context, uniformWaterWaves, 4);
	for (auto i = 0; i < 4; i++) {
		renderer->setProgramUniformFloat(context, uniformWaterAmplitude[i], 0.5f / (i + 1));
		renderer->setProgramUniformFloat(context, uniformWaterWaveLength[i], 8 * Math::PI / (i + 1));
		renderer->setProgramUniformFloat(context, uniformWaterSpeed[i], 1.0f + 1.0f * i);
		renderer->setProgramUniformFloatVec2(context, uniformWaterDirection[i], {Math::cos(angle[i]), Math::sin(angle[i])});
	}
	time+= engine->getTiming()->getDeltaTime() / 1000.0f;
}

void LightingShaderWaterImplementation::updateMatrices(Renderer* renderer, void* context) {
	LightingShaderBaseImplementation::updateMatrices(renderer, context);
	if (uniformModelMatrix != -1) renderer->setProgramUniformFloatMatrix4x4(context, uniformModelMatrix, renderer->getModelViewMatrix().getArray());
}

void LightingShaderWaterImplementation::updateShaderParameters(Renderer* renderer, void* context) {
}
