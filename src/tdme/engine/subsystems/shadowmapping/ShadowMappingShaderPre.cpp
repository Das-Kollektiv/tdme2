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
	vertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"pre_vertexshader.c"
	);
	if (vertexShaderGlId == 0)
		return;

	fragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/shadowmapping",
		"pre_fragmentshader.c"
	);
	if (fragmentShaderGlId == 0)
		return;

	programGlId = renderer->createProgram();
	renderer->attachShaderToProgram(programGlId, vertexShaderGlId);
	renderer->attachShaderToProgram(programGlId, fragmentShaderGlId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programGlId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programGlId, 1, "inNormal");
		renderer->setProgramAttributeLocation(programGlId, 2, "inTextureUV");
	}
	if (renderer->linkProgram(programGlId) == false)
		return;

	uniformMVPMatrix = renderer->getProgramUniformLocation(programGlId, "mvpMatrix");
	if (uniformMVPMatrix == -1)
		return;

	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(programGlId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1)
		return;

	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(programGlId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1)
		return;

	uniformDiffuseTextureMaskedTransparency = renderer->getProgramUniformLocation(programGlId, "diffuseTextureMaskedTransparency");
	if (uniformDiffuseTextureMaskedTransparency == -1)
		return;

	initialized = true;
}

void ShadowMappingShaderPre::useProgram()
{
	renderer->useProgram(programGlId);
}

void ShadowMappingShaderPre::unUseProgram()
{
}

void ShadowMappingShaderPre::setProgramMVPMatrix(const Matrix4x4& mvpMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(uniformMVPMatrix, mvpMatrix.getArray());
}

void ShadowMappingShaderPre::updateMaterial(GLRenderer* renderer)
{
	renderer->setProgramUniformInteger(uniformDiffuseTextureMaskedTransparency, renderer->material.diffuseTextureMaskedTransparency);
}

void ShadowMappingShaderPre::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	switch (renderer->getTextureUnit()) {
		case LightingShader::TEXTUREUNIT_DIFFUSE:
			renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}
