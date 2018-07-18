#include <tdme/gui/elements/GUIProgressBarController.h>

#include <array>
#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Math.h>
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
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Math;
using tdme::utils::Console;
using tdme::utils::Float;
using tdme::utils::MutableString;
using tdme::utils::Time;

using tdme::gui::elements::GUIProgressBarController;

GUIProgressBarController::GUIProgressBarController(GUINode* node): GUINodeController(node)
{
}

bool GUIProgressBarController::isDisabled() {
	return false;
}

void GUIProgressBarController::setDisabled(bool disabled) {

}

void GUIProgressBarController::initialize() {
	backgroundNode = this->node->getScreenNode()->getNodeById(this->node->getId() + "_background");
	barNode = this->node->getScreenNode()->getNodeById(this->node->getId() + "_bar");
	setValue(MutableString(dynamic_cast<GUIElementNode*>(node)->getValue()));
}

void GUIProgressBarController::dispose() {
}

void GUIProgressBarController::postLayout() {
	updateBar();
}

void GUIProgressBarController::handleMouseEvent(GUINode* node, GUIMouseEvent* event) {
}

void GUIProgressBarController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) {
}

void GUIProgressBarController::tick() {
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
	this->valueFloat = Math::clamp(Float::parseFloat(this->value.getString()), 0.0f, 1.0f);
	updateBar();
}

void GUIProgressBarController::updateBar() {
	auto barWidth = static_cast<int>(valueFloat * (this->node->getComputedConstraints().width - this->node->getPadding().left - this->node->getPadding().right));
	barNode->getComputedConstraints().contentAlignmentTop = (node->getComputedConstraints().height - this->node->getPadding().top - this->node->getPadding().bottom - backgroundNode->getContentHeight()) / 2;
	barNode->getComputedConstraints().contentAlignmentLeft = 0.0f;
	barNode->getComputedConstraints().width = barWidth;
}
