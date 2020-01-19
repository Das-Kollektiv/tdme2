#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPreTreeImplementation.h>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::engine::subsystems::earlyzrejection::EZRShaderPreTreeImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool EZRShaderPreTreeImplementation::isSupported(Renderer* renderer) {
	return true;
}

EZRShaderPreTreeImplementation::EZRShaderPreTreeImplementation(Renderer* renderer): EZRShaderPreBaseImplementation(renderer)
{
}

EZRShaderPreTreeImplementation::~EZRShaderPreTreeImplementation() {
}

void EZRShaderPreTreeImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// load shadow mapping shaders
	//	pre render
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/earlyzrejection",
		"pre_vertexshader.c",
		"#define HAVE_TREE",
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
			"create_tree_transform_matrix.inc.c"
		)
	);
	if (vertexShaderId == 0) return;
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/earlyzrejection",
		"pre_fragmentshader.c"
	);
	if (fragmentShaderId == 0) return;

	// create program
	//	pre
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	EZRShaderPreBaseImplementation::initialize();

}

