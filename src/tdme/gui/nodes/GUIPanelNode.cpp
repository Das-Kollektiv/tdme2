// Generated from /tdme/src/tdme/gui/nodes/GUIPanelNode.java
#include <tdme/gui/nodes/GUIPanelNode.h>

#include <string>

#include <tdme/gui/events/GUIMouseEvent.h>

using std::wstring;

using tdme::gui::nodes::GUIPanelNode;
using tdme::gui::events::GUIMouseEvent;

GUIPanelNode::GUIPanelNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIPanelNode::GUIPanelNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUILayoutNode_Alignment* alignment)  /* throws(GUIParserException) */
	: GUIPanelNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,overflowX,overflowY,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn,alignment);
}

void GUIPanelNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUILayoutNode_Alignment* alignment) /* throws(GUIParserException) */
{
	super::ctor(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn, alignment);
}

const wstring GUIPanelNode::getNodeType()
{
	return L"panel";
}

void GUIPanelNode::handleMouseEvent(GUIMouseEvent* event)
{
	super::handleMouseEvent(event);
	if (isEventBelongingToNode(event) == true) {
		event->setProcessed(true);
	}
}

void GUIPanelNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	super::handleKeyboardEvent(event);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIPanelNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIPanelNode", 27);
    return c;
}

java::lang::Class* GUIPanelNode::getClass0()
{
	return class_();
}

