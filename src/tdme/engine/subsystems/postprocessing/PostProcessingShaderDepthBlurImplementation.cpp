#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderDepthBlurImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderDepthBlurImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;

bool PostProcessingShaderDepthBlurImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->getShaderVersion() == "gl3";
}

PostProcessingShaderDepthBlurImplementation::PostProcessingShaderDepthBlurImplementation(RendererBackend* rendererBackend): PostProcessingShaderBaseImplementation(rendererBackend)
{
}

void PostProcessingShaderDepthBlurImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"blur_fragmentshader.frag",
		Engine::is4K() == true?"#define HAVE_4K":""
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"blur_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

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
