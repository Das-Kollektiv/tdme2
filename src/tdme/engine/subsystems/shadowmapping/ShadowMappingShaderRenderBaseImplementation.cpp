#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderBaseImplementation.h>

#include <string>

#include <tdme/math/Math.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::to_string;

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

ShadowMappingShaderRenderBaseImplementation::ShadowMappingShaderRenderBaseImplementation(GLRenderer* renderer)
{
	this->renderer = renderer;
	initialized = false;
}

ShadowMappingShaderRenderBaseImplementation::~ShadowMappingShaderRenderBaseImplementation()
{
}

bool ShadowMappingShaderRenderBaseImplementation::isInitialized()
{
	return initialized;
}

void ShadowMappingShaderRenderBaseImplementation::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderProgramGlId, 0, "inVertex");
		renderer->setProgramAttributeLocation(renderProgramGlId, 1, "inNormal");
		renderer->setProgramAttributeLocation(renderProgramGlId, 2, "inTextureUV");
	}
	// link
	if (renderer->linkProgram(renderProgramGlId) == false)
		return;

	//	uniforms
	renderUniformTextureUnit = renderer->getProgramUniformLocation(renderProgramGlId, "textureUnit");
	if (renderUniformTextureUnit == -1) return;
	renderUniformTexturePixelWidth = renderer->getProgramUniformLocation(renderProgramGlId, "texturePixelWidth");
	if (renderUniformTexturePixelWidth == -1) return;
	renderUniformTexturePixelHeight = renderer->getProgramUniformLocation(renderProgramGlId, "texturePixelHeight");
	if (renderUniformTexturePixelHeight == -1) return;
	renderUniformDepthBiasMVPMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "depthBiasMVPMatrix");
	if (renderUniformDepthBiasMVPMatrix == -1) return;
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderUniformProjectionMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "projectionMatrix");
		if (renderUniformProjectionMatrix == -1) return;
		renderUniformCameraMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "cameraMatrix");
		if (renderUniformCameraMatrix == -1) return;
	} else {
		renderUniformMVPMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "mvpMatrix");
		if (renderUniformMVPMatrix == -1) return;
		renderUniformNormalMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "normalMatrix");
		if (renderUniformNormalMatrix == -1) return;
	}
	uniformTextureMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(renderProgramGlId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1) return;
	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(renderProgramGlId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1) return;
	uniformDiffuseTextureMaskedTransparency = renderer->getProgramUniformLocation(renderProgramGlId, "diffuseTextureMaskedTransparency");
	if (uniformDiffuseTextureMaskedTransparency == -1) return;
	uniformDiffuseTextureMaskedTransparencyThreshold = renderer->getProgramUniformLocation(renderProgramGlId, "diffuseTextureMaskedTransparencyThreshold");
	if (uniformDiffuseTextureMaskedTransparencyThreshold == -1) return;
	renderUniformLightDirection = renderer->getProgramUniformLocation(renderProgramGlId, "lightDirection");
	if (renderUniformLightDirection == -1) return;
	if (rendererVersion != "gles2") {
		if (renderer->isInstancedRenderingAvailable() == false) {
			renderUniformMVMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "mvMatrix");
			if (renderUniformMVMatrix == -1) return;
		}
		renderUniformLightPosition = renderer->getProgramUniformLocation(renderProgramGlId, "lightPosition");
		if (renderUniformLightPosition == -1) return;
		renderUniformLightSpotExponent = renderer->getProgramUniformLocation(renderProgramGlId, "lightSpotExponent");
		if (renderUniformLightSpotExponent == -1) return;
		renderUniformLightSpotCosCutoff = renderer->getProgramUniformLocation(renderProgramGlId, "lightSpotCosCutoff");
		if (renderUniformLightSpotCosCutoff == -1) return;
		renderUniformLightConstantAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, "lightConstantAttenuation");
		if (renderUniformLightConstantAttenuation == -1) return;
		renderUniformLightLinearAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, "lightLinearAttenuation");
		if (renderUniformLightLinearAttenuation == -1) return;
		renderUniformLightQuadraticAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, "lightQuadraticAttenuation");
		if (renderUniformLightQuadraticAttenuation == -1) return;
	}

	//
	uniformFrame = renderer->getProgramUniformLocation(renderProgramGlId, "frame");

	//
	initialized = true;
}

void ShadowMappingShaderRenderBaseImplementation::useProgram()
{
	renderer->useProgram(renderProgramGlId);
	renderer->setProgramUniformInteger(renderUniformTextureUnit, ShadowMap::TEXTUREUNIT);
	if (uniformFrame != -1) renderer->setProgramUniformInteger(uniformFrame, renderer->frame);
}

void ShadowMappingShaderRenderBaseImplementation::unUseProgram()
{
}

