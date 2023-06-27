#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderBaseImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
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
using tdme::engine::subsystems::renderer::Renderer;
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

ShadowMapRenderShaderBaseImplementation::ShadowMapRenderShaderBaseImplementation(Renderer* renderer)
{
	this->renderer = renderer;
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
	auto shaderVersion = renderer->getShaderVersion();

	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programId, 1, "inNormal");
		renderer->setProgramAttributeLocation(programId, 2, "inTextureUV");
		renderer->setProgramAttributeLocation(programId, 4, "inOrigin");
	}
	// link
	if (renderer->linkProgram(programId) == false)
		return;

	//	uniforms
	renderUniformShadowMapLookUps = renderer->getProgramUniformLocation(programId, "shadowMapLookUps");
	uniformTextureAtlasSize = renderer->getProgramUniformLocation(programId, "textureAtlasSize");
	if (uniformTextureAtlasSize == -1) return;
	uniformTextureAtlasPixelDimension = renderer->getProgramUniformLocation(programId, "textureAtlasPixelDimension");
	if (uniformTextureAtlasPixelDimension == -1) return;
	uniformTextureUnit = renderer->getProgramUniformLocation(programId, "textureUnit");
	if (uniformTextureUnit == -1) return;
	renderUniformTexturePixelWidth = renderer->getProgramUniformLocation(programId, "texturePixelWidth");
	if (renderUniformTexturePixelWidth == -1) return;
	renderUniformTexturePixelHeight = renderer->getProgramUniformLocation(programId, "texturePixelHeight");
	if (renderUniformTexturePixelHeight == -1) return;
	renderUniformDepthBiasMVPMatrix = renderer->getProgramUniformLocation(programId, "depthBiasMVPMatrix");
	if (renderUniformDepthBiasMVPMatrix == -1) return;
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderUniformProjectionMatrix = renderer->getProgramUniformLocation(programId, "projectionMatrix");
		if (renderUniformProjectionMatrix == -1) return;
		renderUniformCameraMatrix = renderer->getProgramUniformLocation(programId, "cameraMatrix");
		if (renderUniformCameraMatrix == -1) return;
	} else {
		renderUniformMVPMatrix = renderer->getProgramUniformLocation(programId, "mvpMatrix");
		if (renderUniformMVPMatrix == -1) return;
		renderUniformNormalMatrix = renderer->getProgramUniformLocation(programId, "normalMatrix");
		if (renderUniformNormalMatrix == -1) return;
		renderUniformModelTranslation = renderer->getProgramUniformLocation(programId, "modelTranslation");
	}
	uniformTextureMatrix = renderer->getProgramUniformLocation(programId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(programId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1) return;
	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(programId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1) return;
	uniformDiffuseTextureMaskedTransparency = renderer->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparency");
	if (uniformDiffuseTextureMaskedTransparency == -1) return;
	uniformDiffuseTextureMaskedTransparencyThreshold = renderer->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparencyThreshold");
	if (uniformDiffuseTextureMaskedTransparencyThreshold == -1) return;
	renderUniformLightDirection = renderer->getProgramUniformLocation(programId, "lightDirection");
	if (renderUniformLightDirection == -1) return;
	if (shaderVersion != "gl2") {
		if (renderer->isInstancedRenderingAvailable() == false) {
			renderUniformMVMatrix = renderer->getProgramUniformLocation(programId, "mvMatrix");
			if (renderUniformMVMatrix == -1) return;
		}
		renderUniformLightPosition = renderer->getProgramUniformLocation(programId, "lightPosition");
		if (renderUniformLightPosition == -1) return;
		renderUniformLightSpotExponent = renderer->getProgramUniformLocation(programId, "lightSpotExponent");
		if (renderUniformLightSpotExponent == -1) return;
		renderUniformLightSpotCosCutoff = renderer->getProgramUniformLocation(programId, "lightSpotCosCutoff");
		if (renderUniformLightSpotCosCutoff == -1) return;
		renderUniformLightConstantAttenuation = renderer->getProgramUniformLocation(programId, "lightConstantAttenuation");
		if (renderUniformLightConstantAttenuation == -1) return;
		renderUniformLightLinearAttenuation = renderer->getProgramUniformLocation(programId, "lightLinearAttenuation");
		if (renderUniformLightLinearAttenuation == -1) return;
		renderUniformLightQuadraticAttenuation = renderer->getProgramUniformLocation(programId, "lightQuadraticAttenuation");
		if (renderUniformLightQuadraticAttenuation == -1) return;
	}

	//
	renderUniformTime = renderer->getProgramUniformLocation(programId, "time");

	//
	initialized = true;
}

