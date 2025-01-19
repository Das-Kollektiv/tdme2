#include <tdme/engine/subsystems/lighting/LightingShaderLightScatteringFoliageImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderLightScatteringFoliageImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderLightScatteringFoliageImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->getShaderVersion() == "gl3";
}

LightingShaderLightScatteringFoliageImplementation::LightingShaderLightScatteringFoliageImplementation(RendererBackend* rendererBackend): LightingShaderBaseImplementation(rendererBackend)
{
}

const string LightingShaderLightScatteringFoliageImplementation::getId() {
	return "ls_foliage";
}

void LightingShaderLightScatteringFoliageImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// lighting
	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/light_scattering",
		"render_fragmentshader.frag",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n"
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/light_scattering",
		"render_vertexshader.vert",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_FOLIAGE",
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

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();

	//
	if (initialized == false) return;

	// uniforms
	uniformSpeed = rendererBackend->getProgramUniformLocation(programId, "speed");
	uniformAmplitudeDefault = rendererBackend->getProgramUniformLocation(programId, "amplitudeDefault");
	uniformAmplitudeMax = rendererBackend->getProgramUniformLocation(programId, "amplitudeMax");
}

void LightingShaderLightScatteringFoliageImplementation::registerShader() {
}

void LightingShaderLightScatteringFoliageImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
	const auto& shaderParameters = rendererBackend->getShaderParameters(contextIdx);
	if (uniformSpeed != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformSpeed, shaderParameters.getShaderParameter("speed").getFloatValue());
	if (uniformAmplitudeDefault != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformAmplitudeDefault, shaderParameters.getShaderParameter("amplitudeDefault").getFloatValue());
	if (uniformAmplitudeMax != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformAmplitudeMax, shaderParameters.getShaderParameter("amplitudeMax").getFloatValue());
}
