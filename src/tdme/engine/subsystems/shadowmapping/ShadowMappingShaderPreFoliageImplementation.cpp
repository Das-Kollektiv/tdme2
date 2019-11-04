#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreFoliageImplementation.h>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreFoliageImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMappingShaderPreFoliageImplementation::isSupported(Renderer* renderer) {
	return true;
}

ShadowMappingShaderPreFoliageImplementation::ShadowMappingShaderPreFoliageImplementation(Renderer* renderer): ShadowMappingShaderPreBaseImplementation(renderer)
{
}

ShadowMappingShaderPreFoliageImplementation::~ShadowMappingShaderPreFoliageImplementation() {
}

void ShadowMappingShaderPreFoliageImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// load shadow mapping shaders
	//	pre render
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"pre_vertexshader.c",
		"#define HAVE_FOLIAGE",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/shadowmapping",
			"pre_computevertex.inc.c"
		) +
		"\n\n" +
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
			"create_foliage_transform_matrix.inc.c"
		)
	);
	if (vertexShaderId == 0) return;
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"pre_fragmentshader.c"
	);
	if (fragmentShaderId == 0) return;

	// create shadow mapping render program
	//	pre
	programId = renderer->createProgram();
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	ShadowMappingShaderPreBaseImplementation::initialize();
}

