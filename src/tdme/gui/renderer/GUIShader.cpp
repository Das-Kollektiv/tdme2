#include <tdme/gui/renderer/GUIShader.h>

#include <array>

#include <tdme/engine/subsystems/renderer/Renderer.h>

#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/utilities/Console.h>

using tdme::gui::renderer::GUIShader;

using std::array;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::gui::nodes::GUIColor;
using tdme::math::Math;
using tdme::math::Matrix2D3x3;
using tdme::utilities::Console;

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
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/gui",
		"render_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
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

	uniformMaskTextureUnit = renderer->getProgramUniformLocation(programId, "maskTextureUnit");
	if (uniformMaskTextureUnit == -1) return;

	uniformMaskTextureAvailable = renderer->getProgramUniformLocation(programId, "maskTextureAvailable");
	if (uniformMaskTextureAvailable == -1) return;

	uniformMaskMaxValue = renderer->getProgramUniformLocation(programId, "maskMaxValue");
	if (uniformMaskMaxValue == -1) return;

	uniformEffectColorMul = renderer->getProgramUniformLocation(programId, "effectColorMul");
	if (uniformEffectColorMul == -1) return;

	uniformEffectColorAdd = renderer->getProgramUniformLocation(programId, "effectColorAdd");
	if (uniformEffectColorAdd == -1) return;

	// texture matrix
	uniformTextureMatrix = renderer->getProgramUniformLocation(programId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;

	// gradients
	uniformGradientAvailable = renderer->getProgramUniformLocation(programId, "gradientAvailable");
	if (uniformGradientAvailable == -1) return;
	for (auto i = 0; i < uniformGradientColors.size(); i++) {
		uniformGradientColors[i] = renderer->getProgramUniformLocation(programId, "gradientColors[" + to_string(i) + "]");
		if (uniformGradientColors[i] == -1) return;
	}
	uniformGradientColorCount = renderer->getProgramUniformLocation(programId, "gradientColorCount");
	if (uniformGradientColorCount == -1) return;
	for (auto i = 0; i < uniformGradientColorStarts.size(); i++) {
		uniformGradientColorStarts[i] = renderer->getProgramUniformLocation(programId, "gradientColorStarts[" + to_string(i) + "]");
		if (uniformGradientColorStarts[i] == -1) return;
	}
	uniformInverseGradientTextureMatrix = renderer->getProgramUniformLocation(programId, "inverseGradientTextureMatrix");
	if (uniformInverseGradientTextureMatrix == -1) return;

	//
	initialized = true;
}

void GUIShader::useProgram()
{
	auto context = renderer->getDefaultContext();
	renderer->useProgram(context, programId);
	renderer->setLighting(context, renderer->LIGHTING_NONE);
	renderer->setProgramUniformInteger(context, uniformDiffuseTextureUnit, 0);
	renderer->setProgramUniformInteger(context, uniformMaskTextureUnit, 1);
	renderer->setProgramUniformInteger(context, uniformMaskTextureAvailable, 0);
	renderer->setProgramUniformFloat(context, uniformMaskMaxValue, 1.0);
	renderer->setProgramUniformInteger(context, uniformGradientAvailable, 0);
	isRunning = true;
}

void GUIShader::unUseProgram()
{
	isRunning = false;
}

void GUIShader::bindTexture(int32_t textureId)
{
	if (isRunning == false) return;
	switch(renderer->getTextureUnit(renderer->getDefaultContext())) {
		case 0:
			renderer->setProgramUniformInteger(renderer->getDefaultContext(), uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
			break;
		case 1:
			renderer->setProgramUniformFloat(renderer->getDefaultContext(), uniformMaskMaxValue, renderer->getMaskMaxValue(renderer->getDefaultContext()));
			renderer->setProgramUniformInteger(renderer->getDefaultContext(), uniformMaskTextureAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}

void GUIShader::updateEffect()
{
	if (isRunning == false) return;

	// use default context
	auto context = renderer->getDefaultContext();

	//
	renderer->setProgramUniformFloatVec4(context, uniformEffectColorMul, renderer->getEffectColorMul(context));
	renderer->setProgramUniformFloatVec4(context, uniformEffectColorAdd, renderer->getEffectColorAdd(context));
}


void GUIShader::updateTextureMatrix() {
	if (isRunning == false) return;

	// use default context
	auto context = renderer->getDefaultContext();

	//
	renderer->setProgramUniformFloatMatrix3x3(context, uniformTextureMatrix, renderer->getTextureMatrix(context).getArray());
}

void GUIShader::setGradient(int count, array<GUIColor, 10>& colors, array<float, 10>& colorStarts, float rotationAngle) {
	// use default context
	auto context = renderer->getDefaultContext();

	//
	count = Math::clamp(count, 0, 10);
	renderer->setProgramUniformInteger(context, uniformGradientAvailable, count > 0?1:0);
	if (count == 0) return;
	for (auto i = 0; i < count; i++) renderer->setProgramUniformFloatVec4(context, uniformGradientColors[i], colors[i].getArray());
	renderer->setProgramUniformInteger(context, uniformGradientColorCount, count);
	for (auto i = 0; i < count; i++) renderer->setProgramUniformFloat(context, uniformGradientColorStarts[i], colorStarts[i]);
	renderer->setProgramUniformFloatMatrix3x3(context, uniformInverseGradientTextureMatrix, Matrix2D3x3::rotateAroundTextureCenter(-rotationAngle).getArray());
}

void GUIShader::unsetGradient() {
	// use default context
	auto context = renderer->getDefaultContext();

	//
	renderer->setProgramUniformInteger(context, uniformGradientAvailable, 0);
}
