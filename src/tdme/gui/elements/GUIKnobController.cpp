#include <tdme/gui/elements/GUIKnobController.h>

#include <array>
#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Time.h>

using std::array;
using std::to_string;

using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Math;
using tdme::math::Matrix2D3x3;
using tdme::utils::Console;
using tdme::utils::Float;
using tdme::utils::MutableString;
using tdme::utils::Time;

using tdme::gui::elements::GUIKnobController;

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
	setValue(MutableString(dynamic_cast<GUIElementNode*>(node)->getValue()));

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
		event->getType() == GUIMouseEvent_Type::MOUSEEVENT_RELEASED == true) {
		this->node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast<GUIElementNode*>(this->node));
		event->setProcessed(true);
	} else
	if (node == this->node && node->isEventBelongingToNode(event) == true &&
		event->getType() == GUIMouseEvent_Type::MOUSEEVENT_PRESSED == true &&
		event->getButton() == 1) {
		mouseLastX = event->getX();
		event->setProcessed(true);
	} else
	if (event->getType() == GUIMouseEvent_Type::MOUSEEVENT_DRAGGED == true &&
		event->getButton() == 1) {
		valueFloat = Math::clamp(
			static_cast<float>(valueFloat + ((event->getX() - mouseLastX) / 75.0f)) ,
			0.0f,
			1.0f
		);
		updateKnob();
		node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(this->node));
		mouseLastX = event->getX();
		event->setProcessed(true);
	}
}

void GUIKnobController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) {
	GUIElementController::handleKeyboardEvent(node, event);
	if (node == this->node) {
		switch (event->getKeyCode()) {
			case GUIKeyboardEvent::KEYCODE_LEFT: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent_Type::KEYBOARDEVENT_KEY_PRESSED) {
						this->valueFloat = Math::clamp(valueFloat - 0.1f, 0.0f, 1.0f);
						updateKnob();
						node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(this->node));
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RIGHT: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent_Type::KEYBOARDEVENT_KEY_PRESSED) {
						this->valueFloat = Math::clamp(valueFloat + 0.1f, 0.0f, 1.0f);
						updateKnob();
						node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(this->node));
					}
				}
				break;
		}
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
	this->valueFloat = Math::clamp(Float::parseFloat(this->value.getString()), 0.0f, 1.0f);
	updateKnob();
}

void GUIKnobController::updateKnob() {
	dynamic_cast<GUIImageNode*>(knobNode)->setTextureMatrix(Matrix2D3x3::rotateAroundTextureCenter((-valueFloat * (360.0f - 60.0f)) - 210.f));
}
