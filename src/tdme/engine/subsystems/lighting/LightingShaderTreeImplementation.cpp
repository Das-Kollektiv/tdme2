#include <tdme/engine/subsystems/lighting/LightingShaderTreeImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/Renderer.h>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;
using std::string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTreeImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderTreeImplementation::isSupported(Renderer* renderer) {
	return true;
}

LightingShaderTreeImplementation::LightingShaderTreeImplementation(Renderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

void LightingShaderTreeImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	fragment shader
	renderLightingFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_fragmentshader.c",
		"#define HAVE_DEPTH_FOG"
	);
	if (renderLightingFragmentShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.c",
		"#define HAVE_TREE\n#define HAVE_DEPTH_FOG",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_rotation_matrix.inc.c"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_translation_matrix.inc.c"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_tree_transform_matrix.inc.c"
		)
	);
	if (renderLightingVertexShaderId == 0) return;

	// create, attach and link program
	renderLightingProgramId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingVertexShaderId);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingFragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
}

