// Generated from /tdme/src/tdme/gui/nodes/GUIElementNode.java
#include <tdme/gui/nodes/GUIElementNode.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementIgnoreEventsController.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode_Overflow.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/_ArrayList.h>

using tdme::gui::nodes::GUIElementNode;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementIgnoreEventsController;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

GUIElementNode::GUIElementNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIElementNode::GUIElementNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, String* name, String* value, bool selected, bool disabled, bool focusable, bool ignoreEvents)  /* throws(GUIParserException) */
	: GUIElementNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,overflowX,overflowY,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn,name,value,selected,disabled,focusable,ignoreEvents);
}

void GUIElementNode::init()
{
	activeConditions = new GUINodeConditions();
}

String* GUIElementNode::CONDITION_ALWAYS;

String* GUIElementNode::CONDITION_ONMOUSEOVER;

String* GUIElementNode::CONDITION_CLICK;

String* GUIElementNode::CONDITION_FOCUS;

void GUIElementNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, String* name, String* value, bool selected, bool disabled, bool focusable, bool ignoreEvents) /* throws(GUIParserException) */
{
	super::ctor(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
	init();
	this->name = name;
	this->value = value;
	this->selected = selected;
	this->disabled = disabled;
	this->focusable = focusable;
	this->ignoreEvents = ignoreEvents;
	this->controller = ignoreEvents == true ? static_cast< GUINodeController* >(new GUIElementIgnoreEventsController(this)) : static_cast< GUINodeController* >(new GUIElementController(this));
	this->controller->initialize();
}

String* GUIElementNode::getNodeType()
{
	return u"element"_j;
}

bool GUIElementNode::isContentNode()
{
	return false;
}

int32_t GUIElementNode::getContentWidth()
{
	auto width = 0;
	for (auto i = 0; i < subNodes->size(); i++) {
		auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
		auto contentWidth = guiSubNode->getAutoWidth();
		if (contentWidth > width) {
			width = contentWidth;
		}
	}
	width += border->left + border->right;
	width += padding->left + padding->right;
	return width;
}

int32_t GUIElementNode::getContentHeight()
{
	auto height = 0;
	for (auto i = 0; i < subNodes->size(); i++) {
		auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
		auto contentHeight = guiSubNode->getAutoHeight();
		if (contentHeight > height) {
			height = contentHeight;
		}
	}
	height += border->top + border->bottom;
	height += padding->top + padding->bottom;
	return height;
}

bool GUIElementNode::isFocusable()
{
	return focusable;
}

void GUIElementNode::setTop(int32_t top)
{
	super::setTop(top);
	top += computedConstraints->alignmentTop;
	for (auto i = 0; i < subNodes->size(); i++) {
		java_cast< GUINode* >(subNodes->get(i))->setTop(top);
	}
}

void GUIElementNode::setLeft(int32_t left)
{
	super::setLeft(left);
	left += computedConstraints->alignmentLeft;
	for (auto i = 0; i < subNodes->size(); i++) {
		java_cast< GUINode* >(subNodes->get(i))->setLeft(left);
	}
}

void GUIElementNode::layoutSubNodes()
{
	super::layoutSubNodes();
	auto height = computedConstraints->height - border->top - border->bottom- padding->top- padding->bottom;
	auto width = computedConstraints->width - border->left - border->right- padding->left- padding->right;
	for (auto i = 0; i < subNodes->size(); i++) {
		auto guiSubNode = java_cast< GUINode* >(subNodes->get(i));
		auto doLayoutSubNodes = false;
		if (guiSubNode->requestedConstraints->heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
			guiSubNode->computedConstraints->height = height;
			doLayoutSubNodes = true;
		} else if (guiSubNode->requestedConstraints->widthType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
			guiSubNode->computedConstraints->width = width;
			doLayoutSubNodes = true;
		}
		if (dynamic_cast< GUIParentNode* >(guiSubNode) != nullptr && doLayoutSubNodes == true) {
			(java_cast< GUIParentNode* >(guiSubNode))->layoutSubNodes();
		}
	}
}

void GUIElementNode::layout()
{
	if (requestedConstraints->heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
		auto subNodesHeight = requestedConstraints->height - border->top - border->bottom- padding->top- padding->bottom;
		for (auto i = 0; i < subNodes->size(); i++) {
			auto subNode = java_cast< GUINode* >(subNodes->get(i));
			if (overflowY == GUIParentNode_Overflow::DOWNSIZE_CHILDREN && subNode->requestedConstraints->heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL && subNode->requestedConstraints->height > subNodesHeight) {
				subNode->requestedConstraints->height = subNodesHeight;
			}
		}
	}
	if (requestedConstraints->widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
		auto subNodesWidth = requestedConstraints->width - border->left - border->right- padding->left- padding->right;
		for (auto i = 0; i < subNodes->size(); i++) {
			auto subNode = java_cast< GUINode* >(subNodes->get(i));
			if (overflowY == GUIParentNode_Overflow::DOWNSIZE_CHILDREN && subNode->requestedConstraints->widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL && subNode->requestedConstraints->width > subNodesWidth) {
				subNode->requestedConstraints->width = subNodesWidth;
			}
		}
	}
	super::layout();
	setTop(computedConstraints->top);
	setLeft(computedConstraints->left);
	computeHorizontalChildrenAlignment();
	computeVerticalChildrenAlignment();
}

String* GUIElementNode::getName()
{
	return name;
}

String* GUIElementNode::getValue()
{
	return value;
}

bool GUIElementNode::isSelected()
{
	return selected;
}

bool GUIElementNode::isDisabled()
{
	return disabled;
}

GUINodeConditions* GUIElementNode::getActiveConditions()
{
	return activeConditions;
}

void GUIElementNode::handleMouseEvent(GUIMouseEvent* event)
{
	if (conditionsMet == false)
		return;

	activeConditions->remove(CONDITION_ONMOUSEOVER);
	activeConditions->remove(CONDITION_CLICK);
	if (screenNode->mouseEventProcessedByFloatingNode == true)
		return;

	if (isEventBelongingToNode(event)) {
		{
			auto v = event->getType();
			if ((v == GUIMouseEvent_Type::MOUSE_MOVED)) {
				activeConditions->add(CONDITION_ONMOUSEOVER);
				if (ignoreEvents == false)
					event->setProcessed(true);

				goto end_switch0;;
			}
			if ((v == GUIMouseEvent_Type::MOUSE_PRESSED)) {
				activeConditions->add(CONDITION_CLICK);
				if (ignoreEvents == false)
					event->setProcessed(true);

				goto end_switch0;;
			}
			if ((((v != GUIMouseEvent_Type::MOUSE_MOVED) && (v != GUIMouseEvent_Type::MOUSE_PRESSED)))) {
				goto end_switch0;;
			}
end_switch0:;
		}

	}
	super::handleMouseEvent(event);
}

void GUIElementNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	if (ignoreEvents == true)
		return;

	if (conditionsMet == false)
		return;

	for (auto i = 0; i < subNodes->size(); i++) {
		auto subNode = java_cast< GUINode* >(subNodes->get(i));
		subNode->handleKeyboardEvent(event);
	}
	super::handleKeyboardEvent(event);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIElementNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIElementNode", 29);
    return c;
}

void GUIElementNode::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_ALWAYS = u"always"_j;
	CONDITION_ONMOUSEOVER = u"mouseover"_j;
	CONDITION_CLICK = u"click"_j;
	CONDITION_FOCUS = u"focus"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIElementNode::getClass0()
{
	return class_();
}

