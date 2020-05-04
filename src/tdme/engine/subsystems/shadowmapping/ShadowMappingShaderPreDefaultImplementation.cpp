#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreDefaultImplementation.h>

#include <string>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreDefaultImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMappingShaderPreDefaultImplementation::isSupported(Renderer* renderer) {
	return true;
}

ShadowMappingShaderPreDefaultImplementation::ShadowMappingShaderPreDefaultImplementation(Renderer* renderer): ShadowMappingShaderPreBaseImplementation(renderer)
{
}

ShadowMappingShaderPreDefaultImplementation::~ShadowMappingShaderPreDefaultImplementation() {
}

const string ShadowMappingShaderPreDefaultImplementation::getId() {
	return "default";
}

void ShadowMappingShaderPreDefaultImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// load shadow mapping shaders
	//	pre render
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"pre_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"pre_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	// create shadow mapping render program
	//	pre
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	ShadowMappingShaderPreBaseImplementation::initialize();
}

