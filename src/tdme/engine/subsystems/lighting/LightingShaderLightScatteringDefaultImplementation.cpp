#include <tdme/engine/subsystems/lighting/LightingShaderLightScatteringDefaultImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderLightScatteringDefaultImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderLightScatteringDefaultImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->getShaderVersion() == "gl3";
}

LightingShaderLightScatteringDefaultImplementation::LightingShaderLightScatteringDefaultImplementation(RendererBackend* rendererBackend): LightingShaderBaseImplementation(rendererBackend)
{
}

const string LightingShaderLightScatteringDefaultImplementation::getId() {
	return "ls_default";
}

void LightingShaderLightScatteringDefaultImplementation::initialize()
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
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
}

void LightingShaderLightScatteringDefaultImplementation::registerShader() {
}

void LightingShaderLightScatteringDefaultImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
}
