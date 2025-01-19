#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderTreeImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderTreeImplementation;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool ShadowMapCreationShaderTreeImplementation::isSupported(RendererBackend* rendererBackend) {
	return true;
}

ShadowMapCreationShaderTreeImplementation::ShadowMapCreationShaderTreeImplementation(RendererBackend* rendererBackend): ShadowMapCreationShaderBaseImplementation(rendererBackend)
{
}

ShadowMapCreationShaderTreeImplementation::~ShadowMapCreationShaderTreeImplementation() {
}

const string ShadowMapCreationShaderTreeImplementation::getId() {
	return "tree";
}

void ShadowMapCreationShaderTreeImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// load shadow map creation shaders
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/shadowmapping",
		"creation_vertexshader.vert",
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
		"creation_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	// create shadow map creation shader render program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	ShadowMapCreationShaderBaseImplementation::initialize();

	//
	if (initialized == false) return;

	// uniforms
	uniformSpeed = rendererBackend->getProgramUniformLocation(programId, "speed");
}

void ShadowMapCreationShaderTreeImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
	const auto& shaderParameters = rendererBackend->getShaderParameters(contextIdx);
	if (uniformSpeed != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformSpeed, shaderParameters.getShaderParameter("speed").getFloatValue());
}
