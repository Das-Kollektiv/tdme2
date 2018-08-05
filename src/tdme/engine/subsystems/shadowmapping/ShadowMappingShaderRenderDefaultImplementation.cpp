#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderDefaultImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderDefaultImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

ShadowMappingShaderRenderDefaultImplementation::ShadowMappingShaderRenderDefaultImplementation(GLRenderer* renderer): ShadowMappingShaderRenderBaseImplementation(renderer)
{
}

ShadowMappingShaderRenderDefaultImplementation::~ShadowMappingShaderRenderDefaultImplementation()
{
}

void ShadowMappingShaderRenderDefaultImplementation::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	// load shadow mapping shaders
	renderVertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"render_vertexshader.c",
		"",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + rendererVersion + "/shadowmapping",
			"render_computevertex.inc.c"
		)
	);
	if (renderVertexShaderGlId == 0) return;

	renderFragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"render_fragmentshader.c"
	);
	if (renderFragmentShaderGlId == 0) return;

	// create shadow mapping render program
	renderProgramGlId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramGlId, renderVertexShaderGlId);
	renderer->attachShaderToProgram(renderProgramGlId, renderFragmentShaderGlId);

	ShadowMappingShaderRenderBaseImplementation::initialize();
}
