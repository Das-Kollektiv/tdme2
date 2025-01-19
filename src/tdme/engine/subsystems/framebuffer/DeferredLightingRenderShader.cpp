#include <tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/framebuffer/BRDFLUTShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/GeometryBuffer.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/SimpleTextureAtlas.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::framebuffer::BRDFLUTShader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::Engine;
using tdme::engine::GeometryBuffer;
using tdme::math::Math;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::SimpleTextureAtlas;

DeferredLightingRenderShader::DeferredLightingRenderShader(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
	initialized = false;
	isRunning = false;
}

DeferredLightingRenderShader::~DeferredLightingRenderShader()
{
}

bool DeferredLightingRenderShader::isInitialized()
{
	return initialized;
}

void DeferredLightingRenderShader::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert",
		"#define HAVE_DEPTH_FOG"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"deferred_lighting_fragmentshader.frag",
		string() +
		"#define HAVE_DEPTH_FOG\n" +
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n#define USE_IBL\n" +
		"#define DECAL_COUNT " + to_string(DECAL_COUNT) + "\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/specular",
			"specular_lighting.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"tonemapping.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"functions.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"pbr_lighting.inc.glsl"
		) +
		"\n\n"
	);
	if (fragmentShaderId == 0) return;

	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 2, "inTextureUV");
	}
	if (rendererBackend->linkProgram(programId) == false) return;

	// uniforms
	//	geometry buffers
	uniformGeometryBufferTextureId1 = rendererBackend->getProgramUniformLocation(programId, "geometryBufferTextureId1");
	if (uniformGeometryBufferTextureId1 == -1) return;
	uniformGeometryBufferTextureId2 = rendererBackend->getProgramUniformLocation(programId, "geometryBufferTextureId2");
	if (uniformGeometryBufferTextureId2 == -1) return;
	uniformGeometryBufferTextureId3 = rendererBackend->getProgramUniformLocation(programId, "geometryBufferTextureId3");
	if (uniformGeometryBufferTextureId3 == -1) return;
	//	color buffers
	uniformColorBufferTextureUnit1 = rendererBackend->getProgramUniformLocation(programId, "colorBufferTextureUnit1");
	if (uniformColorBufferTextureUnit1 == -1) return;
	uniformColorBufferTextureUnit2 = rendererBackend->getProgramUniformLocation(programId, "colorBufferTextureUnit2");
	if (uniformColorBufferTextureUnit2 == -1) return;
	uniformColorBufferTextureUnit3 = rendererBackend->getProgramUniformLocation(programId, "colorBufferTextureUnit3");
	if (uniformColorBufferTextureUnit3 == -1) return;
	uniformColorBufferTextureUnit4 = rendererBackend->getProgramUniformLocation(programId, "colorBufferTextureUnit4");
	if (uniformColorBufferTextureUnit4 == -1) return;
	uniformColorBufferTextureUnit5 = rendererBackend->getProgramUniformLocation(programId, "colorBufferTextureUnit5");
	if (uniformColorBufferTextureUnit5 == -1) return;
	//	depth buffer
	uniformDepthBufferTextureUnit = rendererBackend->getProgramUniformLocation(programId, "depthBufferTextureUnit");
	if (uniformDepthBufferTextureUnit == -1) return;

	//	specular lights
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformSpecularLightEnabled[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) +"].enabled");
		if (uniformSpecularLightEnabled[i] == -1) return;
		uniformSpecularLightAmbient[i] = rendererBackend->getProgramUniformLocation(programId,"specularLights[" + to_string(i) + "].ambient");
		if (uniformSpecularLightAmbient[i] == -1) return;
		uniformSpecularLightDiffuse[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].diffuse");
		if (uniformSpecularLightDiffuse[i] == -1) return;
		uniformSpecularLightSpecular[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].specular");
		if (uniformSpecularLightSpecular[i] == -1) return;
		uniformSpecularLightPosition[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].position");
		if (uniformSpecularLightPosition[i] == -1) return;
		uniformSpecularLightSpotDirection[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotDirection");
		if (uniformSpecularLightSpotDirection[i] == -1) return;
		uniformSpecularLightSpotExponent[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotExponent");
		if (uniformSpecularLightSpotExponent[i] == -1) return;
		uniformSpecularLightSpotCosCutoff[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotCosCutoff");
		if (uniformSpecularLightSpotCosCutoff[i] == -1) return;
		uniformSpecularLightConstantAttenuation[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].constantAttenuation");
		if (uniformSpecularLightConstantAttenuation[i] == -1) return;
		uniformSpecularLightLinearAttenuation[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].linearAttenuation");
		if (uniformSpecularLightLinearAttenuation[i] == -1) return;
		uniformSpecularLightQuadraticAttenuation[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].quadraticAttenuation");
		if (uniformSpecularLightQuadraticAttenuation[i] == -1) return;
		uniformSpecularLightRadius[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].radius");
		if (uniformSpecularLightRadius[i] == -1) return;
	}

	//	camera matrix
	uniformCameraMatrix = rendererBackend->getProgramUniformLocation(programId, "cameraMatrix");
	if (uniformCameraMatrix == -1) return;

	// projection * view inverted
	uniformProjectionCameraMatrixInverted = rendererBackend->getProgramUniformLocation(programId, "projectionCameraMatrixInverted");
	if (uniformProjectionCameraMatrixInverted == -1) return;

	// PBR
	uniformCamera = rendererBackend->getProgramUniformLocation(programId, "u_Camera");
	if (uniformCamera == -1) return;

	//	lights
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformPBRLightEnabled[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].enabled");
		if (uniformPBRLightEnabled[i] == -1) return;
		//uniformLightAmbient[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].ambient");
		//if (uniformLightAmbient[i] == -1) return;
		uniformPBRLightDirection[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].direction");
		if (uniformPBRLightDirection[i] == -1) return;
		uniformPBRLightRange[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].range");
		if (uniformPBRLightRange[i] == -1) return;
		uniformPBRLightColor[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].color");
		if (uniformPBRLightColor[i] == -1) return;
		uniformPBRLightIntensity[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].intensity");
		if (uniformPBRLightIntensity[i] == -1) return;
		uniformPBRLightPosition[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].position");
		if (uniformPBRLightPosition[i] == -1) return;
		uniformPBRLightInnerConeCos[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].innerConeCos");
		if (uniformPBRLightInnerConeCos[i] == -1) return;
		uniformPBRLightOuterConeCos[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].outerConeCos");
		if (uniformPBRLightOuterConeCos[i] == -1) return;
		uniformPBRLightType[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].type");
		if (uniformPBRLightType[i] == -1) return;
	}

	// IBL
	uniformDiffuseEnvSampler = rendererBackend->getProgramUniformLocation(programId, "u_DiffuseEnvSampler");
	if (uniformDiffuseEnvSampler == -1) return;
	uniformSpecularEnvSampler = rendererBackend->getProgramUniformLocation(programId, "u_SpecularEnvSampler");
	if (uniformSpecularEnvSampler == -1) return;
	uniformbrdfLUT = rendererBackend->getProgramUniformLocation(programId, "u_brdfLUT");
	if (uniformbrdfLUT == -1) return;

	//
	string environmentType = "studio_grey";
	textureDiffuseEnvSampler =
		Engine::getInstance()->getTextureManager()->addCubeMapTexture(
			"pbr-environment-diffuse",
			envDiffuseTextures[0] = TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_left.png"),
			envDiffuseTextures[1] = TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_right.png"),
			envDiffuseTextures[2] = TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_top.png"),
			envDiffuseTextures[3] = TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_bottom.png"),
			envDiffuseTextures[4] = TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_front.png"),
			envDiffuseTextures[5] = TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_back.png"),
			rendererBackend->CONTEXTINDEX_DEFAULT
		);
	textureSpecularEnvSampler =
		Engine::getInstance()->getTextureManager()->addCubeMapTexture(
			"pbr-environment-specular",
			envSpecularTextures[0] = TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_left.png"),
			envSpecularTextures[1] = TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_right.png"),
			envSpecularTextures[2] = TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_top.png"),
			envSpecularTextures[3] = TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_bottom.png"),
			envSpecularTextures[4] = TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_front.png"),
			envSpecularTextures[5] = TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_back.png"),
			rendererBackend->CONTEXTINDEX_DEFAULT
		);
	texturebrdfLUT = Engine::getBRDFLUTShader()->getColorTextureId();

	// 	decals
	uniformDecalCount = rendererBackend->getProgramUniformLocation(programId, "decalCount");
	if (uniformDecalCount == -1) return;

	uniformDecalsTextureUnit = rendererBackend->getProgramUniformLocation(programId, "decalsTextureUnit");
	if (uniformDecalsTextureUnit == -1) return;

	//
	for (auto i = 0; i < DECAL_COUNT; i++) {
		uniformDecalWorldToDecalSpace[i] = rendererBackend->getProgramUniformLocation(programId, "decals[" + to_string(i) + "].worldToDecalSpace");
		if (uniformDecalWorldToDecalSpace[i] == -1) return;
		uniformDecalAtlasTextureOrientation[i] = rendererBackend->getProgramUniformLocation(programId, "decals[" + to_string(i) + "].texture.orientation");
		if (uniformDecalAtlasTextureOrientation[i] == -1) return;
		uniformDecalAtlasTexturePosition[i] = rendererBackend->getProgramUniformLocation(programId, "decals[" + to_string(i) + "].texture.position");
		if (uniformDecalAtlasTexturePosition[i] == -1) return;
		uniformDecalAtlasTextureDimension[i] = rendererBackend->getProgramUniformLocation(programId, "decals[" + to_string(i) + "].texture.dimension");
		if (uniformDecalAtlasTextureDimension[i] == -1) return;
		uniformDecalSpriteSheetDimension[i] = rendererBackend->getProgramUniformLocation(programId, "decals[" + to_string(i) + "].spriteSheetDimension");
		if (uniformDecalSpriteSheetDimension[i] == -1) return;
		uniformDecalSpriteIndex[i] = rendererBackend->getProgramUniformLocation(programId, "decals[" + to_string(i) + "].spriteIndex");
		if (uniformDecalSpriteIndex[i] == -1) return;
	}

	//
	initialized = true;
}

