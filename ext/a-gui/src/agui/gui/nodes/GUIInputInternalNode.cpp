#include <agui/gui/nodes/GUIInputInternalNode.h>

#include <agui/agui.h>
#include <agui/gui/elements/GUIInputController.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIInputInternalController.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/renderer/GUIFont.h>
#include <agui/gui/renderer/GUIRenderer.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/Integer.h>
#include <agui/utilities/MutableString.h>

using agui::gui::elements::GUIInputController;
using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIInputInternalController;
using agui::gui::nodes::GUIInputInternalNode;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::renderer::GUIFont;
using agui::gui::renderer::GUIRenderer;
using agui::gui::GUI;
using agui::math::Math;
using agui::utilities::Console;
using agui::utilities::Exception;
using agui::utilities::Integer;
using agui::utilities::MutableString;

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
	const string& tooltip,
	const string& font,
	int size,
	const string& color,
	const string& colorDisabled,
	const MutableString& text,
	int maxLength
	):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
	this->font = font.empty() == true?nullptr:screenNode->getFont(font, size);
	this->color = color.empty() == true || color.length() == 0 ? GUIColor() : GUIColor(color);
	this->colorDisabled = colorDisabled.empty() == true || colorDisabled.length() == 0 ? GUIColor() : GUIColor(colorDisabled);
	this->text = text;
	this->maxLength = maxLength;
	if (this->font != nullptr) this->font->initialize();
	//
	auto controller = new GUIInputInternalController(this);
	controller->initialize();
	this->setController(controller);
}

int GUIInputInternalNode::createMaxLength(const string& s)
{
	try {
		auto maxLength = Integer::parse(s);
		return maxLength;
	} catch (Exception& exception) {
		Console::print(string("GUIInputInternalNode::createMaxLength(): An error occurred: "));
		Console::printLine(string(exception.what()));
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
}

void GUIInputInternalNode::render(GUIRenderer* guiRenderer)
{
	if (shouldRender() == false) return;

	GUINode::render(guiRenderer);
	auto inputInternalController = required_dynamic_cast<GUIInputInternalController*>(this->getController());
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
		const auto& cursorColor = disable == false?color:colorDisabled;
		guiRenderer->bindTexture(0);
		guiRenderer->addQuad(
			((left) / (screenWidth / 2.0f)) - 1.0f,
			((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
			cursorColor[0],
			cursorColor[1],
			cursorColor[2],
			cursorColor[3],
			0.0f,
			1.0f,
			((left + width) / (screenWidth / 2.0f)) - 1.0f,
			((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
			cursorColor[0],
			cursorColor[1],
			cursorColor[2],
			cursorColor[3],
			1.0f,
			1.0f,
			((left + width) / (screenWidth / 2.0f)) - 1.0f,
			((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
			cursorColor[0],
			cursorColor[1],
			cursorColor[2],
			cursorColor[3],
			1.0f,
			0.0f,
			((left) / (screenWidth / 2.0f)) - 1.0f,
			((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
			cursorColor[0],
			cursorColor[1],
			cursorColor[2],
			cursorColor[3],
			0.0f,
			0.0f
		);
		guiRenderer->render();
	}
}

