#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderBaseImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;

bool PostProcessingShaderSSAOImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->getShaderVersion() == "gl3";
}

PostProcessingShaderSSAOImplementation::PostProcessingShaderSSAOImplementation(RendererBackend* rendererBackend): PostProcessingShaderBaseImplementation(rendererBackend)
{
}

void PostProcessingShaderSSAOImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"ssao_fragmentshader.frag",
		Engine::is4K() == true?"#define HAVE_4K":""
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"ssao_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	PostProcessingShaderBaseImplementation::initialize();

	// register shader
	if (initialized == false) return;

	//
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_POSTPROCESSING,
		"ssao",
		{
			{ "strength", ShaderParameter(0.25f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			{ "area", ShaderParameter(0.0075f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			{ "falloff", ShaderParameter(0.1f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			{ "radius", ShaderParameter(0.02f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			{ "samples", ShaderParameter(8), ShaderParameter(1), ShaderParameter(16), ShaderParameter(1) }

		}
	);
}

void PostProcessingShaderSSAOImplementation::setShaderParameters(int contextIdx, Engine* engine) {
}
