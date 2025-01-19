#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderDefaultImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;

bool PostProcessingShaderDefaultImplementation::isSupported(RendererBackend* rendererBackend) {
	return true;
}

PostProcessingShaderDefaultImplementation::PostProcessingShaderDefaultImplementation(RendererBackend* rendererBackend): PostProcessingShaderBaseImplementation(rendererBackend)
{
}

void PostProcessingShaderDefaultImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"default_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"default_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	PostProcessingShaderBaseImplementation::initialize();
}

void PostProcessingShaderDefaultImplementation::setShaderParameters(int contextIdx, Engine* engine) {
}
