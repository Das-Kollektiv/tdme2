#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>

#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

ShadowMappingShaderPre::ShadowMappingShaderPre(GLRenderer* renderer) 
{
	this->renderer = renderer;
	initialized = false;
}

bool ShadowMappingShaderPre::isInitialized()
{
	return initialized;
}

void ShadowMappingShaderPre::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	// load shadow mapping shaders
	//	pre render
	vertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"pre_vertexshader.c"
	);
	if (vertexShaderGlId == 0) return;

	fragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"pre_fragmentshader.c"
	);
	if (fragmentShaderGlId == 0) return;

	// create shadow mapping render program
	//	pre
	programGlId = renderer->createProgram();
	renderer->attachShaderToProgram(programGlId, vertexShaderGlId);
	renderer->attachShaderToProgram(programGlId, fragmentShaderGlId);
	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programGlId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programGlId, 2, "inTextureUV");
	}
	// link
	if (renderer->linkProgram(programGlId) == false) return;

	// uniforms
	if (renderer->isInstancedRenderingAvailable() == true) {
		//	uniforms
		uniformProjectionMatrix = renderer->getProgramUniformLocation(programGlId, "projectionMatrix");
		if (uniformProjectionMatrix == -1) return;
		uniformCameraMatrix = renderer->getProgramUniformLocation(programGlId, "cameraMatrix");
		if (uniformCameraMatrix == -1) return;
	} else {
		//	uniforms
		uniformMVPMatrix = renderer->getProgramUniformLocation(programGlId, "mvpMatrix");
		if (uniformMVPMatrix == -1) return;
	}
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(programGlId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1) return;
	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(programGlId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1) return;
	uniformDiffuseTextureMaskedTransparency = renderer->getProgramUniformLocation(programGlId, "diffuseTextureMaskedTransparency");
	if (uniformDiffuseTextureMaskedTransparency == -1) return;
	uniformDiffuseTextureMaskedTransparencyThreshold = renderer->getProgramUniformLocation(programGlId, "diffuseTextureMaskedTransparencyThreshold");
	if (uniformDiffuseTextureMaskedTransparencyThreshold == -1) return;

	//
	initialized = true;
}

void ShadowMappingShaderPre::useProgram()
{
	renderer->useProgram(programGlId);
}

void ShadowMappingShaderPre::unUseProgram()
{
}

void ShadowMappingShaderPre::updateMatrices(const Matrix4x4& mvpMatrix)
{
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderer->setProgramUniformFloatMatrix4x4(uniformProjectionMatrix, renderer->getProjectionMatrix().getArray());
		renderer->setProgramUniformFloatMatrix4x4(uniformCameraMatrix, renderer->getCameraMatrix().getArray());
	} else {
		renderer->setProgramUniformFloatMatrix4x4(uniformMVPMatrix, mvpMatrix.getArray());
	}
}

void ShadowMappingShaderPre::updateMaterial(GLRenderer* renderer)
{
	renderer->setProgramUniformInteger(uniformDiffuseTextureMaskedTransparency, renderer->material.diffuseTextureMaskedTransparency);
	renderer->setProgramUniformFloat(uniformDiffuseTextureMaskedTransparencyThreshold, renderer->material.diffuseTextureMaskedTransparencyThreshold);
}

void ShadowMappingShaderPre::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	switch (renderer->getTextureUnit()) {
		case LightingShader::TEXTUREUNIT_DIFFUSE:
			renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}