void ShadowMappingShaderRenderBaseImplementation::setProgramViewMatrices() {
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderer->setProgramUniformFloatMatrix4x4(renderUniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
		renderer->setProgramUniformFloatMatrix4x4(renderUniformCameraMatrix, renderer->getCameraMatrix().getArray());
	}
}
void ShadowMappingShaderRenderBaseImplementation::setProgramMVMatrix(const Matrix4x4& mvMatrix)
{
	if (renderer->isInstancedRenderingAvailable() == true) return;
	if (renderUniformMVMatrix == -1) return;
	renderer->setProgramUniformFloatMatrix4x4(renderUniformMVMatrix, mvMatrix.getArray());
}

void ShadowMappingShaderRenderBaseImplementation::setProgramMVPMatrix(const Matrix4x4& mvpMatrix)
{
	if (renderer->isInstancedRenderingAvailable() == true) return;
	renderer->setProgramUniformFloatMatrix4x4(renderUniformMVPMatrix, mvpMatrix.getArray());
}

void ShadowMappingShaderRenderBaseImplementation::setProgramNormalMatrix(const Matrix4x4& normalMatrix)
{
	if (renderer->isInstancedRenderingAvailable() == true) return;
	renderer->setProgramUniformFloatMatrix4x4(renderUniformNormalMatrix, normalMatrix.getArray());
}

void ShadowMappingShaderRenderBaseImplementation::updateTextureMatrix(GLRenderer* renderer) {
	renderer->setProgramUniformFloatMatrix3x3(uniformTextureMatrix, renderer->getTextureMatrix().getArray());
}

void ShadowMappingShaderRenderBaseImplementation::updateMaterial(GLRenderer* renderer)
{
	renderer->setProgramUniformInteger(uniformDiffuseTextureMaskedTransparency, renderer->material.diffuseTextureMaskedTransparency);
	renderer->setProgramUniformFloat(uniformDiffuseTextureMaskedTransparencyThreshold, renderer->material.diffuseTextureMaskedTransparencyThreshold);
}

void ShadowMappingShaderRenderBaseImplementation::updateLight(GLRenderer* renderer, int32_t lightId) {
	if (lightId != this->lightId) {
		return;
	}

	auto& light = renderer->lights[lightId];
	auto lightPosition = Vector3(light.position[0], light.position[1], light.position[2]);
	auto lightSpotDirection = Vector3(light.spotDirection[0], light.spotDirection[1], light.spotDirection[2]);
	if (renderUniformLightPosition != -1) renderer->setProgramUniformFloatVec3(renderUniformLightPosition, lightPosition.getArray());
	if (renderUniformLightDirection != -1) renderer->setProgramUniformFloatVec3(renderUniformLightDirection, lightSpotDirection.getArray());
	if (renderUniformLightSpotExponent != -1) renderer->setProgramUniformFloat(renderUniformLightSpotExponent, light.spotExponent);
	if (renderUniformLightSpotCosCutoff != -1) renderer->setProgramUniformFloat(renderUniformLightSpotCosCutoff, light.spotCosCutoff);
	if (renderUniformLightConstantAttenuation != -1) renderer->setProgramUniformFloat(renderUniformLightConstantAttenuation, light.constantAttenuation);
	if (renderUniformLightLinearAttenuation != -1) renderer->setProgramUniformFloat(renderUniformLightLinearAttenuation, light.linearAttenuation);
	if (renderUniformLightQuadraticAttenuation != -1) renderer->setProgramUniformFloat(renderUniformLightQuadraticAttenuation, light.quadraticAttenuation);
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderer->setProgramUniformFloatMatrix4x4(renderUniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
		renderer->setProgramUniformFloatMatrix4x4(renderUniformCameraMatrix, renderer->getCameraMatrix().getArray());
	}
	renderer->setProgramUniformFloat(renderUniformTexturePixelWidth, 1.0f / static_cast< float >(ShadowMapping::getShadowMapWidth()));
	renderer->setProgramUniformFloat(renderUniformTexturePixelHeight, 1.0f / static_cast< float >(ShadowMapping::getShadowMapHeight()));
}

void ShadowMappingShaderRenderBaseImplementation::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	switch (renderer->getTextureUnit()) {
		case LightingShaderConstants::TEXTUREUNIT_DIFFUSE:
			renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}

void ShadowMappingShaderRenderBaseImplementation::setProgramDepthBiasMVPMatrix(const Matrix4x4& depthBiasMVPMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformDepthBiasMVPMatrix, depthBiasMVPMatrix.getArray());
}

void ShadowMappingShaderRenderBaseImplementation::setRenderLightId(int32_t lightId) {
	this->lightId = lightId;
}
