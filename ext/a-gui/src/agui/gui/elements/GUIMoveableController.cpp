#include <agui/gui/elements/GUIMoveableController.h>

#include <array>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/MutableString.h>

using std::array;
using std::to_string;

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::math::Math;
using agui::utilities::Console;
using agui::utilities::MutableString;

using agui::gui::elements::GUIMoveableController;

GUIMoveableController::GUIMoveableController(GUINode* node): GUINodeController(node)
{
}

bool GUIMoveableController::isDisabled() {
	return false;
}

void GUIMoveableController::setDisabled(bool disabled) {

}

void GUIMoveableController::initialize() {
}

void GUIMoveableController::dispose() {
}

void GUIMoveableController::postLayout() {
}

void GUIMoveableController::handleMouseEvent(GUINode* node, GUIMouseEvent* event) {
	if (node == this->node &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED == true &&
		event->getButton() == MOUSE_BUTTON_LEFT) {
		//
		if (dragging == true) {
			clicked = false;
			dragging = false;
			event->setProcessed(true);
			//
			node->getScreenNode()->forwardMoveRelease(this->node, event->getXUnscaled(), event->getYUnscaled());
		}
	} else
	if (node == this->node && node->isEventBelongingToNode(event) == true &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED == true &&
		event->getButton() == MOUSE_BUTTON_LEFT) {
		//
		mouseLastX = event->getX();
		mouseLastY = event->getY();
		// we clicked our node
		clicked = true;
	} else
	if (clicked == true &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED == true &&
		event->getButton() == MOUSE_BUTTON_LEFT) {
		//
		auto movedX = event->getX() - mouseLastX;
		auto movedY = event->getY() - mouseLastY;
		//
		if (dragging == true) {
			// switch to positioning by pixels if not yet done
			//	horizontal
			if (this->node->getRequestsConstraints().leftType != GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
				this->node->getRequestsConstraints().leftType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
				this->node->getRequestsConstraints().left = this->node->getComputedConstraints().left;
			}
			//	vertical
			if (this->node->getRequestsConstraints().topType != GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
				this->node->getRequestsConstraints().topType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
				this->node->getRequestsConstraints().top = this->node->getComputedConstraints().top;
			}
			// move it, move it
			this->node->getRequestsConstraints().left+= movedX;
			this->node->getRequestsConstraints().top+= movedY;
			this->node->getComputedConstraints().left+= movedX;
			this->node->getComputedConstraints().top+= movedY;
			//
			node->getScreenNode()->forwardMove(this->node);
			//
			node->getScreenNode()->invalidateLayout(this->node);
			//
			mouseLastX = event->getX();
			mouseLastY = event->getY();
			//
			event->setProcessed(true);
		} else
		if (node->getScreenNode()->isMoveAccepted(node) == true) {
			//
			mouseLastX = event->getX();
			mouseLastY = event->getY();
			//
			dragging = true;
			//
			event->setProcessed(true);
		}
	}
}

void GUIMoveableController::handleKeyboardEvent(GUIKeyboardEvent* event) {
}

void GUIMoveableController::tick() {
}

void GUIMoveableController::onFocusGained() {
}

void GUIMoveableController::onFocusLost() {
}

bool GUIMoveableController::hasValue() {
	return true;
}

const MutableString& GUIMoveableController::getValue() {
	return value;
}

void GUIMoveableController::setValue(const MutableString& value) {
}

void GUIMoveableController::onSubTreeChange() {
}

void GUIMoveableController::startMoving(int mouseX, int mouseY) {
	dragging = true;
	mouseLastX = mouseX;
	mouseLastY = mouseY;
}
