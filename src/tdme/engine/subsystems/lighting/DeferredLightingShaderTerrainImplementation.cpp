#include <tdme/engine/subsystems/lighting/DeferredLightingShaderTerrainImplementation.h>

#include <string>

#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>

using std::string;
using std::to_string;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::DeferredLightingShaderTerrainImplementation;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

bool DeferredLightingShaderTerrainImplementation::isSupported(Renderer* renderer) {
	return renderer->isDeferredShadingAvailable() == true;
}

DeferredLightingShaderTerrainImplementation::DeferredLightingShaderTerrainImplementation(Renderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

const string DeferredLightingShaderTerrainImplementation::getId() {
	return "defer_terrain";
}

void DeferredLightingShaderTerrainImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	fragment shader
	renderLightingFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"defer_fragmentshader.frag",
		"#define HAVE_TERRAIN_SHADER\n#define HAVE_DEPTH_FOG"
	);
	if (renderLightingFragmentShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.vert",
		"#define HAVE_TERRAIN_SHADER\n#define HAVE_DEPTH_FOG"
	);
	if (renderLightingVertexShaderId == 0) return;

	// create, attach and link program
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, renderLightingVertexShaderId);
	renderer->attachShaderToProgram(programId, renderLightingFragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
}

void DeferredLightingShaderTerrainImplementation::registerShader() {
}

void DeferredLightingShaderTerrainImplementation::updateShaderParameters(Renderer* renderer, void* context) {
}
