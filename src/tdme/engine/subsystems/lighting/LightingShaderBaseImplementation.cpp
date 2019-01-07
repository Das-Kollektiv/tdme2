#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Light.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Material.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/Console.h>

using std::to_string;
using std::string;

using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::GLRenderer_Light;
using tdme::engine::subsystems::renderer::GLRenderer_Material;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::utils::Console;

LightingShaderBaseImplementation::LightingShaderBaseImplementation(GLRenderer* renderer)
{
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
}

bool LightingShaderBaseImplementation::isInitialized()
{
	return initialized;
}

void LightingShaderBaseImplementation::initialize()
{
	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderLightingProgramId, 0, "inVertex");
		renderer->setProgramAttributeLocation(renderLightingProgramId, 1, "inNormal");
		renderer->setProgramAttributeLocation(renderLightingProgramId, 2, "inTextureUV");
	}

	// link program
	if (renderer->linkProgram(renderLightingProgramId) == false) return;

	// get uniforms
	//	globals
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, "diffuseTextureUnit");
	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, "diffuseTextureAvailable");
	uniformDiffuseTextureMaskedTransparency = renderer->getProgramUniformLocation(renderLightingProgramId, "diffuseTextureMaskedTransparency");
	uniformDiffuseTextureMaskedTransparencyThreshold = renderer->getProgramUniformLocation(renderLightingProgramId, "diffuseTextureMaskedTransparencyThreshold");

	if (renderer->isDisplacementMappingAvailable() == true) {
		uniformDisplacementTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, "displacementTextureUnit");
		if (uniformDisplacementTextureUnit == -1) return;

		uniformDisplacementTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, "displacementTextureAvailable");
		if (uniformDisplacementTextureAvailable == -1) return;

	}
	if (renderer->isSpecularMappingAvailable()) {
		uniformSpecularTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, "specularTextureUnit");
		uniformSpecularTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, "specularTextureAvailable");

	}
	if (renderer->isNormalMappingAvailable()) {
		uniformNormalTextureUnit = renderer->getProgramUniformLocation(renderLightingProgramId, "normalTextureUnit");
		uniformNormalTextureAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, "normalTextureAvailable");
	}

	// texture matrix
	uniformTextureMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;

	// matrices as uniform only if not using instanced rendering
	if (renderer->isInstancedRenderingAvailable() == false) {
		uniformMVPMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, "mvpMatrix");
		if (uniformMVPMatrix == -1) return;

		uniformMVMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, "mvMatrix");
		if (uniformMVMatrix == -1) return;

		uniformNormalMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, "normalMatrix");
		if (uniformNormalMatrix == -1) return;

		uniformEffectColorMul = renderer->getProgramUniformLocation(renderLightingProgramId, "effectColorMul");
		if (uniformEffectColorMul == -1) return;

		uniformEffectColorAdd = renderer->getProgramUniformLocation(renderLightingProgramId, "effectColorAdd");
		if (uniformEffectColorAdd == -1) return;
	} else {
		uniformCameraMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, "cameraMatrix");
		if (uniformCameraMatrix == -1) return;
		uniformProjectionMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, "projectionMatrix");
		if (uniformProjectionMatrix == -1) return;
	}

	//	material
	uniformMaterialAmbient = renderer->getProgramUniformLocation(renderLightingProgramId, "material.ambient");
	uniformMaterialDiffuse = renderer->getProgramUniformLocation(renderLightingProgramId, "material.diffuse");
	if (uniformMaterialDiffuse == -1) return;

	uniformMaterialSpecular = renderer->getProgramUniformLocation(renderLightingProgramId, "material.specular");

	uniformMaterialEmission = renderer->getProgramUniformLocation(renderLightingProgramId, "material.emission");
	if (uniformMaterialEmission == -1) return;

	uniformMaterialShininess = renderer->getProgramUniformLocation(renderLightingProgramId, "material.shininess");

	//	lights
	for (auto i = 0; i < LightingShaderConstants::MAX_LIGHTS; i++) {
		uniformLightEnabled[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) +"].enabled");
		uniformLightAmbient[i] = renderer->getProgramUniformLocation(renderLightingProgramId,"lights[" + to_string(i) + "].ambient");
		uniformLightDiffuse[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].diffuse");
		uniformLightSpecular[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].specular");
		uniformLightPosition[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].position");
		uniformLightSpotDirection[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].spotDirection");
		uniformLightSpotExponent[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].spotExponent");
		uniformLightSpotCosCutoff[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].spotCosCutoff");
		uniformLightConstantAttenuation[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].constantAttenuation");
		uniformLightLinearAttenuation[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].linearAttenuation");
		uniformLightQuadraticAttenuation[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "lights[" + to_string(i) + "].quadraticAttenuation");
	}

	// use foliage animation
	uniformFrame = renderer->getProgramUniformLocation(renderLightingProgramId, "frame");

	//
	initialized = true;
}

