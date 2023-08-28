#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/framebuffer/BRDFLUTShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>

using std::string;
using std::to_string;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::framebuffer::BRDFLUTShader;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::Texture;
using tdme::engine::Timing;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::Float;

LightingShaderPBRBaseImplementation::LightingShaderPBRBaseImplementation(Renderer* renderer)
{
	this->renderer = renderer;
	initialized = false;
}

bool LightingShaderPBRBaseImplementation::isInitialized()
{
	return initialized;
}

void LightingShaderPBRBaseImplementation::initialize()
{

	// link program
	if (renderer->linkProgram(programId) == false) return;

	// uniforms
	uniformBaseColorFactor = renderer->getProgramUniformLocation(programId, "u_BaseColorFactor");
	if (uniformBaseColorFactor == -1) return;
	uniformBaseColorSampler = renderer->getProgramUniformLocation(programId, "u_BaseColorSampler");
	if (uniformBaseColorSampler == -1) return;
	uniformBaseColorSamplerAvailable = renderer->getProgramUniformLocation(programId, "u_BaseColorSamplerAvailable");
	if (uniformBaseColorSamplerAvailable == -1) return;
	uniformAlphaCutoffEnabled = renderer->getProgramUniformLocation(programId, "u_AlphaCutoffEnabled");
	if (uniformAlphaCutoffEnabled == -1) return;
	uniformAlphaCutoff = renderer->getProgramUniformLocation(programId, "u_AlphaCutoff");
	if (uniformAlphaCutoff == -1) return;
	uniformCamera = renderer->getProgramUniformLocation(programId, "u_Camera");
	uniformExposure = renderer->getProgramUniformLocation(programId, "u_Exposure");
	if (uniformExposure == -1) return;
	uniformMetallicFactor = renderer->getProgramUniformLocation(programId, "u_MetallicFactor");
	if (uniformMetallicFactor == -1) return;
	uniformMetallicRoughnessSampler = renderer->getProgramUniformLocation(programId, "u_MetallicRoughnessSampler");
	if (uniformMetallicRoughnessSampler == -1) return;
	uniformMetallicRoughnessSamplerAvailable = renderer->getProgramUniformLocation(programId, "u_MetallicRoughnessSamplerAvailable");
	if (uniformMetallicRoughnessSamplerAvailable == -1) return;
	uniformRoughnessFactor = renderer->getProgramUniformLocation(programId, "u_RoughnessFactor");
	if (uniformRoughnessFactor == -1) return;
	uniformNormalSampler = renderer->getProgramUniformLocation(programId, "u_NormalSampler");
	if (uniformNormalSampler == -1) return;
	uniformNormalSamplerAvailable = renderer->getProgramUniformLocation(programId, "u_NormalSamplerAvailable");
	if (uniformNormalSamplerAvailable == -1) return;
	uniformNormalScale = renderer->getProgramUniformLocation(programId, "u_NormalScale");
	if (uniformNormalScale == -1) return;
	uniformEmissiveSampler = renderer->getProgramUniformLocation(programId, "u_EmissiveSampler");
	// TODO
	// if (uniformEmissiveSampler == -1) return;
	uniformEmissiveSamplerAvailable = renderer->getProgramUniformLocation(programId, "u_EmissiveSamplerAvailable");
	// TODO
	// if (uniformEmissiveSamplerAvailable == -1) return;
	uniformEmissiveFactor = renderer->getProgramUniformLocation(programId, "u_EmissiveFactor");
	// TODO
	// if (uniformEmissiveFactor == -1) return;
	uniformViewProjectionMatrix = renderer->getProgramUniformLocation(programId, "u_ViewProjectionMatrix");
	if (uniformViewProjectionMatrix == -1) return;
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformLightEnabled[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].enabled");
		uniformLightAmbient[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].ambient");
		uniformLightDirection[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].direction");
		uniformLightRange[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].range");
		uniformLightColor[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].color");
		uniformLightIntensity[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].intensity");
		uniformLightPosition[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].position");
		uniformLightInnerConeCos[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].innerConeCos");
		uniformLightOuterConeCos[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].outerConeCos");
		uniformLightType[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].type");
	}

	// IBL
	uniformDiffuseEnvSampler = renderer->getProgramUniformLocation(programId, "u_DiffuseEnvSampler");
	uniformSpecularEnvSampler = renderer->getProgramUniformLocation(programId, "u_SpecularEnvSampler");
	uniformbrdfLUT = renderer->getProgramUniformLocation(programId, "u_brdfLUT");
	texturebrdfLUT = Engine::getBRDFLUTShader()->getColorTextureId();

	//
	loadTextures(".");

	//
	initialized = true;
}