void ShadowMapRenderShaderBaseImplementation::useProgram(Engine* engine, int contextIdx)
{
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_SPECULAR);
	renderer->setProgramUniformInteger(contextIdx, uniformTextureUnit, ShadowMap::TEXTUREUNIT);
	renderer->setProgramUniformInteger(contextIdx, uniformDiffuseTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
	renderer->setProgramUniformInteger(contextIdx, uniformDiffuseTextureAvailable, 0);
	if (renderUniformTime != -1) renderer->setProgramUniformFloat(contextIdx, renderUniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
	if (renderUniformShadowMapLookUps != -1) renderer->setProgramUniformInteger(contextIdx, renderUniformShadowMapLookUps, Engine::getShadowMapRenderLookUps());
}

void ShadowMapRenderShaderBaseImplementation::unUseProgram(int contextIdx)
{
}

void ShadowMapRenderShaderBaseImplementation::updateMatrices(int contextIdx) {
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformCameraMatrix, renderer->getCameraMatrix().getArray());
	} else {
		Matrix4x4 mvMatrix;
		Matrix4x4 mvpMatrix;
		Matrix4x4 normalMatrix;
		Vector3 modelTranslation;
		// model view matrix
		mvMatrix.set(renderer->getModelViewMatrix()).multiply(renderer->getCameraMatrix());
		// object to screen matrix
		mvpMatrix.set(mvMatrix).multiply(renderer->getProjectionMatrix());
		// normal matrix
		normalMatrix.set(renderer->getModelViewMatrix()).invert().transpose();
		// model translation
		renderer->getModelViewMatrix().getTranslation(modelTranslation);
		// upload
		if (renderUniformMVMatrix != -1) renderer->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformMVMatrix, mvMatrix.getArray());
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformMVPMatrix, mvpMatrix.getArray());
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformNormalMatrix, normalMatrix.getArray());
		if (renderUniformModelTranslation != -1) renderer->setProgramUniformFloatVec3(contextIdx, renderUniformModelTranslation, modelTranslation.getArray());
	}
}

void ShadowMapRenderShaderBaseImplementation::updateTextureMatrix(Renderer* renderer, int contextIdx) {
	renderer->setProgramUniformFloatMatrix3x3(contextIdx, uniformTextureMatrix, renderer->getTextureMatrix(contextIdx).getArray());
}

void ShadowMapRenderShaderBaseImplementation::updateMaterial(Renderer* renderer, int contextIdx)
{
	auto material = renderer->getSpecularMaterial(contextIdx);
	renderer->setProgramUniformInteger(contextIdx, uniformDiffuseTextureMaskedTransparency, material.diffuseTextureMaskedTransparency);
	renderer->setProgramUniformFloat(contextIdx, uniformDiffuseTextureMaskedTransparencyThreshold, material.diffuseTextureMaskedTransparencyThreshold);
	renderer->setProgramUniformInteger(contextIdx, uniformTextureAtlasSize, material.textureAtlasSize);
	renderer->setProgramUniformFloatVec2(contextIdx, uniformTextureAtlasPixelDimension, material.textureAtlasPixelDimension);
}

void ShadowMapRenderShaderBaseImplementation::updateLight(Renderer* renderer, int contextIdx, int32_t lightId) {
	if (lightId != this->lightId) {
		return;
	}

	auto& light = renderer->getLight(contextIdx, lightId);
	auto lightPosition = Vector3(light.position[0], light.position[1], light.position[2]);
	auto lightSpotDirection = Vector3(light.spotDirection[0], light.spotDirection[1], light.spotDirection[2]);
	if (renderUniformLightPosition != -1) renderer->setProgramUniformFloatVec3(contextIdx, renderUniformLightPosition, lightPosition.getArray());
	if (renderUniformLightDirection != -1) renderer->setProgramUniformFloatVec3(contextIdx, renderUniformLightDirection, lightSpotDirection.getArray());
	if (renderUniformLightSpotExponent != -1) renderer->setProgramUniformFloat(contextIdx, renderUniformLightSpotExponent, light.spotExponent);
	if (renderUniformLightSpotCosCutoff != -1) renderer->setProgramUniformFloat(contextIdx, renderUniformLightSpotCosCutoff, light.spotCosCutoff);
	if (renderUniformLightConstantAttenuation != -1) renderer->setProgramUniformFloat(contextIdx, renderUniformLightConstantAttenuation, light.constantAttenuation);
	if (renderUniformLightLinearAttenuation != -1) renderer->setProgramUniformFloat(contextIdx, renderUniformLightLinearAttenuation, light.linearAttenuation);
	if (renderUniformLightQuadraticAttenuation != -1) renderer->setProgramUniformFloat(contextIdx, renderUniformLightQuadraticAttenuation, light.quadraticAttenuation);
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformCameraMatrix, renderer->getCameraMatrix().getArray());
	}
	renderer->setProgramUniformFloat(contextIdx, renderUniformTexturePixelWidth, 1.0f / static_cast<float>(Engine::getShadowMapWidth()));
	renderer->setProgramUniformFloat(contextIdx, renderUniformTexturePixelHeight, 1.0f / static_cast<float>(Engine::getShadowMapHeight()));
}

void ShadowMapRenderShaderBaseImplementation::bindTexture(Renderer* renderer, int contextIdx, int32_t textureId)
{
	switch (renderer->getTextureUnit(contextIdx)) {
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE:
			renderer->setProgramUniformInteger(contextIdx, uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}

void ShadowMapRenderShaderBaseImplementation::setDepthBiasMVPMatrix(int contextIdx, const Matrix4x4& depthBiasMVPMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(contextIdx, renderUniformDepthBiasMVPMatrix, depthBiasMVPMatrix.getArray());
}

void ShadowMapRenderShaderBaseImplementation::setRenderLightId(int32_t lightId) {
	this->lightId = lightId;
}

void ShadowMapRenderShaderBaseImplementation::loadTextures(const string& pathName) {
}
