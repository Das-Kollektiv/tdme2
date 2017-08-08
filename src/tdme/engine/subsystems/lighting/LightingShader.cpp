// Generated from /tdme/src/tdme/engine/subsystems/lighting/LightingShader.java
#include <tdme/engine/subsystems/lighting/LightingShader.h>

#include <algorithm>
#include <string>

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
using std::to_wstring;
using std::wstring;

using tdme::engine::subsystems::lighting::LightingShader;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using tdme::engine::subsystems::renderer::GLRenderer_Light;
using tdme::engine::subsystems::renderer::GLRenderer_Material;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

LightingShader::LightingShader(GLRenderer* renderer) 
{
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
}

constexpr int32_t LightingShader::MAX_LIGHTS;

constexpr int32_t LightingShader::TEXTUREUNIT_DIFFUSE;

constexpr int32_t LightingShader::TEXTUREUNIT_SPECULAR;

constexpr int32_t LightingShader::TEXTUREUNIT_DISPLACEMENT;

constexpr int32_t LightingShader::TEXTUREUNIT_NORMAL;

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
		renderer->setProgramAttributeLocation(renderLightingProgramId, 0, L"inVertex");
		renderer->setProgramAttributeLocation(renderLightingProgramId, 1, L"inNormal");
		renderer->setProgramAttributeLocation(renderLightingProgramId, 2, L"inTextureUV");
	}
	if (renderer->linkProgram(renderLightingProgramId) == false)
		return;

	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, L"diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1)
		return;

	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, L"diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1)
		return;

	if (renderer->isDisplacementMappingAvailable() == true) {
		uniformDisplacementTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, L"displacementTextureUnit");
		if (uniformDisplacementTextureUnit == -1)
			return;

		uniformDisplacementTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, L"displacementTextureAvailable");
		if (uniformDisplacementTextureAvailable == -1)
			return;

	}
	if (renderer->isSpecularMappingAvailable()) {
		uniformSpecularTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, L"specularTextureUnit");
		if (uniformSpecularTextureUnit == -1)
			return;

		uniformSpecularTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, L"specularTextureAvailable");
		if (uniformSpecularTextureAvailable == -1)
			return;

	}
	if (renderer->isNormalMappingAvailable()) {
		uniformNormalTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, L"normalTextureUnit");
		if (uniformNormalTextureUnit == -1)
			return;

		uniformNormalTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, L"normalTextureAvailable");
		if (uniformNormalTextureAvailable == -1)
			return;

	}
	uniformMVPMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, L"mvpMatrix");
	if (uniformMVPMatrix == -1)
		return;

	uniformMVMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, L"mvMatrix");
	if (uniformMVMatrix == -1)
		return;

	uniformNormalMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, L"normalMatrix");
	if (uniformNormalMatrix == -1)
		return;

	uniformSceneColor = renderer->getProgramUniformLocation(renderLightingProgramId, L"sceneColor");
	if (uniformSceneColor == -1)
		return;

	uniformEffectColorMul = renderer->getProgramUniformLocation(renderLightingProgramId, L"effectColorMul");
	if (uniformEffectColorMul == -1)
		return;

	uniformEffectColorAdd = renderer->getProgramUniformLocation(renderLightingProgramId, L"effectColorAdd");
	if (uniformEffectColorAdd == -1)
		return;

	uniformMaterialAmbient = renderer->getProgramUniformLocation(renderLightingProgramId, L"material.ambient");
	if (uniformMaterialAmbient == -1)
		return;

	uniformMaterialDiffuse = renderer->getProgramUniformLocation(renderLightingProgramId, L"material.diffuse");
	if (uniformMaterialDiffuse == -1)
		return;

	uniformMaterialSpecular = renderer->getProgramUniformLocation(renderLightingProgramId, L"material.specular");
	if (uniformMaterialSpecular == -1)
		return;

	uniformMaterialEmission = renderer->getProgramUniformLocation(renderLightingProgramId, L"material.emission");
	if (uniformMaterialEmission == -1)
		return;

	uniformMaterialShininess = renderer->getProgramUniformLocation(renderLightingProgramId, L"material.shininess");
	if (uniformMaterialShininess == -1)
		return;

	for (auto i = 0; i < MAX_LIGHTS; i++) {
		uniformLightEnabled[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) +L"].enabled");
		if (uniformLightEnabled[i] == -1)
			return;

		uniformLightAmbient[i] = renderer->getProgramUniformLocation(renderLightingProgramId,L"lights[" + to_wstring(i) + L"].ambient");
		if (uniformLightAmbient[i] == -1)
			return;

		uniformLightDiffuse[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].diffuse");
		if (uniformLightDiffuse[i] == -1)
			return;

		uniformLightSpecular[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].specular");
		if (uniformLightSpecular[i] == -1)
			return;

		uniformLightPosition[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].position");
		if (uniformLightPosition[i] == -1)
			return;

		uniformLightSpotDirection[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].spotDirection");
		if (uniformLightSpotDirection[i] == -1)
			return;

		uniformLightSpotExponent[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].spotExponent");
		if (uniformLightSpotExponent[i] == -1)
			return;

		uniformLightSpotCosCutoff[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].spotCosCutoff");
		if (uniformLightSpotCosCutoff[i] == -1)
			return;

		uniformLightConstantAttenuation[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].constantAttenuation");
		if (uniformLightConstantAttenuation[i] == -1)
			return;

		uniformLightLinearAttenuation[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].linearAttenuation");
		if (uniformLightLinearAttenuation[i] == -1)
			return;

		uniformLightQuadraticAttenuation[i] = renderer->getProgramUniformLocation(renderLightingProgramId, L"lights[" + to_wstring(i) + L"].quadraticAttenuation");
		if (uniformLightQuadraticAttenuation[i] == -1)
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

	renderer->setProgramUniformInteger(uniformLightEnabled[lightId], renderer->lights[lightId].enabled);
	if (renderer->lights[lightId].enabled == 1) {
		renderer->setProgramUniformFloatVec4(uniformLightAmbient[lightId], &renderer->lights[lightId].ambient);
		renderer->setProgramUniformFloatVec4(uniformLightDiffuse[lightId], &renderer->lights[lightId].diffuse);
		renderer->setProgramUniformFloatVec4(uniformLightSpecular[lightId], &renderer->lights[lightId].specular);
		renderer->setProgramUniformFloatVec4(uniformLightPosition[lightId], &renderer->lights[lightId].position);
		renderer->setProgramUniformFloatVec3(uniformLightSpotDirection[lightId], &renderer->lights[lightId].spotDirection);
		renderer->setProgramUniformFloat(uniformLightSpotExponent[lightId], renderer->lights[lightId].spotExponent);
		renderer->setProgramUniformFloat(uniformLightSpotCosCutoff[lightId], renderer->lights[lightId].spotCosCutoff);
		renderer->setProgramUniformFloat(uniformLightConstantAttenuation[lightId], renderer->lights[lightId].constantAttenuation);
		renderer->setProgramUniformFloat(uniformLightLinearAttenuation[lightId], renderer->lights[lightId].linearAttenuation);
		renderer->setProgramUniformFloat(uniformLightQuadraticAttenuation[lightId], renderer->lights[lightId].quadraticAttenuation);
	}
}

void LightingShader::updateMatrices(GLRenderer* renderer)
{
	if (isRunning == false)
		return;

	mvMatrix.set(renderer->getModelViewMatrix());
	mvpMatrix.set(&mvMatrix)->multiply(renderer->getProjectionMatrix());
	normalMatrix.set(&mvMatrix)->invert()->transpose();
	renderer->setProgramUniformFloatMatrix4x4(uniformMVPMatrix, mvpMatrix.getArray());
	renderer->setProgramUniformFloatMatrix4x4(uniformMVMatrix, mvMatrix.getArray());
	renderer->setProgramUniformFloatMatrix4x4(uniformNormalMatrix, normalMatrix.getArray());
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
