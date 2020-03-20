#include <tdme/engine/subsystems/lighting/LightingShaderPBRDefaultImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;
using std::string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderPBRDefaultImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderPBRDefaultImplementation::isSupported(Renderer* renderer) {
	return renderer->isPBRAvailable();
}

LightingShaderPBRDefaultImplementation::LightingShaderPBRDefaultImplementation(Renderer* renderer): LightingShaderPBRBaseImplementation(renderer)
{
}

void LightingShaderPBRDefaultImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	fragment shader
	renderLightingFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"metallic-roughness.frag",
		"#define LIGHT_COUNT	8\n#define HAS_NORMALS\n#define HAS_UV_SET1\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/lighting/pbr",
			"tonemapping.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/lighting/pbr",
			"textures.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/lighting/pbr",
			"functions.glsl"
		)
	);
	if (renderLightingFragmentShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/pbr",
		"primitive.vert",
		"#define LIGHT_COUNT	8\n#define HAS_NORMALS\n#define HAS_UV_SET1\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n"
	);
	if (renderLightingVertexShaderId == 0) return;

	// create, attach and link program
	renderLightingProgramId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingVertexShaderId);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingFragmentShaderId);

	//
	LightingShaderPBRBaseImplementation::initialize();
}

