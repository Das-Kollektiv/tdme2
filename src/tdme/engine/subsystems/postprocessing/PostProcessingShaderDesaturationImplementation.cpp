#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderDesaturationImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ShaderParameter.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderDesaturationImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::ShaderParameter;

bool PostProcessingShaderDesaturationImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->getShaderVersion() == "gl3";
}

PostProcessingShaderDesaturationImplementation::PostProcessingShaderDesaturationImplementation(RendererBackend* rendererBackend): PostProcessingShaderBaseImplementation(rendererBackend)
{
}

void PostProcessingShaderDesaturationImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"desaturation_fragmentshader.frag",
		Engine::is4K() == true?"#define HAVE_4K":""
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"desaturation_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	PostProcessingShaderBaseImplementation::initialize();

	//
	if (initialized == false) return;

	// uniforms
	uniformIntensity = rendererBackend->getProgramUniformLocation(programId, "intensity");

	// register shader
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_POSTPROCESSING,
		"desaturation",
		{
			{ "intensity", ShaderParameter(0.0f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
		}
	);
}

void PostProcessingShaderDesaturationImplementation::setShaderParameters(int contextIdx, Engine* engine) {
	if (uniformIntensity != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformIntensity, engine->getShaderParameter("desaturation", "intensity").getFloatValue());
}
