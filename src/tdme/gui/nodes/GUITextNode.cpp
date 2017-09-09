// Generated from /tdme/src/tdme/gui/nodes/GUITextNode.java
#include <tdme/gui/nodes/GUITextNode.h>

#include <string>
#include <vector>

#include <java/lang/String.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/utils/MutableString.h>

using std::vector;
using std::wstring;

using tdme::gui::nodes::GUITextNode;
using java::lang::String;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::renderer::GUIFont;
using tdme::utils::MutableString;

GUITextNode::GUITextNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITextNode::GUITextNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const wstring& font, const wstring& color, MutableString* text)  /* throws(Exception) */
	: GUITextNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn,font,color,text);
}

void GUITextNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const wstring& font, const wstring& color, MutableString* text) /* throws(Exception) */
{
	super::ctor(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
	this->font = GUI::getFont(font);
	this->color = color.empty() == true || color.length() == 0 ? new GUIColor() : new GUIColor(color);
	this->text = text;
	this->font->initialize();
}

String* GUITextNode::getNodeType()
{
	return u"text"_j;
}

bool GUITextNode::isContentNode()
{
	return true;
}

int32_t GUITextNode::getContentWidth()
{
	return font->getTextWidth(text) + border->left + border->right+ padding->left+ padding->right;
}

int32_t GUITextNode::getContentHeight()
{
	return font->getLineHeight() + border->top + border->bottom+ padding->top+ padding->bottom;
}

MutableString* GUITextNode::getText()
{
	return text;
}

void GUITextNode::dispose()
{
	this->font->dispose();
	super::dispose();
}

void GUITextNode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	if (conditionsMet == false)
		return;

	super::render(guiRenderer, floatingNodes);
	font->drawString(guiRenderer, computedConstraints->left + computedConstraints->alignmentLeft + computedConstraints->contentAlignmentLeft, computedConstraints->top + computedConstraints->alignmentTop + computedConstraints->contentAlignmentTop, text, 0, 0, color);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITextNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUITextNode", 26);
    return c;
}

java::lang::Class* GUITextNode::getClass0()
{
	return class_();
}

