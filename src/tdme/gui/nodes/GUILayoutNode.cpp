// Generated from /tdme/src/tdme/gui/nodes/GUILayoutNode.java
#include <tdme/gui/nodes/GUILayoutNode.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
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
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/utils/_ArrayList.h>

using tdme::gui::nodes::GUILayoutNode;
using java::lang::Object;
using java::lang::String;
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
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUILayoutNode::GUILayoutNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUILayoutNode::GUILayoutNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUILayoutNode_Alignment* alignment)  /* throws(GUIParserException) */
	: GUILayoutNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,overflowX,overflowY,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn,alignment);
}

void GUILayoutNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUILayoutNode_Alignment* alignment) /* throws(GUIParserException) */
{
	super::ctor(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
	this->alignment = alignment;
}

String* GUILayoutNode::getNodeType()
{
	return u"layout"_j;
}

bool GUILayoutNode::isContentNode()
{
	return false;
}

int32_t GUILayoutNode::getContentWidth()
{
	auto width = 0;
	if (alignment == GUILayoutNode_Alignment::HORIZONTAL) {
		for (auto i = 0; i < subNodes->size(); i++) {
			auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			width += guiSubNode->getAutoWidth();
		}
	} else {
		for (auto i = 0; i < subNodes->size(); i++) {
			auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			auto contentWidth = guiSubNode->getAutoWidth();
			if (contentWidth > width) {
				width = contentWidth;
			}
		}
	}
	width += border->left + border->right;
	width += padding->left + padding->right;
	return width;
}

int32_t GUILayoutNode::getContentHeight()
{
	auto height = 0;
	if (alignment == GUILayoutNode_Alignment::VERTICAL) {
		for (auto i = 0; i < subNodes->size(); i++) {
			auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			height += guiSubNode->getAutoHeight();
		}
	} else {
		for (auto i = 0; i < subNodes->size(); i++) {
			auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			auto contentHeight = guiSubNode->getAutoHeight();
			if (contentHeight > height) {
				height = contentHeight;
			}
		}
	}
	height += border->top + border->bottom;
	height += padding->top + padding->bottom;
	return height;
}

void GUILayoutNode::layoutSubNodes()
{
	super::layoutSubNodes();
	super::layoutSubNodes();
	{
		auto v = alignment;
		if ((v == GUILayoutNode_Alignment::VERTICAL)) {
			{
				auto starCount = 0;
				auto height = computedConstraints->height - border->top - border->bottom- padding->top- padding->bottom;
				auto nodesHeight = 0;
				auto finalNodesHeight = 0;
				for (auto i = 0; i < subNodes->size(); i++) {
					auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
					if (guiSubNode->flow == GUINode_Flow::FLOATING) {
						continue;
					}
					if (guiSubNode->requestedConstraints->heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
						starCount++;
					} else {
						nodesHeight += guiSubNode->computedConstraints->height;
						finalNodesHeight += guiSubNode->computedConstraints->height;
					}
				}
				auto verticalStarPixelRest = 0.0f;
				for (auto i = 0; i < subNodes->size(); i++) {
					auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
					if (guiSubNode->requestedConstraints->heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
						auto nodeStarHeight = (static_cast< float >(height) - static_cast< float >(nodesHeight)) / static_cast< float >(starCount);
						auto nodeStarHeightInt = static_cast< int32_t >(nodeStarHeight);
						verticalStarPixelRest += nodeStarHeight - nodeStarHeightInt;
						if (static_cast< int32_t >(verticalStarPixelRest) > 0) {
							nodeStarHeightInt += static_cast< int32_t >(verticalStarPixelRest);
							verticalStarPixelRest -= static_cast< int32_t >(verticalStarPixelRest);
						}
						guiSubNode->computedConstraints->height = nodeStarHeightInt;
						if (guiSubNode->computedConstraints->height < 0) {
							guiSubNode->computedConstraints->height = 0;
						}
						finalNodesHeight += guiSubNode->computedConstraints->height;
						if (dynamic_cast< GUIParentNode* >(guiSubNode) != nullptr) {
							(java_cast< GUIParentNode* >(guiSubNode))->layoutSubNodes();
						}
					}
				}
				{
					auto v_ = alignments->vertical;
					if ((v_ == GUINode_AlignmentVertical::TOP)) {
						for (auto i = 0; i < subNodes->size(); i++) {
							auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
							guiSubNode->computedConstraints->alignmentTop = border->top + padding->top;
						}
						goto end_switch1;;
					}
					if ((v_ == GUINode_AlignmentVertical::CENTER)) {
						for (auto i = 0; i < subNodes->size(); i++) {
							auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
							guiSubNode->computedConstraints->alignmentTop = border->top + padding->top + ((height - finalNodesHeight) / 2);
						}
						goto end_switch1;;
					}
					if ((v_ == GUINode_AlignmentVertical::BOTTOM)) {
						for (auto i = 0; i < subNodes->size(); i++) {
							auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
							guiSubNode->computedConstraints->alignmentTop = (height - finalNodesHeight);
						}
						goto end_switch1;;
					}
end_switch1:;
				}

				computeHorizontalChildrenAlignment();
				goto end_switch0;;
			}		}
		if ((v == GUILayoutNode_Alignment::VERTICAL) || (v == GUILayoutNode_Alignment::HORIZONTAL)) {
{
				auto starCount = 0;
				auto width = computedConstraints->width - border->left - border->right- padding->left- padding->right;
				auto nodesWidth = 0;
				auto finalNodesWidth = 0;
				for (auto i = 0; i < subNodes->size(); i++) {
					auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
					if (guiSubNode->flow == GUINode_Flow::FLOATING) {
						continue;
					}
					if (guiSubNode->requestedConstraints->widthType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
						starCount++;
					} else {
						nodesWidth += guiSubNode->computedConstraints->width;
						finalNodesWidth += guiSubNode->computedConstraints->width;
					}
				}
				auto horizontalStarPixelRest = 0.0f;
				for (auto i = 0; i < subNodes->size(); i++) {
					auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
					if (guiSubNode->requestedConstraints->widthType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
						auto nodeStarWidth = (static_cast< float >(width) - static_cast< float >(nodesWidth)) / static_cast< float >(starCount);
						auto nodeStarWidthInt = static_cast< int32_t >(nodeStarWidth);
						horizontalStarPixelRest += nodeStarWidth - nodeStarWidthInt;
						if (static_cast< int32_t >(horizontalStarPixelRest) > 0) {
							nodeStarWidthInt += static_cast< int32_t >(horizontalStarPixelRest);
							horizontalStarPixelRest -= static_cast< int32_t >(horizontalStarPixelRest);
						}
						guiSubNode->computedConstraints->width = nodeStarWidthInt;
						if (guiSubNode->computedConstraints->width < 0) {
							guiSubNode->computedConstraints->width = 0;
						}
						finalNodesWidth += guiSubNode->computedConstraints->width;
						if (dynamic_cast< GUIParentNode* >(guiSubNode) != nullptr) {
							(java_cast< GUIParentNode* >(guiSubNode))->layoutSubNodes();
						}
					}
				}
				{
					auto v_ = alignments->horizontal;
					if ((v_ == GUINode_AlignmentHorizontal::LEFT)) {
						for (auto i = 0; i < subNodes->size(); i++) {
							auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
							guiSubNode->computedConstraints->alignmentLeft = border->left + padding->left;
						}
						goto end_switch2;;
					}
					if ((v_ == GUINode_AlignmentHorizontal::CENTER)) {
						for (auto i = 0; i < subNodes->size(); i++) {
							auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
							guiSubNode->computedConstraints->alignmentLeft = border->left + padding->left + ((width - finalNodesWidth) / 2);
						}
						goto end_switch2;;
					}
					if ((v_ == GUINode_AlignmentHorizontal::RIGHT)) {
						for (auto i = 0; i < subNodes->size(); i++) {
							auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
							guiSubNode->computedConstraints->alignmentLeft = (width - finalNodesWidth);
						}
						goto end_switch2;;
					}
end_switch2:;
				}

				computeVerticalChildrenAlignment();
				goto end_switch0;;
			}		}
		if ((v == GUILayoutNode_Alignment::VERTICAL) || (v == GUILayoutNode_Alignment::HORIZONTAL) || (v == GUILayoutNode_Alignment::NONE)) {
{
				computeHorizontalChildrenAlignment();
				computeVerticalChildrenAlignment();
				goto end_switch0;;
			}		}
end_switch0:;
	}

	for (auto i = 0; i < subNodes->size(); i++) {
		auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
		guiSubNode->computeContentAlignment();
	}
	setTop(computedConstraints->top);
	setLeft(computedConstraints->left);
}

void GUILayoutNode::setTop(int32_t top)
{
	super::setTop(top);
	top += computedConstraints->alignmentTop;
	for (auto i = 0; i < subNodes->size(); i++) {
		auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
		guiSubNode->setTop(top);
		if (alignment != GUILayoutNode_Alignment::VERTICAL || guiSubNode->flow == GUINode_Flow::FLOATING) {
			continue;
		}
		top += guiSubNode->computedConstraints->height;
	}
}

void GUILayoutNode::setLeft(int32_t left)
{
	super::setLeft(left);
	left += computedConstraints->alignmentLeft;
	for (auto i = 0; i < subNodes->size(); i++) {
		auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
		guiSubNode->setLeft(left);
		if (alignment != GUILayoutNode_Alignment::HORIZONTAL || guiSubNode->flow == GUINode_Flow::FLOATING) {
			continue;
		}
		left += guiSubNode->computedConstraints->width;
	}
}

GUILayoutNode_Alignment* GUILayoutNode::createAlignment(String* alignment)
{
	clinit();
	return GUILayoutNode_Alignment::valueOf(alignment != nullptr && alignment->length() > 0 ? alignment->toUpperCase() : u"NONE"_j);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUILayoutNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUILayoutNode", 28);
    return c;
}

java::lang::Class* GUILayoutNode::getClass0()
{
	return class_();
}

