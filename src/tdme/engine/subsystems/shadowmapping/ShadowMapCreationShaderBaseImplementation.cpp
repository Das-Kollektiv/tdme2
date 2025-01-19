	#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderBaseImplementation.h>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>

using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderBaseImplementation;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Matrix4x4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;

ShadowMapCreationShaderBaseImplementation::ShadowMapCreationShaderBaseImplementation(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
	initialized = false;
}

ShadowMapCreationShaderBaseImplementation::~ShadowMapCreationShaderBaseImplementation() {
}

bool ShadowMapCreationShaderBaseImplementation::isInitialized()
{
	return initialized;
}

void ShadowMapCreationShaderBaseImplementation::initialize()
{
	// map inputs to attributes
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 2, "inTextureUV");
		rendererBackend->setProgramAttributeLocation(programId, 4, "inOrigin");
	}
	// link
	if (rendererBackend->linkProgram(programId) == false) return;

	// uniforms
	if (rendererBackend->isInstancedRenderingAvailable() == true) {
		//	uniforms
		uniformProjectionMatrix = rendererBackend->getProgramUniformLocation(programId, "projectionMatrix");
		if (uniformProjectionMatrix == -1) return;
		uniformCameraMatrix = rendererBackend->getProgramUniformLocation(programId, "cameraMatrix");
		if (uniformCameraMatrix == -1) return;
	} else {
		//	uniforms
		uniformMVPMatrix = rendererBackend->getProgramUniformLocation(programId, "mvpMatrix");
		if (uniformMVPMatrix == -1) return;
		uniformModelTranslation = rendererBackend->getProgramUniformLocation(programId, "modelTranslation");
	}
	uniformTextureMatrix = rendererBackend->getProgramUniformLocation(programId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;
	uniformTextureAtlasSize = rendererBackend->getProgramUniformLocation(programId, "textureAtlasSize");
	if (uniformTextureAtlasSize == -1) return;
	uniformTextureAtlasPixelDimension = rendererBackend->getProgramUniformLocation(programId, "textureAtlasPixelDimension");
	if (uniformTextureAtlasPixelDimension == -1) return;
	uniformDiffuseTextureUnit = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1) return;
	uniformDiffuseTextureAvailable = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1) return;
	uniformDiffuseTextureMaskedTransparency = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparency");
	if (uniformDiffuseTextureMaskedTransparency == -1) return;
	uniformDiffuseTextureMaskedTransparencyThreshold = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureMaskedTransparencyThreshold");
	if (uniformDiffuseTextureMaskedTransparencyThreshold == -1) return;

	//
	uniformTime = rendererBackend->getProgramUniformLocation(programId, "time");

	//
	initialized = true;
}

void ShadowMapCreationShaderBaseImplementation::useProgram(Engine* engine, int contextIdx)
{
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_SPECULAR);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
	if (uniformTime != -1) rendererBackend->setProgramUniformFloat(contextIdx, uniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
}

void ShadowMapCreationShaderBaseImplementation::unUseProgram(int contextIdx)
{
}

void ShadowMapCreationShaderBaseImplementation::updateMatrices(int contextIdx)
{
	if (rendererBackend->isInstancedRenderingAvailable() == true) {
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformProjectionMatrix, rendererBackend->getProjectionMatrix().getArray());
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformCameraMatrix, rendererBackend->getCameraMatrix().getArray());
	} else {
		Matrix4x4 mvpMatrix;
		Vector3 modelTranslation;
		// model view projection matrix
		mvpMatrix.set(rendererBackend->getModelViewMatrix()).multiply(rendererBackend->getCameraMatrix()).multiply(rendererBackend->getProjectionMatrix());
		// model translation
		rendererBackend->getModelViewMatrix().getTranslation(modelTranslation);
		rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformMVPMatrix, mvpMatrix.getArray());
		if (uniformModelTranslation != -1) rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformModelTranslation, modelTranslation.getArray());
	}
}

void ShadowMapCreationShaderBaseImplementation::updateTextureMatrix(RendererBackend* rendererBackend, int contextIdx) {
	rendererBackend->setProgramUniformFloatMatrix3x3(contextIdx, uniformTextureMatrix, rendererBackend->getTextureMatrix(contextIdx).getArray());
}

void ShadowMapCreationShaderBaseImplementation::updateMaterial(RendererBackend* rendererBackend, int contextIdx)
{
	auto material = rendererBackend->getSpecularMaterial(contextIdx);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureMaskedTransparency, material.diffuseTextureMaskedTransparency);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformDiffuseTextureMaskedTransparencyThreshold, material.diffuseTextureMaskedTransparencyThreshold);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformTextureAtlasSize, material.textureAtlasSize);
	rendererBackend->setProgramUniformFloatVec2(contextIdx, uniformTextureAtlasPixelDimension, material.textureAtlasPixelDimension);
}

void ShadowMapCreationShaderBaseImplementation::bindTexture(RendererBackend* rendererBackend, int contextIdx, int32_t textureId)
{
	switch (rendererBackend->getTextureUnit(contextIdx)) {
		case LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE:
			rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}

void ShadowMapCreationShaderBaseImplementation::unloadTextures() {
}

void ShadowMapCreationShaderBaseImplementation::loadTextures(const string& pathName) {
}

