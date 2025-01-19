#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderTreeImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderTreeImplementation;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMapRenderShaderTreeImplementation::isSupported(RendererBackend* rendererBackend) {
	return true;
}

ShadowMapRenderShaderTreeImplementation::ShadowMapRenderShaderTreeImplementation(RendererBackend* rendererBackend): ShadowMapRenderShaderBaseImplementation(rendererBackend)
{
}

ShadowMapRenderShaderTreeImplementation::~ShadowMapRenderShaderTreeImplementation()
{
}

const string ShadowMapRenderShaderTreeImplementation::getId() {
	return "tree";
}

void ShadowMapRenderShaderTreeImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// load shadow mapping shaders
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"render_vertexshader.vert",
		"#define HAVE_TREE",
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
			"create_tree_transform_matrix.inc.glsl"
		)
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"render_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	// create shadow mapping render program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	ShadowMapRenderShaderBaseImplementation::initialize();

	//
	if (initialized == false) return;

	// uniforms
	uniformSpeed = rendererBackend->getProgramUniformLocation(programId, "speed");
}

void ShadowMapRenderShaderTreeImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
	const auto& shaderParameters = rendererBackend->getShaderParameters(contextIdx);
	if (uniformSpeed != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformSpeed, shaderParameters.getShaderParameter("speed").getFloatValue());
}
