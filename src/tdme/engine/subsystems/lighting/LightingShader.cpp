// Generated from /tdme/src/tdme/engine/subsystems/lighting/LightingShader.java
#include <tdme/engine/subsystems/lighting/LightingShader.h>

#include <algorithm>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Light.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Material.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <Array.h>

using std::copy;
using std::begin;
using std::end;

using tdme::engine::subsystems::lighting::LightingShader;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using tdme::engine::subsystems::renderer::GLRenderer_Light;
using tdme::engine::subsystems::renderer::GLRenderer_Material;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

LightingShader::LightingShader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LightingShader::LightingShader(GLRenderer* renderer) 
	: LightingShader(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer);
}

void LightingShader::init()
{
}

constexpr int32_t LightingShader::MAX_LIGHTS;

constexpr int32_t LightingShader::TEXTUREUNIT_DIFFUSE;

constexpr int32_t LightingShader::TEXTUREUNIT_SPECULAR;

constexpr int32_t LightingShader::TEXTUREUNIT_DISPLACEMENT;

constexpr int32_t LightingShader::TEXTUREUNIT_NORMAL;

void LightingShader::ctor(GLRenderer* renderer)
{
	super::ctor();
	init();
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
	uniformLightEnabled = new int32_tArray(MAX_LIGHTS);
	uniformLightAmbient = new int32_tArray(MAX_LIGHTS);
	uniformLightDiffuse = new int32_tArray(MAX_LIGHTS);
	uniformLightSpecular = new int32_tArray(MAX_LIGHTS);
	uniformLightPosition = new int32_tArray(MAX_LIGHTS);
	uniformLightSpotDirection = new int32_tArray(MAX_LIGHTS);
	uniformLightSpotExponent = new int32_tArray(MAX_LIGHTS);
	uniformLightSpotCosCutoff = new int32_tArray(MAX_LIGHTS);
	uniformLightConstantAttenuation = new int32_tArray(MAX_LIGHTS);
	uniformLightLinearAttenuation = new int32_tArray(MAX_LIGHTS);
	uniformLightQuadraticAttenuation = new int32_tArray(MAX_LIGHTS);
	mvMatrix = new Matrix4x4();
	mvpMatrix = new Matrix4x4();
	normalMatrix = new Matrix4x4();
}

bool LightingShader::isInitialized()
{
	return initialized;
}

