#include <tdme/gui/nodes/GUILayoutNode.h>

#include <tdme/gui/nodes/GUILayoutNode_Alignment.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>
#include <tdme/gui/nodes/GUINode_Alignments.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Flow.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/utils/StringUtils.h>

using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::nodes::GUILayoutNode_Alignment;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::utils::StringUtils;

GUILayoutNode::GUILayoutNode(
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
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	GUILayoutNode_Alignment* alignment
) throw(GUIParserException):
	GUIParentNode(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, border, padding, showOn, hideOn)
{
	this->alignment = alignment;
}

const string GUILayoutNode::getNodeType()
{
	return "layout";
}

bool GUILayoutNode::isContentNode()
{
	return false;
}

int32_t GUILayoutNode::getContentWidth()
{
	auto width = 0;
	if (alignment == GUILayoutNode_Alignment::HORIZONTAL) {
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			width += guiSubNode->getAutoWidth();
		}
	} else {
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			auto contentWidth = guiSubNode->getAutoWidth();
			if (contentWidth > width) {
				width = contentWidth;
			}
		}
	}
	width += border.left + border.right;
	width += padding.left + padding.right;
	return width;
}

int32_t GUILayoutNode::getContentHeight()
{
	auto height = 0;
	if (alignment == GUILayoutNode_Alignment::VERTICAL) {
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			height += guiSubNode->getAutoHeight();
		}
	} else {
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			auto contentHeight = guiSubNode->getAutoHeight();
			if (contentHeight > height) {
				height = contentHeight;
			}
		}
	}
	height += border.top + border.bottom;
	height += padding.top + padding.bottom;
	return height;
}

void GUILayoutNode::layoutSubNodes()
{
	GUIParentNode::layoutSubNodes();
	GUIParentNode::layoutSubNodes();
	{
		auto v = alignment;
		if (v == GUILayoutNode_Alignment::VERTICAL) {
			auto starCount = 0;
			auto height = computedConstraints.height - border.top - border.bottom - padding.top - padding.bottom;
			auto nodesHeight = 0;
			auto finalNodesHeight = 0;
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
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
				if (guiSubNode->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
					auto nodeStarHeight = (static_cast< float >(height) - static_cast< float >(nodesHeight)) / static_cast< float >(starCount);
					auto nodeStarHeightInt = static_cast< int32_t >(nodeStarHeight);
					verticalStarPixelRest += nodeStarHeight - nodeStarHeightInt;
					if (static_cast< int32_t >(verticalStarPixelRest) > 0) {
						nodeStarHeightInt += static_cast< int32_t >(verticalStarPixelRest);
						verticalStarPixelRest -= static_cast< int32_t >(verticalStarPixelRest);
					}
					guiSubNode->computedConstraints.height = nodeStarHeightInt;
					if (guiSubNode->computedConstraints.height < 0) {
						guiSubNode->computedConstraints.height = 0;
					}
					finalNodesHeight += guiSubNode->computedConstraints.height;
					if (dynamic_cast< GUIParentNode* >(guiSubNode) != nullptr) {
						(dynamic_cast< GUIParentNode* >(guiSubNode))->layoutSubNodes();
					}
				}
			}
			auto v2 = alignments.vertical;
			if (v2 == GUINode_AlignmentVertical::TOP) {
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes[i];
					guiSubNode->computedConstraints.alignmentTop = border.top + padding.top;
				}
			} else
			if (v2 == GUINode_AlignmentVertical::CENTER) {
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes[i];
					guiSubNode->computedConstraints.alignmentTop = border.top + padding.top + ((height - finalNodesHeight) / 2);
				}
			} else
			if (v2 == GUINode_AlignmentVertical::BOTTOM) {
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes[i];
					guiSubNode->computedConstraints.alignmentTop = (height - finalNodesHeight);
				}
			}

			computeHorizontalChildrenAlignment();
		} else
		if (v == GUILayoutNode_Alignment::HORIZONTAL) {
			auto starCount = 0;
			auto width = computedConstraints.width - border.left - border.right - padding.left - padding.right;
			auto nodesWidth = 0;
			auto finalNodesWidth = 0;
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->flow == GUINode_Flow::FLOATING) {
					continue;
				}
				if (guiSubNode->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
					starCount++;
				} else {
					nodesWidth += guiSubNode->computedConstraints.width;
					finalNodesWidth += guiSubNode->computedConstraints.width;
				}
			}
			auto horizontalStarPixelRest = 0.0f;
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
					auto nodeStarWidth = (static_cast< float >(width) - static_cast< float >(nodesWidth)) / static_cast< float >(starCount);
					auto nodeStarWidthInt = static_cast< int32_t >(nodeStarWidth);
					horizontalStarPixelRest += nodeStarWidth - nodeStarWidthInt;
					if (static_cast< int32_t >(horizontalStarPixelRest) > 0) {
						nodeStarWidthInt += static_cast< int32_t >(horizontalStarPixelRest);
						horizontalStarPixelRest -= static_cast< int32_t >(horizontalStarPixelRest);
					}
					guiSubNode->computedConstraints.width = nodeStarWidthInt;
					if (guiSubNode->computedConstraints.width < 0) {
						guiSubNode->computedConstraints.width = 0;
					}
					finalNodesWidth += guiSubNode->computedConstraints.width;
					if (dynamic_cast< GUIParentNode* >(guiSubNode) != nullptr) {
						(dynamic_cast< GUIParentNode* >(guiSubNode))->layoutSubNodes();
					}
				}
			}

			auto v2 = alignments.horizontal;
			if (v2 == GUINode_AlignmentHorizontal::LEFT) {
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes[i];
					guiSubNode->computedConstraints.alignmentLeft = border.left + padding.left;
				}
			} else
			if (v2 == GUINode_AlignmentHorizontal::CENTER) {
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes[i];
					guiSubNode->computedConstraints.alignmentLeft = border.left + padding.left + ((width - finalNodesWidth) / 2);
				}
			} else
			if (v2 == GUINode_AlignmentHorizontal::RIGHT) {
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes[i];
					guiSubNode->computedConstraints.alignmentLeft = (width - finalNodesWidth);
				}
			}

			computeVerticalChildrenAlignment();
		} else {
			computeHorizontalChildrenAlignment();
			computeVerticalChildrenAlignment();
		}
	}

	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		guiSubNode->computeContentAlignment();
	}
	setTop(computedConstraints.top);
	setLeft(computedConstraints.left);
}

void GUILayoutNode::setTop(int32_t top)
{
	GUIParentNode::setTop(top);
	top += computedConstraints.alignmentTop;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		guiSubNode->setTop(top);
		if (alignment != GUILayoutNode_Alignment::VERTICAL || guiSubNode->flow == GUINode_Flow::FLOATING) {
			continue;
		}
		top += guiSubNode->computedConstraints.height;
	}
}

void GUILayoutNode::setLeft(int32_t left)
{
	GUIParentNode::setLeft(left);
	left += computedConstraints.alignmentLeft;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		guiSubNode->setLeft(left);
		if (alignment != GUILayoutNode_Alignment::HORIZONTAL || guiSubNode->flow == GUINode_Flow::FLOATING) {
			continue;
		}
		left += guiSubNode->computedConstraints.width;
	}
}

GUILayoutNode_Alignment* GUILayoutNode::createAlignment(const string& alignment)
{
	return GUILayoutNode_Alignment::valueOf(alignment.empty() == false && alignment.length() > 0 ? StringUtils::toUpperCase(alignment) : "NONE");
}

