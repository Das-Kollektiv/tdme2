#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Matrix4x4;
using tdme::utilities::Console;

LightingShaderBaseImplementation::LightingShaderBaseImplementation(Renderer* renderer)
{
	this->renderer = renderer;
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
		renderer->setProgramAttributeLocation(programId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programId, 1, "inNormal");
		renderer->setProgramAttributeLocation(programId, 2, "inTextureUV");
		renderer->setProgramAttributeLocation(programId, 4, "inOrigin");
	}

	// link program
	if (renderer->linkProgram(programId) == false) return;

	// get uniforms
	//	globals
	uniformTextureAtlasSize = renderer->getProgramUniformLocation(programId, "textureAtlasSize");
	uniformTextureAtlasPixelDimension = renderer->getProgramUniformLocation(programId, "textureAtlasPixelDimension");
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(programId, "diffuseTextureUnit");
	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(programId, "diffuseTextureAvailable");
	uniformDiffuseTextureMaskedTransparency = renderer->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparency");
	uniformDiffuseTextureMaskedTransparencyThreshold = renderer->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparencyThreshold");

	// additional mapping
	if (renderer->isSpecularMappingAvailable() == true) {
		uniformSpecularTextureUnit = renderer->getProgramUniformLocation(programId, "specularTextureUnit");
		uniformSpecularTextureAvailable = renderer->getProgramUniformLocation(programId, "specularTextureAvailable");

	}
	if (renderer->isNormalMappingAvailable() == true) {
		uniformNormalTextureUnit = renderer->getProgramUniformLocation(programId, "normalTextureUnit");
		uniformNormalTextureAvailable = renderer->getProgramUniformLocation(programId, "normalTextureAvailable");
	}

	// environment mapping
	uniformEnvironmentMappingTextureUnit = renderer->getProgramUniformLocation(programId, "environmentMappingTextureUnit");
	uniformEnvironmentMappingTextureAvailable = renderer->getProgramUniformLocation(programId, "environmentMappingTextureAvailable");
	uniformEnvironmentMappingPosition = renderer->getProgramUniformLocation(programId, "environmentMappingPosition");

	// texture matrix
	uniformTextureMatrix = renderer->getProgramUniformLocation(programId, "textureMatrix");

	// matrices as uniform only if not using instanced rendering
	if (renderer->isInstancedRenderingAvailable() == false) {
		uniformNormalMatrix = renderer->getProgramUniformLocation(programId, "normalMatrix");
		if (uniformNormalMatrix == -1) return;

		uniformModelMatrix = renderer->getProgramUniformLocation(programId, "modelMatrix");
		if (uniformModelMatrix == -1) return;

		uniformEffectColorMul = renderer->getProgramUniformLocation(programId, "effectColorMul");
		uniformEffectColorAdd = renderer->getProgramUniformLocation(programId, "effectColorAdd");
	}

	// camera, projection matrix
	uniformCameraMatrix = renderer->getProgramUniformLocation(programId, "cameraMatrix");
	if (uniformCameraMatrix == -1) return;
	uniformProjectionMatrix = renderer->getProgramUniformLocation(programId, "projectionMatrix");
	if (uniformProjectionMatrix == -1) return;
	uniformCameraPosition = renderer->getProgramUniformLocation(programId, "cameraPosition");

	//	material
	uniformMaterialAmbient = renderer->getProgramUniformLocation(programId, "specularMaterial.ambient");
	uniformMaterialDiffuse = renderer->getProgramUniformLocation(programId, "specularMaterial.diffuse");
	uniformMaterialSpecular = renderer->getProgramUniformLocation(programId, "specularMaterial.specular");
	uniformMaterialEmission = renderer->getProgramUniformLocation(programId, "specularMaterial.emission");
	uniformMaterialShininess = renderer->getProgramUniformLocation(programId, "specularMaterial.shininess");
	uniformMaterialReflection = renderer->getProgramUniformLocation(programId, "specularMaterial.reflection");

	//	lights
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformLightEnabled[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) +"].enabled");
		uniformLightAmbient[i] = renderer->getProgramUniformLocation(programId,"specularLights[" + to_string(i) + "].ambient");
		uniformLightDiffuse[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].diffuse");
		uniformLightSpecular[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].specular");
		uniformLightPosition[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].position");
		uniformLightSpotDirection[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotDirection");
		uniformLightSpotExponent[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotExponent");
		uniformLightSpotCosCutoff[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotCosCutoff");
		uniformLightConstantAttenuation[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].constantAttenuation");
		uniformLightLinearAttenuation[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].linearAttenuation");
		uniformLightQuadraticAttenuation[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].quadraticAttenuation");
		uniformLightRadius[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].radius");
	}

	uniformMaterialReflectionFragmentShader = renderer->getProgramUniformLocation(programId, "materialReflection");

	// use foliage animation
	uniformTime = renderer->getProgramUniformLocation(programId, "time");

	//
	initialized = true;
}

void LightingShaderBaseImplementation::useProgram(Engine* engine, int contextIdx)
{
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_SPECULAR);
	// initialize static uniforms
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformCameraMatrix, renderer->getCameraMatrix().getArray());
	}
	if (uniformDiffuseTextureUnit != -1) {
		renderer->setProgramUniformInteger(contextIdx, uniformDiffuseTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
	}
	if (renderer->isSpecularMappingAvailable() == true && uniformSpecularTextureUnit != -1) {
		renderer->setProgramUniformInteger(contextIdx, uniformSpecularTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_SPECULAR);
	}
	if (renderer->isNormalMappingAvailable() == true && uniformNormalTextureUnit != -1) {
		renderer->setProgramUniformInteger(contextIdx, uniformNormalTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_NORMAL);
	}

	// initialize dynamic uniforms
	updateEffect(renderer, contextIdx);
	updateMaterial(renderer, contextIdx);
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		updateLight(renderer, contextIdx, i);
	}

	// environment mapping texture unit
	if (uniformEnvironmentMappingTextureUnit != -1) {
		renderer->setProgramUniformInteger(contextIdx, uniformEnvironmentMappingTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_ENVIRONMENT);
	}

	// time
	if (uniformTime != -1) renderer->setProgramUniformFloat(contextIdx, uniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
}

