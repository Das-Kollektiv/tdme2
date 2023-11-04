#include <tdme/gui/elements/GUIMoveableController.h>

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MutableString.h>

using std::array;
using std::to_string;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::MutableString;

using tdme::gui::elements::GUIMoveableController;

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
			event->setProcessed(true);
			dragging = false;
		}
		//
		node->getScreenNode()->forwardMoveRelease(this->node, event->getXUnscaled(), event->getYUnscaled());
	} else
	if (node == this->node && node->isEventBelongingToNode(event) == true &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED == true &&
		event->getButton() == MOUSE_BUTTON_LEFT &&
		(Math::abs(event->getX() - mouseLastX) > 5 ||
		Math::abs(event->getY() - mouseLastY) > 5)) {
		if (node->getScreenNode()->isMoveAccepted(node) == true) {
			//
			dragging = true;
		}
		//
		event->setProcessed(true);
	} else
	if (dragging == true &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED == true &&
		event->getButton() == MOUSE_BUTTON_LEFT) {
		auto movedX = event->getX() - mouseLastX;
		auto movedY = event->getY() - mouseLastY;
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
		event->setProcessed(true);
	}
	//
	mouseLastX = event->getX();
	mouseLastY = event->getY();
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
