// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.java
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using java::lang::Math;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

ShadowMappingShaderRender::ShadowMappingShaderRender(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ShadowMappingShaderRender::ShadowMappingShaderRender(GLRenderer* renderer) 
	: ShadowMappingShaderRender(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer);
}

void ShadowMappingShaderRender::ctor(GLRenderer* renderer)
{
	super::ctor();
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
	renderVertexShaderGlId = renderer->loadShader(renderer->SHADER_VERTEX_SHADER, ::java::lang::StringBuilder().append(u"shader/"_j)->append(rendererVersion)
		->append(u"/shadowmapping"_j)->toString(), u"render_vertexshader.c"_j);
	if (renderVertexShaderGlId == 0)
		return;

	renderFragmentShaderGlId = renderer->loadShader(renderer->SHADER_FRAGMENT_SHADER, ::java::lang::StringBuilder().append(u"shader/"_j)->append(rendererVersion)
		->append(u"/shadowmapping"_j)->toString(), u"render_fragmentshader.c"_j);
	if (renderFragmentShaderGlId == 0)
		return;

	renderProgramGlId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramGlId, renderVertexShaderGlId);
	renderer->attachShaderToProgram(renderProgramGlId, renderFragmentShaderGlId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderProgramGlId, 0, u"inVertex"_j);
		renderer->setProgramAttributeLocation(renderProgramGlId, 1, u"inNormal"_j);
		renderer->setProgramAttributeLocation(renderProgramGlId, 2, u"inTextureUV"_j);
	}
	if (renderer->linkProgram(renderProgramGlId) == false)
		return;

	renderUniformTextureUnit = renderer->getProgramUniformLocation(renderProgramGlId, u"textureUnit"_j);
	if (renderUniformTextureUnit == -1)
		return;

	renderUniformTexturePixelWidth = renderer->getProgramUniformLocation(renderProgramGlId, u"texturePixelWidth"_j);
	if (renderUniformTexturePixelWidth == -1)
		return;

	renderUniformTexturePixelHeight = renderer->getProgramUniformLocation(renderProgramGlId, u"texturePixelHeight"_j);
	if (renderUniformTexturePixelHeight == -1)
		return;

	renderUniformDepthBiasMVPMatrix = renderer->getProgramUniformLocation(renderProgramGlId, u"depthBiasMVPMatrix"_j);
	if (renderUniformDepthBiasMVPMatrix == -1)
		return;

	renderUniformMVMatrix = renderer->getProgramUniformLocation(renderProgramGlId, u"mvMatrix"_j);
	if (renderUniformMVMatrix == -1)
		return;

	renderUniformMVPMatrix = renderer->getProgramUniformLocation(renderProgramGlId, u"mvpMatrix"_j);
	if (renderUniformMVPMatrix == -1)
		return;

	renderUniformNormalMatrix = renderer->getProgramUniformLocation(renderProgramGlId, u"normalMatrix"_j);
	if (renderUniformNormalMatrix == -1)
		return;

	renderUniformLightDirection = renderer->getProgramUniformLocation(renderProgramGlId, u"lightDirection"_j);
	if (renderUniformLightDirection == -1)
		return;

	if (rendererVersion->equals(u"gles2"_j) == false) {
		renderUniformLightPosition = renderer->getProgramUniformLocation(renderProgramGlId, u"lightPosition"_j);
		if (renderUniformLightPosition == -1)
			return;

		renderUniformLightSpotExponent = renderer->getProgramUniformLocation(renderProgramGlId, u"lightSpotExponent"_j);
		if (renderUniformLightSpotExponent == -1)
			return;

		renderUniformLightSpotCosCutoff = renderer->getProgramUniformLocation(renderProgramGlId, u"lightSpotCosCutoff"_j);
		if (renderUniformLightSpotCosCutoff == -1)
			return;

		renderUniformLightConstantAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, u"lightConstantAttenuation"_j);
		if (renderUniformLightConstantAttenuation == -1)
			return;

		renderUniformLightLinearAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, u"lightLinearAttenuation"_j);
		if (renderUniformLightLinearAttenuation == -1)
			return;

		renderUniformLightQuadraticAttenuation = renderer->getProgramUniformLocation(renderProgramGlId, u"lightQuadraticAttenuation"_j);
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

void ShadowMappingShaderRender::setProgramDepthBiasMVPMatrix(Matrix4x4* depthBiasMVPMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(renderUniformDepthBiasMVPMatrix, depthBiasMVPMatrix->getArray());
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

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ShadowMappingShaderRender::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.shadowmapping.ShadowMappingShaderRender", 62);
    return c;
}

java::lang::Class* ShadowMappingShaderRender::getClass0()
{
	return class_();
}

