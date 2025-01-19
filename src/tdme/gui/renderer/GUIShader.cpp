#include <tdme/gui/renderer/GUIShader.h>

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>

#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/utilities/Console.h>

using tdme::gui::renderer::GUIShader;

using std::array;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::gui::nodes::GUIColor;
using tdme::math::Math;
using tdme::math::Matrix3x3;
using tdme::utilities::Console;

GUIShader::GUIShader(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
	initialized = false;
	isRunning = false;
}

bool GUIShader::isInitialized()
{
	return initialized;
}

void GUIShader::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/gui",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/gui",
		"render_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_GUI);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 1, "inSolidColor");
		rendererBackend->setProgramAttributeLocation(programId, 2, "inTextureUV");
		rendererBackend->setProgramAttributeLocation(programId, 3, "inColor");
	}
	if (rendererBackend->linkProgram(programId) == false) return;

	uniformDiffuseTextureUnit = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1) return;

	uniformDiffuseTextureAvailable = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1) return;

	uniformMaskTextureUnit = rendererBackend->getProgramUniformLocation(programId, "maskTextureUnit");
	if (uniformMaskTextureUnit == -1) return;

	uniformMaskTextureAvailable = rendererBackend->getProgramUniformLocation(programId, "maskTextureAvailable");
	if (uniformMaskTextureAvailable == -1) return;

	uniformMaskMaxValue = rendererBackend->getProgramUniformLocation(programId, "maskMaxValue");
	if (uniformMaskMaxValue == -1) return;

	uniformEffectColorMul = rendererBackend->getProgramUniformLocation(programId, "effectColorMul");
	if (uniformEffectColorMul == -1) return;

	uniformEffectColorAdd = rendererBackend->getProgramUniformLocation(programId, "effectColorAdd");
	if (uniformEffectColorAdd == -1) return;

	// texture matrix
	uniformTextureMatrix = rendererBackend->getProgramUniformLocation(programId, "textureMatrix");
	if (uniformTextureMatrix == -1) return;

	// gradients
	uniformGradientAvailable = rendererBackend->getProgramUniformLocation(programId, "gradientAvailable");
	if (uniformGradientAvailable == -1) return;
	for (auto i = 0; i < uniformGradientColors.size(); i++) {
		uniformGradientColors[i] = rendererBackend->getProgramUniformLocation(programId, "gradientColors[" + to_string(i) + "]");
		if (uniformGradientColors[i] == -1) return;
	}
	uniformGradientColorCount = rendererBackend->getProgramUniformLocation(programId, "gradientColorCount");
	if (uniformGradientColorCount == -1) return;
	for (auto i = 0; i < uniformGradientColorStarts.size(); i++) {
		uniformGradientColorStarts[i] = rendererBackend->getProgramUniformLocation(programId, "gradientColorStarts[" + to_string(i) + "]");
		if (uniformGradientColorStarts[i] == -1) return;
	}
	uniformInverseGradientTextureMatrix = rendererBackend->getProgramUniformLocation(programId, "inverseGradientTextureMatrix");
	if (uniformInverseGradientTextureMatrix == -1) return;

	//
	initialized = true;
}

void GUIShader::useProgram()
{
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureUnit, 0);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformMaskTextureUnit, 1);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformMaskTextureAvailable, 0);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformMaskMaxValue, 1.0);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformGradientAvailable, 0);
	isRunning = true;
}

void GUIShader::unUseProgram()
{
	isRunning = false;
}

void GUIShader::bindTexture(int32_t textureId)
{
	if (isRunning == false) return;
	switch(rendererBackend->getTextureUnit(rendererBackend->CONTEXTINDEX_DEFAULT)) {
		case 0:
			rendererBackend->setProgramUniformInteger(rendererBackend->CONTEXTINDEX_DEFAULT, uniformDiffuseTextureAvailable, textureId == 0?0:1);
			break;
		case 1:
			rendererBackend->setProgramUniformFloat(rendererBackend->CONTEXTINDEX_DEFAULT, uniformMaskMaxValue, rendererBackend->getMaskMaxValue(rendererBackend->CONTEXTINDEX_DEFAULT));
			rendererBackend->setProgramUniformInteger(rendererBackend->CONTEXTINDEX_DEFAULT, uniformMaskTextureAvailable, textureId == 0?0:1);
			break;
	}
}

void GUIShader::updateEffect()
{
	if (isRunning == false) return;

	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformEffectColorMul, rendererBackend->getEffectColorMul(contextIdx));
	rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformEffectColorAdd, rendererBackend->getEffectColorAdd(contextIdx));
}


void GUIShader::updateTextureMatrix() {
	if (isRunning == false) return;

	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	rendererBackend->setProgramUniformFloatMatrix3x3(contextIdx, uniformTextureMatrix, rendererBackend->getTextureMatrix(contextIdx).getArray());
}

void GUIShader::setGradient(int count, array<GUIColor, 10>& colors, array<float, 10>& colorStarts, float rotationAngle) {
	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	count = Math::clamp(count, 0, 10);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformGradientAvailable, count > 0?1:0);
	if (count == 0) return;
	for (auto i = 0; i < count; i++) rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformGradientColors[i], colors[i].getArray());
	rendererBackend->setProgramUniformInteger(contextIdx, uniformGradientColorCount, count);
	for (auto i = 0; i < count; i++) rendererBackend->setProgramUniformFloat(contextIdx, uniformGradientColorStarts[i], colorStarts[i]);
	rendererBackend->setProgramUniformFloatMatrix3x3(contextIdx, uniformInverseGradientTextureMatrix, Matrix3x3::rotateAroundTextureCenter(-rotationAngle).getArray());
}

void GUIShader::unsetGradient() {
	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	rendererBackend->setProgramUniformInteger(contextIdx, uniformGradientAvailable, 0);
}
