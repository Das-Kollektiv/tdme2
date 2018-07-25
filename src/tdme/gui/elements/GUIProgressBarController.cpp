#include <tdme/gui/elements/GUIProgressBarController.h>

#include <array>
#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
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
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
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
	backgroundNode = dynamic_cast<GUIImageNode*>(this->node->getScreenNode()->getNodeById(this->node->getId() + "_background"));
	barNode = dynamic_cast<GUIImageNode*>(this->node->getScreenNode()->getNodeById(this->node->getId() + "_bar"));
	textNode = dynamic_cast<GUITextNode*>(this->node->getScreenNode()->getNodeById(this->node->getId() + "_text"));
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
	auto barWidth = this->node->getComputedConstraints().width - this->node->getPadding().left - this->node->getPadding().right;
	barNode->getClipping().right = barWidth - (int)((float)barWidth * valueFloat);
	textNode->setText((MutableString((int)(valueFloat * 100.0f))).append(" %"));
	textNode->getScreenNode()->layout(textNode);
}
