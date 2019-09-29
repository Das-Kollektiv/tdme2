#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPreFoliageImplementation.h>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::engine::subsystems::earlyzrejection::EZRShaderPreFoliageImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool EZRShaderPreFoliageImplementation::isSupported(Renderer* renderer) {
	return renderer->isGeometryShaderAvailable();
}

EZRShaderPreFoliageImplementation::EZRShaderPreFoliageImplementation(Renderer* renderer): EZRShaderPreBaseImplementation(renderer)
{
}

EZRShaderPreFoliageImplementation::~EZRShaderPreFoliageImplementation() {
}

void EZRShaderPreFoliageImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// load shadow mapping shaders
	//	pre render
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/earlyzrejection",
		"pre_vertexshader.c",
		"#define HAVE_FOLIAGE\n\n",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/earlyzrejection",
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
		"shader/" + shaderVersion + "/earlyzrejection",
		"pre_fragmentshader.c"
	);
	if (fragmentShaderId == 0) return;

	// create shadow mapping render program
	//	pre
	programId = renderer->createProgram();
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	EZRShaderPreBaseImplementation::initialize();

}