void LightingShaderPBRBaseImplementation::useProgram(Engine* engine, int contextIdx)
{
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_PBR);
	renderer->setProgramUniformInteger(contextIdx, uniformBaseColorSampler, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
	renderer->setProgramUniformInteger(contextIdx, uniformMetallicRoughnessSampler, LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS);
	renderer->setProgramUniformInteger(contextIdx, uniformNormalSampler, LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL);
	renderer->setProgramUniformInteger(contextIdx, uniformEmissiveSampler, LightingShaderConstants::PBR_TEXTUREUNIT_EMISSIVE);
	renderer->setProgramUniformInteger(contextIdx, uniformDiffuseEnvSampler, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_DIFFUSE);
	renderer->setProgramUniformInteger(contextIdx, uniformSpecularEnvSampler, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_SPECULAR);
	renderer->setProgramUniformInteger(contextIdx, uniformbrdfLUT, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_BRDF);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_DIFFUSE);
	renderer->bindCubeMapTexture(contextIdx, textureDiffuseEnvSampler);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_SPECULAR);
	renderer->bindCubeMapTexture(contextIdx, textureSpecularEnvSampler);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_BRDF);
	renderer->bindTexture(contextIdx, texturebrdfLUT);
	renderer->setTextureUnit(contextIdx, 0);
}

void LightingShaderPBRBaseImplementation::unUseProgram(int contextIdx)
{
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_EMISSIVE);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_DIFFUSE);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_SPECULAR);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_BRDF);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 0);
}

void LightingShaderPBRBaseImplementation::updateEffect(Renderer* renderer, int contextIdx)
{
}

void LightingShaderPBRBaseImplementation::updateMaterial(Renderer* renderer, int contextIdx)
{
	auto material = renderer->getPBRMaterial(contextIdx);
	renderer->setProgramUniformFloatVec4(contextIdx, uniformBaseColorFactor, material.baseColorFactor);
	renderer->setProgramUniformFloat(contextIdx, uniformExposure, material.exposure);
	renderer->setProgramUniformFloat(contextIdx, uniformMetallicFactor, material.metallicFactor);
	renderer->setProgramUniformFloat(contextIdx, uniformRoughnessFactor, material.roughnessFactor);
	renderer->setProgramUniformFloatVec3(contextIdx, uniformEmissiveFactor, material.emissiveFactor);
	renderer->setProgramUniformFloat(contextIdx, uniformNormalScale, material.normalScale);
	renderer->setProgramUniformInteger(contextIdx, uniformAlphaCutoffEnabled, material.baseColorTextureMaskedTransparency);
	renderer->setProgramUniformFloat(contextIdx, uniformAlphaCutoff, material.baseColorTextureMaskedTransparency == 0?0.0f:material.baseColorTextureMaskedTransparencyThreshold);
}

