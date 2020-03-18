#include <tdme/engine/subsystems/lighting/LightingShaderFrontImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;
using std::string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFrontImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderFrontImplementation::isSupported(Renderer* renderer) {
	return renderer->getShaderVersion() == "gl3";
}

LightingShaderFrontImplementation::LightingShaderFrontImplementation(Renderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

void LightingShaderFrontImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	fragment shader
	renderLightingFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_fragmentshader.c",
		"#define HAVE_SOLID_SHADING\n#define HAVE_FRONT"
	);
	if (renderLightingFragmentShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.c",
		"#define HAVE_SOLID_SHADING\n#define HAVE_FRONT"
	);
	if (renderLightingVertexShaderId == 0) return;

	// create, attach and link program
	renderLightingProgramId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingVertexShaderId);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingFragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
}