void LightingShaderBaseImplementation::useProgram(Engine* engine)
{
	isRunning = true;
	renderer->useProgram(renderLightingProgramId);
	// initialize static uniforms
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderer->setProgramUniformFloatMatrix4x4(uniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
		renderer->setProgramUniformFloatMatrix4x4(uniformCameraMatrix, renderer->getCameraMatrix().getArray());
	}
	if (uniformDiffuseTextureUnit != -1) {
		renderer->setProgramUniformInteger(uniformDiffuseTextureUnit, LightingShaderConstants::TEXTUREUNIT_DIFFUSE);
	}
	if (renderer->isSpecularMappingAvailable() == true && uniformSpecularTextureUnit != -1) {
		renderer->setProgramUniformInteger(uniformSpecularTextureUnit, LightingShaderConstants::TEXTUREUNIT_SPECULAR);
	}
	if (renderer->isNormalMappingAvailable() == true && uniformNormalTextureUnit != -1) {
		renderer->setProgramUniformInteger(uniformNormalTextureUnit, LightingShaderConstants::TEXTUREUNIT_NORMAL);
	}
	if (renderer->isDisplacementMappingAvailable() == true && uniformDisplacementTextureUnit != -1) {
		renderer->setProgramUniformInteger(uniformDisplacementTextureUnit, LightingShaderConstants::TEXTUREUNIT_DISPLACEMENT);
	}
	// initialize dynamic uniforms
	updateEffect(renderer);
	updateMaterial(renderer);
	for (auto i = 0; i < LightingShaderConstants::MAX_LIGHTS; i++) {
		updateLight(renderer, i);
	}
	// frame
	if (renderer->isGeometryShaderAvailable() == true) {
		renderer->setProgramUniformInteger(uniformFrame, engine->getTiming()->getFrame());
	}
}

void LightingShaderBaseImplementation::unUseProgram()
{
	isRunning = false;
}

void LightingShaderBaseImplementation::updateEffect(GLRenderer* renderer)
{
	// skip if not running
	if (isRunning == false) return;

	// skip if using instanced rendering
	if (renderer->isInstancedRenderingAvailable() == false) {
		//
		renderer->setProgramUniformFloatVec4(uniformEffectColorMul, renderer->effectColorMul);
		renderer->setProgramUniformFloatVec4(uniformEffectColorAdd, renderer->effectColorAdd);
	}
}

void LightingShaderBaseImplementation::updateMaterial(GLRenderer* renderer)
{
	// skip if not running
	if (isRunning == false) return;

	//
	array<float, 4> tmpColor4 {{ 0.0f, 0.0f, 0.0f, 0.0f }};

	// ambient without alpha, as we only use alpha from diffuse color
	tmpColor4 = renderer->material.ambient;
	tmpColor4[3] = 0.0f;
	if (uniformMaterialAmbient != -1) renderer->setProgramUniformFloatVec4(uniformMaterialAmbient, tmpColor4);
	// diffuse
	renderer->setProgramUniformFloatVec4(uniformMaterialDiffuse, renderer->material.diffuse);
	// specular without alpha, as we only use alpha from diffuse color
	tmpColor4 = renderer->material.specular;
	tmpColor4[3] = 0.0f;
	if (uniformMaterialSpecular != -1) renderer->setProgramUniformFloatVec4(uniformMaterialSpecular, tmpColor4);
	// emission without alpha, as we only use alpha from diffuse color
	tmpColor4 = renderer->material.emission;
	tmpColor4[3] = 0.0f;
	renderer->setProgramUniformFloatVec4(uniformMaterialEmission, tmpColor4);
	// shininess
	if (uniformMaterialShininess != -1) renderer->setProgramUniformFloat(uniformMaterialShininess, renderer->material.shininess);
	// diffuse texture masked transparency
	if (uniformDiffuseTextureMaskedTransparency != -1) {
		renderer->setProgramUniformInteger(uniformDiffuseTextureMaskedTransparency, renderer->material.diffuseTextureMaskedTransparency);
	}
	// diffuse texture masked transparency threshold
	if (uniformDiffuseTextureMaskedTransparencyThreshold != -1) {
		renderer->setProgramUniformFloat(uniformDiffuseTextureMaskedTransparencyThreshold, renderer->material.diffuseTextureMaskedTransparencyThreshold);
	}
}

