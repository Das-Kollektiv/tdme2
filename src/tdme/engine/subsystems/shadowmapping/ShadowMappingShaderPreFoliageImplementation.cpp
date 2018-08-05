#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreFoliageImplementation.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreFoliageImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMappingShaderPreFoliageImplementation::isSupported(GLRenderer* renderer) {
	return renderer->isGeometryShaderAvailable();
}

ShadowMappingShaderPreFoliageImplementation::ShadowMappingShaderPreFoliageImplementation(GLRenderer* renderer): ShadowMappingShaderPreBaseImplementation(renderer)
{
}

ShadowMappingShaderPreFoliageImplementation::~ShadowMappingShaderPreFoliageImplementation() {
}

void ShadowMappingShaderPreFoliageImplementation::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	// load shadow mapping shaders
	//	pre render
	vertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"pre_vertexshader.c",
		"#define HAVE_GEOMETRY_SHADER\n\n"
	);
	if (vertexShaderGlId == 0) return;
	if (renderer->isGeometryShaderAvailable() == true) {
		geometryShaderGlId = renderer->loadShader(
			renderer->SHADER_GEOMETRY_SHADER,
			"shader/" + rendererVersion + "/shadowmapping",
			"pre_geometryshader_foliage.c",
			"",
			FileSystem::getInstance()->getContentAsString(
				"shader/" + rendererVersion + "/shadowmapping",
				"pre_computevertex.inc.c"
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
		if (geometryShaderGlId == 0) return;
	}
	fragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"pre_fragmentshader.c"
	);
	if (fragmentShaderGlId == 0) return;

	// create shadow mapping render program
	//	pre
	programGlId = renderer->createProgram();
	renderer->attachShaderToProgram(programGlId, vertexShaderGlId);
	if (renderer->isGeometryShaderAvailable() == true) {
		renderer->attachShaderToProgram(programGlId, geometryShaderGlId);
	}
	renderer->attachShaderToProgram(programGlId, fragmentShaderGlId);

	//
	ShadowMappingShaderPreBaseImplementation::initialize();
}

