#include <agui/gui/elements/GUIProgressBarController.h>

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
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>
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
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUI;
using agui::math::Math;
using agui::utilities::Console;
using agui::utilities::Float;
using agui::utilities::MutableString;
using agui::utilities::Time;

using agui::gui::elements::GUIProgressBarController;

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
	valueFloat = Math::clamp(Float::parse(this->value.getString()), 0.0f, 1.0f);
	textNode->setText((MutableString((int)(valueFloat * 100.0f))).append(" %"));
	updateBar();
}

void GUIProgressBarController::updateBar() {
	auto barParentNode = barNode->getParentNode();
	auto barWidth = barParentNode->getComputedConstraints().width - barParentNode->getPadding().left - barParentNode->getPadding().right;
	barNode->getClipping().right = barWidth - (int)((float)barWidth * valueFloat);
}
