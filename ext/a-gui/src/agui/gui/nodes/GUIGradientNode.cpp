#include <agui/gui/nodes/GUIGradientNode.h>

#include <agui/agui.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/gui/textures/GUITextureManager.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_Clipping.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/renderer/GUIRenderer.h>
#include <agui/gui/GUI.h>
#include <agui/math/Matrix3x3.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/Float.h>
#include <agui/utilities/Integer.h>
#include <agui/utilities/StringTools.h>

using agui::gui::nodes::GUIGradientNode;

using agui::gui::textures::GUITexture;
using agui::gui::textures::GUITextureManager;
using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_Clipping;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::renderer::GUIRenderer;
using agui::gui::GUI;
using agui::math::Matrix3x3;
using agui::utilities::Console;
using agui::utilities::Float;
using agui::utilities::Integer;
using agui::utilities::StringTools;

GUIGradientNode::Gradient GUIGradientNode::createGradient(const string& colors, const string& rotation) {
	Gradient gradient;
	gradient.rotationAngle = Integer::parse(rotation);
	auto colorsArray = StringTools::tokenize(colors, ",");
	for (const auto& color: colorsArray) {
		auto colorComponents = StringTools::tokenize(color, "=");
		if (colorComponents.size() != 2) {
			Console::printLine("GUIGradientNode::createGradient():color invalid: " + color);
			continue;
		}
		if (StringTools::endsWith(colorComponents[0], "%") == false) {
			Console::printLine("GUIGradientNode::createGradient():color start invalid: " + colorComponents[0]);
			continue;
		}
		colorComponents[0] = StringTools::trim(colorComponents[0]);
		colorComponents[0] = StringTools::substring(colorComponents[0], 0, colorComponents[0].size() - 1);
		colorComponents[1] = StringTools::trim(colorComponents[1]);
		auto start = Float::parse(colorComponents[0]) / 100.0f;
		auto guiColor = GUIColor(colorComponents[1]);
		gradient.colors[gradient.count] = guiColor;
		gradient.colorStarts[gradient.count] = start;
		gradient.count++;
	}
	return gradient;
}

GUIGradientNode::GUIGradientNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScale9Grid,
	const GUIColor& backgroundImageEffectColorMul,
	const GUIColor& backgroundImageEffectColorAdd,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& tooltip,
	const GUIColor& effectColorMul,
	const GUIColor& effectColorAdd,
	const GUINode_Clipping& clipping,
	const string& mask,
	float maskMaxValue,
	const Gradient& gradient):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
	this->effectColorMul = effectColorMul;
	this->effectColorAdd = effectColorAdd;
	this->textureMatrix.identity();
	this->clipping = clipping;
	this->setMask(mask);
	this->maskMaxValue = maskMaxValue;
	this->gradient = gradient;
}

const string GUIGradientNode::getNodeType()
{
	return "gradient";
}

bool GUIGradientNode::isContentNode()
{
	return true;
}

int GUIGradientNode::getContentWidth()
{
	if (requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return border.left + border.right + padding.left + padding.right;
	} else {
		return computedConstraints.width;
	}
}

int GUIGradientNode::getContentHeight()
{
	if (requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return border.top + border.bottom + padding.top + padding.bottom;
	} else {
		return computedConstraints.height;
	}
}

void GUIGradientNode::dispose()
{
	if (maskTexture != nullptr) GUI::getTextureManager()->removeTexture(maskTexture->getId());
	GUINode::dispose();
}

