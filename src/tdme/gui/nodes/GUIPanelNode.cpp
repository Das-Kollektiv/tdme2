#include <tdme/gui/nodes/GUIPanelNode.h>

#include <string>
#include <set>
#include <vector>

#include <tdme/gui/events/GUIMouseEvent.h>

using std::set;
using std::string;
using std::vector;

using tdme::gui::nodes::GUIPanelNode;
using tdme::gui::events::GUIMouseEvent;

GUIPanelNode::GUIPanelNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const string& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, const GUINode_Alignments& alignments, const GUINode_RequestedConstraints& requestedConstraints, const GUIColor& backgroundColor, const GUINode_Border& border, const GUINode_Padding& padding, const GUINodeConditions& showOn, const GUINodeConditions& hideOn, GUILayoutNode_Alignment* alignment) throw (GUIParserException)
	: GUILayoutNode(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn, alignment)
{
}

const string GUIPanelNode::getNodeType()
{
	return "panel";
}

void GUIPanelNode::determineMouseEventNodes(GUIMouseEvent* event, set<string>& eventNodeIds)
{
	GUILayoutNode::determineMouseEventNodes(event, eventNodeIds);
	if (isEventBelongingToNode(event) == true) {
		event->setProcessed(true);
	}
}

void GUIPanelNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUILayoutNode::handleKeyboardEvent(event);
}

