#include <tdme/engine/subsystems/lighting/LightingShaderPBRDefaultImplementation.h>

#include <string>

#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderPBRDefaultImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderPBRDefaultImplementation::isSupported(Renderer* renderer) {
	return renderer->isPBRAvailable();
}

LightingShaderPBRDefaultImplementation::LightingShaderPBRDefaultImplementation(Renderer* renderer): LightingShaderPBRBaseImplementation(renderer)
{
}

const string LightingShaderPBRDefaultImplementation::getId() {
	return "pbr-default";
}

void LightingShaderPBRDefaultImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"render_vertexshader.vert",
		string() +
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n"
		#if !defined(VULKAN)
			+ "#define USE_IBL\n"
		#endif
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"render_fragmentshader.frag",
		string() +
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n"
		#if !defined(VULKAN)
			+ "#define USE_IBL\n"
		#endif
		,
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
}

void LightingShaderPBRDefaultImplementation::registerShader() {
	Engine::registerShader(Engine::ShaderType::SHADERTYPE_OBJECT3D, getId());
}

void LightingShaderPBRDefaultImplementation::updateShaderParameters(Renderer* renderer, void* context) {
}
