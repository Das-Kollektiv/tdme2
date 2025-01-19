#include <tdme/engine/subsystems/lighting/LightingShaderFoliageImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFoliageImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderFoliageImplementation::isSupported(RendererBackend* rendererBackend) {
	return true;
}

LightingShaderFoliageImplementation::LightingShaderFoliageImplementation(RendererBackend* rendererBackend): LightingShaderBaseImplementation(rendererBackend)
{
}

const string LightingShaderFoliageImplementation::getId() {
	return "foliage";
}

void LightingShaderFoliageImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.vert",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_FOLIAGE\n#define HAVE_DEPTH_FOG",
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
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_fragmentshader.frag",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_DEPTH_FOG",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/specular",
			"specular_lighting.inc.glsl"
		)
	);
	if (fragmentShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();

	// uniforms
	uniformSpeed = rendererBackend->getProgramUniformLocation(programId, "speed");
	uniformAmplitudeDefault = rendererBackend->getProgramUniformLocation(programId, "amplitudeDefault");
	uniformAmplitudeMax = rendererBackend->getProgramUniformLocation(programId, "amplitudeMax");
}

void LightingShaderFoliageImplementation::registerShader() {
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

void LightingShaderFoliageImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
	const auto& shaderParameters = rendererBackend->getShaderParameters(contextIdx);
	if (uniformSpeed != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformSpeed, shaderParameters.getShaderParameter("speed").getFloatValue());
	if (uniformAmplitudeDefault != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformAmplitudeDefault, shaderParameters.getShaderParameter("amplitudeDefault").getFloatValue());
	if (uniformAmplitudeMax != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformAmplitudeMax, shaderParameters.getShaderParameter("amplitudeMax").getFloatValue());
}