void GUIGradientNode::render(GUIRenderer* guiRenderer)
{
	if (shouldRender() == false) return;

	GUINode::render(guiRenderer);

	// clipping
	{
		auto renderOffsetXCurrent = guiRenderer->getRenderOffsetX();
		auto renderOffsetYCurrent = guiRenderer->getRenderOffsetY();
		auto screenWidth = screenNode->getScreenWidth();
		auto screenHeight = screenNode->getScreenHeight();
		float left = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft + padding.left + clipping.left;
		float top = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop + padding.top + clipping.top;
		float width = getContentWidth() - padding.left - padding.right - clipping.left - clipping.right;
		float height = getContentHeight() - padding.top - padding.bottom - clipping.top - clipping.bottom;
		auto renderAreaLeft = ((left) / (screenWidth / 2.0f)) - renderOffsetXCurrent - 1.0f;
		auto renderAreaTop = ((screenHeight - top) / (screenHeight / 2.0f)) + renderOffsetYCurrent - 1.0f;
		auto renderAreaRight = ((left + width) / (screenWidth / 2.0f)) - renderOffsetXCurrent - 1.0f;
		auto renderAreaBottom = ((screenHeight - top - height) / (screenHeight / 2.0f)) + renderOffsetYCurrent - 1.0f;
		guiRenderer->setSubRenderAreaLeft(renderAreaLeft);
		guiRenderer->setSubRenderAreaTop(renderAreaTop);
		guiRenderer->setSubRenderAreaRight(renderAreaRight);
		guiRenderer->setSubRenderAreaBottom(renderAreaBottom);
	}

	// render texture if required
	if (maskTextureId != 0) {
		guiRenderer->setMaskMaxValue(maskMaxValue);
		guiRenderer->bindMask(maskTextureId);
	}
	guiRenderer->setGradient(gradient.count, gradient.colors, gradient.colorStarts, gradient.rotationAngle);
	//
	auto screenWidth = screenNode->getScreenWidth();
	auto screenHeight = screenNode->getScreenHeight();
	guiRenderer->setTexureMatrix(textureMatrix);
	guiRenderer->setEffectColorMul(effectColorMul);
	guiRenderer->setEffectColorAdd(effectColorAdd);
	float left = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft + padding.left;
	float top = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop + padding.top;
	float width = getContentWidth() - padding.left - padding.right;
	float height = getContentHeight() - padding.top - padding.bottom;
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f,
		0.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f,
		0.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f,
		1.0f,
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f,
		1.0f
	);
	guiRenderer->render();
	// gradient
	guiRenderer->unsetGradient();
	//
	guiRenderer->bindTexture(0);
	if (maskTextureId != 0) {
		guiRenderer->setMaskMaxValue(1.0f);
		guiRenderer->bindMask(0);
	}
	guiRenderer->setTexureMatrix((Matrix3x3()).identity());
}

void GUIGradientNode::setTextureMatrix(const Matrix3x3& textureMatrix) {
	this->textureMatrix.set(textureMatrix);
}

const GUIColor& GUIGradientNode::getEffectColorMul() {
	return effectColorMul;
}

void GUIGradientNode::setEffectColorMul(const GUIColor& effectColorMul) {
	this->effectColorMul = effectColorMul;
}

const GUIColor& GUIGradientNode::getEffectColorAdd() {
	return effectColorAdd;
}

void GUIGradientNode::setEffectColorAdd(const GUIColor& effectColorAdd) {
	this->effectColorAdd = effectColorAdd;
}

GUINode_Clipping& GUIGradientNode::getClipping() {
	return clipping;
}

GUINode_Clipping GUIGradientNode::createClipping(const string& allClipping, const string& left, const string& top, const string& right, const string& bottom)
{
	GUINode_Clipping clipping;
	clipping.left = getRequestedPixelValue(allClipping, 0);
	clipping.top = getRequestedPixelValue(allClipping, 0);
	clipping.right = getRequestedPixelValue(allClipping, 0);
	clipping.bottom = getRequestedPixelValue(allClipping, 0);
	clipping.left = getRequestedPixelValue(left, clipping.left);
	clipping.top = getRequestedPixelValue(top, clipping.top);
	clipping.right = getRequestedPixelValue(right, clipping.right);
	clipping.bottom = getRequestedPixelValue(bottom, clipping.bottom);
	return clipping;
}

const string& GUIGradientNode::getMask() {
	return mask;
}

void GUIGradientNode::setMask(const string& mask) {
	if (maskTexture != nullptr) {
		GUI::getTextureManager()->removeTexture(maskTexture->getId());
		maskTexture = nullptr;
	}
	this->mask = mask;
	this->maskTexture = mask.empty() == true?nullptr:screenNode->getImage(mask);
	this->maskTextureId = maskTexture == nullptr?0:GUI::getTextureManager()->addTexture(maskTexture, 0);
}
