#include <tdme/engine/subsystems/lighting/LightingShaderPBRTreeImplementation.h>

#include <string>

#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderPBRTreeImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderPBRTreeImplementation::isSupported(Renderer* renderer) {
	return renderer->isPBRAvailable();
}

LightingShaderPBRTreeImplementation::LightingShaderPBRTreeImplementation(Renderer* renderer): LightingShaderPBRBaseImplementation(renderer)
{
}

const string LightingShaderPBRTreeImplementation::getId() {
	return "pbr-tree";
}

void LightingShaderPBRTreeImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"render_vertexshader.vert",
		"#define HAVE_TREE\n",
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
			"create_tree_transform_matrix.inc.glsl"
		) + "\n\n"
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"render_fragmentshader.frag",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n#define USE_IBL\n",
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
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderPBRBaseImplementation::initialize();

	//
	initialized = false;

	// uniforms
	uniformSpeed = renderer->getProgramUniformLocation(programId, "speed");
	if (uniformSpeed == -1) return;
	uniformTime = renderer->getProgramUniformLocation(programId, "time");
	if (uniformTime == -1) return;

	//
	initialized = true;
}

void LightingShaderPBRTreeImplementation::registerShader() {
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_OBJECT3D,
		getId(),
		{{ "speed", ShaderParameter(1.0f) }}
	);
}

void LightingShaderPBRTreeImplementation::useProgram(Engine* engine, void* context)
{
	LightingShaderPBRBaseImplementation::useProgram(engine, context);

	// time
	if (uniformTime != -1) renderer->setProgramUniformFloat(context, uniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
}

void LightingShaderPBRTreeImplementation::updateShaderParameters(Renderer* renderer, void* context) {
	auto& shaderParameters = renderer->getShaderParameters(context);
	if (uniformSpeed != -1) renderer->setProgramUniformFloat(context, uniformSpeed, shaderParameters.getShaderParameter("speed").getFloatValue());
}
