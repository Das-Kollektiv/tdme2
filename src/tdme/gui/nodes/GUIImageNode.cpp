#include <tdme/gui/nodes/GUIImageNode.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/math/Matrix2D3x3.h>

using tdme::gui::nodes::GUIImageNode;

using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::renderer::GUIRenderer;
using tdme::math::Matrix2D3x3;

GUIImageNode::GUIImageNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScale9Grid,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& src,
	const GUIColor& effectColorMul,
	const GUIColor& effectColorAdd,
	const GUINode_Scale9Grid& scale9Grid)
	throw(GUIParserException):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, border, padding, showOn, hideOn)
{
	init();
	this->texture = GUI::getImage(src);
	this->textureId = Engine::getInstance()->getTextureManager()->addTexture(texture);
	this->effectColorMul = effectColorMul;
	this->effectColorAdd = effectColorAdd;
	this->scale9Grid = scale9Grid;
	this->textureMatrix.identity();
}

void GUIImageNode::init()
{
}

const string GUIImageNode::getNodeType()
{
	return "image";
}

bool GUIImageNode::isContentNode()
{
	return true;
}

int32_t GUIImageNode::getContentWidth()
{
	if (requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return (texture != nullptr ? texture->getWidth() : 0) + border.left + border.right + padding.left + padding.right;
	} else {
		return computedConstraints.width;
	}
}

int32_t GUIImageNode::getContentHeight()
{
	if (requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return (texture != nullptr ? texture->getHeight() : 0) + border.top + border.bottom + padding.top + padding.bottom;
	} else {
		return computedConstraints.height;
	}
}

void GUIImageNode::dispose()
{
	Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
	GUINode::dispose();
}