void LightingShader::initialize()
{
	auto rendererVersion = renderer->getGLVersion();
	renderLightingFragmentShaderId = renderer->loadShader(renderer->SHADER_FRAGMENT_SHADER, ::java::lang::StringBuilder().append(u"shader/"_j)->append(rendererVersion)
		->append(u"/lighting"_j)->toString(), u"render_fragmentshader.c"_j);
	if (renderLightingFragmentShaderId == 0)
		return;

	renderLightingVertexShaderId = renderer->loadShader(renderer->SHADER_VERTEX_SHADER, ::java::lang::StringBuilder().append(u"shader/"_j)->append(rendererVersion)
		->append(u"/lighting"_j)->toString(), u"render_vertexshader.c"_j);
	if (renderLightingVertexShaderId == 0)
		return;

	renderLightingProgramId = renderer->createProgram();
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingVertexShaderId);
	renderer->attachShaderToProgram(renderLightingProgramId, renderLightingFragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderLightingProgramId, 0, u"inVertex"_j);
		renderer->setProgramAttributeLocation(renderLightingProgramId, 1, u"inNormal"_j);
		renderer->setProgramAttributeLocation(renderLightingProgramId, 2, u"inTextureUV"_j);
	}
	if (renderer->linkProgram(renderLightingProgramId) == false)
		return;

	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, u"diffuseTextureUnit"_j);
	if (uniformDiffuseTextureUnit == -1)
		return;

	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, u"diffuseTextureAvailable"_j);
	if (uniformDiffuseTextureAvailable == -1)
		return;

	if (renderer->isDisplacementMappingAvailable() == true) {
		uniformDisplacementTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, u"displacementTextureUnit"_j);
		if (uniformDisplacementTextureUnit == -1)
			return;

		uniformDisplacementTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, u"displacementTextureAvailable"_j);
		if (uniformDisplacementTextureAvailable == -1)
			return;

	}
	if (renderer->isSpecularMappingAvailable()) {
		uniformSpecularTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, u"specularTextureUnit"_j);
		if (uniformSpecularTextureUnit == -1)
			return;

		uniformSpecularTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, u"specularTextureAvailable"_j);
		if (uniformSpecularTextureAvailable == -1)
			return;

	}
	if (renderer->isNormalMappingAvailable()) {
		uniformNormalTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, u"normalTextureUnit"_j);
		if (uniformNormalTextureUnit == -1)
			return;

		uniformNormalTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, u"normalTextureAvailable"_j);
		if (uniformNormalTextureAvailable == -1)
			return;

	}
	uniformMVPMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, u"mvpMatrix"_j);
	if (uniformMVPMatrix == -1)
		return;

	uniformMVMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, u"mvMatrix"_j);
	if (uniformMVMatrix == -1)
		return;

	uniformNormalMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, u"normalMatrix"_j);
	if (uniformNormalMatrix == -1)
		return;

	uniformSceneColor = renderer->getProgramUniformLocation(renderLightingProgramId, u"sceneColor"_j);
	if (uniformSceneColor == -1)
		return;

	uniformEffectColorMul = renderer->getProgramUniformLocation(renderLightingProgramId, u"effectColorMul"_j);
	if (uniformEffectColorMul == -1)
		return;

	uniformEffectColorAdd = renderer->getProgramUniformLocation(renderLightingProgramId, u"effectColorAdd"_j);
	if (uniformEffectColorAdd == -1)
		return;

	uniformMaterialAmbient = renderer->getProgramUniformLocation(renderLightingProgramId, u"material.ambient"_j);
	if (uniformMaterialAmbient == -1)
		return;

	uniformMaterialDiffuse = renderer->getProgramUniformLocation(renderLightingProgramId, u"material.diffuse"_j);
	if (uniformMaterialDiffuse == -1)
		return;

	uniformMaterialSpecular = renderer->getProgramUniformLocation(renderLightingProgramId, u"material.specular"_j);
	if (uniformMaterialSpecular == -1)
		return;

	uniformMaterialEmission = renderer->getProgramUniformLocation(renderLightingProgramId, u"material.emission"_j);
	if (uniformMaterialEmission == -1)
		return;

	uniformMaterialShininess = renderer->getProgramUniformLocation(renderLightingProgramId, u"material.shininess"_j);
	if (uniformMaterialShininess == -1)
		return;

	for (auto i = 0; i < MAX_LIGHTS; i++) {
		(*uniformLightEnabled)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].enabled"_j)->toString());
		if ((*uniformLightEnabled)[i] == -1)
			return;

		(*uniformLightAmbient)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].ambient"_j)->toString());
		if ((*uniformLightAmbient)[i] == -1)
			return;

		(*uniformLightDiffuse)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].diffuse"_j)->toString());
		if ((*uniformLightDiffuse)[i] == -1)
			return;

		(*uniformLightSpecular)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].specular"_j)->toString());
		if ((*uniformLightSpecular)[i] == -1)
			return;

		(*uniformLightPosition)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].position"_j)->toString());
		if ((*uniformLightPosition)[i] == -1)
			return;

		(*uniformLightSpotDirection)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].spotDirection"_j)->toString());
		if ((*uniformLightSpotDirection)[i] == -1)
			return;

		(*uniformLightSpotExponent)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].spotExponent"_j)->toString());
		if ((*uniformLightSpotExponent)[i] == -1)
			return;

		(*uniformLightSpotCosCutoff)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].spotCosCutoff"_j)->toString());
		if ((*uniformLightSpotCosCutoff)[i] == -1)
			return;

		(*uniformLightConstantAttenuation)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].constantAttenuation"_j)->toString());
		if ((*uniformLightConstantAttenuation)[i] == -1)
			return;

		(*uniformLightLinearAttenuation)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].linearAttenuation"_j)->toString());
		if ((*uniformLightLinearAttenuation)[i] == -1)
			return;

		(*uniformLightQuadraticAttenuation)[i] = renderer->getProgramUniformLocation(renderLightingProgramId, ::java::lang::StringBuilder().append(u"lights["_j)->append(i)
			->append(u"].quadraticAttenuation"_j)->toString());
		if ((*uniformLightQuadraticAttenuation)[i] == -1)
			return;

	}
	initialized = true;
}

void LightingShader::useProgram()
{
	isRunning = true;
	renderer->useProgram(renderLightingProgramId);
	renderer->setProgramUniformInteger(uniformDiffuseTextureUnit, TEXTUREUNIT_DIFFUSE);
	if (renderer->isSpecularMappingAvailable() == true) {
		renderer->setProgramUniformInteger(uniformSpecularTextureUnit, TEXTUREUNIT_SPECULAR);
	}
	if (renderer->isNormalMappingAvailable() == true) {
		renderer->setProgramUniformInteger(uniformNormalTextureUnit, TEXTUREUNIT_NORMAL);
	}
	if (renderer->isDisplacementMappingAvailable() == true) {
		renderer->setProgramUniformInteger(uniformDisplacementTextureUnit, TEXTUREUNIT_DISPLACEMENT);
	}
	renderer->setProgramUniformFloatVec4(uniformSceneColor, &defaultSceneColor);
	updateEffect(renderer);
	updateMaterial(renderer);
	for (auto i = 0; i < MAX_LIGHTS; i++) {
		updateLight(renderer, i);
	}
}

