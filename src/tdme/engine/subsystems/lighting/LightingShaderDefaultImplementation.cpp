#include <tdme/engine/subsystems/lighting/LightingShaderDefaultImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;
using std::string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderDefaultImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderDefaultImplementation::isSupported(Renderer* renderer) {
	return true;
}

LightingShaderDefaultImplementation::LightingShaderDefaultImplementation(Renderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

void LightingShaderDefaultImplementation::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	// lighting
	//	fragment shader
	renderLightingFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/lighting",
		"render_fragmentshader.c",
		"#define HAVE_DEPTH_FOG\n\n"
	);
	if (renderLightingFragmentShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/lighting",
		"render_vertexshader.c",
		"#define HAVE_DEPTH_FOG\n\n",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + rendererVersion + "/lighting",
			"render_computevertex.inc.c"
		)
	);
	if (renderLightingVertexShaderId == 0) return;

	// create, attach and link program
	renderLightingProgramId = renderer->createProgram();
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingVertexShaderId);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingFragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
}

