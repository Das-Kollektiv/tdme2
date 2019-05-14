#include <tdme/engine/subsystems/lighting/LightingShaderTerrainImplementation.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>

using std::to_string;
using std::string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderTerrainImplementation;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::fileio::textures::TextureReader;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;

bool LightingShaderTerrainImplementation::isSupported(Renderer* renderer) {
	return renderer->getShaderVersion() == "gl3";
}

LightingShaderTerrainImplementation::LightingShaderTerrainImplementation(Renderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

void LightingShaderTerrainImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	fragment shader
	renderLightingFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting",
		"render_fragmentshader.c",
		"#define HAVE_TERRAIN_SHADER\n#define HAVE_DEPTH_FOG\n\n"
	);
	if (renderLightingFragmentShaderId == 0) return;

	//	vertex shader
	renderLightingVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting",
		"render_vertexshader.c",
		"#define HAVE_TERRAIN_SHADER\n#define HAVE_DEPTH_FOG\n\n",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/lighting",
			"render_computevertex.inc.c"
		)
	);
	if (renderLightingVertexShaderId == 0) return;

	// create, attach and link program
	renderLightingProgramId = renderer->createProgram();
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingVertexShaderId);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingFragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
	if (initialized == false) return;

	//
	initialized = false;

	uniformGrasTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, "grasTextureUnit");
	if (uniformGrasTextureUnit == -1) return;

	uniformDirtTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, "dirtTextureUnit");
	if (uniformDirtTextureUnit == -1) return;

	uniformSnowTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, "snowTextureUnit");
	if (uniformSnowTextureUnit == -1) return;

	uniformStoneTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, "stoneTextureUnit");
	if (uniformStoneTextureUnit == -1) return;

	//
	grasTextureId = Engine::getInstance()->getTextureManager()->addTexture(TextureReader::read("resources/engine/textures", "terrain_gras.png"));
	dirtTextureId = Engine::getInstance()->getTextureManager()->addTexture(TextureReader::read("resources/engine/textures", "terrain_dirt.png"));
	snowTextureId = Engine::getInstance()->getTextureManager()->addTexture(TextureReader::read("resources/engine/textures", "terrain_snow.png"));
	stoneTextureId = Engine::getInstance()->getTextureManager()->addTexture(TextureReader::read("resources/engine/textures", "terrain_stone.png"));

	//
	initialized = true;
}

void LightingShaderTerrainImplementation::useProgram(Engine* engine, void* context) {
	LightingShaderBaseImplementation::useProgram(engine, context);

	//
	auto currentTextureUnit = renderer->getTextureUnit(context);
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_TERRAIN_GRAS);
	renderer->bindTexture(context, grasTextureId);
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_TERRAIN_DIRT);
	renderer->bindTexture(context, dirtTextureId);
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_TERRAIN_STONE);
	renderer->bindTexture(context, stoneTextureId);
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_TERRAIN_SNOW);
	renderer->bindTexture(context, snowTextureId);
	renderer->setTextureUnit(context, currentTextureUnit);

	//
	renderer->setProgramUniformInteger(context, uniformGrasTextureUnit, LightingShaderConstants::TEXTUREUNIT_TERRAIN_GRAS);
	renderer->setProgramUniformInteger(context, uniformDirtTextureUnit, LightingShaderConstants::TEXTUREUNIT_TERRAIN_DIRT);
	renderer->setProgramUniformInteger(context, uniformSnowTextureUnit, LightingShaderConstants::TEXTUREUNIT_TERRAIN_SNOW);
	renderer->setProgramUniformInteger(context, uniformStoneTextureUnit, LightingShaderConstants::TEXTUREUNIT_TERRAIN_STONE);
}

void LightingShaderTerrainImplementation::unUseProgram(void* context) {
	//
	auto currentTextureUnit = renderer->getTextureUnit(context);
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_TERRAIN_GRAS);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_TERRAIN_DIRT);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_TERRAIN_STONE);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_TERRAIN_SNOW);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, currentTextureUnit);

	//
	LightingShaderBaseImplementation::unUseProgram(context);
}
