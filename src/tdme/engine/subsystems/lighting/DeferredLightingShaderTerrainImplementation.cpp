#include <tdme/engine/subsystems/lighting/DeferredLightingShaderTerrainImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Texture.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::to_string;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::lighting::DeferredLightingShaderTerrainImplementation;
using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::Texture;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

bool DeferredLightingShaderTerrainImplementation::isSupported(RendererBackend* rendererBackend) {
	return rendererBackend->isDeferredShadingAvailable() == true;
}

DeferredLightingShaderTerrainImplementation::DeferredLightingShaderTerrainImplementation(RendererBackend* rendererBackend): LightingShaderBaseImplementation(rendererBackend)
{
}

const string DeferredLightingShaderTerrainImplementation::getId() {
	return "defer_terrain";
}

void DeferredLightingShaderTerrainImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// lighting
	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"render_vertexshader.vert",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_TERRAIN_SHADER\n#define HAVE_DEPTH_FOG\n" + additionalDefinitions
	);
	if (vertexShaderId == 0) return;

	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lighting/specular",
		"defer_fragmentshader.frag",
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define HAVE_TERRAIN_SHADER\n#define HAVE_DEPTH_FOG\n" + additionalDefinitions,
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions",
			"terrain.inc.glsl"
		) + "\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/specular",
			"specular_lighting.inc.glsl"
		) + "\n"
	);
	if (fragmentShaderId == 0) return;

	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);

	//
	LightingShaderBaseImplementation::initialize();
	if (initialized == false) return;

	//
	initialized = false;

	uniformModelMatrix = rendererBackend->getProgramUniformLocation(programId, "modelMatrix");

	uniformGrasTextureUnit = rendererBackend->getProgramUniformLocation(programId, "grasTextureUnit");
	if (uniformGrasTextureUnit == -1) return;

	uniformDirtTextureUnit = rendererBackend->getProgramUniformLocation(programId, "dirtTextureUnit");
	if (uniformDirtTextureUnit == -1) return;

	uniformSnowTextureUnit = rendererBackend->getProgramUniformLocation(programId, "snowTextureUnit");
	if (uniformSnowTextureUnit == -1) return;

	uniformStoneTextureUnit = rendererBackend->getProgramUniformLocation(programId, "stoneTextureUnit");
	if (uniformStoneTextureUnit == -1) return;

	//
	loadTextures(".");

	//
	initialized = true;
}

void DeferredLightingShaderTerrainImplementation::registerShader() {
}

void DeferredLightingShaderTerrainImplementation::useProgram(Engine* engine, int contextIdx) {
	LightingShaderBaseImplementation::useProgram(engine, contextIdx);

	//
	auto currentTextureUnit = rendererBackend->getTextureUnit(contextIdx);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_GRAS);
	rendererBackend->bindTexture(contextIdx, grasTextureId);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_DIRT);
	rendererBackend->bindTexture(contextIdx, dirtTextureId);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_SNOW);
	rendererBackend->bindTexture(contextIdx, snowTextureId);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_STONE);
	rendererBackend->bindTexture(contextIdx, stoneTextureId);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_BRUSH);
	rendererBackend->setTextureUnit(contextIdx, currentTextureUnit);

	//
	rendererBackend->setProgramUniformInteger(contextIdx, uniformGrasTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_GRAS);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDirtTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_DIRT);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformSnowTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_SNOW);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformStoneTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_STONE);
}

void DeferredLightingShaderTerrainImplementation::unUseProgram(int contextIdx) {
	//
	auto currentTextureUnit = rendererBackend->getTextureUnit(contextIdx);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_GRAS);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_DIRT);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_SNOW);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_STONE);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, currentTextureUnit);

	//
	LightingShaderBaseImplementation::unUseProgram(contextIdx);
}

void DeferredLightingShaderTerrainImplementation::updateMatrices(RendererBackend* rendererBackend, int contextIdx) {
	LightingShaderBaseImplementation::updateMatrices(rendererBackend, contextIdx);
	if (uniformModelMatrix != -1) rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformModelMatrix, rendererBackend->getModelViewMatrix().getArray());
}

void DeferredLightingShaderTerrainImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
}

void DeferredLightingShaderTerrainImplementation::unloadTextures() {
	if (grasTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(grasTexture->getId());
		grasTexture->releaseReference();
		grasTexture = nullptr;
		grasTextureId = rendererBackend->ID_NONE;
	}
	if (dirtTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(dirtTexture->getId());
		dirtTexture->releaseReference();
		dirtTexture = nullptr;
		dirtTextureId = rendererBackend->ID_NONE;
	}
	if (snowTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(snowTexture->getId());
		snowTexture->releaseReference();
		snowTexture = nullptr;
		snowTextureId = rendererBackend->ID_NONE;
	}
	if (stoneTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(stoneTexture->getId());
		stoneTexture->releaseReference();
		stoneTexture = nullptr;
		stoneTextureId = rendererBackend->ID_NONE;
	}
}

void DeferredLightingShaderTerrainImplementation::loadTextures(const string& pathName) {
	//
	grasTextureId = Engine::getInstance()->getTextureManager()->addTexture(grasTexture = TextureReader::read(pathName + "/resources/engine/textures", "terrain_gras.png"), rendererBackend->CONTEXTINDEX_DEFAULT);
	dirtTextureId = Engine::getInstance()->getTextureManager()->addTexture(dirtTexture = TextureReader::read(pathName + "/resources/engine/textures", "terrain_dirt.png"), rendererBackend->CONTEXTINDEX_DEFAULT);
	snowTextureId = Engine::getInstance()->getTextureManager()->addTexture(snowTexture = TextureReader::read(pathName + "/resources/engine/textures", "terrain_snow.png"), rendererBackend->CONTEXTINDEX_DEFAULT);
	stoneTextureId = Engine::getInstance()->getTextureManager()->addTexture(stoneTexture = TextureReader::read(pathName + "/resources/engine/textures", "terrain_stone.png"), rendererBackend->CONTEXTINDEX_DEFAULT);
}
