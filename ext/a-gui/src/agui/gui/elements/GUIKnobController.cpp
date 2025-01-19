#include <agui/gui/elements/GUIKnobController.h>

#include <array>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>
#include <agui/math/Matrix3x3.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/Float.h>
#include <agui/utilities/MutableString.h>
#include <agui/utilities/Time.h>

using std::array;
using std::to_string;

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::math::Math;
using agui::math::Matrix3x3;
using agui::utilities::Console;
using agui::utilities::Float;
using agui::utilities::MutableString;
using agui::utilities::Time;

using agui::gui::elements::GUIKnobController;

GUIKnobController::GUIKnobController(GUINode* node): GUIElementController(node)
{
}

bool GUIKnobController::isDisabled() {
	return false;
}

void GUIKnobController::setDisabled(bool disabled) {

}

void GUIKnobController::initialize() {
	knobNode = this->node->getScreenNode()->getNodeById(this->node->getId() + "_knob");
	setValue(MutableString(required_dynamic_cast<GUIElementNode*>(node)->getValue()));

	//
	GUIElementController::initialize();
}

void GUIKnobController::dispose() {
	GUIElementController::dispose();
}

void GUIKnobController::postLayout() {
	updateKnob();
}

void GUIKnobController::handleMouseEvent(GUINode* node, GUIMouseEvent* event) {
	GUIElementController::handleMouseEvent(node, event);
	if (node == this->node &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED == true) {
		this->node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(this->node));
		event->setProcessed(true);
	} else
	if (node == this->node && node->isEventBelongingToNode(event) == true &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED == true &&
		event->getButton() == MOUSE_BUTTON_LEFT) {
		mouseLastX = event->getX();
		event->setProcessed(true);
	} else
	if (event->getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED == true &&
		event->getButton() == MOUSE_BUTTON_LEFT) {
		valueFloat = Math::clamp(
			static_cast<float>(valueFloat + ((event->getX() - mouseLastX) / 75.0f)) ,
			0.0f,
			1.0f
		);
		updateKnob();
		node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(this->node));
		mouseLastX = event->getX();
		event->setProcessed(true);
	}
}

void GUIKnobController::handleKeyboardEvent(GUIKeyboardEvent* event) {
	GUIElementController::handleKeyboardEvent(event);
	switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_LEFT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					this->valueFloat = Math::clamp(valueFloat - 0.1f, 0.0f, 1.0f);
					updateKnob();
					node->getScreenNode()->forwardChange(required_dynamic_cast< GUIElementNode* >(this->node));
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_RIGHT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					this->valueFloat = Math::clamp(valueFloat + 0.1f, 0.0f, 1.0f);
					updateKnob();
					node->getScreenNode()->forwardChange(required_dynamic_cast< GUIElementNode* >(this->node));
				}
			}
			break;
	}
}

void GUIKnobController::tick() {
	GUIElementController::tick();
}

void GUIKnobController::onFocusGained() {
}

void GUIKnobController::onFocusLost() {
}

bool GUIKnobController::hasValue() {
	return true;
}

const MutableString& GUIKnobController::getValue() {
	return value.set(valueFloat, 4);
}

void GUIKnobController::setValue(const MutableString& value) {
	this->value.set(value);
	this->valueFloat = Math::clamp(Float::parse(this->value.getString()), 0.0f, 1.0f);
	updateKnob();
}

void GUIKnobController::updateKnob() {
	required_dynamic_cast<GUIImageNode*>(knobNode)->setTextureMatrix(Matrix3x3::rotateAroundTextureCenter((-valueFloat * (360.0f - 60.0f)) - 210.f));
}