void LightingShaderBaseImplementation::updateLight(GLRenderer* renderer, int32_t lightId)
{
	// skip if not running
	if (isRunning == false) return;

	// lights
	renderer->setProgramUniformInteger(uniformLightEnabled[lightId], renderer->lights[lightId].enabled);
	if (renderer->lights[lightId].enabled == 1) {
		if (uniformLightAmbient[lightId] != -1) renderer->setProgramUniformFloatVec4(uniformLightAmbient[lightId], renderer->lights[lightId].ambient);
		if (uniformLightDiffuse[lightId] != -1) renderer->setProgramUniformFloatVec4(uniformLightDiffuse[lightId], renderer->lights[lightId].diffuse);
		if (uniformLightSpecular[lightId] != -1) renderer->setProgramUniformFloatVec4(uniformLightSpecular[lightId], renderer->lights[lightId].specular);
		if (uniformLightPosition[lightId] != -1) renderer->setProgramUniformFloatVec4(uniformLightPosition[lightId], renderer->lights[lightId].position);
		if (uniformLightSpotDirection[lightId] != -1) renderer->setProgramUniformFloatVec3(uniformLightSpotDirection[lightId], renderer->lights[lightId].spotDirection);
		if (uniformLightSpotExponent[lightId] != -1) renderer->setProgramUniformFloat(uniformLightSpotExponent[lightId], renderer->lights[lightId].spotExponent);
		if (uniformLightSpotCosCutoff[lightId] != -1) renderer->setProgramUniformFloat(uniformLightSpotCosCutoff[lightId], renderer->lights[lightId].spotCosCutoff);
		if (uniformLightConstantAttenuation[lightId] != -1) renderer->setProgramUniformFloat(uniformLightConstantAttenuation[lightId], renderer->lights[lightId].constantAttenuation);
		if (uniformLightLinearAttenuation[lightId] != -1) renderer->setProgramUniformFloat(uniformLightLinearAttenuation[lightId], renderer->lights[lightId].linearAttenuation);
		if (uniformLightQuadraticAttenuation[lightId] != -1) renderer->setProgramUniformFloat(uniformLightQuadraticAttenuation[lightId], renderer->lights[lightId].quadraticAttenuation);
	}
}

void LightingShaderBaseImplementation::updateMatrices(GLRenderer* renderer)
{
	// skip if not running
	if (isRunning == false) return;

	// set up camera and projection matrices if using instanced rendering
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderer->setProgramUniformFloatMatrix4x4(uniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
		renderer->setProgramUniformFloatMatrix4x4(uniformCameraMatrix, renderer->getCameraMatrix().getArray());
	}

	// skip if using instanced rendering
	if (renderer->isInstancedRenderingAvailable() == false) {
		// model view matrix
		mvMatrix.set(renderer->getModelViewMatrix());
		// object to screen matrix
		mvpMatrix.set(mvMatrix).multiply(renderer->getProjectionMatrix());
		// normal matrix
		normalMatrix.set(mvMatrix).invert().transpose();
		// upload matrices
		renderer->setProgramUniformFloatMatrix4x4(uniformMVPMatrix, mvpMatrix.getArray());
		renderer->setProgramUniformFloatMatrix4x4(uniformMVMatrix, mvMatrix.getArray());
		renderer->setProgramUniformFloatMatrix4x4(uniformNormalMatrix, normalMatrix.getArray());
	}
}

void LightingShaderBaseImplementation::updateTextureMatrix(GLRenderer* renderer) {
	// skip if not running
	if (isRunning == false) return;

	//
	renderer->setProgramUniformFloatMatrix3x3(uniformTextureMatrix, renderer->getTextureMatrix().getArray());
}


void LightingShaderBaseImplementation::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	// skip if not running
	if (isRunning == false) return;

	switch (renderer->getTextureUnit()) {
		case LightingShaderConstants::TEXTUREUNIT_DIFFUSE:
			if (uniformDiffuseTextureAvailable != -1) {
				renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			}
			break;
		case LightingShaderConstants::TEXTUREUNIT_SPECULAR:
			if (renderer->isSpecularMappingAvailable() == false)
				break;

			if (uniformSpecularTextureAvailable != -1) renderer->setProgramUniformInteger(uniformSpecularTextureAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::TEXTUREUNIT_NORMAL:
			if (renderer->isNormalMappingAvailable() == false)
				break;

			if (uniformNormalTextureAvailable != -1) renderer->setProgramUniformInteger(uniformNormalTextureAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::TEXTUREUNIT_DISPLACEMENT:
			if (renderer->isDisplacementMappingAvailable() == false)
				break;

			renderer->setProgramUniformInteger(uniformDisplacementTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}

}
