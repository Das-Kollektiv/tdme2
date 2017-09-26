// Generated from /tdme/src/tdme/gui/nodes/GUIVerticalScrollbarInternalController.java
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalController.h>

#include <java/lang/StringBuilder.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUILayoutNode.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalController_State.h>

using tdme::gui::nodes::GUIVerticalScrollbarInternalController;
using java::lang::StringBuilder;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIVerticalScrollbarInternalController::GUIVerticalScrollbarInternalController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIVerticalScrollbarInternalController::GUIVerticalScrollbarInternalController(GUINode* node) 
	: GUIVerticalScrollbarInternalController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUIVerticalScrollbarInternalController::init()
{
	state = GUIVerticalScrollbarInternalController_State::NONE;
	mouseYOffset = -1;
}

void GUIVerticalScrollbarInternalController::ctor(GUINode* node)
{
	super::ctor(node);
	init();
	this->contentNode = java_cast< GUILayoutNode* >(node->getScreenNode()->getNodeById(node->getParentControllerNode()->id + L"_inner"));
}

bool GUIVerticalScrollbarInternalController::isDisabled()
{
	return false;
}

void GUIVerticalScrollbarInternalController::setDisabled(bool disabled)
{
}

void GUIVerticalScrollbarInternalController::initialize()
{
}

void GUIVerticalScrollbarInternalController::dispose()
{
}

void GUIVerticalScrollbarInternalController::postLayout()
{
}

GUIVerticalScrollbarInternalController_State* GUIVerticalScrollbarInternalController::getState()
{
	return state;
}

float GUIVerticalScrollbarInternalController::getBarHeight()
{
	float elementHeight = contentNode->computedConstraints->height;
	float contentHeight = contentNode->getContentHeight();
	auto barHeightRelative = (elementHeight / contentHeight);
	if (barHeightRelative > 1.0f)
		barHeightRelative = 1.0f;

	return (node->computedConstraints->height - node->border->top - node->border->bottom) * barHeightRelative;
}

float GUIVerticalScrollbarInternalController::getBarTop()
{
	float elementHeight = contentNode->computedConstraints->height;
	float contentHeight = contentNode->getContentHeight();
	auto scrollableHeight = contentHeight - elementHeight;
	auto childrenRenderOffsetY = contentNode->childrenRenderOffsetY;
	auto barHeight = (node->computedConstraints->height - node->border->top - node->border->bottom) * (elementHeight / contentHeight);
	if (scrollableHeight > 0.0f) {
		return node->computedConstraints->top + node->computedConstraints->alignmentTop + node->border->top+ (childrenRenderOffsetY * ((node->computedConstraints->height - barHeight) / scrollableHeight));
	} else {
		return node->computedConstraints->top + node->computedConstraints->alignmentTop + node->border->top;
	}
}

void GUIVerticalScrollbarInternalController::setDraggedY(float draggedY)
{
	float elementHeight = contentNode->computedConstraints->height;
	float contentHeight = contentNode->getContentHeight();
	auto scrollableHeight = contentHeight - elementHeight;
	if (scrollableHeight <= 0.0f)
		return;

	auto barHeight = getBarHeight();
	auto childrenRenderOffsetY = contentNode->getChildrenRenderOffsetY() + (draggedY * (scrollableHeight / (node->computedConstraints->height - barHeight)));
	if (childrenRenderOffsetY < 0)
		childrenRenderOffsetY = 0;

	if (childrenRenderOffsetY > scrollableHeight)
		childrenRenderOffsetY = scrollableHeight;

	contentNode->setChildrenRenderOffsetY(childrenRenderOffsetY);
}

void GUIVerticalScrollbarInternalController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (node != this->node)
		return;

	if (node->isEventBelongingToNode(event) == true && event->getType() == GUIMouseEvent_Type::MOUSE_MOVED) {
		state = GUIVerticalScrollbarInternalController_State::MOUSEOVER;
		event->setProcessed(true);
	} else if (event->getButton() == 1) {
		if (node->isEventBelongingToNode(event) == true && event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			auto barTop = getBarTop();
			auto barHeight = getBarHeight();
			if (event->getY() < barTop) {
				float elementHeight = contentNode->computedConstraints->height;
				float contentHeight = contentNode->getContentHeight();
				auto scrollableHeight = contentHeight - elementHeight;
				setDraggedY(-elementHeight * ((node->computedConstraints->height - barHeight) / scrollableHeight));
			} else if (event->getY() > barTop + barHeight) {
				float elementHeight = contentNode->computedConstraints->height;
				float contentHeight = contentNode->getContentHeight();
				auto scrollableHeight = contentHeight - elementHeight;
				setDraggedY(+elementHeight * ((node->computedConstraints->height - barHeight) / scrollableHeight));
			} else if (event->getY() >= barTop && event->getY() < barTop + barHeight) {
				mouseYOffset = static_cast< int32_t >((event->getY() - barTop));
				state = GUIVerticalScrollbarInternalController_State::DRAGGING;
			}
			event->setProcessed(true);
		} else if (state == GUIVerticalScrollbarInternalController_State::DRAGGING && event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			mouseYOffset = -1;
			state = GUIVerticalScrollbarInternalController_State::NONE;
			event->setProcessed(true);
		} else if (state == GUIVerticalScrollbarInternalController_State::DRAGGING && event->getType() == GUIMouseEvent_Type::MOUSE_DRAGGED) {
			auto barTop = getBarTop();
			auto draggedY = event->getY() - barTop - mouseYOffset;
			setDraggedY(draggedY);
			event->setProcessed(true);
		}
	} else {
		state = GUIVerticalScrollbarInternalController_State::NONE;
	}
}

void GUIVerticalScrollbarInternalController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUIVerticalScrollbarInternalController::tick()
{
}

void GUIVerticalScrollbarInternalController::onFocusGained()
{
}

void GUIVerticalScrollbarInternalController::onFocusLost()
{
}

bool GUIVerticalScrollbarInternalController::hasValue()
{
	return false;
}

MutableString* GUIVerticalScrollbarInternalController::getValue()
{
	return nullptr;
}

void GUIVerticalScrollbarInternalController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIVerticalScrollbarInternalController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIVerticalScrollbarInternalController", 53);
    return c;
}

java::lang::Class* GUIVerticalScrollbarInternalController::getClass0()
{
	return class_();
}

