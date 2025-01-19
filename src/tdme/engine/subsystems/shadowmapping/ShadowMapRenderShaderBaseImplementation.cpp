#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderBaseImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderBaseImplementation;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

ShadowMapRenderShaderBaseImplementation::ShadowMapRenderShaderBaseImplementation(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
	initialized = false;
}

ShadowMapRenderShaderBaseImplementation::~ShadowMapRenderShaderBaseImplementation()
{
}

bool ShadowMapRenderShaderBaseImplementation::isInitialized()
{
	return initialized;
}

void ShadowMapRenderShaderBaseImplementation::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();

	// map inputs to attributes
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 1, "inNormal");
		rendererBackend->setProgramAttributeLocation(programId, 2, "inTextureUV");
		rendererBackend->setProgramAttributeLocation(programId, 4, "inOrigin");
	}
	// link
	if (rendererBackend->linkProgram(programId) == false)
		return;

	//	uniforms
	renderUniformShadowMapLookUps = rendererBackend->getProgramUniformLocation(programId, "shadowMapLookUps");
	uniformTextureAtlasSize = rendererBackend->getProgramUniformLocation(programId, "textureAtlasSize");
	if (uniformTextureAtlasSize == -1) return;
	uniformTextureAtlasPixelDimension = rendererBackend->getProgramUniformLocation(programId, "textureAtlasPixelDimension");
	if (uniformTextureAtlasPixelDimension == -1) return;
	uniformTextureUnit = rendererBackend->getProgramUniformLocation(programId, "textureUnit");
	if (uniformTextureUnit == -1) return;
	renderUniformTexturePixelWidth = rendererBackend->getProgramUniformLocation(programId, "texturePixelWidth");
	if (renderUniformTexturePixelWidth == -1) return;
	renderUniformTexturePixelHeight = rendererBackend->getProgramUniformLocation(programId, "texturePixelHeight");
	if (renderUniformTexturePixelHeight == -1) return;
	renderUniformDepthBiasMVPMatrix = rendererBackend->getProgramUniformLocation(programId, "depthBiasMVPMatrix");
	if (renderUniformDepthBiasMVPMatrix == -1) return;
	if (rendererBackend->isInstancedRenderingAvailable() == true) {
		renderUniformProjectionMatrix = rendererBackend->getProgramUniformLocation(programId, "projectionMatrix");
		if (renderUniformProjectionMatrix == -1) return;
		renderUniformCameraMatrix = rendererBackend->getProgramUniformLocation(programId, "cameraMatrix");
		if (renderUniformCameraMatrix == -1) return;
	} else {
		renderUniformMVPMatrix = rendererBackend->getProgramUniformLocation(programId, "mvpMatrix");
		if (renderUniformMVPMatrix == -1) return;
		renderUniformNormalMatrix = rendererBackend->getProgramUniformLocation(programId, "normalMatrix");
		if (renderUniformNormalMatrix == -1) return;
		renderUniformModelTranslation = rendererBackend->getProgramUniformLocation(programId, "modelTranslation");
	}
	uniformTextureMatrix = rendererBackend->getProgramUniformLocation(programId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;
	uniformDiffuseTextureUnit = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1) return;
	uniformDiffuseTextureAvailable = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1) return;
	uniformDiffuseTextureMaskedTransparency = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparency");
	if (uniformDiffuseTextureMaskedTransparency == -1) return;
	uniformDiffuseTextureMaskedTransparencyThreshold = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparencyThreshold");
	if (uniformDiffuseTextureMaskedTransparencyThreshold == -1) return;
	renderUniformLightDirection = rendererBackend->getProgramUniformLocation(programId, "lightDirection");
	if (renderUniformLightDirection == -1) return;
	if (shaderVersion != "gl2") {
		if (rendererBackend->isInstancedRenderingAvailable() == false) {
			renderUniformMVMatrix = rendererBackend->getProgramUniformLocation(programId, "mvMatrix");
			if (renderUniformMVMatrix == -1) return;
		}
		renderUniformLightPosition = rendererBackend->getProgramUniformLocation(programId, "lightPosition");
		if (renderUniformLightPosition == -1) return;
		renderUniformLightSpotExponent = rendererBackend->getProgramUniformLocation(programId, "lightSpotExponent");
		if (renderUniformLightSpotExponent == -1) return;
		renderUniformLightSpotCosCutoff = rendererBackend->getProgramUniformLocation(programId, "lightSpotCosCutoff");
		if (renderUniformLightSpotCosCutoff == -1) return;
		renderUniformLightConstantAttenuation = rendererBackend->getProgramUniformLocation(programId, "lightConstantAttenuation");
		if (renderUniformLightConstantAttenuation == -1) return;
		renderUniformLightLinearAttenuation = rendererBackend->getProgramUniformLocation(programId, "lightLinearAttenuation");
		if (renderUniformLightLinearAttenuation == -1) return;
		renderUniformLightQuadraticAttenuation = rendererBackend->getProgramUniformLocation(programId, "lightQuadraticAttenuation");
		if (renderUniformLightQuadraticAttenuation == -1) return;
	}

	//
	renderUniformTime = rendererBackend->getProgramUniformLocation(programId, "time");

	//
	initialized = true;
}

void ShadowMapRenderShaderBaseImplementation::useProgram(Engine* engine, int contextIdx)
{
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_SPECULAR);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformTextureUnit, ShadowMap::TEXTUREUNIT);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureAvailable, 0);
	if (renderUniformTime != -1) rendererBackend->setProgramUniformFloat(contextIdx, renderUniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
	if (renderUniformShadowMapLookUps != -1) rendererBackend->setProgramUniformInteger(contextIdx, renderUniformShadowMapLookUps, Engine::getShadowMapRenderLookUps());
}

