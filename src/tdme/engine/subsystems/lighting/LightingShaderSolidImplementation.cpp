#include <tdme/engine/subsystems/lighting/LightingShaderSolidImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderSolidImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderSolidImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->getShaderVersion() == "gl3";
}

LightingShaderSolidImplementation::LightingShaderSolidImplementation(RendererBackend* rendererBackend): LightingShaderBaseImplementation(rendererBackend)
{
}

const string LightingShaderSolidImplementation::getId() {
	return "solid";
}

void LightingShaderSolidImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.vert",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_SOLID_SHADING"
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_fragmentshader.frag",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_SOLID_SHADING",
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
}

void LightingShaderSolidImplementation::registerShader() {
	Engine::registerShader(Engine::ShaderType::SHADERTYPE_OBJECT, getId());
}


void LightingShaderSolidImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
}
