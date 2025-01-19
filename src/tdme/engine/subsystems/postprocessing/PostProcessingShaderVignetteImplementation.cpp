#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderVignetteImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/math/Vector3.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderVignetteImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::ShaderParameter;
using tdme::math::Vector3;

bool PostProcessingShaderVignetteImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->getShaderVersion() == "gl3";
}

PostProcessingShaderVignetteImplementation::PostProcessingShaderVignetteImplementation(RendererBackend* rendererBackend): PostProcessingShaderBaseImplementation(rendererBackend)
{
}

void PostProcessingShaderVignetteImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"vignette_fragmentshader.frag",
		Engine::is4K() == true?"#define HAVE_4K":""
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"vignette_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	PostProcessingShaderBaseImplementation::initialize();

	// uniforms
	uniformIntensity = rendererBackend->getProgramUniformLocation(programId, "intensity");
	uniformBorderColor = rendererBackend->getProgramUniformLocation(programId, "borderColor");

	//
	if (initialized == false) return;

	// register shader
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_POSTPROCESSING,
		"vignette",
		{
			{ "intensity", ShaderParameter(0.0f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			{ "borderColor", ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.05f, 0.05f, 0.05f, 0.0f)) }
		}
	);
}

void PostProcessingShaderVignetteImplementation::setShaderParameters(int contextIdx, Engine* engine) {
	if (uniformIntensity != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformIntensity, engine->getShaderParameter("vignette", "intensity").getFloatValue());
	if (uniformBorderColor != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformBorderColor, engine->getShaderParameter("vignette", "borderColor").getColor3ValueArray());
}
