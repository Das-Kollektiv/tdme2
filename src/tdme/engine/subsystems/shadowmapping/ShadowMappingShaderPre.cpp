#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
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
	preVertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		L"shader/" + rendererVersion + L"/shadowmapping",
		L"pre_vertexshader.c"
	);
	if (preVertexShaderGlId == 0)
		return;

	preFragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		L"shader/" + rendererVersion + L"/shadowmapping",
		L"pre_fragmentshader.c"
	);
	if (preFragmentShaderGlId == 0)
		return;

	preProgramGlId = renderer->createProgram();
	renderer->attachShaderToProgram(preProgramGlId, preVertexShaderGlId);
	renderer->attachShaderToProgram(preProgramGlId, preFragmentShaderGlId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(preProgramGlId, 0, L"inVertex");
		renderer->setProgramAttributeLocation(preProgramGlId, 1, L"inNormal");
		renderer->setProgramAttributeLocation(preProgramGlId, 2, L"inTextureUV");
	}
	if (renderer->linkProgram(preProgramGlId) == false)
		return;

	preUniformMVPMatrix = renderer->getProgramUniformLocation(preProgramGlId, L"mvpMatrix");
	if (preUniformMVPMatrix == -1)
		return;

	initialized = true;
}

void ShadowMappingShaderPre::useProgram()
{
	renderer->useProgram(preProgramGlId);
}

void ShadowMappingShaderPre::unUseProgram()
{
}

void ShadowMappingShaderPre::setProgramMVPMatrix(const Matrix4x4& mvpMatrix)
{
	renderer->setProgramUniformFloatMatrix4x4(preUniformMVPMatrix, mvpMatrix.getArray());
}
