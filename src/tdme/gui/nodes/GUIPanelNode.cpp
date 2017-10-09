#include <tdme/gui/nodes/GUIPanelNode.h>

#include <string>

#include <tdme/gui/events/GUIMouseEvent.h>

using std::wstring;

using tdme::gui::nodes::GUIPanelNode;
using tdme::gui::events::GUIMouseEvent;

GUIPanelNode::GUIPanelNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUILayoutNode_Alignment* alignment)  /* throws(GUIParserException) */
	: GUILayoutNode(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn, alignment)
{
}

const wstring GUIPanelNode::getNodeType()
{
	return L"panel";
}

void GUIPanelNode::handleMouseEvent(GUIMouseEvent* event)
{
	GUILayoutNode::handleMouseEvent(event);
	if (isEventBelongingToNode(event) == true) {
		event->setProcessed(true);
	}
}

void GUIPanelNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUILayoutNode::handleKeyboardEvent(event);
}

