#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Matrix4x4;
using tdme::utilities::Console;

LightingShaderBaseImplementation::LightingShaderBaseImplementation(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
	initialized = false;
}

bool LightingShaderBaseImplementation::isInitialized()
{
	return initialized;
}

void LightingShaderBaseImplementation::initialize()
{
	// map inputs to attributes
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 1, "inNormal");
		rendererBackend->setProgramAttributeLocation(programId, 2, "inTextureUV");
		rendererBackend->setProgramAttributeLocation(programId, 4, "inOrigin");
	}

	// link program
	if (rendererBackend->linkProgram(programId) == false) return;

	// get uniforms
	//	globals
	uniformTextureAtlasSize = rendererBackend->getProgramUniformLocation(programId, "textureAtlasSize");
	uniformTextureAtlasPixelDimension = rendererBackend->getProgramUniformLocation(programId, "textureAtlasPixelDimension");
	uniformDiffuseTextureUnit = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureUnit");
	uniformDiffuseTextureAvailable = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureAvailable");
	uniformDiffuseTextureMaskedTransparency = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparency");
	uniformDiffuseTextureMaskedTransparencyThreshold = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparencyThreshold");

	// additional mapping
	if (rendererBackend->isSpecularMappingAvailable() == true) {
		uniformSpecularTextureUnit = rendererBackend->getProgramUniformLocation(programId, "specularTextureUnit");
		uniformSpecularTextureAvailable = rendererBackend->getProgramUniformLocation(programId, "specularTextureAvailable");

	}
	if (rendererBackend->isNormalMappingAvailable() == true) {
		uniformNormalTextureUnit = rendererBackend->getProgramUniformLocation(programId, "normalTextureUnit");
		uniformNormalTextureAvailable = rendererBackend->getProgramUniformLocation(programId, "normalTextureAvailable");
	}

	// environment mapping
	uniformEnvironmentMappingTextureUnit = rendererBackend->getProgramUniformLocation(programId, "environmentMappingTextureUnit");
	uniformEnvironmentMappingTextureAvailable = rendererBackend->getProgramUniformLocation(programId, "environmentMappingTextureAvailable");
	uniformEnvironmentMappingPosition = rendererBackend->getProgramUniformLocation(programId, "environmentMappingPosition");

	// texture matrix
	uniformTextureMatrix = rendererBackend->getProgramUniformLocation(programId, "textureMatrix");

	// matrices as uniform only if not using instanced rendering
	if (rendererBackend->isInstancedRenderingAvailable() == false) {
		uniformNormalMatrix = rendererBackend->getProgramUniformLocation(programId, "normalMatrix");
		if (uniformNormalMatrix == -1) return;

		uniformModelMatrix = rendererBackend->getProgramUniformLocation(programId, "modelMatrix");
		if (uniformModelMatrix == -1) return;

		uniformEffectColorMul = rendererBackend->getProgramUniformLocation(programId, "effectColorMul");
		uniformEffectColorAdd = rendererBackend->getProgramUniformLocation(programId, "effectColorAdd");
	}

	// camera, projection matrix
	uniformCameraMatrix = rendererBackend->getProgramUniformLocation(programId, "cameraMatrix");
	if (uniformCameraMatrix == -1) return;
	uniformProjectionMatrix = rendererBackend->getProgramUniformLocation(programId, "projectionMatrix");
	if (uniformProjectionMatrix == -1) return;
	uniformCameraPosition = rendererBackend->getProgramUniformLocation(programId, "cameraPosition");

	//	material
	uniformMaterialAmbient = rendererBackend->getProgramUniformLocation(programId, "specularMaterial.ambient");
	uniformMaterialDiffuse = rendererBackend->getProgramUniformLocation(programId, "specularMaterial.diffuse");
	uniformMaterialSpecular = rendererBackend->getProgramUniformLocation(programId, "specularMaterial.specular");
	uniformMaterialEmission = rendererBackend->getProgramUniformLocation(programId, "specularMaterial.emission");
	uniformMaterialShininess = rendererBackend->getProgramUniformLocation(programId, "specularMaterial.shininess");
	uniformMaterialReflection = rendererBackend->getProgramUniformLocation(programId, "specularMaterial.reflection");

	//	lights
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformLightEnabled[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) +"].enabled");
		uniformLightAmbient[i] = rendererBackend->getProgramUniformLocation(programId,"specularLights[" + to_string(i) + "].ambient");
		uniformLightDiffuse[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].diffuse");
		uniformLightSpecular[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].specular");
		uniformLightPosition[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].position");
		uniformLightSpotDirection[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotDirection");
		uniformLightSpotExponent[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotExponent");
		uniformLightSpotCosCutoff[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotCosCutoff");
		uniformLightConstantAttenuation[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].constantAttenuation");
		uniformLightLinearAttenuation[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].linearAttenuation");
		uniformLightQuadraticAttenuation[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].quadraticAttenuation");
		uniformLightRadius[i] = rendererBackend->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].radius");
	}

	uniformMaterialReflectionFragmentShader = rendererBackend->getProgramUniformLocation(programId, "materialReflection");

	// use foliage animation
	uniformTime = rendererBackend->getProgramUniformLocation(programId, "time");

	//
	initialized = true;
}

