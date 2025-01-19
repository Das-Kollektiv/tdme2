#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderDefaultImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderDefaultImplementation;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMapCreationShaderDefaultImplementation::isSupported(RendererBackend* rendererBackend) {
	return true;
}

ShadowMapCreationShaderDefaultImplementation::ShadowMapCreationShaderDefaultImplementation(RendererBackend* rendererBackend): ShadowMapCreationShaderBaseImplementation(rendererBackend)
{
}

ShadowMapCreationShaderDefaultImplementation::~ShadowMapCreationShaderDefaultImplementation() {
}

const string ShadowMapCreationShaderDefaultImplementation::getId() {
	return "default";
}

void ShadowMapCreationShaderDefaultImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// load shadow mapping creation shaders
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"creation_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"creation_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	// create shadow map creation program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	ShadowMapCreationShaderBaseImplementation::initialize();
}

void ShadowMapCreationShaderDefaultImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
}
