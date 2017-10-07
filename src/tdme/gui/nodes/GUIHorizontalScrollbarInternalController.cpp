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

GUIHorizontalScrollbarInternalController::GUIHorizontalScrollbarInternalController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUIHorizontalScrollbarInternalController::GUIHorizontalScrollbarInternalController(GUINode* node) 
	: GUIHorizontalScrollbarInternalController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUIHorizontalScrollbarInternalController::init()
{
	state = GUIHorizontalScrollbarInternalController_State::NONE;
	mouseXOffset = -1;
}

void GUIHorizontalScrollbarInternalController::ctor(GUINode* node)
{
	super::ctor(node);
	init();
	this->contentNode = dynamic_cast< GUILayoutNode* >(node->getScreenNode()->getNodeById(node->getParentControllerNode()->id + L"_inner"));
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
}

GUIHorizontalScrollbarInternalController_State* GUIHorizontalScrollbarInternalController::getState()
{
	return state;
}

float GUIHorizontalScrollbarInternalController::getBarWidth()
{
	float elementWidth = contentNode->computedConstraints->width;
	float contentWidth = contentNode->getContentWidth();
	auto barWidthRelative = (elementWidth / contentWidth);
	if (barWidthRelative > 1.0f)
		barWidthRelative = 1.0f;

	return (node->computedConstraints->width - node->border->left - node->border->right) * barWidthRelative;
}

float GUIHorizontalScrollbarInternalController::getBarLeft()
{
	float elementWidth = contentNode->computedConstraints->width;
	float contentWidth = contentNode->getContentWidth();
	auto scrollableWidth = contentWidth - elementWidth;
	auto childrenRenderOffsetX = contentNode->childrenRenderOffsetX;
	auto barWidth = (node->computedConstraints->width - node->border->left - node->border->right) * (elementWidth / contentWidth);
	if (scrollableWidth > 0.0f) {
		return node->computedConstraints->left + node->computedConstraints->alignmentLeft + node->border->left+ (childrenRenderOffsetX * ((node->computedConstraints->width - barWidth) / scrollableWidth));
	} else {
		return node->computedConstraints->left + node->computedConstraints->alignmentLeft + node->border->left;
	}
}

void GUIHorizontalScrollbarInternalController::setDraggedX(float draggedX)
{
	float elementWidth = contentNode->computedConstraints->width;
	float contentWidth = contentNode->getContentWidth();
	auto scrollableWidth = contentWidth - elementWidth;
	if (scrollableWidth <= 0.0f)
		return;

	auto barWidth = getBarWidth();
	auto childrenRenderOffsetX = contentNode->getChildrenRenderOffsetX() + (draggedX * (scrollableWidth / (node->computedConstraints->width - barWidth)));
	if (childrenRenderOffsetX < 0)
		childrenRenderOffsetX = 0;

	if (childrenRenderOffsetX > scrollableWidth)
		childrenRenderOffsetX = scrollableWidth;

	contentNode->setChildrenRenderOffsetX(childrenRenderOffsetX);
}

void GUIHorizontalScrollbarInternalController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (node != this->node)
		return;

	if (node->isEventBelongingToNode(event) == true && event->getType() == GUIMouseEvent_Type::MOUSE_MOVED) {
		state = GUIHorizontalScrollbarInternalController_State::MOUSEOVER;
		event->setProcessed(true);
	} else if (event->getButton() == 1) {
		if (node->isEventBelongingToNode(event) == true && event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			auto barLeft = getBarLeft();
			auto barWidth = getBarWidth();
			if (event->getX() < barLeft) {
				float elementWidth = contentNode->computedConstraints->width;
				float contentWidth = contentNode->getContentWidth();
				auto scrollableWidth = contentWidth - elementWidth;
				setDraggedX(-elementWidth * ((node->computedConstraints->width - barWidth) / scrollableWidth));
			} else if (event->getX() > barLeft + barWidth) {
				float elementWidth = contentNode->computedConstraints->width;
				float contentWidth = contentNode->getContentWidth();
				auto scrollableWidth = contentWidth - elementWidth;
				setDraggedX(+elementWidth * ((node->computedConstraints->width - barWidth) / scrollableWidth));
			} else if (event->getX() >= barLeft && event->getX() < barLeft + barWidth) {
				mouseXOffset = static_cast< int32_t >((event->getX() - barLeft));
				state = GUIHorizontalScrollbarInternalController_State::DRAGGING;
			}
			event->setProcessed(true);
		} else if (state == GUIHorizontalScrollbarInternalController_State::DRAGGING && event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			mouseXOffset = -1;
			state = GUIHorizontalScrollbarInternalController_State::NONE;
			event->setProcessed(true);
		} else if (state == GUIHorizontalScrollbarInternalController_State::DRAGGING && event->getType() == GUIMouseEvent_Type::MOUSE_DRAGGED) {
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

MutableString* GUIHorizontalScrollbarInternalController::getValue()
{
	return nullptr;
}

void GUIHorizontalScrollbarInternalController::setValue(MutableString* value)
{
}

