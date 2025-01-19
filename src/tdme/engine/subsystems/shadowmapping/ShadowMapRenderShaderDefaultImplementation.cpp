#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderDefaultImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderDefaultImplementation;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMapRenderShaderDefaultImplementation::isSupported(RendererBackend* rendererBackend) {
	return true;
}

ShadowMapRenderShaderDefaultImplementation::ShadowMapRenderShaderDefaultImplementation(RendererBackend* rendererBackend): ShadowMapRenderShaderBaseImplementation(rendererBackend)
{
}

ShadowMapRenderShaderDefaultImplementation::~ShadowMapRenderShaderDefaultImplementation()
{
}

const string ShadowMapRenderShaderDefaultImplementation::getId() {
	return "default";
}

void ShadowMapRenderShaderDefaultImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// load shadow mapping shaders
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"render_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	// create shadow mapping render program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	ShadowMapRenderShaderBaseImplementation::initialize();
}

void ShadowMapRenderShaderDefaultImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
}
