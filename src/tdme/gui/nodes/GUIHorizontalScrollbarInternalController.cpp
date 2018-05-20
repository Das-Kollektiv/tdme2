#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalController.h>

#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalController_State.h>
#include <tdme/gui/nodes/GUILayoutNode.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::nodes::GUIHorizontalScrollbarInternalController;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State;
using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

GUIHorizontalScrollbarInternalController::GUIHorizontalScrollbarInternalController(GUINode* node) 
	: GUINodeController(node)
{
	init();
	this->contentNode = dynamic_cast< GUILayoutNode* >(node->getScreenNode()->getNodeById(node->getParentControllerNode()->id + "_inner"));
}

void GUIHorizontalScrollbarInternalController::init()
{
	state = GUIHorizontalScrollbarInternalController_State::NONE;
	mouseXOffset = -1;
}

bool GUIHorizontalScrollbarInternalController::isDisabled()
{
	return false;
}

void GUIHorizontalScrollbarInternalController::setDisabled(bool disabled)
{
}

void GUIHorizontalScrollbarInternalController::initialize()
{
}

void GUIHorizontalScrollbarInternalController::dispose()
{
}

void GUIHorizontalScrollbarInternalController::postLayout()
{
	contentWidth = contentNode->getContentWidth();
}

GUIHorizontalScrollbarInternalController_State* GUIHorizontalScrollbarInternalController::getState()
{
	return state;
}

float GUIHorizontalScrollbarInternalController::getBarWidth()
{
	float elementWidth = contentNode->computedConstraints.width;
	auto barWidthRelative = (elementWidth / contentWidth);
	if (barWidthRelative > 1.0f) barWidthRelative = 1.0f;
	float barWidth = (node->computedConstraints.width - node->border.left - node->border.right) * barWidthRelative;
	if (barWidth < 5.0f) barWidth = 5.0f;
	return barWidth;
}

float GUIHorizontalScrollbarInternalController::getBarLeft()
{
	float elementWidth = contentNode->computedConstraints.width;
	auto scrollableWidth = contentWidth - elementWidth;
	auto childrenRenderOffsetX = contentNode->getChildrenRenderOffsetX();
	if (scrollableWidth > 0.0f) {
		return node->computedConstraints.left + node->computedConstraints.alignmentLeft + node->border.left+ (childrenRenderOffsetX * ((node->computedConstraints.width - getBarWidth()) / scrollableWidth));
	} else {
		return node->computedConstraints.left + node->computedConstraints.alignmentLeft + node->border.left;
	}
}

void GUIHorizontalScrollbarInternalController::setDraggedX(float draggedX)
{
	float elementWidth = contentNode->computedConstraints.width;
	auto scrollableWidth = contentWidth - elementWidth;
	if (scrollableWidth <= 0.0f) return;

	auto childrenRenderOffsetX = contentNode->getChildrenRenderOffsetX() + (draggedX * (scrollableWidth / (node->computedConstraints.width - getBarWidth())));
	if (childrenRenderOffsetX < 0) childrenRenderOffsetX = 0;
	if (childrenRenderOffsetX > scrollableWidth) childrenRenderOffsetX = scrollableWidth;

	contentNode->setChildrenRenderOffsetX(childrenRenderOffsetX);
}

void GUIHorizontalScrollbarInternalController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (node != this->node)
		return;

	if (node->isEventBelongingToNode(event) == true && event->getType() == GUIMouseEvent_Type::MOUSEEVENT_MOVED) {
		state = GUIHorizontalScrollbarInternalController_State::MOUSEOVER;
		event->setProcessed(true);
	} else if (event->getButton() == 1) {
		if (node->isEventBelongingToNode(event) == true && event->getType() == GUIMouseEvent_Type::MOUSEEVENT_PRESSED) {
			auto barLeft = getBarLeft();
			auto barWidth = getBarWidth();
			if (event->getX() < barLeft) {
				float elementWidth = contentNode->computedConstraints.width;
				auto scrollableWidth = contentWidth - elementWidth;
				setDraggedX(-elementWidth * ((node->computedConstraints.width - barWidth) / scrollableWidth));
			} else if (event->getX() > barLeft + barWidth) {
				float elementWidth = contentNode->computedConstraints.width;
				auto scrollableWidth = contentWidth - elementWidth;
				setDraggedX(+elementWidth * ((node->computedConstraints.width - barWidth) / scrollableWidth));
			} else if (event->getX() >= barLeft && event->getX() < barLeft + barWidth) {
				mouseXOffset = static_cast< int32_t >((event->getX() - barLeft));
				state = GUIHorizontalScrollbarInternalController_State::DRAGGING;
			}
			event->setProcessed(true);
		} else if (state == GUIHorizontalScrollbarInternalController_State::DRAGGING && event->getType() == GUIMouseEvent_Type::MOUSEEVENT_RELEASED) {
			mouseXOffset = -1;
			state = GUIHorizontalScrollbarInternalController_State::NONE;
			event->setProcessed(true);
		} else if (state == GUIHorizontalScrollbarInternalController_State::DRAGGING && event->getType() == GUIMouseEvent_Type::MOUSEEVENT_DRAGGED) {
			auto barLeft = getBarLeft();
			auto draggedX = event->getX() - barLeft - mouseXOffset;
			setDraggedX(draggedX);
			event->setProcessed(true);
		}
	} else {
		state = GUIHorizontalScrollbarInternalController_State::NONE;
	}
}

void GUIHorizontalScrollbarInternalController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUIHorizontalScrollbarInternalController::tick()
{
}

void GUIHorizontalScrollbarInternalController::onFocusGained()
{
}

void GUIHorizontalScrollbarInternalController::onFocusLost()
{
}

bool GUIHorizontalScrollbarInternalController::hasValue()
{
	return false;
}

const MutableString& GUIHorizontalScrollbarInternalController::getValue()
{
	return value;
}

void GUIHorizontalScrollbarInternalController::setValue(const MutableString& value)
{
}

