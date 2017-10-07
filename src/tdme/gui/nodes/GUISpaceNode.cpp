#include <tdme/gui/nodes/GUISpaceNode.h>

#include <string>

#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/utils/StringUtils.h>

using std::wstring;

using tdme::gui::nodes::GUISpaceNode;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::utils::StringUtils;

GUISpaceNode::GUISpaceNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUISpaceNode::GUISpaceNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn)
	: GUISpaceNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn);
}

void GUISpaceNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn)
{
	super::ctor(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
}

const wstring GUISpaceNode::getNodeType()
{
	return L"space";
}

bool GUISpaceNode::isContentNode()
{
	return false;
}

int32_t GUISpaceNode::getContentWidth()
{
	return computedConstraints->width;
}

int32_t GUISpaceNode::getContentHeight()
{
	return computedConstraints->height;
}

GUINode_RequestedConstraints* GUISpaceNode::createRequestedConstraints(const wstring& left, const wstring& top, const wstring& width, const wstring& height)
{
	auto constraints = new GUINode_RequestedConstraints();
	constraints->leftType = getRequestedConstraintsType(StringUtils::trim(left), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->left = getRequestedConstraintsValue(StringUtils::trim(left), 0);
	constraints->topType = getRequestedConstraintsType(StringUtils::trim(top), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->top = getRequestedConstraintsValue(StringUtils::trim(top), 0);
	constraints->widthType = getRequestedConstraintsType(StringUtils::trim(width), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->width = getRequestedConstraintsValue(StringUtils::trim(width), 1);
	constraints->heightType = getRequestedConstraintsType(StringUtils::trim(height), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->height = getRequestedConstraintsValue(StringUtils::trim(height), 1);
	return constraints;
}

void GUISpaceNode::dispose()
{
	super::dispose();
}

void GUISpaceNode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	if (conditionsMet == false)
		return;

	super::render(guiRenderer, floatingNodes);
}

