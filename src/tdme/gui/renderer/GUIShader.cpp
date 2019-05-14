#include <tdme/gui/renderer/GUIShader.h>

#include <tdme/engine/subsystems/renderer/Renderer.h>

using tdme::gui::renderer::GUIShader;
using tdme::engine::subsystems::renderer::Renderer;

GUIShader::GUIShader(Renderer* renderer) 
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
	auto shaderVersion = renderer->getShaderVersion();
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/gui",
		"render_vertexshader.c"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/gui",
		"render_fragmentshader.c"
	);
	if (fragmentShaderId == 0) return;

	programId = renderer->createProgram();
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programId, 2, "inTextureUV");
		renderer->setProgramAttributeLocation(programId, 3, "inColor");
	}
	if (renderer->linkProgram(programId) == false) return;

	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(programId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1) return;

	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(programId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1) return;

	uniformEffectColorMul = renderer->getProgramUniformLocation(programId, "effectColorMul");
	if (uniformEffectColorMul == -1) return;

	uniformEffectColorAdd = renderer->getProgramUniformLocation(programId, "effectColorAdd");
	if (uniformEffectColorAdd == -1) return;

	// texture matrix
	uniformTextureMatrix = renderer->getProgramUniformLocation(programId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;

	initialized = true;
}

void GUIShader::useProgram()
{
	renderer->useProgram(programId);
	renderer->setProgramUniformInteger(uniformDiffuseTextureUnit, 0);
	isRunning = true;
}

void GUIShader::unUseProgram()
{
	renderer->useProgram(renderer->ID_NONE);
	isRunning = false;
}

void GUIShader::bindTexture(Renderer* renderer, int32_t textureId)
{
	if (isRunning == false) return;
	renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
}

void GUIShader::updateEffect(Renderer* renderer)
{
	if (isRunning == false) return;
	renderer->setProgramUniformFloatVec4(uniformEffectColorMul, renderer->effectColorMul);
	renderer->setProgramUniformFloatVec4(uniformEffectColorAdd, renderer->effectColorAdd);
}


void GUIShader::updateTextureMatrix(Renderer* renderer) {
	if (isRunning == false) return;

	renderer->setProgramUniformFloatMatrix3x3(uniformTextureMatrix, renderer->getTextureMatrix().getArray());
}