void LightingShaderBaseImplementation::unUseProgram(int contextIdx)
{
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_SPECULAR);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_NORMAL);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 0);
}

void LightingShaderBaseImplementation::updateEffect(Renderer* renderer, int contextIdx)
{
	// skip if using instanced rendering
	if (renderer->isInstancedRenderingAvailable() == false) {
		//
		renderer->setProgramUniformFloatVec4(contextIdx, uniformEffectColorMul, renderer->getEffectColorMul(contextIdx));
		renderer->setProgramUniformFloatVec4(contextIdx, uniformEffectColorAdd, renderer->getEffectColorAdd(contextIdx));
	}
}

void LightingShaderBaseImplementation::updateMaterial(Renderer* renderer, int contextIdx)
{
	//
	array<float, 4> tmpColor4 {{ 0.0f, 0.0f, 0.0f, 0.0f }};

	auto material = renderer->getSpecularMaterial(contextIdx);

	// ambient without alpha, as we only use alpha from diffuse color
	tmpColor4 = material.ambient;
	tmpColor4[3] = 0.0f;
	if (uniformMaterialAmbient != -1) renderer->setProgramUniformFloatVec4(contextIdx, uniformMaterialAmbient, tmpColor4);
	// diffuse
	if (uniformMaterialDiffuse != -1) renderer->setProgramUniformFloatVec4(contextIdx, uniformMaterialDiffuse, material.diffuse);
	// specular without alpha, as we only use alpha from diffuse color
	tmpColor4 = material.specular;
	tmpColor4[3] = 0.0f;
	if (uniformMaterialSpecular != -1) renderer->setProgramUniformFloatVec4(contextIdx, uniformMaterialSpecular, tmpColor4);
	// emission without alpha, as we only use alpha from diffuse color
	tmpColor4 = material.emission;
	tmpColor4[3] = 0.0f;
	if (uniformMaterialEmission != -1) renderer->setProgramUniformFloatVec4(contextIdx, uniformMaterialEmission, tmpColor4);
	// shininess
	if (uniformMaterialShininess != -1) renderer->setProgramUniformFloat(contextIdx, uniformMaterialShininess, material.shininess);
	// reflection
	if (uniformMaterialReflection != -1) renderer->setProgramUniformFloat(contextIdx, uniformMaterialReflection, material.reflection);
	if (uniformMaterialReflectionFragmentShader != -1) renderer->setProgramUniformFloat(contextIdx, uniformMaterialReflectionFragmentShader, material.reflection);
	// diffuse texture masked transparency
	if (uniformDiffuseTextureMaskedTransparency != -1) {
		renderer->setProgramUniformInteger(contextIdx, uniformDiffuseTextureMaskedTransparency, material.diffuseTextureMaskedTransparency);
	}
	// diffuse texture masked transparency threshold
	if (uniformDiffuseTextureMaskedTransparencyThreshold != -1) {
		renderer->setProgramUniformFloat(contextIdx, uniformDiffuseTextureMaskedTransparencyThreshold, material.diffuseTextureMaskedTransparencyThreshold);
	}
	// texture atlas size
	if (uniformTextureAtlasSize != -1) {
		renderer->setProgramUniformInteger(contextIdx, uniformTextureAtlasSize, material.textureAtlasSize);
	}
	// texture atlas pixel dimension
	if (uniformTextureAtlasPixelDimension != -1) {
		renderer->setProgramUniformFloatVec2(contextIdx, uniformTextureAtlasPixelDimension, material.textureAtlasPixelDimension);
	}
}

