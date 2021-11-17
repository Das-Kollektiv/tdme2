#include <tdme/gui/elements/GUIProgressBarController.h>

#include <array>
#include <string>

#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Time.h>

using std::array;
using std::to_string;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUI;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::MutableString;
using tdme::utilities::Time;

using tdme::gui::elements::GUIProgressBarController;

GUIProgressBarController::GUIProgressBarController(GUINode* node): GUIElementController(node)
{
}

bool GUIProgressBarController::isDisabled() {
	return false;
}

void GUIProgressBarController::setDisabled(bool disabled) {

}

void GUIProgressBarController::initialize() {
	barNode = required_dynamic_cast<GUIImageNode*>(this->node->getScreenNode()->getNodeById(this->node->getId() + "_bar"));
	textNode = required_dynamic_cast<GUITextNode*>(this->node->getScreenNode()->getNodeById(this->node->getId() + "_text"));
	setValue(MutableString(required_dynamic_cast<GUIElementNode*>(node)->getValue()));
	GUIElementController::initialize();
}

void GUIProgressBarController::dispose() {
	GUIElementController::dispose();
}

void GUIProgressBarController::postLayout() {
	updateBar();
}

void GUIProgressBarController::handleMouseEvent(GUINode* node, GUIMouseEvent* event) {
	GUIElementController::handleMouseEvent(node, event);
}

void GUIProgressBarController::handleKeyboardEvent(GUIKeyboardEvent* event) {
	GUIElementController::handleKeyboardEvent(event);
}

void GUIProgressBarController::tick() {
	GUIElementController::tick();
}

void GUIProgressBarController::onFocusGained() {
}

void GUIProgressBarController::onFocusLost() {
}

bool GUIProgressBarController::hasValue() {
	return true;
}

const MutableString& GUIProgressBarController::getValue() {
	return value.set(valueFloat, 4);
}

void GUIProgressBarController::setValue(const MutableString& value) {
	this->value.set(value);
	valueFloat = Math::clamp(Float::parseFloat(this->value.getString()), 0.0f, 1.0f);
	textNode->setText((MutableString((int)(valueFloat * 100.0f))).append(" %"));
	updateBar();
}

void GUIProgressBarController::updateBar() {
	auto barWidth = this->node->getComputedConstraints().width - this->node->getPadding().left - this->node->getPadding().right;
	barNode->getClipping().right = barWidth - (int)((float)barWidth * valueFloat);
}
