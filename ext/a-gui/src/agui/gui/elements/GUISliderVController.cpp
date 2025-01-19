#include <agui/gui/elements/GUISliderVController.h>

#include <array>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>
#include <agui/math/Vector2.h>
#include <agui/utilities/Float.h>
#include <agui/utilities/MutableString.h>
#include <agui/utilities/Time.h>

using std::array;
using std::to_string;

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::math::Math;
using agui::math::Vector2;
using agui::utilities::Float;
using agui::utilities::MutableString;
using agui::utilities::Time;

using agui::gui::elements::GUISliderVController;

GUISliderVController::GUISliderVController(GUINode* node): GUIElementController(node)
{
	// TODO: maybe introduce a custom relative node alignment, I use content alignment for now
}

bool GUISliderVController::isDisabled() {
	return false;
}

void GUISliderVController::setDisabled(bool disabled) {

}

void GUISliderVController::initialize() {
	sliderNode = this->node->getScreenNode()->getNodeById(this->node->getId() + "_slider");
	setValue(MutableString(required_dynamic_cast<GUIElementNode*>(node)->getValue()));

	//
	GUIElementController::initialize();
}

void GUISliderVController::dispose() {
	GUIElementController::dispose();
}

void GUISliderVController::postLayout() {
	updateSlider();
}

void GUISliderVController::handleMouseEvent(GUINode* node, GUIMouseEvent* event) {
	GUIElementController::handleMouseEvent(node, event);
	Vector2 nodeMousePosition;
	if (node == this->node &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED == true) {
		this->node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(this->node));
		event->setProcessed(true);
	} else
	if (event->getButton() == MOUSE_BUTTON_LEFT &&
		((node == this->node && event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED == true && node->isEventBelongingToNode(event) == true) ||
		event->getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED == true)) {
		event->setProcessed(true);
		node->getEventNodePosition(event, nodeMousePosition);
		auto sliderPosition = Math::clamp(
			static_cast<int>(nodeMousePosition[1]) - sliderNode->getContentHeight() / 2 - this->node->getPadding().top,
			0,
			this->node->getComputedConstraints().height - this->node->getPadding().top - this->node->getPadding().bottom - sliderNode->getContentHeight()
		);
		valueFloat = 1.0f - static_cast<float>(sliderPosition) / static_cast<float>(this->node->getComputedConstraints().height - this->node->getPadding().top - this->node->getPadding().bottom - sliderNode->getContentHeight());
		updateSlider();
		node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(this->node));
	}
}

void GUISliderVController::handleKeyboardEvent(GUIKeyboardEvent* event) {
	GUIElementController::handleKeyboardEvent(event);
	switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_UP: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					this->valueFloat = Math::clamp(valueFloat + 0.1f, 0.0f, 1.0f);
					updateSlider();
					node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(this->node));
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_DOWN: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					this->valueFloat = Math::clamp(valueFloat - 0.1f, 0.0f, 1.0f);
					updateSlider();
					node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(this->node));
				}
			}
			break;
	}
}

void GUISliderVController::tick() {
	GUIElementController::tick();
}

void GUISliderVController::onFocusGained() {
}

void GUISliderVController::onFocusLost() {
}

bool GUISliderVController::hasValue() {
	return true;
}

const MutableString& GUISliderVController::getValue() {
	return value.set(valueFloat, 4);
}

void GUISliderVController::setValue(const MutableString& value) {
	this->value.set(value);
	this->valueFloat = Math::clamp(Float::parse(this->value.getString()), 0.0f, 1.0f);
	updateSlider();
}

void GUISliderVController::updateSlider() {
	auto sliderPosition = static_cast<int>((1.0f - valueFloat) * (this->node->getComputedConstraints().height - this->node->getPadding().top - this->node->getPadding().bottom - sliderNode->getContentHeight()));
	sliderNode->getComputedConstraints().additionalAlignmentLeft = (node->getComputedConstraints().width - this->node->getPadding().left - this->node->getPadding().right - sliderNode->getContentWidth()) / 2;
	sliderNode->getComputedConstraints().additionalAlignmentTop = sliderPosition;
}