void ShadowMapRenderShaderBaseImplementation::unUseProgram(int contextIdx)
{
}

void ShadowMapRenderShaderBaseImplementation::updateMatrices(int contextIdx) {
	if (rendererBackend->isInstancedRenderingAvailable() == true) {
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformProjectionMatrix, rendererBackend->getProjectionMatrix().getArray());
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformCameraMatrix, rendererBackend->getCameraMatrix().getArray());
	} else {
		Matrix4x4 mvMatrix;
		Matrix4x4 mvpMatrix;
		Matrix4x4 normalMatrix;
		Vector3 modelTranslation;
		// model view matrix
		mvMatrix.set(rendererBackend->getModelViewMatrix()).multiply(rendererBackend->getCameraMatrix());
		// object to screen matrix
		mvpMatrix.set(mvMatrix).multiply(rendererBackend->getProjectionMatrix());
		// normal matrix
		normalMatrix.set(rendererBackend->getModelViewMatrix()).invert().transpose();
		// model translation
		rendererBackend->getModelViewMatrix().getTranslation(modelTranslation);
		// upload
		if (renderUniformMVMatrix != -1) rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformMVMatrix, mvMatrix.getArray());
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformMVPMatrix, mvpMatrix.getArray());
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformNormalMatrix, normalMatrix.getArray());
		if (renderUniformModelTranslation != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, renderUniformModelTranslation, modelTranslation.getArray());
	}
}

void ShadowMapRenderShaderBaseImplementation::updateTextureMatrix(RendererBackend* rendererBackend, int contextIdx) {
	rendererBackend->setProgramUniformFloatMatrix3x3(contextIdx, uniformTextureMatrix, rendererBackend->getTextureMatrix(contextIdx).getArray());
}

void ShadowMapRenderShaderBaseImplementation::updateMaterial(RendererBackend* rendererBackend, int contextIdx)
{
	auto material = rendererBackend->getSpecularMaterial(contextIdx);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureMaskedTransparency, material.diffuseTextureMaskedTransparency);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformDiffuseTextureMaskedTransparencyThreshold, material.diffuseTextureMaskedTransparencyThreshold);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformTextureAtlasSize, material.textureAtlasSize);
	rendererBackend->setProgramUniformFloatVec2(contextIdx, uniformTextureAtlasPixelDimension, material.textureAtlasPixelDimension);
}

void ShadowMapRenderShaderBaseImplementation::updateLight(RendererBackend* rendererBackend, int contextIdx, int32_t lightId) {
	if (lightId != this->lightId) {
		return;
	}

	const auto& light = rendererBackend->getLight(contextIdx, lightId);
	auto lightPosition = Vector3(light.position[0], light.position[1], light.position[2]);
	auto lightSpotDirection = Vector3(light.spotDirection[0], light.spotDirection[1], light.spotDirection[2]);
	if (renderUniformLightPosition != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, renderUniformLightPosition, lightPosition.getArray());
	if (renderUniformLightDirection != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, renderUniformLightDirection, lightSpotDirection.getArray());
	if (renderUniformLightSpotExponent != -1) rendererBackend->setProgramUniformFloat(contextIdx, renderUniformLightSpotExponent, light.spotExponent);
	if (renderUniformLightSpotCosCutoff != -1) rendererBackend->setProgramUniformFloat(contextIdx, renderUniformLightSpotCosCutoff, light.spotCosCutoff);
	if (renderUniformLightConstantAttenuation != -1) rendererBackend->setProgramUniformFloat(contextIdx, renderUniformLightConstantAttenuation, light.constantAttenuation);
	if (renderUniformLightLinearAttenuation != -1) rendererBackend->setProgramUniformFloat(contextIdx, renderUniformLightLinearAttenuation, light.linearAttenuation);
	if (renderUniformLightQuadraticAttenuation != -1) rendererBackend->setProgramUniformFloat(contextIdx, renderUniformLightQuadraticAttenuation, light.quadraticAttenuation);
	if (rendererBackend->isInstancedRenderingAvailable() == true) {
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformProjectionMatrix, rendererBackend->getProjectionMatrix().getArray());
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformCameraMatrix, rendererBackend->getCameraMatrix().getArray());
	}
	rendererBackend->setProgramUniformFloat(contextIdx, renderUniformTexturePixelWidth, 1.0f / static_cast<float>(Engine::getShadowMapWidth()));
	rendererBackend->setProgramUniformFloat(contextIdx, renderUniformTexturePixelHeight, 1.0f / static_cast<float>(Engine::getShadowMapHeight()));
}

void ShadowMapRenderShaderBaseImplementation::bindTexture(RendererBackend* rendererBackend, int contextIdx, int32_t textureId)
{
	switch (rendererBackend->getTextureUnit(contextIdx)) {
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE:
			rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}

void ShadowMapRenderShaderBaseImplementation::setDepthBiasMVPMatrix(int contextIdx, const Matrix4x4& depthBiasMVPMatrix)
{
	rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformDepthBiasMVPMatrix, depthBiasMVPMatrix.getArray());
}

void ShadowMapRenderShaderBaseImplementation::setRenderLightId(int32_t lightId) {
	this->lightId = lightId;
}

void ShadowMapRenderShaderBaseImplementation::unloadTextures() {
}

void ShadowMapRenderShaderBaseImplementation::loadTextures(const string& pathName) {
}
