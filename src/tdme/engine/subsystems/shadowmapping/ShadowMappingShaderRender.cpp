#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>

#include <tdme/math/Math.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::math::Math;
using tdme::engine::subsystems::renderer::GLRenderer;
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
	renderVertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		L"shader/" + rendererVersion + L"/shadowmapping",
		L"render_vertexshader.c"
	);
	if (renderVertexShaderGlId == 0)
		return;

	renderFragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		L"shader/" + rendererVersion + L"/shadowmapping",
		L"render_fragmentshader.c"
	);
	if (renderFragmentShaderGlId == 0)
		return;

	renderProgramGlId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramGlId, renderVertexShaderGlId);
	renderer->attachShaderToProgram(renderProgramGlId, renderFragmentShaderGlId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderProgramGlId, 0, L"inVertex");
		renderer->setProgramAttributeLocation(renderProgramGlId, 1, L"inNormal");
		renderer->setProgramAttributeLocation(renderProgramGlId, 2, L"inTextureUV");
	}
	if (renderer->linkProgram(renderProgramGlId) == false)
		return;

	renderUniformTextureUnit = renderer->getProgramUniformLocation(renderProgramGlId, L"textureUnit");
	if (renderUniformTextureUnit == -1)
		return;

	renderUniformTexturePixelWidth = renderer->getProgramUniformLocation(renderProgramGlId, L"texturePixelWidth");
	if (renderUniformTexturePixelWidth == -1)
		return;

	renderUniformTexturePixelHeight = renderer->getProgramUniformLocation(renderProgramGlId, L"texturePixelHeight");
	if (renderUniformTexturePixelHeight == -1)
		return;

	renderUniformDepthBiasMVPMatrix = renderer->getProgramUniformLocation(renderProgramGlId, L"depthBiasMVPMatrix");
	if (renderUniformDepthBiasMVPMatrix == -1)
		return;

	renderUniformMVMatrix = renderer->getProgramUniformLocation(renderProgramGlId, L"mvMatrix");
	if (renderUniformMVMatrix == -1)
		return;

	renderUniformMVPMatrix = renderer->getProgramUniformLocation(renderProgramGlId, L"mvpMatrix");
	if (renderUniformMVPMatrix == -1)
		return;

	renderUniformNormalMatrix = renderer->getProgramUniformLocation(renderProgramGlId, L"normalMatrix");
	if (renderUniformNormalMatrix == -1)
		return;

	renderUniformLightDirection = renderer->getProgramUniformLocation(renderProgramGlId, L"lightDirection");
	if (renderUniformLightDirection == -1)
		return;

	if (rendererVersion != L"gles2") {
		renderUniformLightPosition = renderer->getProgramUniformLocation(renderProgramGlId, L"lightPosition");
		if (renderUniformLightPosition == -1)
			return;

		renderUniformLightSpotExponent = renderer->getProgramUniformLocation(renderProgramGlId, L"lightSpotExponent");
		if (renderUniformLightSpotExponent == -1)
			return;

		renderUniformLightSpotCosCutoff = renderer->getProgramUniformLocation(renderProgramGlId, L"lightSpotCosCutoff");
		if (renderUniformLightSpotCosCutoff == -1)
			return;

		renderUniformLightConstantAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, L"lightConstantAttenuation");
		if (renderUniformLightConstantAttenuation == -1)
			return;

		renderUniformLightLinearAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, L"lightLinearAttenuation");
		if (renderUniformLightLinearAttenuation == -1)
			return;

		renderUniformLightQuadraticAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, L"lightQuadraticAttenuation");
		if (renderUniformLightQuadraticAttenuation == -1)
			return;

	}
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

void ShadowMappingShaderRender::setProgramMVMatrix(Matrix4x4* mvMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformMVMatrix, mvMatrix->getArray());
}

void ShadowMappingShaderRender::setProgramMVPMatrix(Matrix4x4* mvpMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformMVPMatrix, mvpMatrix->getArray());
}

void ShadowMappingShaderRender::setProgramNormalMatrix(Matrix4x4* normalMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformNormalMatrix, normalMatrix->getArray());
}

void ShadowMappingShaderRender::setProgramLightPosition(Vector3* lightPosition)
{
	renderer->setProgramUniformFloatVec3(renderUniformLightPosition, lightPosition->getArray());
}

void ShadowMappingShaderRender::setProgramLightDirection(Vector3* lightDirection)
{
	renderer->setProgramUniformFloatVec3(renderUniformLightDirection, lightDirection->getArray());
}

void ShadowMappingShaderRender::setProgramDepthBiasMVPMatrix(Matrix4x4& depthBiasMVPMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformDepthBiasMVPMatrix, depthBiasMVPMatrix.getArray());
}

void ShadowMappingShaderRender::setProgramLightSpotExponent(float spotExponent)
{
	renderer->setProgramUniformFloat(renderUniformLightSpotExponent, spotExponent);
}

void ShadowMappingShaderRender::setProgramLightSpotCosCutOff(float spotCosCutOff)
{
	renderer->setProgramUniformFloat(renderUniformLightSpotCosCutoff, static_cast< float >(Math::cos(Math::PI / 180.0f * spotCosCutOff)));
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
