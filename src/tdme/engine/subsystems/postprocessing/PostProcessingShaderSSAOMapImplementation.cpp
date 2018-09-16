#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOMapImplementation.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOMapImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::Engine;

PostProcessingShaderSSAOMapImplementation::PostProcessingShaderSSAOMapImplementation(GLRenderer* renderer): PostProcessingShaderBaseImplementation(renderer)
{
}

void PostProcessingShaderSSAOMapImplementation::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/postprocessing",
		"ssao_map_fragmentshader.c"
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/postprocessing",
		"ssao_map_vertexshader.c"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = renderer->createProgram();
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	PostProcessingShaderBaseImplementation::initialize();
}
