#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderDefaultImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderDefaultImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMappingShaderRenderDefaultImplementation::isSupported(Renderer* renderer) {
	return true;
}

ShadowMappingShaderRenderDefaultImplementation::ShadowMappingShaderRenderDefaultImplementation(Renderer* renderer): ShadowMappingShaderRenderBaseImplementation(renderer)
{
}

ShadowMappingShaderRenderDefaultImplementation::~ShadowMappingShaderRenderDefaultImplementation()
{
}

void ShadowMappingShaderRenderDefaultImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// load shadow mapping shaders
	renderVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"render_vertexshader.c",
		"",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/shadowmapping",
			"render_computevertex.inc.c"
		)
	);
	if (renderVertexShaderId == 0) return;

	renderFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"render_fragmentshader.c"
	);
	if (renderFragmentShaderId == 0) return;

	// create shadow mapping render program
	renderProgramId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(renderProgramId, renderVertexShaderId);
	renderer->attachShaderToProgram(renderProgramId, renderFragmentShaderId);

	ShadowMappingShaderRenderBaseImplementation::initialize();
}
