#include <agui/gui/nodes/GUIPanelNode.h>

#include <string>
#include <unordered_set>

#include <agui/agui.h>
#include <agui/gui/events/GUIMouseEvent.h>

using std::string;
using std::unordered_set;

using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIPanelNode;

GUIPanelNode::GUIPanelNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	GUIParentNode_Overflow* overflowX,
	GUIParentNode_Overflow* overflowY,
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
	GUILayoutNode_Alignment* alignment
) :
	GUILayoutNode(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip, alignment)
{
}

const string GUIPanelNode::getNodeType()
{
	return "panel";
}

void GUIPanelNode::determineMouseEventNodes(GUIMouseEvent* event, bool floatingNode, unordered_set<string>& eventNodeIds, unordered_set<string>& eventFloatingNodeIds, int flags)
{
	GUILayoutNode::determineMouseEventNodes(event, floatingNode, eventNodeIds, eventFloatingNodeIds, flags);
	if (isEventBelongingToNode(event) == true) {
		event->setProcessed(true);
	}
}

