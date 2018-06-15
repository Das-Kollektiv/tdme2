#include <tdme/gui/renderer/GUIShader.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using tdme::gui::renderer::GUIShader;
using tdme::engine::subsystems::renderer::GLRenderer;

GUIShader::GUIShader(GLRenderer* renderer) 
{
	this->renderer = renderer;
	initialized = false;
	isRunning = false;
}

bool GUIShader::isInitialized()
{
	return initialized;
}

void GUIShader::initialize()
{
	auto rendererVersion = renderer->getGLVersion();
	vertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/gui",
		"render_vertexshader.c"
	);
	if (vertexShaderGlId == 0)
		return;

	fragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/gui",
		"render_fragmentshader.c"
	);
	if (fragmentShaderGlId == 0)
		return;

	programGlId = renderer->createProgram();
	renderer->attachShaderToProgram(programGlId, vertexShaderGlId);
	renderer->attachShaderToProgram(programGlId, fragmentShaderGlId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programGlId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programGlId, 2, "inTextureUV");
		renderer->setProgramAttributeLocation(programGlId, 3, "inColor");
	}
	if (renderer->linkProgram(programGlId) == false)
		return;

	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(programGlId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1)
		return;

	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(programGlId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1)
		return;

	uniformEffectColorMul = renderer->getProgramUniformLocation(programGlId, "effectColorMul");
	if (uniformEffectColorMul == -1)
		return;

	uniformEffectColorAdd = renderer->getProgramUniformLocation(programGlId, "effectColorAdd");
	if (uniformEffectColorAdd == -1)
		return;

	// texture matrix
	uniformTextureMatrix = renderer->getProgramUniformLocation(programGlId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;

	initialized = true;
}

void GUIShader::useProgram()
{
	renderer->useProgram(programGlId);
	renderer->setProgramUniformInteger(uniformDiffuseTextureUnit, 0);
	isRunning = true;
}

void GUIShader::unUseProgram()
{
	isRunning = false;
}

void GUIShader::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	if (isRunning == false)
		return;

	renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
}

void GUIShader::updateEffect(GLRenderer* renderer)
{
	if (isRunning == false)
		return;

	renderer->setProgramUniformFloatVec4(uniformEffectColorMul, renderer->effectColorMul);
	renderer->setProgramUniformFloatVec4(uniformEffectColorAdd, renderer->effectColorAdd);
}


void GUIShader::updateTextureMatrix(GLRenderer* renderer) {
	if (isRunning == false)
		return;

	renderer->setProgramUniformFloatMatrix3x3(uniformTextureMatrix, renderer->getTextureMatrix().getArray());
}
