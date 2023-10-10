#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderDepthBlurImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderDepthBlurImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

bool PostProcessingShaderDepthBlurImplementation::isSupported(Renderer* renderer) {
	return renderer->getShaderVersion() == "gl3";
}

PostProcessingShaderDepthBlurImplementation::PostProcessingShaderDepthBlurImplementation(Renderer* renderer): PostProcessingShaderBaseImplementation(renderer)
{
}

void PostProcessingShaderDepthBlurImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"blur_fragmentshader.frag",
		Engine::is4K() == true?"#define HAVE_4K":""
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"blur_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	PostProcessingShaderBaseImplementation::initialize();

	// register shader
	if (initialized == true) {
		Engine::registerShader(
			Engine::ShaderType::SHADERTYPE_POSTPROCESSING,
			"depth_blur"
		);
	}
}

void PostProcessingShaderDepthBlurImplementation::setShaderParameters(int contextIdx, Engine* engine) {
}
