#include <tdme/engine/subsystems/lighting/LightingShaderFoliageImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;
using std::string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFoliageImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderFoliageImplementation::isSupported(GLRenderer* renderer) {
	return renderer->getGLVersion() == "gl3";
}

LightingShaderFoliageImplementation::LightingShaderFoliageImplementation(GLRenderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

void LightingShaderFoliageImplementation::initialize()
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

	// geometry shader
	renderLightingGeometryShaderId = renderer->loadShader(
		renderer->SHADER_GEOMETRY_SHADER,
		"shader/" + rendererVersion + "/lighting",
		"render_geometryshader_foliage.c",
		"#define HAVE_DEPTH_FOG\n\n",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + rendererVersion + "/lighting",
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
	if (renderLightingGeometryShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/lighting",
		"render_vertexshader.c",
		"#define HAVE_GEOMETRY_SHADER\n#define HAVE_DEPTH_FOG\n\n"
	);
	if (renderLightingVertexShaderId == 0) return;

	// create, attach and link program
	renderLightingProgramId = renderer->createProgram();
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingVertexShaderId);
	if (renderer->isGeometryShaderAvailable() == true) {
		renderer->attachShaderToProgram(renderLightingProgramId, renderLightingGeometryShaderId);
	}
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingFragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
}

