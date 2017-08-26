// Generated from /tdme/src/tdme/gui/nodes/GUIHorizontalScrollbarInternalNode.java
#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalNode.h>

#include <array>
#include <vector>

#include <java/lang/String.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalController_State.h>
#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalController.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <Array.h>

using std::array;
using std::vector;

using tdme::gui::nodes::GUIHorizontalScrollbarInternalNode;
using java::lang::String;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::renderer::GUIRenderer;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIHorizontalScrollbarInternalNode::GUIHorizontalScrollbarInternalNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIHorizontalScrollbarInternalNode::GUIHorizontalScrollbarInternalNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUIColor* barColorNone, GUIColor* barColorMouseOver, GUIColor* barColorDragging) 
	: GUIHorizontalScrollbarInternalNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn,barColorNone,barColorMouseOver,barColorDragging);
}

void GUIHorizontalScrollbarInternalNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUIColor* barColorNone, GUIColor* barColorMouseOver, GUIColor* barColorDragging)
{
	super::ctor(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
	this->controller = new GUIHorizontalScrollbarInternalController(this);
	this->barColorNone = barColorNone;
	this->barColorMouseOver = barColorMouseOver;
	this->barColorDragging = barColorDragging;
}

String* GUIHorizontalScrollbarInternalNode::getNodeType()
{
	return u"scrollbar"_j;
}

bool GUIHorizontalScrollbarInternalNode::isContentNode()
{
	return false;
}

int32_t GUIHorizontalScrollbarInternalNode::getContentWidth()
{
	return computedConstraints->width;
}

int32_t GUIHorizontalScrollbarInternalNode::getContentHeight()
{
	return computedConstraints->height;
}

void GUIHorizontalScrollbarInternalNode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	if (conditionsMet == false)
		return;

	super::render(guiRenderer, floatingNodes);
	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	auto controller = java_cast< GUIHorizontalScrollbarInternalController* >(this->controller);
	auto barWidth = controller->getBarWidth();
	auto barLeft = controller->getBarLeft();
	auto left = barLeft;
	float top = computedConstraints->top + computedConstraints->alignmentTop + border->top;
	auto width = barWidth;
	float height = computedConstraints->height - border->top - border->bottom;
	array<float, 4>* barColorArray = nullptr;
	{
		auto v = controller->getState();
		if ((v == GUIHorizontalScrollbarInternalController_State::NONE)) {
			barColorArray = barColorNone->getArray();
			goto end_switch0;;
		}
		if ((v == GUIHorizontalScrollbarInternalController_State::MOUSEOVER)) {
			barColorArray = barColorMouseOver->getArray();
			goto end_switch0;;
		}
		if ((v == GUIHorizontalScrollbarInternalController_State::DRAGGING)) {
			barColorArray = barColorDragging->getArray();
			goto end_switch0;;
		}
		end_switch0:;
	}

	guiRenderer->bindTexture(0);
	guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*barColorArray)[0], (*barColorArray)[1], (*barColorArray)[2], (*barColorArray)[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*barColorArray)[0], (*barColorArray)[1], (*barColorArray)[2], (*barColorArray)[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*barColorArray)[0], (*barColorArray)[1], (*barColorArray)[2], (*barColorArray)[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*barColorArray)[0], (*barColorArray)[1], (*barColorArray)[2], (*barColorArray)[3], 0.0f, 0.0f);
	guiRenderer->render();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIHorizontalScrollbarInternalNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIHorizontalScrollbarInternalNode", 49);
    return c;
}

java::lang::Class* GUIHorizontalScrollbarInternalNode::getClass0()
{
	return class_();
}

