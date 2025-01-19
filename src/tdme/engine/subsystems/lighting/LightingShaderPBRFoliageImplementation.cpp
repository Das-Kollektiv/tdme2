#include <tdme/engine/subsystems/lighting/LightingShaderPBRFoliageImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/engine/Timing.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderPBRFoliageImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::engine::Timing;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderPBRFoliageImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->isPBRAvailable();
}

LightingShaderPBRFoliageImplementation::LightingShaderPBRFoliageImplementation(RendererBackend* rendererBackend): LightingShaderPBRBaseImplementation(rendererBackend)
{
}

const string LightingShaderPBRFoliageImplementation::getId() {
	return "pbr-foliage";
}

void LightingShaderPBRFoliageImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"render_vertexshader.vert",
		string() +
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n#define HAVE_FOLIAGE\n#define USE_IBL\n",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_rotation_matrix.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_translation_matrix.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_foliage_transform_matrix.inc.glsl"
		) + "\n\n"
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"render_fragmentshader.frag",
		string() +
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n#define HAVE_FOLIAGE\n#define USE_IBL\n",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"tonemapping.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"textures.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"functions.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"pbr_lighting.inc.glsl"
		) +
		"\n\n"
	);
	if (fragmentShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderPBRBaseImplementation::initialize();

	//
	if (initialized == false) return;

	//
	initialized = false;

	// uniforms
	uniformSpeed = rendererBackend->getProgramUniformLocation(programId, "speed");
	if (uniformSpeed == -1) return;
	uniformTime = rendererBackend->getProgramUniformLocation(programId, "time");
	if (uniformTime == -1) return;
	uniformAmplitudeDefault = rendererBackend->getProgramUniformLocation(programId, "amplitudeDefault");
	if (uniformAmplitudeDefault == -1) return;
	uniformAmplitudeMax = rendererBackend->getProgramUniformLocation(programId, "amplitudeMax");
	if (uniformAmplitudeMax == -1) return;

	//
	initialized = true;
}

void LightingShaderPBRFoliageImplementation::registerShader() {
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_OBJECT,
		getId(),
		{
			{ "speed", ShaderParameter(1.0f), ShaderParameter(0.0f), ShaderParameter(20.0f), ShaderParameter(1.0f) },
			{ "amplitudeDefault", ShaderParameter(0.0f), ShaderParameter(-45.0f), ShaderParameter(45.0f), ShaderParameter(4.5f) },
			{ "amplitudeMax", ShaderParameter(20.0f), ShaderParameter(-45.0f), ShaderParameter(45.0f), ShaderParameter(4.5f) },
		}
	);
}

void LightingShaderPBRFoliageImplementation::useProgram(Engine* engine, int contextIdx)
{
	LightingShaderPBRBaseImplementation::useProgram(engine, contextIdx);

	// time
	if (uniformTime != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
}

void LightingShaderPBRFoliageImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
	const auto& shaderParameters = rendererBackend->getShaderParameters(contextIdx);
	if (uniformSpeed != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformSpeed, shaderParameters.getShaderParameter("speed").getFloatValue());
	if (uniformAmplitudeDefault != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformAmplitudeDefault, shaderParameters.getShaderParameter("amplitudeDefault").getFloatValue());
	if (uniformAmplitudeMax != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformAmplitudeMax, shaderParameters.getShaderParameter("amplitudeMax").getFloatValue());
}
