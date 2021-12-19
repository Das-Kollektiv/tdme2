// @see https://jayconrod.com/posts/34/water-simulation-in-glsl

#include <tdme/engine/subsystems/lighting/LightingShaderWaterImplementation.h>

#include <array>
#include <string>

#include <tdme/tdme.h>
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
	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.vert",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_WATER_SHADER\n#define HAVE_DEPTH_FOG",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"water.inc.glsl"
		)
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_fragmentshader.frag",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_WATER_SHADER\n#define HAVE_DEPTH_FOG",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/specular",
			"specular_lighting.inc.glsl"
		)
	);
	if (fragmentShaderId == 0) return;

	// create, attach and link program
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();

	//
	initialized = false;

	//
	uniformWaterHeight = renderer->getProgramUniformLocation(programId, "waterHeight");
	if (uniformWaterHeight == -1) return;
	uniformTime = renderer->getProgramUniformLocation(programId, "time");
	if (uniformTime == -1) return;
	uniformWaterWaves = renderer->getProgramUniformLocation(programId, "waterWaves");
	if (uniformWaterWaves == -1) return;
	for (auto i = 0; i < WAVES_MAX; i++) {
		uniformWaterAmplitude[i] = renderer->getProgramUniformLocation(programId, "waterAmplitude[" + to_string(i) + "]");
		if (uniformWaterAmplitude[i] == -1) return;
	}
	for (auto i = 0; i < WAVES_MAX; i++) {
		uniformWaterWaveLength[i] = renderer->getProgramUniformLocation(programId, "waterWavelength[" + to_string(i) + "]");
		if (uniformWaterWaveLength[i] == -1) return;
	}
	for (auto i = 0; i < WAVES_MAX; i++) {
		uniformWaterSpeed[i] = renderer->getProgramUniformLocation(programId, "waterSpeed[" + to_string(i) + "]");
		if (uniformWaterSpeed[i] == -1) return;
	}
	for (auto i = 0; i < WAVES_MAX; i++) {
		uniformWaterDirection[i] = renderer->getProgramUniformLocation(programId, "waterDirection[" + to_string(i) + "]");
		if (uniformWaterDirection[i] == -1) return;
	}
	uniformModelMatrix = renderer->getProgramUniformLocation(programId, "modelMatrix");

	//
	initialized = true;

	//
	for (auto i = 0; i < 4; i++) angle[i] = -Math::PI / 3.0f + Math::random() * Math::PI * 2.0f / 3.0f;
}

void LightingShaderWaterImplementation::registerShader() {
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_OBJECT3D,
		getId(),
		{{ "speed", ShaderParameter(1.0f) }}
	);
}

void LightingShaderWaterImplementation::useProgram(Engine* engine, int contextIdx) {
	LightingShaderBaseImplementation::useProgram(engine, contextIdx);

	//
	renderer->setProgramUniformFloat(contextIdx, uniformWaterHeight, 0.50f);
	renderer->setProgramUniformFloat(contextIdx, uniformTime, time);
	renderer->setProgramUniformInteger(contextIdx, uniformWaterWaves, 4);
	for (auto i = 0; i < 4; i++) {
		renderer->setProgramUniformFloat(contextIdx, uniformWaterAmplitude[i], 0.5f / (i + 1));
		renderer->setProgramUniformFloat(contextIdx, uniformWaterWaveLength[i], 8 * Math::PI / (i + 1));
		renderer->setProgramUniformFloat(contextIdx, uniformWaterSpeed[i], 1.0f + 1.0f * i / 2.0f);
		renderer->setProgramUniformFloatVec2(contextIdx, uniformWaterDirection[i], {Math::cos(angle[i]), Math::sin(angle[i])});
	}
	time+= engine->getTiming()->getDeltaTime() / 1000.0f;
}

void LightingShaderWaterImplementation::updateMatrices(Renderer* renderer, int contextIdx) {
	LightingShaderBaseImplementation::updateMatrices(renderer, contextIdx);
	if (uniformModelMatrix != -1) renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformModelMatrix, renderer->getModelViewMatrix().getArray());
}

void LightingShaderWaterImplementation::updateShaderParameters(Renderer* renderer, int contextIdx) {
}
