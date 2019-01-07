#include <tdme/engine/subsystems/lighting/LightingShaderSkyImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;
using std::string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderSkyImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderSkyImplementation::isSupported(GLRenderer* renderer) {
	return true;
}

LightingShaderSkyImplementation::LightingShaderSkyImplementation(GLRenderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

void LightingShaderSkyImplementation::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	// lighting
	//	fragment shader
	renderLightingFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/lighting",
		"render_fragmentshader.c",
		"#define HAVE_SOLID_SHADING\n#define HAVE_SKY_SHADING\n\n"
	);
	if (renderLightingFragmentShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/lighting",
		"render_vertexshader.c",
		"#define HAVE_SOLID_SHADING\n#define HAVE_SKY_SHADING\n\n",
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