void GUIImageNode::render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes)
{
	if (conditionsMet == false)
		return;

	GUINode::render(guiRenderer, floatingNodes);
	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	guiRenderer->bindTexture(textureId);
	guiRenderer->setTexureMatrix(textureMatrix);
	guiRenderer->setEffectColorMul(effectColorMul);
	guiRenderer->setEffectColorAdd(effectColorAdd);
	if (scale9Grid.left == 0 &&
		scale9Grid.right == 0 &&
		scale9Grid.top == 0 &&
		scale9Grid.bottom == 0) {
		float left = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft;
		float top = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop;
		float width = getContentWidth();
		float height = getContentHeight();
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
	} else {
		auto scaleX = 1.0f;
		auto scaleY = 1.0f;
		// we have a scale here, because we have a axis without "scale9grid"
		if (scale9Grid.top == 0 && scale9Grid.bottom == 0) {
			scaleY = (float)getContentHeight() / (float)texture->getHeight();
			scaleX = scaleY;
		} else
		// we have a scale here, because we have a axis without "scale9grid"
		if (scale9Grid.left == 0 && scale9Grid.right == 0) {
			scaleX = (float)getContentWidth() / (float)texture->getWidth();
			scaleY = scaleX;
		}
		// we have no certain scale, take original image size
		GUINode_Scale9Grid scaledScale9Grid;
		scaledScale9Grid.left = static_cast<int>(scale9Grid.left * scaleX);
		scaledScale9Grid.right = static_cast<int>(scale9Grid.right * scaleX);
		scaledScale9Grid.top = static_cast<int>(scale9Grid.top * scaleY);
		scaledScale9Grid.bottom = static_cast<int>(scale9Grid.bottom * scaleY);
		float imageScreenLeft = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft;
		float imageScreenTop = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop;
		float imageScreenScale9Left = imageScreenLeft + scaledScale9Grid.left;
		float imageScreenScale9Top = imageScreenTop + scaledScale9Grid.top;
		float imageScreenWidth = getContentWidth();
		float imageScreenHeight = getContentHeight();
		float imageScreenScale9Right = imageScreenLeft + imageScreenWidth - scaledScale9Grid.right;
		float imageScreenScale9Bottom = imageScreenTop + imageScreenHeight - scaledScale9Grid.bottom;
		float imageTextureWidth = texture->getWidth();
		float imageTextureHeight = texture->getHeight();
		// left top
		if (scaledScale9Grid.left > 0 && scaledScale9Grid.top > 0) {
			float left = imageScreenLeft;
			float top = imageScreenTop;
			float width = scaledScale9Grid.left;
			float height = scaledScale9Grid.top;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				0.0f,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				0.0f,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f / imageTextureHeight * scale9Grid.top,
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				1.0f / imageTextureHeight * scale9Grid.top
			);
		}
		// middle top
		if (scaledScale9Grid.top > 0) {
			float left = imageScreenScale9Left;
			float top = imageScreenTop;
			float width = imageScreenWidth - scaledScale9Grid.left - scaledScale9Grid.right;
			float height = scaledScale9Grid.top;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				0.0f,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				0.0f,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f / imageTextureHeight * scale9Grid.top,
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f / imageTextureHeight * scale9Grid.top
			);
		}
		// right top
		if (scaledScale9Grid.right > 0 && scaledScale9Grid.top > 0) {
			float left = imageScreenScale9Right;
			float top = imageScreenTop;
			float width = scaledScale9Grid.right;
			float height = scaledScale9Grid.top;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
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
				1.0f / imageTextureHeight * scale9Grid.top,
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f / imageTextureHeight * scale9Grid.top
			);
		}
		// right bottom
		if (scaledScale9Grid.right > 0 && scaledScale9Grid.bottom > 0) {
			float left = imageScreenScale9Right;
			float top = imageScreenScale9Bottom;
			float width = scaledScale9Grid.right;
			float height = scaledScale9Grid.bottom;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f,
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f,
				1.0f,
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f
			);
		}
		// middle bottom
		if (scaledScale9Grid.bottom > 0) {
			float left = imageScreenScale9Left;
			float top = imageScreenScale9Bottom;
			float width = imageScreenWidth - scaledScale9Grid.left - scaledScale9Grid.right;
			float height = scaledScale9Grid.bottom;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f,
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f
			);
		}
		// left bottom
		if (scaledScale9Grid.left > 0 && scaledScale9Grid.bottom > 0) {
			float left = imageScreenLeft;
			float top = imageScreenScale9Bottom;
			float width = scaledScale9Grid.left;
			float height = scaledScale9Grid.bottom;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f,
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				1.0f
			);
		}
		// left middle
		if (scaledScale9Grid.left > 0) {
			float left = imageScreenLeft;
			float top = imageScreenScale9Top;
			float width = scaledScale9Grid.left;
			float height = imageScreenHeight - scaledScale9Grid.top - scaledScale9Grid.bottom;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				1.0f / imageTextureHeight * scale9Grid.top,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f / imageTextureHeight * scale9Grid.top,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom)
			);
		}
		// right middle
		if (scaledScale9Grid.right > 0) {
			float left = imageScreenScale9Right;
			float top = imageScreenScale9Top;
			float width = scaledScale9Grid.right;
			float height = imageScreenHeight - scaledScale9Grid.top - scaledScale9Grid.bottom;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f / imageTextureHeight * scale9Grid.top,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f,
				1.0f / imageTextureHeight * scale9Grid.top,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f,
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom)
			);
		}
		// center
		{
			float left = imageScreenScale9Left;
			float top = imageScreenScale9Top;
			float width = imageScreenWidth - scaledScale9Grid.left - scaledScale9Grid.right;
			float height = imageScreenHeight - scaledScale9Grid.top - scaledScale9Grid.bottom;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f / imageTextureHeight * scale9Grid.top,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f / imageTextureHeight * scale9Grid.top,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f / imageTextureWidth * scale9Grid.left,
				1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom)
			);
		}
	}
	guiRenderer->render();
	guiRenderer->bindTexture(0);
	guiRenderer->setTexureMatrix((Matrix2D3x3()).identity());
}

void GUIImageNode::setTextureMatrix(const Matrix2D3x3& textureMatrix) {
	this->textureMatrix.set(textureMatrix);
}