void LightingShader::unUseProgram()
{
	isRunning = false;
}

void LightingShader::updateEffect(GLRenderer* renderer)
{
	if (isRunning == false)
		return;

	renderer->setProgramUniformFloatVec4(uniformEffectColorMul, &renderer->effectColorMul);
	renderer->setProgramUniformFloatVec4(uniformEffectColorAdd, &renderer->effectColorAdd);
}

void LightingShader::updateMaterial(GLRenderer* renderer)
{
	if (isRunning == false)
		return;

	tmpColor4[3] = 0.0f;
	copy(begin(renderer->material.ambient), end(renderer->material.ambient), begin(tmpColor4));
	renderer->setProgramUniformFloatVec4(uniformMaterialAmbient, &tmpColor4);
	renderer->setProgramUniformFloatVec4(uniformMaterialDiffuse, &renderer->material.diffuse);
	copy(begin(renderer->material.specular), end(renderer->material.specular), begin(tmpColor4));
	renderer->setProgramUniformFloatVec4(uniformMaterialSpecular, &tmpColor4);
	copy(begin(renderer->material.emission), end(renderer->material.emission), begin(tmpColor4));
	renderer->setProgramUniformFloatVec4(uniformMaterialEmission, &tmpColor4);
	renderer->setProgramUniformFloat(uniformMaterialShininess, renderer->material.shininess);
}

void LightingShader::updateLight(GLRenderer* renderer, int32_t lightId)
{
	if (isRunning == false)
		return;

	renderer->setProgramUniformInteger((*uniformLightEnabled)[lightId], renderer->lights[lightId].enabled);
	if (renderer->lights[lightId].enabled == 1) {
		renderer->setProgramUniformFloatVec4((*uniformLightAmbient)[lightId], &renderer->lights[lightId].ambient);
		renderer->setProgramUniformFloatVec4((*uniformLightDiffuse)[lightId], &renderer->lights[lightId].diffuse);
		renderer->setProgramUniformFloatVec4((*uniformLightSpecular)[lightId], &renderer->lights[lightId].specular);
		renderer->setProgramUniformFloatVec4((*uniformLightPosition)[lightId], &renderer->lights[lightId].position);
		renderer->setProgramUniformFloatVec3((*uniformLightSpotDirection)[lightId], &renderer->lights[lightId].spotDirection);
		renderer->setProgramUniformFloat((*uniformLightSpotExponent)[lightId], renderer->lights[lightId].spotExponent);
		renderer->setProgramUniformFloat((*uniformLightSpotCosCutoff)[lightId], renderer->lights[lightId].spotCosCutoff);
		renderer->setProgramUniformFloat((*uniformLightConstantAttenuation)[lightId], renderer->lights[lightId].constantAttenuation);
		renderer->setProgramUniformFloat((*uniformLightLinearAttenuation)[lightId], renderer->lights[lightId].linearAttenuation);
		renderer->setProgramUniformFloat((*uniformLightQuadraticAttenuation)[lightId], renderer->lights[lightId].quadraticAttenuation);
	}
}

void LightingShader::updateMatrices(GLRenderer* renderer)
{
	if (isRunning == false)
		return;

	mvMatrix->set(renderer->getModelViewMatrix());
	mvpMatrix->set(mvMatrix)->multiply(renderer->getProjectionMatrix());
	normalMatrix->set(mvMatrix)->invert()->transpose();
	renderer->setProgramUniformFloatMatrix4x4(uniformMVPMatrix, mvpMatrix->getArray());
	renderer->setProgramUniformFloatMatrix4x4(uniformMVMatrix, mvMatrix->getArray());
	renderer->setProgramUniformFloatMatrix4x4(uniformNormalMatrix, normalMatrix->getArray());
}

void LightingShader::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	if (isRunning == false)
		return;

	switch (renderer->getTextureUnit()) {
	case TEXTUREUNIT_DIFFUSE:
		renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
		break;
	case TEXTUREUNIT_SPECULAR:
		if (renderer->isSpecularMappingAvailable() == false)
			break;

		renderer->setProgramUniformInteger(uniformSpecularTextureAvailable, textureId == 0 ? 0 : 1);
		break;
	case TEXTUREUNIT_NORMAL:
		if (renderer->isNormalMappingAvailable() == false)
			break;

		renderer->setProgramUniformInteger(uniformNormalTextureAvailable, textureId == 0 ? 0 : 1);
		break;
	case TEXTUREUNIT_DISPLACEMENT:
		if (renderer->isDisplacementMappingAvailable() == false)
			break;

		renderer->setProgramUniformInteger(uniformDisplacementTextureAvailable, textureId == 0 ? 0 : 1);
		break;
	}

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LightingShader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.lighting.LightingShader", 46);
    return c;
}

java::lang::Class* LightingShader::getClass0()
{
	return class_();
}

