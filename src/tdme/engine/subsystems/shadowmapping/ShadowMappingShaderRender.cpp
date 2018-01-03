#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>

#include <tdme/math/Math.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

ShadowMappingShaderRender::ShadowMappingShaderRender(GLRenderer* renderer) 
{
	this->renderer = renderer;
	initialized = false;
}


bool ShadowMappingShaderRender::isInitialized()
{
	return initialized;
}

void ShadowMappingShaderRender::initialize()
{
	auto rendererVersion = renderer->getGLVersion();
	// load shadow mapping shaders
	renderVertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"render_vertexshader.c"
	);
	if (renderVertexShaderGlId == 0)
		return;

	renderFragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"render_fragmentshader.c"
	);
	if (renderFragmentShaderGlId == 0)
		return;
	// create shadow mapping render program
	renderProgramGlId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramGlId, renderVertexShaderGlId);
	renderer->attachShaderToProgram(renderProgramGlId, renderFragmentShaderGlId);
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
	if (renderUniformTextureUnit == -1)
		return;
	renderUniformTexturePixelWidth = renderer->getProgramUniformLocation(renderProgramGlId, "texturePixelWidth");
	if (renderUniformTexturePixelWidth == -1)
		return;
	renderUniformTexturePixelHeight = renderer->getProgramUniformLocation(renderProgramGlId, "texturePixelHeight");
	if (renderUniformTexturePixelHeight == -1)
		return;
	renderUniformDepthBiasMVPMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "depthBiasMVPMatrix");
	if (renderUniformDepthBiasMVPMatrix == -1)
		return;
	renderUniformMVMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "mvMatrix");
	if (renderUniformMVMatrix == -1)
		return;
	renderUniformMVPMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "mvpMatrix");
	if (renderUniformMVPMatrix == -1)
		return;
	renderUniformNormalMatrix = renderer->getProgramUniformLocation(renderProgramGlId, "normalMatrix");
	if (renderUniformNormalMatrix == -1)
		return;
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(renderProgramGlId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1)
		return;
	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(renderProgramGlId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1)
		return;
	uniformDiffuseTextureMaskedTransparency = renderer->getProgramUniformLocation(renderProgramGlId, "diffuseTextureMaskedTransparency");
	if (uniformDiffuseTextureMaskedTransparency == -1)
		return;
	renderUniformLightDirection = renderer->getProgramUniformLocation(renderProgramGlId, "lightDirection");
	if (renderUniformLightDirection == -1)
		return;
	if (rendererVersion != "gles2") {
		renderUniformLightPosition = renderer->getProgramUniformLocation(renderProgramGlId, "lightPosition");
		if (renderUniformLightPosition == -1)
			return;
		renderUniformLightSpotExponent = renderer->getProgramUniformLocation(renderProgramGlId, "lightSpotExponent");
		if (renderUniformLightSpotExponent == -1)
			return;
		renderUniformLightSpotCosCutoff = renderer->getProgramUniformLocation(renderProgramGlId, "lightSpotCosCutoff");
		if (renderUniformLightSpotCosCutoff == -1)
			return;
		renderUniformLightConstantAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, "lightConstantAttenuation");
		if (renderUniformLightConstantAttenuation == -1)
			return;
		renderUniformLightLinearAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, "lightLinearAttenuation");
		if (renderUniformLightLinearAttenuation == -1)
			return;
		renderUniformLightQuadraticAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, "lightQuadraticAttenuation");
		if (renderUniformLightQuadraticAttenuation == -1)
			return;
	}
	//
	initialized = true;
}

void ShadowMappingShaderRender::useProgram()
{
	renderer->useProgram(renderProgramGlId);
}

void ShadowMappingShaderRender::unUseProgram()
{
}

void ShadowMappingShaderRender::setProgramTextureUnit(int32_t textureUnit)
{
	renderer->setProgramUniformInteger(renderUniformTextureUnit, textureUnit);
}

void ShadowMappingShaderRender::setProgramTexturePixelDimensions(float width, float height)
{
	renderer->setProgramUniformFloat(renderUniformTexturePixelWidth, width);
	renderer->setProgramUniformFloat(renderUniformTexturePixelHeight, height);
}

void ShadowMappingShaderRender::setProgramMVMatrix(const Matrix4x4& mvMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformMVMatrix, mvMatrix.getArray());
}

void ShadowMappingShaderRender::setProgramMVPMatrix(const Matrix4x4& mvpMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformMVPMatrix, mvpMatrix.getArray());
}

void ShadowMappingShaderRender::setProgramNormalMatrix(const Matrix4x4& normalMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformNormalMatrix, normalMatrix.getArray());
}

void ShadowMappingShaderRender::updateMaterial(GLRenderer* renderer)
{
	renderer->setProgramUniformInteger(uniformDiffuseTextureMaskedTransparency, renderer->material.diffuseTextureMaskedTransparency);
}

void ShadowMappingShaderRender::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	switch (renderer->getTextureUnit()) {
		case LightingShader::TEXTUREUNIT_DIFFUSE:
			renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}

void ShadowMappingShaderRender::setProgramLightPosition(const Vector3& lightPosition)
{
	renderer->setProgramUniformFloatVec3(renderUniformLightPosition, lightPosition.getArray());
}

void ShadowMappingShaderRender::setProgramLightDirection(const Vector3& lightDirection)
{
	renderer->setProgramUniformFloatVec3(renderUniformLightDirection, lightDirection.getArray());
}

void ShadowMappingShaderRender::setProgramDepthBiasMVPMatrix(const Matrix4x4& depthBiasMVPMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformDepthBiasMVPMatrix, depthBiasMVPMatrix.getArray());
}

void ShadowMappingShaderRender::setProgramLightSpotExponent(float spotExponent)
{
	renderer->setProgramUniformFloat(renderUniformLightSpotExponent, spotExponent);
}

void ShadowMappingShaderRender::setProgramLightSpotCosCutOff(float spotCosCutOff)
{
	renderer->setProgramUniformFloat(renderUniformLightSpotCosCutoff, Math::cos(Math::PI / 180.0f * spotCosCutOff));
}

void ShadowMappingShaderRender::setProgramLightConstantAttenuation(float constantAttenuation)
{
	renderer->setProgramUniformFloat(renderUniformLightConstantAttenuation, constantAttenuation);
}

void ShadowMappingShaderRender::setProgramLightLinearAttenuation(float linearAttenuation)
{
	renderer->setProgramUniformFloat(renderUniformLightLinearAttenuation, linearAttenuation);
}

void ShadowMappingShaderRender::setProgramLightQuadraticAttenuation(float quadraticAttenuation)
{
	renderer->setProgramUniformFloat(renderUniformLightQuadraticAttenuation, quadraticAttenuation);
}
