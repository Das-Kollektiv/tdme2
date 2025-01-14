#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOImplementation;
using tdme::engine::subsystems::postprocessing::PostProcessingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

bool PostProcessingShaderSSAOImplementation::isSupported(Renderer* renderer) {
	return renderer->getShaderVersion() == "gl3";
}

PostProcessingShaderSSAOImplementation::PostProcessingShaderSSAOImplementation(Renderer* renderer): PostProcessingShaderBaseImplementation(renderer)
{
}

void PostProcessingShaderSSAOImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"ssao_fragmentshader.frag",
		Engine::is4K() == true?"#define HAVE_4K":""
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"ssao_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

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