void LightingShaderBaseImplementation::useProgram(Engine* engine, int contextIdx)
{
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_SPECULAR);
	// initialize static uniforms
	if (rendererBackend->isInstancedRenderingAvailable() == true) {
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformProjectionMatrix, rendererBackend->getProjectionMatrix().getArray());
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformCameraMatrix, rendererBackend->getCameraMatrix().getArray());
	}
	if (uniformDiffuseTextureUnit != -1) {
		rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
	}
	if (rendererBackend->isSpecularMappingAvailable() == true && uniformSpecularTextureUnit != -1) {
		rendererBackend->setProgramUniformInteger(contextIdx, uniformSpecularTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_SPECULAR);
	}
	if (rendererBackend->isNormalMappingAvailable() == true && uniformNormalTextureUnit != -1) {
		rendererBackend->setProgramUniformInteger(contextIdx, uniformNormalTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_NORMAL);
	}

	// initialize dynamic uniforms
	updateEffect(rendererBackend, contextIdx);
	updateMaterial(rendererBackend, contextIdx);
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		updateLight(rendererBackend, contextIdx, i);
	}

	// environment mapping texture unit
	if (uniformEnvironmentMappingTextureUnit != -1) {
		rendererBackend->setProgramUniformInteger(contextIdx, uniformEnvironmentMappingTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_ENVIRONMENT);
	}

	// time
	if (uniformTime != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
}

void LightingShaderBaseImplementation::unUseProgram(int contextIdx)
{
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_SPECULAR);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_NORMAL);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 0);
}

void LightingShaderBaseImplementation::updateEffect(RendererBackend* rendererBackend, int contextIdx)
{
	// skip if using instanced rendering
	if (rendererBackend->isInstancedRenderingAvailable() == false) {
		//
		rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformEffectColorMul, rendererBackend->getEffectColorMul(contextIdx));
		rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformEffectColorAdd, rendererBackend->getEffectColorAdd(contextIdx));
	}
}

void LightingShaderBaseImplementation::updateMaterial(RendererBackend* rendererBackend, int contextIdx)
{
	//
	array<float, 4> tmpColor4 {{ 0.0f, 0.0f, 0.0f, 0.0f }};

	auto material = rendererBackend->getSpecularMaterial(contextIdx);

	// ambient without alpha, as we only use alpha from diffuse color
	tmpColor4 = material.ambient;
	tmpColor4[3] = 0.0f;
	if (uniformMaterialAmbient != -1) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformMaterialAmbient, tmpColor4);
	// diffuse
	if (uniformMaterialDiffuse != -1) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformMaterialDiffuse, material.diffuse);
	// specular without alpha, as we only use alpha from diffuse color
	tmpColor4 = material.specular;
	tmpColor4[3] = 0.0f;
	if (uniformMaterialSpecular != -1) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformMaterialSpecular, tmpColor4);
	// emission without alpha, as we only use alpha from diffuse color
	tmpColor4 = material.emission;
	tmpColor4[3] = 0.0f;
	if (uniformMaterialEmission != -1) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformMaterialEmission, tmpColor4);
	// shininess
	if (uniformMaterialShininess != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformMaterialShininess, material.shininess);
	// reflection
	if (uniformMaterialReflection != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformMaterialReflection, material.reflection);
	if (uniformMaterialReflectionFragmentShader != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformMaterialReflectionFragmentShader, material.reflection);
	// diffuse texture masked transparency
	if (uniformDiffuseTextureMaskedTransparency != -1) {
		rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureMaskedTransparency, material.diffuseTextureMaskedTransparency);
	}
	// diffuse texture masked transparency threshold
	if (uniformDiffuseTextureMaskedTransparencyThreshold != -1) {
		rendererBackend->setProgramUniformFloat(contextIdx, uniformDiffuseTextureMaskedTransparencyThreshold, material.diffuseTextureMaskedTransparencyThreshold);
	}
	// texture atlas size
	if (uniformTextureAtlasSize != -1) {
		rendererBackend->setProgramUniformInteger(contextIdx, uniformTextureAtlasSize, material.textureAtlasSize);
	}
	// texture atlas pixel dimension
	if (uniformTextureAtlasPixelDimension != -1) {
		rendererBackend->setProgramUniformFloatVec2(contextIdx, uniformTextureAtlasPixelDimension, material.textureAtlasPixelDimension);
	}
}

