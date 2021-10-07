#include <tdme/gui/nodes/GUIGradientNode.h>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_Clipping.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Matrix2D3x3.h>

using tdme::gui::nodes::GUIGradientNode;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::Engine;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Clipping;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::math::Matrix2D3x3;

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
	const GUIColor& effectColorMul,
	const GUIColor& effectColorAdd,
	const GUINode_Clipping& clipping,
	const string& mask,
	float maskMaxValue):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn)
{
	this->effectColorMul = effectColorMul;
	this->effectColorAdd = effectColorAdd;
	this->textureMatrix.identity();
	this->clipping = clipping;
	this->setMask(mask);
	this->maskMaxValue = maskMaxValue;
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
	if (maskTexture != nullptr) Engine::getInstance()->getTextureManager()->removeTexture(maskTexture->getId());
	GUINode::dispose();
}

void GUIGradientNode::render(GUIRenderer* guiRenderer)
{
	if (shouldRender() == false) return;

	GUINode::render(guiRenderer);

	{
		auto renderOffsetYCurrent = guiRenderer->getRenderOffsetY();
		auto screenWidth = screenNode->getScreenWidth();
		auto screenHeight = screenNode->getScreenHeight();
		float left = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft + padding.left + clipping.left;
		float top = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop + padding.top + clipping.top;
		float width = getContentWidth() - padding.left - padding.right - clipping.left - clipping.right;
		float height = getContentHeight() - padding.top - padding.bottom - clipping.top - clipping.bottom;
		auto renderAreaLeft = ((left) / (screenWidth / 2.0f)) - 1.0f;
		auto renderAreaTop = ((screenHeight - top) / (screenHeight / 2.0f)) + renderOffsetYCurrent - 1.0f;
		auto renderAreaRight = ((left + width) / (screenWidth / 2.0f)) - 1.0f;
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
	// gradient
	array<GUIColor, 10> gradientColors;
	array<float, 10> gradientColorStarts;
	gradientColors[0] = GUIColor("red");
	gradientColors[1] = GUIColor("green");
	gradientColorStarts[0] = 0.00f;
	gradientColorStarts[1] = 1.00f;
	guiRenderer->setGradient(2, gradientColors, gradientColorStarts, 45.0f);
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
	guiRenderer->setTexureMatrix((Matrix2D3x3()).identity());
}

void GUIGradientNode::setTextureMatrix(const Matrix2D3x3& textureMatrix) {
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
		Engine::getInstance()->getTextureManager()->removeTexture(maskTexture->getId());
		maskTexture = nullptr;
	}
	this->mask = mask;
	this->maskTexture = mask.empty() == true?nullptr:GUI::getImage(screenNode->getApplicationRootPathName(), mask);
	this->maskTextureId = maskTexture == nullptr?0:Engine::getInstance()->getTextureManager()->addTexture(maskTexture, nullptr);
}
