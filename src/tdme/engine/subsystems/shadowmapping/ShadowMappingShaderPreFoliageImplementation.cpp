#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreFoliageImplementation.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreFoliageImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

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
		"pre_vertexshader.c"
	);
	if (vertexShaderGlId == 0) return;
	if (renderer->isGeometryShaderAvailable() == true) {
		geometryShaderGlId = renderer->loadShader(
			renderer->SHADER_GEOMETRY_SHADER,
			"shader/" + rendererVersion + "/shadowmapping",
			"pre_geometryshader.c",
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
	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programGlId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programGlId, 2, "inTextureUV");
	}

	//
	ShadowMappingShaderPreBaseImplementation::initialize();
}

