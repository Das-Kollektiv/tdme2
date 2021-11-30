#include <tdme/gui/nodes/GUIInputInternalNode.h>

#include <tdme/gui/elements/GUIInputController.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIInputInternalController.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>

using tdme::gui::elements::GUIInputController;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIInputInternalController;
using tdme::gui::nodes::GUIInputInternalNode;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;

GUIInputInternalNode::GUIInputInternalNode(
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
	const string& font,
	const string& color,
	const string& colorDisabled,
	const MutableString& text,
	int maxLength
	):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn)
{
	this->font = font.empty() == true?nullptr:GUI::getFont(screenNode->getApplicationRootPathName(), font);
	this->color = color.empty() == true || color.length() == 0 ? GUIColor() : GUIColor(color);
	this->colorDisabled = colorDisabled.empty() == true || colorDisabled.length() == 0 ? GUIColor() : GUIColor(colorDisabled);
	this->text = text;
	this->maxLength = maxLength;
	if (this->font != nullptr) this->font->initialize();
	this->controller = new GUIInputInternalController(this);
	this->controller->initialize();
}

int GUIInputInternalNode::createMaxLength(const string& s)
{
	try {
		auto maxLength = Integer::parseInt(s);
		return maxLength;
	} catch (Exception& exception) {
		Console::print(string("GUIInputInternalNode::createMaxLength(): An error occurred: "));
		Console::println(string(exception.what()));
		return 0;
	}
}

const string GUIInputInternalNode::getNodeType()
{
	return "text";
}

bool GUIInputInternalNode::isContentNode()
{
	return true;
}

int GUIInputInternalNode::getContentWidth()
{
	return font == nullptr?0:font->getTextWidth(text) + border.left + border.right + padding.left + padding.right;
}

int GUIInputInternalNode::getContentHeight()
{
	return font == nullptr?0:font->getLineHeight() + border.top + border.bottom + padding.top + padding.bottom;
}

void GUIInputInternalNode::dispose()
{
	if (font != nullptr) font->dispose();
	GUINode::dispose();
	this->controller->dispose();
}

void GUIInputInternalNode::render(GUIRenderer* guiRenderer)
{
	if (shouldRender() == false) return;

	GUINode::render(guiRenderer);
	auto inputInternalController = required_dynamic_cast<GUIInputInternalController*>(this->controller);
	auto inputNode = this->getParentControllerNode();
	auto inputNodeController = required_dynamic_cast<GUIInputController*>(inputNode->getController());
	auto disable = inputNodeController->isDisabled();
	auto index = inputInternalController->getIndex();
	auto selectionIndex = inputInternalController->getSelectionIndex();
	if (font != nullptr) {
		font->drawString(
			guiRenderer,
			computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft,
			computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop,
			text,
			inputInternalController->getOffset(),
			0,
			disable == false?color:colorDisabled,
			selectionIndex == -1 || selectionIndex == index?-1:Math::min(selectionIndex, index),
			selectionIndex == -1 || selectionIndex == index?-1:Math::max(selectionIndex, index),
			inputNode->getBackgroundColor()
		);
	}
	if (screenNode->getGUI() != nullptr &&
		static_cast<GUIParentNode*>(screenNode->getGUI()->getFocussedNode()) == inputNode &&
		inputInternalController->isShowCursor() == true &&
		inputInternalController->getCursorMode() == GUIInputInternalController::CURSORMODE_SHOW &&
		(selectionIndex == -1 || selectionIndex == index)) {
		auto screenWidth = screenNode->getScreenWidth();
		auto screenHeight = screenNode->getScreenHeight();
		float left = computedConstraints.left + computedConstraints.alignmentLeft + border.left + padding.left + (font != nullptr?font->getTextIndexX(text, inputInternalController->getOffset(), 0, inputInternalController->getIndex()):0);
		float top = computedConstraints.top + computedConstraints.alignmentTop + border.top + padding.top;
		float width = 2;
		float height = computedConstraints.height - border.top - border.bottom- padding.top - padding.bottom;
		auto& colorData = (disable == false?color:colorDisabled).getArray();
		guiRenderer->bindTexture(0);
		guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, colorData[0], colorData[1], colorData[2], colorData[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, colorData[0], colorData[1], colorData[2], colorData[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, colorData[0], colorData[1], colorData[2], colorData[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, colorData[0], colorData[1], colorData[2], colorData[3], 0.0f, 0.0f);
		guiRenderer->render();
	}
}

