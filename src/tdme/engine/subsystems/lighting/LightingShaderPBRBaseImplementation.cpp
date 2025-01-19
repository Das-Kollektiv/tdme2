#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/framebuffer/BRDFLUTShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
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
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::Texture;
using tdme::engine::Timing;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::Float;

LightingShaderPBRBaseImplementation::LightingShaderPBRBaseImplementation(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
	initialized = false;
}

bool LightingShaderPBRBaseImplementation::isInitialized()
{
	return initialized;
}

void LightingShaderPBRBaseImplementation::initialize()
{

	// link program
	if (rendererBackend->linkProgram(programId) == false) return;

	// uniforms
	uniformBaseColorFactor = rendererBackend->getProgramUniformLocation(programId, "u_BaseColorFactor");
	if (uniformBaseColorFactor == -1) return;
	uniformBaseColorSampler = rendererBackend->getProgramUniformLocation(programId, "u_BaseColorSampler");
	if (uniformBaseColorSampler == -1) return;
	uniformBaseColorSamplerAvailable = rendererBackend->getProgramUniformLocation(programId, "u_BaseColorSamplerAvailable");
	if (uniformBaseColorSamplerAvailable == -1) return;
	uniformAlphaCutoffEnabled = rendererBackend->getProgramUniformLocation(programId, "u_AlphaCutoffEnabled");
	if (uniformAlphaCutoffEnabled == -1) return;
	uniformAlphaCutoff = rendererBackend->getProgramUniformLocation(programId, "u_AlphaCutoff");
	if (uniformAlphaCutoff == -1) return;
	uniformCamera = rendererBackend->getProgramUniformLocation(programId, "u_Camera");
	uniformExposure = rendererBackend->getProgramUniformLocation(programId, "u_Exposure");
	if (uniformExposure == -1) return;
	uniformMetallicFactor = rendererBackend->getProgramUniformLocation(programId, "u_MetallicFactor");
	if (uniformMetallicFactor == -1) return;
	uniformMetallicRoughnessSampler = rendererBackend->getProgramUniformLocation(programId, "u_MetallicRoughnessSampler");
	if (uniformMetallicRoughnessSampler == -1) return;
	uniformMetallicRoughnessSamplerAvailable = rendererBackend->getProgramUniformLocation(programId, "u_MetallicRoughnessSamplerAvailable");
	if (uniformMetallicRoughnessSamplerAvailable == -1) return;
	uniformRoughnessFactor = rendererBackend->getProgramUniformLocation(programId, "u_RoughnessFactor");
	if (uniformRoughnessFactor == -1) return;
	uniformNormalSampler = rendererBackend->getProgramUniformLocation(programId, "u_NormalSampler");
	if (uniformNormalSampler == -1) return;
	uniformNormalSamplerAvailable = rendererBackend->getProgramUniformLocation(programId, "u_NormalSamplerAvailable");
	if (uniformNormalSamplerAvailable == -1) return;
	uniformNormalScale = rendererBackend->getProgramUniformLocation(programId, "u_NormalScale");
	if (uniformNormalScale == -1) return;
	uniformEmissiveSampler = rendererBackend->getProgramUniformLocation(programId, "u_EmissiveSampler");
	// TODO
	// if (uniformEmissiveSampler == -1) return;
	uniformEmissiveSamplerAvailable = rendererBackend->getProgramUniformLocation(programId, "u_EmissiveSamplerAvailable");
	// TODO
	// if (uniformEmissiveSamplerAvailable == -1) return;
	uniformEmissiveFactor = rendererBackend->getProgramUniformLocation(programId, "u_EmissiveFactor");
	// TODO
	// if (uniformEmissiveFactor == -1) return;
	uniformViewProjectionMatrix = rendererBackend->getProgramUniformLocation(programId, "u_ViewProjectionMatrix");
	if (uniformViewProjectionMatrix == -1) return;
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformLightEnabled[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].enabled");
		uniformLightAmbient[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].ambient");
		uniformLightDirection[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].direction");
		uniformLightRange[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].range");
		uniformLightColor[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].color");
		uniformLightIntensity[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].intensity");
		uniformLightPosition[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].position");
		uniformLightInnerConeCos[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].innerConeCos");
		uniformLightOuterConeCos[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].outerConeCos");
		uniformLightType[i] = rendererBackend->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].type");
	}

	// IBL
	uniformDiffuseEnvSampler = rendererBackend->getProgramUniformLocation(programId, "u_DiffuseEnvSampler");
	uniformSpecularEnvSampler = rendererBackend->getProgramUniformLocation(programId, "u_SpecularEnvSampler");
	uniformbrdfLUT = rendererBackend->getProgramUniformLocation(programId, "u_brdfLUT");
	texturebrdfLUT = Engine::getBRDFLUTShader()->getColorTextureId();

	//
	loadTextures(".");

	//
	initialized = true;
}

