#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderFoliageImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderFoliageImplementation;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMapRenderShaderFoliageImplementation::isSupported(Renderer* renderer) {
	return true;
}

ShadowMapRenderShaderFoliageImplementation::ShadowMapRenderShaderFoliageImplementation(Renderer* renderer): ShadowMapRenderShaderBaseImplementation(renderer)
{
}

ShadowMapRenderShaderFoliageImplementation::~ShadowMapRenderShaderFoliageImplementation()
{
}

const string ShadowMapRenderShaderFoliageImplementation::getId() {
	return "foliage";
}

void ShadowMapRenderShaderFoliageImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// load shadow mapping shaders
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"render_vertexshader.vert",
		"#define HAVE_FOLIAGE",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_rotation_matrix.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_translation_matrix.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"create_foliage_transform_matrix.inc.glsl"
		)
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"render_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	// create shadow mapping render program
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	ShadowMapRenderShaderBaseImplementation::initialize();

	//
	if (initialized == false) return;

	//
	if (initialized == false) return;

	// uniforms
	uniformSpeed = renderer->getProgramUniformLocation(programId, "speed");
	uniformAmplitudeDefault = renderer->getProgramUniformLocation(programId, "amplitudeDefault");
	uniformAmplitudeMax = renderer->getProgramUniformLocation(programId, "amplitudeMax");
}

void ShadowMapRenderShaderFoliageImplementation::updateShaderParameters(Renderer* renderer, int contextIdx) {
	auto& shaderParameters = renderer->getShaderParameters(contextIdx);
	if (uniformSpeed != -1) renderer->setProgramUniformFloat(contextIdx, uniformSpeed, shaderParameters.getShaderParameter("speed").getFloatValue());
	if (uniformAmplitudeDefault != -1) renderer->setProgramUniformFloat(contextIdx, uniformAmplitudeDefault, shaderParameters.getShaderParameter("amplitudeDefault").getFloatValue());
	if (uniformAmplitudeMax != -1) renderer->setProgramUniformFloat(contextIdx, uniformAmplitudeMax, shaderParameters.getShaderParameter("amplitudeMax").getFloatValue());
}