void LightingShaderBaseImplementation::updateLight(Renderer* renderer, int contextIdx, int32_t lightId)
{
	// lights
	auto& light = renderer->getLight(contextIdx, lightId);
	if (uniformLightEnabled[lightId] != -1) renderer->setProgramUniformInteger(contextIdx, uniformLightEnabled[lightId], light.enabled);
	if (light.enabled == 0) return;
	if (uniformLightAmbient[lightId] != -1) renderer->setProgramUniformFloatVec4(contextIdx, uniformLightAmbient[lightId], light.ambient);
	if (uniformLightDiffuse[lightId] != -1) renderer->setProgramUniformFloatVec4(contextIdx, uniformLightDiffuse[lightId], light.diffuse);
	if (uniformLightSpecular[lightId] != -1) renderer->setProgramUniformFloatVec4(contextIdx, uniformLightSpecular[lightId], light.specular);
	if (uniformLightPosition[lightId] != -1) renderer->setProgramUniformFloatVec4(contextIdx, uniformLightPosition[lightId], light.position);
	if (uniformLightSpotDirection[lightId] != -1) renderer->setProgramUniformFloatVec3(contextIdx, uniformLightSpotDirection[lightId], light.spotDirection);
	if (uniformLightSpotExponent[lightId] != -1) renderer->setProgramUniformFloat(contextIdx, uniformLightSpotExponent[lightId], light.spotExponent);
	if (uniformLightSpotCosCutoff[lightId] != -1) renderer->setProgramUniformFloat(contextIdx, uniformLightSpotCosCutoff[lightId], light.spotCosCutoff);
	if (uniformLightConstantAttenuation[lightId] != -1) renderer->setProgramUniformFloat(contextIdx, uniformLightConstantAttenuation[lightId], light.constantAttenuation);
	if (uniformLightLinearAttenuation[lightId] != -1) renderer->setProgramUniformFloat(contextIdx, uniformLightLinearAttenuation[lightId], light.linearAttenuation);
	if (uniformLightQuadraticAttenuation[lightId] != -1) renderer->setProgramUniformFloat(contextIdx, uniformLightQuadraticAttenuation[lightId], light.quadraticAttenuation);
	if (uniformLightRadius[lightId] != -1) renderer->setProgramUniformFloat(contextIdx, uniformLightQuadraticAttenuation[lightId], light.radius);
}

void LightingShaderBaseImplementation::updateMatrices(Renderer* renderer, int contextIdx)
{
	// set up camera and projection matrices if using instanced rendering
	renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
	renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformCameraMatrix, renderer->getCameraMatrix().getArray());
	// camera position
	if (uniformCameraPosition != -1) {
		renderer->setProgramUniformFloatVec3(contextIdx, uniformCameraPosition, renderer->getCameraPosition().getArray());
	}
	//
	if (renderer->isInstancedRenderingAvailable() == false) {
		// matrices
		Matrix4x4 normalMatrix;
		// normal matrix
		normalMatrix.set(renderer->getModelViewMatrix()).invert().transpose();
		// upload matrices
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformNormalMatrix, normalMatrix.getArray());
		renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformModelMatrix, renderer->getModelViewMatrix().getArray());
	}
}

// TODO: shader parameters

void LightingShaderBaseImplementation::updateTextureMatrix(Renderer* renderer, int contextIdx) {
	//
	renderer->setProgramUniformFloatMatrix3x3(contextIdx, uniformTextureMatrix, renderer->getTextureMatrix(contextIdx).getArray());
}

void LightingShaderBaseImplementation::updateShaderParameters(Renderer* renderer, int contextIdx) {
}

void LightingShaderBaseImplementation::bindTexture(Renderer* renderer, int contextIdx, int32_t textureId)
{
	switch (renderer->getTextureUnit(contextIdx)) {
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE:
			if (uniformDiffuseTextureAvailable != -1) {
				renderer->setProgramUniformInteger(contextIdx, uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			}
			break;
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_SPECULAR:
			if (renderer->isSpecularMappingAvailable() == false)
				break;

			if (uniformSpecularTextureAvailable != -1) renderer->setProgramUniformInteger(contextIdx, uniformSpecularTextureAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_NORMAL:
			if (renderer->isNormalMappingAvailable() == false)
				break;

			if (uniformNormalTextureAvailable != -1) renderer->setProgramUniformInteger(contextIdx, uniformNormalTextureAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_ENVIRONMENT:
			if (uniformEnvironmentMappingTextureUnit != -1 && textureId != 0) {
				if (uniformEnvironmentMappingTextureAvailable != -1) {
					renderer->setProgramUniformInteger(contextIdx, uniformEnvironmentMappingTextureAvailable, 1);
				}
				if (uniformEnvironmentMappingPosition != -1) {
					renderer->setProgramUniformFloatVec3(contextIdx, uniformEnvironmentMappingPosition, renderer->getEnvironmentMappingCubeMapPosition(contextIdx));
				}
			} else {
				if (uniformEnvironmentMappingTextureAvailable != -1) renderer->setProgramUniformInteger(contextIdx, uniformEnvironmentMappingTextureAvailable, 0);
			}
	}
}

void LightingShaderBaseImplementation::loadTextures(const string& pathName) {
}
