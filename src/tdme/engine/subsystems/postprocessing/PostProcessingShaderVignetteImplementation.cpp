#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderVignetteImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/math/Vector3.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderVignetteImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::ShaderParameter;
using tdme::math::Vector3;

bool PostProcessingShaderVignetteImplementation::isSupported(Renderer* renderer) {
	return renderer->getShaderVersion() == "gl3";
}

PostProcessingShaderVignetteImplementation::PostProcessingShaderVignetteImplementation(Renderer* renderer): PostProcessingShaderBaseImplementation(renderer)
{
}

void PostProcessingShaderVignetteImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"vignette_fragmentshader.frag",
		Engine::is4K() == true?"#define HAVE_4K":""
	);
	if (fragmentShaderId == 0) return;

	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/postprocessing",
		"vignette_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	// create, attach and link program
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	PostProcessingShaderBaseImplementation::initialize();

	// uniforms
	uniformIntensity = renderer->getProgramUniformLocation(programId, "intensity");
	uniformBorderColor = renderer->getProgramUniformLocation(programId, "borderColor");

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
	if (uniformIntensity != -1) renderer->setProgramUniformFloat(contextIdx, uniformIntensity, engine->getShaderParameter("vignette", "intensity").getFloatValue());
	if (uniformBorderColor != -1) renderer->setProgramUniformFloatVec3(contextIdx, uniformBorderColor, engine->getShaderParameter("vignette", "borderColor").getColor3ValueArray());
}
