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
#include <tdme/gui/renderer/GUIRenderer.h>

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
using tdme::gui::renderer::GUIRenderer;

GUIImageNode::GUIImageNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& src,
	const GUIColor& effectColorMul,
	const GUIColor& effectColorAdd)
	throw(GUIParserException):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, border, padding, showOn, hideOn)
{
	init();
	this->texture = GUI::getImage(src);
	this->textureId = Engine::getInstance()->getTextureManager()->addTexture(texture);
	this->effectColorMul = effectColorMul;
	this->effectColorAdd = effectColorAdd;
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
	float left = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft;
	float top = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop;
	float width = getContentWidth();
	float height = getContentHeight();
	guiRenderer->bindTexture(textureId);
	guiRenderer->setEffectColorMul(effectColorMul);
	guiRenderer->setEffectColorAdd(effectColorAdd);
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		0.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		0.0f,
		1.0f
	);
	guiRenderer->render();
	guiRenderer->bindTexture(0);
}

