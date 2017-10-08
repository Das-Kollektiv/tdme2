#include <tdme/gui/nodes/GUIInputInternalNode.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUIInputController.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIInputInternalController_CursorMode.h>
#include <tdme/gui/nodes/GUIInputInternalController.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Integer.h>

using tdme::gui::nodes::GUIInputInternalNode;
using tdme::gui::GUI;
using tdme::gui::elements::GUIInputController;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIInputInternalController_CursorMode;
using tdme::gui::nodes::GUIInputInternalController;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::MutableString;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::Integer;

GUIInputInternalNode::GUIInputInternalNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const wstring& font, const wstring& color, const wstring& colorDisabled, MutableString* text, int32_t maxLength)  /* throws(Exception) */
	: 	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn)
{
	this->font = GUI::getFont(font);
	this->color = color.empty() == true || color.length() == 0 ? new GUIColor() : new GUIColor(color);
	this->colorDisabled = colorDisabled.empty() == true || colorDisabled.length() == 0 ? new GUIColor() : new GUIColor(colorDisabled);
	this->text = text;
	this->maxLength = maxLength;
	this->font->initialize();
	this->controller = new GUIInputInternalController(this);
	this->controller->initialize();
}

int32_t GUIInputInternalNode::createMaxLength(const wstring& s)
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

const wstring GUIInputInternalNode::getNodeType()
{
	return L"text";
}

bool GUIInputInternalNode::isContentNode()
{
	return true;
}

int32_t GUIInputInternalNode::getContentWidth()
{
	return font->getTextWidth(text) + border->left + border->right+ padding->left+ padding->right;
}

int32_t GUIInputInternalNode::getContentHeight()
{
	return font->getLineHeight() + border->top + border->bottom+ padding->top+ padding->bottom;
}

GUIFont* GUIInputInternalNode::getFont()
{
	return font;
}

MutableString* GUIInputInternalNode::getText()
{
	return text;
}

int32_t GUIInputInternalNode::getMaxLength()
{
	return maxLength;
}

void GUIInputInternalNode::dispose()
{
	this->font->dispose();
	GUINode::dispose();
	this->controller->dispose();
}

void GUIInputInternalNode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	if (conditionsMet == false)
		return;

	GUINode::render(guiRenderer, floatingNodes);
	auto controller = dynamic_cast< GUIInputInternalController* >(this->controller);
	auto inputController = dynamic_cast< GUIInputController* >(this->getParentControllerNode()->getController());
	auto disable = inputController->isDisabled();
	font->drawString(guiRenderer, computedConstraints->left + computedConstraints->alignmentLeft + computedConstraints->contentAlignmentLeft, computedConstraints->top + computedConstraints->alignmentTop + computedConstraints->contentAlignmentTop, text, controller->getOffset(), 0, disable == false ? color : colorDisabled);
	if (static_cast< GUIParentNode* >(screenNode->getGUI()->getFocussedNode()) == this->parentNode && controller->getCursorMode() == GUIInputInternalController_CursorMode::SHOW) {
		float screenWidth = guiRenderer->getGUI()->getWidth();
		float screenHeight = guiRenderer->getGUI()->getHeight();
		float left = computedConstraints->left + computedConstraints->alignmentLeft + border->left+ padding->left+ font->getTextIndexX(text, controller->getOffset(), 0, controller->getIndex());
		float top = computedConstraints->top + computedConstraints->alignmentTop + border->top+ padding->top;
		float width = 2;
		float height = computedConstraints->height - border->top - border->bottom- padding->top- padding->bottom;
		auto colorData = &(disable == false ? color : colorDisabled)->getArray();
		guiRenderer->bindTexture(0);
		guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*colorData)[0], (*colorData)[1], (*colorData)[2], (*colorData)[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*colorData)[0], (*colorData)[1], (*colorData)[2], (*colorData)[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*colorData)[0], (*colorData)[1], (*colorData)[2], (*colorData)[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*colorData)[0], (*colorData)[1], (*colorData)[2], (*colorData)[3], 0.0f, 0.0f);
		guiRenderer->render();
	}
}