void LightingShaderPBRBaseImplementation::updateLight(Renderer* renderer, int contextIdx, int32_t lightId)
{
	const auto& light = renderer->getLight(contextIdx, lightId);
	if (uniformLightEnabled[lightId] != -1) renderer->setProgramUniformInteger(contextIdx, uniformLightEnabled[lightId], light.enabled);
	if (light.enabled == 0) return;
	if (uniformLightAmbient[lightId] != -1)
		renderer->setProgramUniformFloatVec3(
			contextIdx,
			uniformLightAmbient[lightId],
			{{
				light.ambient[0],
				light.ambient[1],
				light.ambient[2]
			}}
		);
	if (uniformLightDirection[lightId] != -1) renderer->setProgramUniformFloatVec3(contextIdx, uniformLightDirection[lightId], light.spotDirection);
	if (uniformLightRange[lightId] != -1) renderer->setProgramUniformFloat(contextIdx, uniformLightRange[lightId], 0.0f);
	if (uniformLightColor[lightId] != -1)
		renderer->setProgramUniformFloatVec3(
			contextIdx,
			uniformLightColor[lightId],
			{{
				light.diffuse[0],
				light.diffuse[1],
				light.diffuse[2]
			}}
		);
	if (uniformLightIntensity[lightId] != -1) renderer->setProgramUniformFloat(contextIdx, uniformLightIntensity[lightId], 1.0f);
	if (uniformLightPosition[lightId] != -1) renderer->setProgramUniformFloatVec3(contextIdx, uniformLightPosition[lightId],{{ light.position[0], light.position[1], light.position[2] }});
	if (uniformLightType[lightId] != -1) renderer->setProgramUniformInteger(contextIdx, uniformLightType[lightId], 0);
}

void LightingShaderPBRBaseImplementation::updateMatrices(Renderer* renderer, int contextIdx)
{
	// set up camera position and view projection matrices
	// matrices
	Matrix4x4 vpMatrix;
	// object to screen matrix
	vpMatrix.set(renderer->getCameraMatrix()).multiply(renderer->getProjectionMatrix());
	// upload matrices
	renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformViewProjectionMatrix, vpMatrix.getArray());
	if (uniformCamera != -1) renderer->setProgramUniformFloatVec3(contextIdx, uniformCamera, renderer->getCameraPosition().getArray());
}

void LightingShaderPBRBaseImplementation::updateTextureMatrix(Renderer* renderer, int contextIdx) {
}

void LightingShaderPBRBaseImplementation::updateShaderParameters(Renderer* renderer, int contextIdx) {
}

void LightingShaderPBRBaseImplementation::bindTexture(Renderer* renderer, int contextIdx, int32_t textureId)
{
	switch (renderer->getTextureUnit(contextIdx)) {
		case LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR:
			if (uniformBaseColorSamplerAvailable != -1) renderer->setProgramUniformInteger(contextIdx, uniformBaseColorSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS:
			if (uniformMetallicRoughnessSamplerAvailable != -1) renderer->setProgramUniformInteger(contextIdx, uniformMetallicRoughnessSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL:
			if (uniformNormalSamplerAvailable != -1) renderer->setProgramUniformInteger(contextIdx, uniformNormalSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::PBR_TEXTUREUNIT_EMISSIVE:
			if (uniformEmissiveSamplerAvailable != -1) renderer->setProgramUniformInteger(contextIdx, uniformEmissiveSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}

void LightingShaderPBRBaseImplementation::unloadTextures() {
	//
	for (auto i = 0; i < envDiffuseTextures.size(); i++) {
		if (envDiffuseTextures[i] == nullptr) continue;
		envDiffuseTextures[i]->releaseReference();
		envDiffuseTextures[i] = nullptr;
	}
	for (auto i = 0; i < envSpecularTextures.size(); i++) {
		if (envSpecularTextures[i] == nullptr) continue;
		envSpecularTextures[i]->releaseReference();
		envSpecularTextures[i] = nullptr;
	}
	//
	Engine::getInstance()->getTextureManager()->removeTexture("pbr-environment-diffuse");
	Engine::getInstance()->getTextureManager()->removeTexture("pbr-specular-diffuse");
}

void LightingShaderPBRBaseImplementation::loadTextures(const string& pathName) {
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
			renderer->CONTEXTINDEX_DEFAULT
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
			renderer->CONTEXTINDEX_DEFAULT
		);
}
