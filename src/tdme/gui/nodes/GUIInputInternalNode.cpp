// Generated from /tdme/src/tdme/gui/nodes/GUIInputInternalNode.java
#include <tdme/gui/nodes/GUIInputInternalNode.h>

#include <java/lang/Integer.h>
#include <java/lang/String.h>
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
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include <Array.h>

using tdme::gui::nodes::GUIInputInternalNode;
using java::lang::Integer;
using java::lang::String;
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
using tdme::utils::_Console;
using tdme::utils::_Exception;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIInputInternalNode::GUIInputInternalNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIInputInternalNode::GUIInputInternalNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, String* font, String* color, String* colorDisabled, MutableString* text, int32_t maxLength)  /* throws(Exception) */
	: GUIInputInternalNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn,font,color,colorDisabled,text,maxLength);
}

int32_t GUIInputInternalNode::createMaxLength(String* s)
{
	clinit();
	try {
		auto maxLength = Integer::parseInt(s);
		return maxLength;
	} catch (_Exception& exception) {
		_Console::print(string("GUIInputInternalNode::createMaxLength(): An error occurred: "));
		_Console::println(string(exception.what()));
		return 0;
	}
}

void GUIInputInternalNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, String* font, String* color, String* colorDisabled, MutableString* text, int32_t maxLength) /* throws(Exception) */
{
	super::ctor(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
	this->font = GUI::getFont(font);
	this->color = color == nullptr || color->length() == 0 ? new GUIColor() : new GUIColor(color);
	this->colorDisabled = colorDisabled == nullptr || colorDisabled->length() == 0 ? new GUIColor() : new GUIColor(colorDisabled);
	this->text = text;
	this->maxLength = maxLength;
	this->font->initialize();
	this->controller = new GUIInputInternalController(this);
	this->controller->initialize();
}

String* GUIInputInternalNode::getNodeType()
{
	return u"text"_j;
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
	super::dispose();
	this->controller->dispose();
}

void GUIInputInternalNode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	if (conditionsMet == false)
		return;

	super::render(guiRenderer, floatingNodes);
	auto controller = java_cast< GUIInputInternalController* >(this->controller);
	auto inputController = java_cast< GUIInputController* >(this->getParentControllerNode()->getController());
	auto disable = inputController->isDisabled();
	font->drawString(guiRenderer, computedConstraints->left + computedConstraints->alignmentLeft + computedConstraints->contentAlignmentLeft, computedConstraints->top + computedConstraints->alignmentTop + computedConstraints->contentAlignmentTop, text, controller->getOffset(), 0, disable == false ? color : colorDisabled);
	if (static_cast< GUIParentNode* >(screenNode->getGUI()->getFocussedNode()) == this->parentNode && controller->getCursorMode() == GUIInputInternalController_CursorMode::SHOW) {
		float screenWidth = guiRenderer->getGUI()->getWidth();
		float screenHeight = guiRenderer->getGUI()->getHeight();
		float left = computedConstraints->left + computedConstraints->alignmentLeft + border->left+ padding->left+ font->getTextIndexX(text, controller->getOffset(), 0, controller->getIndex());
		float top = computedConstraints->top + computedConstraints->alignmentTop + border->top+ padding->top;
		float width = 2;
		float height = computedConstraints->height - border->top - border->bottom- padding->top- padding->bottom;
		auto colorData = (disable == false ? color : colorDisabled)->getArray();
		guiRenderer->bindTexture(0);
		guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*colorData)[0], (*colorData)[1], (*colorData)[2], (*colorData)[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*colorData)[0], (*colorData)[1], (*colorData)[2], (*colorData)[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*colorData)[0], (*colorData)[1], (*colorData)[2], (*colorData)[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*colorData)[0], (*colorData)[1], (*colorData)[2], (*colorData)[3], 0.0f, 0.0f);
		guiRenderer->render();
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIInputInternalNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIInputInternalNode", 35);
    return c;
}

java::lang::Class* GUIInputInternalNode::getClass0()
{
	return class_();
}

