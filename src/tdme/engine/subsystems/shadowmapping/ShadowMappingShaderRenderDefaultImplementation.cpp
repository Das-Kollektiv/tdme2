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
		"render_vertexshader.c"
	);
	if (renderVertexShaderGlId == 0) return;

	if (renderer->isGeometryShaderAvailable() == true) {
		renderGeometryShaderGlId = renderer->loadShader(
			renderer->SHADER_GEOMETRY_SHADER,
			"shader/" + rendererVersion + "/shadowmapping",
			"render_geometryshader.c",
			"",
			/*
			FileSystem::getInstance()->getContentAsString(
				"shader/" + rendererVersion + "/lighting",
				"render_computevertex.inc.c"
			) +
			"\n\n" +
			*/
			FileSystem::getInstance()->getContentAsString(
				"shader/" + rendererVersion + "/functions",
				"create_rotation_matrix.inc.c"
			) +
			"\n\n" +
			FileSystem::getInstance()->getContentAsString(
				"shader/" + rendererVersion + "/functions",
				"create_translation_matrix.inc.c"
			)
		);
		if (renderGeometryShaderGlId == 0) return;
	}

	renderFragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"render_fragmentshader.c"
	);
	if (renderFragmentShaderGlId == 0) return;
	// create shadow mapping render program
	renderProgramGlId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramGlId, renderVertexShaderGlId);
	if (renderer->isGeometryShaderAvailable() == true) {
		renderer->attachShaderToProgram(renderProgramGlId, renderGeometryShaderGlId);
	}
	renderer->attachShaderToProgram(renderProgramGlId, renderFragmentShaderGlId);

	ShadowMappingShaderRenderBaseImplementation::initialize();
}