void LightingShaderPBRBaseImplementation::useProgram(Engine* engine, int contextIdx)
{
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_PBR);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformBaseColorSampler, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformMetallicRoughnessSampler, LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformNormalSampler, LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformEmissiveSampler, LightingShaderConstants::PBR_TEXTUREUNIT_EMISSIVE);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseEnvSampler, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_DIFFUSE);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformSpecularEnvSampler, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_SPECULAR);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformbrdfLUT, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_BRDF);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_DIFFUSE);
	rendererBackend->bindCubeMapTexture(contextIdx, textureDiffuseEnvSampler);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_SPECULAR);
	rendererBackend->bindCubeMapTexture(contextIdx, textureSpecularEnvSampler);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_BRDF);
	rendererBackend->bindTexture(contextIdx, texturebrdfLUT);
	rendererBackend->setTextureUnit(contextIdx, 0);
}

void LightingShaderPBRBaseImplementation::unUseProgram(int contextIdx)
{
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_EMISSIVE);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_DIFFUSE);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_SPECULAR);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_ENVIRONMENT_BRDF);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 0);
}

void LightingShaderPBRBaseImplementation::updateEffect(RendererBackend* rendererBackend, int contextIdx)
{
}

void LightingShaderPBRBaseImplementation::updateMaterial(RendererBackend* rendererBackend, int contextIdx)
{
	auto material = rendererBackend->getPBRMaterial(contextIdx);
	rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformBaseColorFactor, material.baseColorFactor);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformExposure, material.exposure);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformMetallicFactor, material.metallicFactor);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformRoughnessFactor, material.roughnessFactor);
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformEmissiveFactor, material.emissiveFactor);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformNormalScale, material.normalScale);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformAlphaCutoffEnabled, material.baseColorTextureMaskedTransparency);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformAlphaCutoff, material.baseColorTextureMaskedTransparency == 0?0.0f:material.baseColorTextureMaskedTransparencyThreshold);
}

void LightingShaderPBRBaseImplementation::updateLight(RendererBackend* rendererBackend, int contextIdx, int32_t lightId)
{
	const auto& light = rendererBackend->getLight(contextIdx, lightId);
	if (uniformLightEnabled[lightId] != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformLightEnabled[lightId], light.enabled);
	if (light.enabled == 0) return;
	if (uniformLightAmbient[lightId] != -1)
		rendererBackend->setProgramUniformFloatVec3(
			contextIdx,
			uniformLightAmbient[lightId],
			{{
				light.ambient[0],
				light.ambient[1],
				light.ambient[2]
			}}
		);
	if (uniformLightDirection[lightId] != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformLightDirection[lightId], light.spotDirection);
	if (uniformLightRange[lightId] != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformLightRange[lightId], 0.0f);
	if (uniformLightColor[lightId] != -1)
		rendererBackend->setProgramUniformFloatVec3(
			contextIdx,
			uniformLightColor[lightId],
			{{
				light.diffuse[0],
				light.diffuse[1],
				light.diffuse[2]
			}}
		);
	if (uniformLightIntensity[lightId] != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformLightIntensity[lightId], 1.0f);
	if (uniformLightPosition[lightId] != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformLightPosition[lightId],{{ light.position[0], light.position[1], light.position[2] }});
	if (uniformLightType[lightId] != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformLightType[lightId], 0);
}

void LightingShaderPBRBaseImplementation::updateMatrices(RendererBackend* rendererBackend, int contextIdx)
{
	// set up camera position and view projection matrices
	// matrices
	Matrix4x4 vpMatrix;
	// object to screen matrix
	vpMatrix.set(rendererBackend->getCameraMatrix()).multiply(rendererBackend->getProjectionMatrix());
	// upload matrices
	rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformViewProjectionMatrix, vpMatrix.getArray());
	if (uniformCamera != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformCamera, rendererBackend->getCameraPosition().getArray());
}

void LightingShaderPBRBaseImplementation::updateTextureMatrix(RendererBackend* rendererBackend, int contextIdx) {
}

void LightingShaderPBRBaseImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
}

void LightingShaderPBRBaseImplementation::bindTexture(RendererBackend* rendererBackend, int contextIdx, int32_t textureId)
{
	switch (rendererBackend->getTextureUnit(contextIdx)) {
		case LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR:
			if (uniformBaseColorSamplerAvailable != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformBaseColorSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS:
			if (uniformMetallicRoughnessSamplerAvailable != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformMetallicRoughnessSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL:
			if (uniformNormalSamplerAvailable != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformNormalSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::PBR_TEXTUREUNIT_EMISSIVE:
			if (uniformEmissiveSamplerAvailable != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformEmissiveSamplerAvailable, textureId == 0 ? 0 : 1);
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
	Engine::getInstance()->getTextureManager()->removeTexture("pbr-environment-specular");
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
}
