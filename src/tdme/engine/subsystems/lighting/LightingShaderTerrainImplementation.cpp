#include <tdme/engine/subsystems/lighting/LightingShaderTerrainImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Texture.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderTerrainImplementation;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::Texture;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool LightingShaderTerrainImplementation::isSupported(Renderer* renderer) {
	return true;
}

LightingShaderTerrainImplementation::LightingShaderTerrainImplementation(Renderer* renderer): LightingShaderBaseImplementation(renderer)
{
}

const string LightingShaderTerrainImplementation::getId() {
	return "terrain";
}

void LightingShaderTerrainImplementation::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.vert",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_TERRAIN_SHADER\n#define HAVE_DEPTH_FOG\n" + additionalDefinitions
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_fragmentshader.frag",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_TERRAIN_SHADER\n#define HAVE_DEPTH_FOG\n" + additionalDefinitions,
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/specular",
			"specular_lighting.inc.glsl"
		) + "\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"terrain.inc.glsl"
		) + "\n"
	);
	if (fragmentShaderId == 0) return;

	// create, attach and link program
	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
	if (initialized == false) return;

	//
	initialized = false;

	uniformModelMatrix = renderer->getProgramUniformLocation(programId, "modelMatrix");

	uniformGrasTextureUnit = renderer->getProgramUniformLocation(programId, "grasTextureUnit");
	if (uniformGrasTextureUnit == -1) return;

	uniformDirtTextureUnit = renderer->getProgramUniformLocation(programId, "dirtTextureUnit");
	if (uniformDirtTextureUnit == -1) return;

	uniformSnowTextureUnit = renderer->getProgramUniformLocation(programId, "snowTextureUnit");
	if (uniformSnowTextureUnit == -1) return;

	uniformStoneTextureUnit = renderer->getProgramUniformLocation(programId, "stoneTextureUnit");
	if (uniformStoneTextureUnit == -1) return;

	//
	loadTextures(".");

	//
	initialized = true;
}

void LightingShaderTerrainImplementation::registerShader() {
	// register shader
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_OBJECT,
		getId()
	);
}

void LightingShaderTerrainImplementation::useProgram(Engine* engine, int contextIdx) {
	LightingShaderBaseImplementation::useProgram(engine, contextIdx);

	//
	auto currentTextureUnit = renderer->getTextureUnit(contextIdx);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_GRAS);
	renderer->bindTexture(contextIdx, grasTextureId);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_DIRT);
	renderer->bindTexture(contextIdx, dirtTextureId);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_SNOW);
	renderer->bindTexture(contextIdx, snowTextureId);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_STONE);
	renderer->bindTexture(contextIdx, stoneTextureId);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_BRUSH);
	renderer->setTextureUnit(contextIdx, currentTextureUnit);

	//
	renderer->setProgramUniformInteger(contextIdx, uniformGrasTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_GRAS);
	renderer->setProgramUniformInteger(contextIdx, uniformDirtTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_DIRT);
	renderer->setProgramUniformInteger(contextIdx, uniformSnowTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_SNOW);
	renderer->setProgramUniformInteger(contextIdx, uniformStoneTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_STONE);
}

void LightingShaderTerrainImplementation::unUseProgram(int contextIdx) {
	//
	auto currentTextureUnit = renderer->getTextureUnit(contextIdx);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_GRAS);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_DIRT);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_SNOW);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_STONE);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, currentTextureUnit);

	//
	LightingShaderBaseImplementation::unUseProgram(contextIdx);
}

void LightingShaderTerrainImplementation::updateMatrices(Renderer* renderer, int contextIdx) {
	LightingShaderBaseImplementation::updateMatrices(renderer, contextIdx);
	if (uniformModelMatrix != -1) renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformModelMatrix, renderer->getModelViewMatrix().getArray());
}

void LightingShaderTerrainImplementation::updateShaderParameters(Renderer* renderer, int contextIdx) {
}

void LightingShaderTerrainImplementation::unloadTextures() {
	if (grasTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(grasTexture->getId());
		grasTexture->releaseReference();
		grasTexture = nullptr;
		grasTextureId = renderer->ID_NONE;
	}
	if (dirtTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(dirtTexture->getId());
		dirtTexture->releaseReference();
		dirtTexture = nullptr;
		dirtTextureId = renderer->ID_NONE;
	}
	if (snowTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(snowTexture->getId());
		snowTexture->releaseReference();
		snowTexture = nullptr;
		snowTextureId = renderer->ID_NONE;
	}
	if (stoneTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(stoneTexture->getId());
		stoneTexture->releaseReference();
		stoneTexture = nullptr;
		stoneTextureId = renderer->ID_NONE;
	}
}

void LightingShaderTerrainImplementation::loadTextures(const string& pathName) {
	//
	grasTextureId = Engine::getInstance()->getTextureManager()->addTexture(grasTexture = TextureReader::read(pathName + "/resources/engine/textures", "terrain_gras.png"), renderer->CONTEXTINDEX_DEFAULT);
	dirtTextureId = Engine::getInstance()->getTextureManager()->addTexture(dirtTexture = TextureReader::read(pathName + "/resources/engine/textures", "terrain_dirt.png"), renderer->CONTEXTINDEX_DEFAULT);
	snowTextureId = Engine::getInstance()->getTextureManager()->addTexture(snowTexture = TextureReader::read(pathName + "/resources/engine/textures", "terrain_snow.png"), renderer->CONTEXTINDEX_DEFAULT);
	stoneTextureId = Engine::getInstance()->getTextureManager()->addTexture(stoneTexture = TextureReader::read(pathName + "/resources/engine/textures", "terrain_stone.png"), renderer->CONTEXTINDEX_DEFAULT);
}