void LightingShaderBaseImplementation::updateLight(RendererBackend* rendererBackend, int contextIdx, int32_t lightId)
{
	// lights
	const auto& light = rendererBackend->getLight(contextIdx, lightId);
	if (uniformLightEnabled[lightId] != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformLightEnabled[lightId], light.enabled);
	if (light.enabled == 0) return;
	if (uniformLightAmbient[lightId] != -1) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformLightAmbient[lightId], light.ambient);
	if (uniformLightDiffuse[lightId] != -1) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformLightDiffuse[lightId], light.diffuse);
	if (uniformLightSpecular[lightId] != -1) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformLightSpecular[lightId], light.specular);
	if (uniformLightPosition[lightId] != -1) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformLightPosition[lightId], light.position);
	if (uniformLightSpotDirection[lightId] != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformLightSpotDirection[lightId], light.spotDirection);
	if (uniformLightSpotExponent[lightId] != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformLightSpotExponent[lightId], light.spotExponent);
	if (uniformLightSpotCosCutoff[lightId] != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformLightSpotCosCutoff[lightId], light.spotCosCutoff);
	if (uniformLightConstantAttenuation[lightId] != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformLightConstantAttenuation[lightId], light.constantAttenuation);
	if (uniformLightLinearAttenuation[lightId] != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformLightLinearAttenuation[lightId], light.linearAttenuation);
	if (uniformLightQuadraticAttenuation[lightId] != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformLightQuadraticAttenuation[lightId], light.quadraticAttenuation);
	if (uniformLightRadius[lightId] != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformLightQuadraticAttenuation[lightId], light.radius);
}

void LightingShaderBaseImplementation::updateMatrices(RendererBackend* rendererBackend, int contextIdx)
{
	// set up camera and projection matrices if using instanced rendering
	rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformProjectionMatrix, rendererBackend->getProjectionMatrix().getArray());
	rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformCameraMatrix, rendererBackend->getCameraMatrix().getArray());
	// camera position
	if (uniformCameraPosition != -1) {
		rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformCameraPosition, rendererBackend->getCameraPosition().getArray());
	}
	//
	if (rendererBackend->isInstancedRenderingAvailable() == false) {
		// matrices
		Matrix4x4 normalMatrix;
		// normal matrix
		normalMatrix.set(rendererBackend->getModelViewMatrix()).invert().transpose();
		// upload matrices
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformNormalMatrix, normalMatrix.getArray());
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformModelMatrix, rendererBackend->getModelViewMatrix().getArray());
	}
}

// TODO: shader parameters

void LightingShaderBaseImplementation::updateTextureMatrix(RendererBackend* rendererBackend, int contextIdx) {
	//
	rendererBackend->setProgramUniformFloatMatrix3x3(contextIdx, uniformTextureMatrix, rendererBackend->getTextureMatrix(contextIdx).getArray());
}

void LightingShaderBaseImplementation::updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) {
}

void LightingShaderBaseImplementation::bindTexture(RendererBackend* rendererBackend, int contextIdx, int32_t textureId)
{
	switch (rendererBackend->getTextureUnit(contextIdx)) {
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE:
			if (uniformDiffuseTextureAvailable != -1) {
				rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			}
			break;
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_SPECULAR:
			if (rendererBackend->isSpecularMappingAvailable() == false)
				break;

			if (uniformSpecularTextureAvailable != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformSpecularTextureAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_NORMAL:
			if (rendererBackend->isNormalMappingAvailable() == false)
				break;

			if (uniformNormalTextureAvailable != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformNormalTextureAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_ENVIRONMENT:
			if (uniformEnvironmentMappingTextureUnit != -1 && textureId != 0) {
				if (uniformEnvironmentMappingTextureAvailable != -1) {
					rendererBackend->setProgramUniformInteger(contextIdx, uniformEnvironmentMappingTextureAvailable, 1);
				}
				if (uniformEnvironmentMappingPosition != -1) {
					rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformEnvironmentMappingPosition, rendererBackend->getEnvironmentMappingCubeMapPosition(contextIdx));
				}
			} else {
				if (uniformEnvironmentMappingTextureAvailable != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformEnvironmentMappingTextureAvailable, 0);
			}
	}
}

void LightingShaderBaseImplementation::unloadTextures() {
}

void LightingShaderBaseImplementation::loadTextures(const string& pathName) {
}
