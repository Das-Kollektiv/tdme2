#include <tdme/engine/subsystems/lighting/DeferredLightingShaderPBRDefaultImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::DeferredLightingShaderPBRDefaultImplementation;
using tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool DeferredLightingShaderPBRDefaultImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->isPBRAvailable() == true && rendererBackend->isDeferredShadingAvailable() == true;
}

DeferredLightingShaderPBRDefaultImplementation::DeferredLightingShaderPBRDefaultImplementation(RendererBackend* rendererBackend): LightingShaderPBRBaseImplementation(rendererBackend)
{
}

const string DeferredLightingShaderPBRDefaultImplementation::getId() {
	return "defer_pbr-default";
}

void DeferredLightingShaderPBRDefaultImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"render_vertexshader.vert",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n#define USE_IBL\n"
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"defer_fragmentshader.frag",
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
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderPBRBaseImplementation::initialize();
}

void DeferredLightingShaderPBRDefaultImplementation::registerShader() {
}

void DeferredLightingShaderPBRDefaultImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
}
