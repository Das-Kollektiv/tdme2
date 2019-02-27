#include <tdme/gui/nodes/GUISpaceNode.h>

#include <string>

#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/utils/StringUtils.h>

using std::string;

using tdme::gui::nodes::GUISpaceNode;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::utils::StringUtils;

GUISpaceNode::GUISpaceNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScale9Grid,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn
):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, border, padding, showOn, hideOn)
{
}

const string GUISpaceNode::getNodeType()
{
	return "space";
}

bool GUISpaceNode::isContentNode()
{
	return false;
}

int32_t GUISpaceNode::getContentWidth()
{
	return computedConstraints.width;
}

int32_t GUISpaceNode::getContentHeight()
{
	return computedConstraints.height;
}

GUINode_RequestedConstraints GUISpaceNode::createRequestedConstraints(const string& left, const string& top, const string& width, const string& height)
{
	GUINode_RequestedConstraints constraints;
	constraints.leftType = getRequestedConstraintsType(StringUtils::trim(left), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints.left = getRequestedConstraintsValue(StringUtils::trim(left), 0);
	constraints.topType = getRequestedConstraintsType(StringUtils::trim(top), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints.top = getRequestedConstraintsValue(StringUtils::trim(top), 0);
	constraints.widthType = getRequestedConstraintsType(StringUtils::trim(width), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints.width = getRequestedConstraintsValue(StringUtils::trim(width), 1);
	constraints.heightType = getRequestedConstraintsType(StringUtils::trim(height), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints.height = getRequestedConstraintsValue(StringUtils::trim(height), 1);
	return constraints;
}

void GUISpaceNode::dispose()
{
	GUINode::dispose();
}

void GUISpaceNode::render(GUIRenderer* guiRenderer)
{
	if (conditionsMet == false) return;

	GUINode::render(guiRenderer);
}

