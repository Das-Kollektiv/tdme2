#include <tdme/engine/subsystems/lighting/LightingShaderFoliageImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFoliageImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderFoliageImplementation::isSupported(Renderer* renderer) {
	return true;
}

LightingShaderFoliageImplementation::LightingShaderFoliageImplementation(Renderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

const string LightingShaderFoliageImplementation::getId() {
	return "foliage";
}

void LightingShaderFoliageImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.vert",
		"#define HAVE_FOLIAGE\n#define HAVE_DEPTH_FOG",
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
		)
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_fragmentshader.frag",
		"#define HAVE_DEPTH_FOG",
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

	// uniforms
	uniformSpeed = renderer->getProgramUniformLocation(programId, "speed");
	uniformAmplitudeDefault = renderer->getProgramUniformLocation(programId, "amplitudeDefault");
	uniformAmplitudeMax = renderer->getProgramUniformLocation(programId, "amplitudeMax");
}

void LightingShaderFoliageImplementation::registerShader() {
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_OBJECT3D,
		getId(),
		{
			{ "speed", ShaderParameter(1.0f) },
			{ "amplitudeDefault", ShaderParameter(0.0f) },
			{ "amplitudeMax", ShaderParameter(20.0f) }
		}
	);
}

void LightingShaderFoliageImplementation::updateShaderParameters(Renderer* renderer, void* context) {
	auto& shaderParameters = renderer->getShaderParameters(context);
	if (uniformSpeed != -1) renderer->setProgramUniformFloat(context, uniformSpeed, shaderParameters.getShaderParameter("speed").getFloatValue());
	if (uniformAmplitudeDefault != -1) renderer->setProgramUniformFloat(context, uniformAmplitudeDefault, shaderParameters.getShaderParameter("amplitudeDefault").getFloatValue());
	if (uniformAmplitudeMax != -1) renderer->setProgramUniformFloat(context, uniformAmplitudeMax, shaderParameters.getShaderParameter("amplitudeMax").getFloatValue());
}
