#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderFoliageImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderFoliageImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMappingShaderRenderFoliageImplementation::isSupported(GLRenderer* renderer) {
	return renderer->isGeometryShaderAvailable();
}

ShadowMappingShaderRenderFoliageImplementation::ShadowMappingShaderRenderFoliageImplementation(GLRenderer* renderer): ShadowMappingShaderRenderBaseImplementation(renderer)
{
}

ShadowMappingShaderRenderFoliageImplementation::~ShadowMappingShaderRenderFoliageImplementation()
{
}

void ShadowMappingShaderRenderFoliageImplementation::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	// load shadow mapping shaders
	renderVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"render_vertexshader.c",
		"#define HAVE_GEOMETRY_SHADER\n\n"
	);
	if (renderVertexShaderId == 0) return;

	renderGeometryShaderId = renderer->loadShader(
		renderer->SHADER_GEOMETRY_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"render_geometryshader_foliage.c",
		"",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + rendererVersion + "/shadowmapping",
			"render_computevertex.inc.c"
		) +
		"\n\n" +
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
	if (renderGeometryShaderId == 0) return;

	renderFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"render_fragmentshader.c"
	);
	if (renderFragmentShaderId == 0) return;

	// create shadow mapping render program
	renderProgramId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramId, renderVertexShaderId);
	renderer->attachShaderToProgram(renderProgramId, renderGeometryShaderId);
	renderer->attachShaderToProgram(renderProgramId, renderFragmentShaderId);

	ShadowMappingShaderRenderBaseImplementation::initialize();
}
