#include <agui/gui/nodes/GUITableNode.h>

#include <agui/agui.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINode_Alignments.h>
#include <agui/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <agui/gui/nodes/GUINode_AlignmentVertical.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Flow.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITableCellNode.h>
#include <agui/gui/nodes/GUITableRowNode.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>
#include <agui/utilities/StringTools.h>

using agui::gui::nodes::GUITableNode;

using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Alignments;
using agui::gui::nodes::GUINode_AlignmentHorizontal;
using agui::gui::nodes::GUINode_AlignmentVertical;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Flow;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITableCellNode;
using agui::gui::nodes::GUITableRowNode;
using agui::gui::GUI;
using agui::math::Math;
using agui::utilities::StringTools;

GUITableNode::GUITableNode(
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
	const string& tooltip
):
	GUIParentNode(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
}

const string GUITableNode::getNodeType()
{
	return "table";
}

bool GUITableNode::isContentNode()
{
	return false;
}

int GUITableNode::getContentWidth()
{
	auto width = 0;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			continue;
		}
		auto contentWidth = guiSubNode->getAutoWidth();
		if (contentWidth > width) {
			width = contentWidth;
		}
	}
	width += border.left + border.right;
	width += padding.left + padding.right;
	return width;
}

int GUITableNode::getContentHeight()
{
	auto height = 0;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			continue;
		}
		height += guiSubNode->getAutoHeight();
	}
	height += border.top + border.bottom;
	height += padding.top + padding.bottom;
	return height;
}

void GUITableNode::layoutSubNodes()
{
	GUIParentNode::layoutSubNodes();
	if (conditionsMet == false) return;
	{
		auto starCount = 0;
		auto height = computedConstraints.height - border.top - border.bottom - padding.top - padding.bottom;
		auto nodesHeight = 0;
		auto finalNodesHeight = 0;
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->conditionsMet == false) continue;
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			if (guiSubNode->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
				starCount++;
			} else {
				nodesHeight += guiSubNode->computedConstraints.height;
				finalNodesHeight += guiSubNode->computedConstraints.height;
			}
		}
		auto verticalStarPixelRest = 0.0f;
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->conditionsMet == false) continue;
			if (guiSubNode->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
				auto nodeStarHeight = (static_cast<float>(height) - static_cast<float>(nodesHeight)) / static_cast<float>(starCount);
				auto nodeStarHeightInt = static_cast<int>(nodeStarHeight);
				verticalStarPixelRest += nodeStarHeight - nodeStarHeightInt;
				if (static_cast<int>(verticalStarPixelRest) > 0) {
					nodeStarHeightInt += static_cast<int>(verticalStarPixelRest);
					verticalStarPixelRest -= static_cast<int>(verticalStarPixelRest);
				}
				guiSubNode->requestedConstraints.height = nodeStarHeightInt;
				guiSubNode->computedConstraints.height = nodeStarHeightInt;
				if (guiSubNode->computedConstraints.height < 0) {
					guiSubNode->computedConstraints.height = 0;
				}
				finalNodesHeight += guiSubNode->computedConstraints.height;
				if (dynamic_cast<GUIParentNode*>(guiSubNode) != nullptr) {
					required_dynamic_cast<GUIParentNode*>(guiSubNode)->layoutSubNodes();
				}
			}
		}
		if (alignments.vertical == GUINode_AlignmentVertical::TOP) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentTop = border.top + padding.top;
			}
		} else
		if (alignments.vertical == GUINode_AlignmentVertical::CENTER) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentTop = border.top + padding.top + ((height - finalNodesHeight) / 2);
			}
		} else
		if (alignments.vertical == GUINode_AlignmentVertical::BOTTOM) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentTop = (height - finalNodesHeight); // TODO: take bottom padding into account
			}
		}

		computeHorizontalChildrenAlignment();
	}

	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		guiSubNode->computeContentAlignment();
	}
	setTop(computedConstraints.top);
	setLeft(computedConstraints.left);
}

void GUITableNode::setTop(int top)
{
	if (requestedConstraints.topType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) top = requestedConstraints.top;
	GUIParentNode::setTop(top);
	top += computedConstraints.alignmentTop;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		guiSubNode->setTop(top);
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			continue;
		}
		top += guiSubNode->computedConstraints.height;
	}
}

void GUITableNode::setLeft(int left)
{
	if (requestedConstraints.leftType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) left = requestedConstraints.left;
	GUIParentNode::setLeft(left);
	left += computedConstraints.alignmentLeft;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		guiSubNode->setLeft(left);
		continue;
		left += guiSubNode->computedConstraints.width;
	}
}

int GUITableNode::getTableCellMaxWidth(int x) {
	auto maxWidth = -1;
	for (auto guiTableRowNode: subNodes) {
		auto guiTableCellNode = required_dynamic_cast<GUITableCellNode*>((required_dynamic_cast<GUITableRowNode*>(guiTableRowNode))->subNodes.at(x));
		if (guiTableCellNode->conditionsMet == false) continue;
		const auto& requestedConstaints = guiTableCellNode->getRequestsConstraints();
		if (requestedConstaints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
			maxWidth = Math::max(maxWidth, computedConstraints.width);
		} else
		if (requestedConstaints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
			maxWidth = Math::max(maxWidth, guiTableCellNode->getAutoWidth());
		} else {
			// TODO: percent, star
			maxWidth = Math::max(maxWidth, guiTableCellNode->getContentWidth());
		}
	}
	return maxWidth;
}

int GUITableNode::getTableCellMaxHeight(int y) {
	auto maxHeight = -1;
	for (auto guiTableCellNode: required_dynamic_cast<GUITableRowNode*>(subNodes.at(y))->subNodes) {
		if (guiTableCellNode->conditionsMet == false) continue;
		const auto& requestedConstaints = guiTableCellNode->getRequestsConstraints();
		if (requestedConstaints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
			maxHeight = Math::max(maxHeight, computedConstraints.height);
		} else
		if (requestedConstaints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
			maxHeight = Math::max(maxHeight, guiTableCellNode->getAutoHeight());
		} else {
			// TODO: percent, star
			maxHeight = Math::max(maxHeight, guiTableCellNode->getContentHeight());
		}
	}
	return maxHeight;
}