void DeferredLightingRenderShader::dispose() {
	//
	for (auto i = 0; i < envDiffuseTextures.size(); i++) {
		if (envDiffuseTextures[i] == nullptr) continue;
		envDiffuseTextures[i]->releaseReference();
		envDiffuseTextures[i] = nullptr;
	}
	//
	for (auto i = 0; i < envSpecularTextures.size(); i++) {
		if (envSpecularTextures[i] == nullptr) continue;
		envSpecularTextures[i]->releaseReference();
		envSpecularTextures[i] = nullptr;
	}
	//
	Engine::getInstance()->getTextureManager()->removeTexture("pbr-environment-diffuse");
	Engine::getInstance()->getTextureManager()->removeTexture("pbr-environment-specular");
}

void DeferredLightingRenderShader::useProgram(Engine* engine, vector<Decal*>& decalEntities)
{
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformGeometryBufferTextureId1, 0);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformGeometryBufferTextureId2, 1);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformGeometryBufferTextureId3, 2);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit1, 3);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit2, 4);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit3, 5);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit4, 6);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit5, 7);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDepthBufferTextureUnit, 8);

	// Matrices
	rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformCameraMatrix, engine->getCamera()->getCameraMatrix().getArray());
	rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformProjectionCameraMatrixInverted, engine->getCamera()->getModelViewProjectionInvertedMatrix().getArray());

	// Specular
	for (auto lightId = 0; lightId < Engine::LIGHTS_MAX; lightId++) {
		auto light = engine->getLightAt(lightId);
		rendererBackend->setProgramUniformInteger(contextIdx, uniformSpecularLightEnabled[lightId], light->isEnabled() == true?1:0);
		if (light->isEnabled() == false) continue;
		rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformSpecularLightAmbient[lightId], light->getAmbient().getArray());
		rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformSpecularLightDiffuse[lightId], light->getDiffuse().getArray());
		rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformSpecularLightSpecular[lightId], light->getSpecular().getArray());
		rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformSpecularLightPosition[lightId], light->getPosition().getArray());
		rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformSpecularLightSpotDirection[lightId], light->getSpotDirection().getArray());
		rendererBackend->setProgramUniformFloat(contextIdx, uniformSpecularLightSpotExponent[lightId], light->getSpotExponent());
		rendererBackend->setProgramUniformFloat(contextIdx, uniformSpecularLightSpotCosCutoff[lightId], static_cast<float>(Math::cos(Math::PI / 180.0f * light->getSpotCutOff())));
		rendererBackend->setProgramUniformFloat(contextIdx, uniformSpecularLightConstantAttenuation[lightId], light->getConstantAttenuation());
		rendererBackend->setProgramUniformFloat(contextIdx, uniformSpecularLightLinearAttenuation[lightId], light->getLinearAttenuation());
		rendererBackend->setProgramUniformFloat(contextIdx, uniformSpecularLightQuadraticAttenuation[lightId], light->getQuadraticAttenuation());
		rendererBackend->setProgramUniformFloat(contextIdx, uniformSpecularLightRadius[lightId], light->getRadius());
	}

	// PBR
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformCamera, rendererBackend->getCameraPosition().getArray());

	//	IBL
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseEnvSampler, 9);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformSpecularEnvSampler, 10);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformbrdfLUT, 11);
	rendererBackend->setTextureUnit(contextIdx, 9);
	rendererBackend->bindCubeMapTexture(contextIdx, textureDiffuseEnvSampler);
	rendererBackend->setTextureUnit(contextIdx, 10);
	rendererBackend->bindCubeMapTexture(contextIdx, textureSpecularEnvSampler);
	rendererBackend->setTextureUnit(contextIdx, 11);
	rendererBackend->bindTexture(contextIdx, texturebrdfLUT);

	//	lights
	for (auto lightId = 0; lightId < Engine::LIGHTS_MAX; lightId++) {
		auto light = engine->getLightAt(lightId);
		if (uniformPBRLightEnabled[lightId] != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformPBRLightEnabled[lightId], light->isEnabled() == true?1:0);
		if (light->isEnabled() == false) continue;
		const auto& ambient = light->getAmbient();
		const auto& diffuse = light->getDiffuse();
		const auto& position = light->getPosition();
		// rendererBackend->setProgramUniformFloatVec3(context, uniformLightAmbient[lightId], {{ ambient[0], ambient[1], ambient[2] }});
		rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformPBRLightDirection[lightId], light->getSpotDirection().getArray());
		rendererBackend->setProgramUniformFloat(contextIdx, uniformPBRLightRange[lightId], 0.0f);
		rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformPBRLightColor[lightId], {{ diffuse[0], diffuse[1], diffuse[2] }});
		rendererBackend->setProgramUniformFloat(contextIdx, uniformPBRLightIntensity[lightId], 1.0f);
		rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformPBRLightPosition[lightId],{{ position[0], position[1], position[2] }});
		if (uniformPBRLightType[lightId] != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformPBRLightType[lightId], 0);
	}

	// decals
	auto& decalsTextureAtlas = engine->getDecalsTextureAtlas();
	if (decalsTextureAtlas.isRequiringUpdate() == true) {
		decalsTextureAtlas.update();
		if (decalsTextureAtlas.getAtlasTexture() != nullptr) {
			if (decalsTextureAtlasTextureId == rendererBackend->ID_NONE) decalsTextureAtlasTextureId = rendererBackend->createTexture();
			rendererBackend->setTextureUnit(contextIdx, 12);
			rendererBackend->bindTexture(contextIdx, decalsTextureAtlasTextureId);
			rendererBackend->uploadTexture(contextIdx, decalsTextureAtlas.getAtlasTexture());
		} else
		if (decalsTextureAtlasTextureId != rendererBackend->ID_NONE) {
			rendererBackend->disposeTexture(decalsTextureAtlasTextureId);
			decalsTextureAtlasTextureId = rendererBackend->ID_NONE;
		}
	}
	auto decalsTextureAtlasTexture = decalsTextureAtlas.getAtlasTexture();
	if (decalsTextureAtlasTexture != nullptr) {
		auto decalCount = Math::min(DECAL_COUNT, decalEntities.size());
		rendererBackend->setProgramUniformInteger(contextIdx, uniformDecalCount, decalCount);
		if (decalCount > 0) {
			auto decalsTextureAtlasTextureWidth = decalsTextureAtlasTexture->getTextureWidth();
			auto decalsTextureAtlasTextureHeight = decalsTextureAtlasTexture->getTextureHeight();
			rendererBackend->setProgramUniformInteger(contextIdx, uniformDecalsTextureUnit, 12);
			rendererBackend->setTextureUnit(contextIdx, 12);
			rendererBackend->bindTexture(contextIdx, decalsTextureAtlasTextureId);
			for (auto i = 0; i < decalCount && i < DECAL_COUNT; i++) {
				auto decalObject = decalEntities[i];
				auto atlasTextureIdx = decalsTextureAtlas.getTextureIdx(decalObject->getDecalTexture());
				if (atlasTextureIdx == -1) continue;
				auto atlasTexture = decalsTextureAtlas.getAtlasTexture(atlasTextureIdx);
				if (atlasTexture == nullptr) continue;
				rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformDecalWorldToDecalSpace[i], decalObject->getWorldToDecalSpaceMatrix().getArray());
				rendererBackend->setProgramUniformInteger(contextIdx, uniformDecalAtlasTextureOrientation[i], atlasTexture->orientation);
				rendererBackend->setProgramUniformFloatVec2(
					contextIdx,
					uniformDecalAtlasTexturePosition[i],
					{
						static_cast<float>(atlasTexture->left) / static_cast<float>(decalsTextureAtlasTextureWidth),
						static_cast<float>(atlasTexture->top) / static_cast<float>(decalsTextureAtlasTextureHeight)
					}
				);
				rendererBackend->setProgramUniformFloatVec2(
					contextIdx,
					uniformDecalAtlasTextureDimension[i],
					{
						static_cast<float>(atlasTexture->width) / static_cast<float>(decalsTextureAtlasTextureWidth),
						static_cast<float>(atlasTexture->height) / static_cast<float>(decalsTextureAtlasTextureHeight)
					}
				);
				rendererBackend->setProgramUniformFloatVec2(
					contextIdx,
					uniformDecalSpriteSheetDimension[i],
					{
						static_cast<float>(decalObject->getTextureHorizontalSprites()),
						static_cast<float>(decalObject->getTextureVerticalSprites())
					}
				);
				rendererBackend->setProgramUniformInteger(contextIdx, uniformDecalSpriteIndex[i], decalObject->computeTextureSpriteIdx());
			}
		}
	} else {
		rendererBackend->setProgramUniformInteger(contextIdx, uniformDecalCount, 0);
	}

	//
	rendererBackend->setTextureUnit(contextIdx, 0);

	//
	isRunning = true;
}

void DeferredLightingRenderShader::unUseProgram()
{
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;
	auto textureUnit = rendererBackend->getTextureUnit(contextIdx);
	// PBR
	//	IBL
	rendererBackend->setTextureUnit(contextIdx, 9);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 10);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 11);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, textureUnit);

	//
	isRunning = false;
}
