// Generated from /tdme/src/tdme/gui/nodes/GUISpaceNode.java
#include <tdme/gui/nodes/GUISpaceNode.h>

#include <java/lang/String.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>

using tdme::gui::nodes::GUISpaceNode;
using java::lang::String;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;

GUISpaceNode::GUISpaceNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUISpaceNode::GUISpaceNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn) 
	: GUISpaceNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn);
}

void GUISpaceNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn)
{
	super::ctor(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
}

String* GUISpaceNode::getNodeType()
{
	return u"space"_j;
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

GUINode_RequestedConstraints* GUISpaceNode::createRequestedConstraints(String* left, String* top, String* width, String* height)
{
	clinit();
	auto constraints = new GUINode_RequestedConstraints();
	constraints->leftType = getRequestedConstraintsType(left->trim(), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->left = getRequestedConstraintsValue(left->trim(), 0);
	constraints->topType = getRequestedConstraintsType(top->trim(), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->top = getRequestedConstraintsValue(top->trim(), 0);
	constraints->widthType = getRequestedConstraintsType(width->trim(), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->width = getRequestedConstraintsValue(width->trim(), 1);
	constraints->heightType = getRequestedConstraintsType(height->trim(), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->height = getRequestedConstraintsValue(height->trim(), 1);
	return constraints;
}

void GUISpaceNode::dispose()
{
	super::dispose();
}

void GUISpaceNode::render(GUIRenderer* guiRenderer, _ArrayList* floatingNodes)
{
	if (conditionsMet == false)
		return;

	super::render(guiRenderer, floatingNodes);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISpaceNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUISpaceNode", 27);
    return c;
}

java::lang::Class* GUISpaceNode::getClass0()
{
	return class_();
}

