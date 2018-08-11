#include <tdme/gui/nodes/GUIElementController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>

using tdme::gui::nodes::GUIElementController;
using tdme::gui::GUI;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

GUIElementController::GUIElementController(GUINode* node) 
	: GUINodeController(node)
{
	this->isActionPerforming = false;
	this->disabled = (dynamic_cast< GUIElementNode* >(node))->isDisabled();
	this->initialized = false;
}

string GUIElementController::CONDITION_DISABLED = "disabled";
string GUIElementController::CONDITION_ENABLED = "enabled";

bool GUIElementController::isDisabled()
{
	return disabled;
}

void GUIElementController::setDisabled(bool disabled)
{
	auto& nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions.remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	isActionPerforming = false;
}

void GUIElementController::initialize()
{
	this->node->getScreenNode()->addTickNode(this->node);
	setDisabled(disabled);
}

void GUIElementController::dispose()
{
}

void GUIElementController::postLayout()
{
}

void GUIElementController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == true) return;
	if (node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSEEVENT_PRESSED) {
			isActionPerforming = true;
			if ((dynamic_cast< GUIElementNode* >(node))->isFocusable() == true) {
				node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast< GUIElementNode* >(node));
			}
		} else if (event->getType() == GUIMouseEvent_Type::MOUSEEVENT_DRAGGED) {
			isActionPerforming = true;
		} else if (event->getType() == GUIMouseEvent_Type::MOUSEEVENT_RELEASED) {
			isActionPerforming = false;
			auto onMouseClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseClickExpression();
			if (onMouseClickExpression.size() > 0) executeExpression(onMouseClickExpression);
			node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMED, dynamic_cast< GUIElementNode* >(node));
		}
	} else
	if (node == this->node && event->getType() == GUIMouseEvent_Type::MOUSEEVENT_MOVED) {
		event->setProcessed(true);
		if (node->isEventBelongingToNode(event)) {
			auto onMouseOverExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseOverExpression();
			if (onMouseOverExpression.size() > 0) executeExpression(onMouseOverExpression);
		} else {
			auto onMouseOutExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseOutExpression();
			if (onMouseOutExpression.size() > 0) executeExpression(onMouseOutExpression);
		}
	} else {
		isActionPerforming = false;
	}
}

void GUIElementController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEYBOARDEVENT_KEY_PRESSED) {
					auto onMouseClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseClickExpression();
					if (onMouseClickExpression.size() > 0) executeExpression(onMouseClickExpression);
					node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMED, dynamic_cast< GUIElementNode* >(node));
				}
			}
			break;
		default: {
				break;
			}
		}
	}
}

void GUIElementController::tick()
{
	// TODO: Maybe move me into GUIElementController::initialize()
	if (initialized == false) {
		auto onInitializeExpression = dynamic_cast<GUIElementNode*>(node)->getOnInitializeExpression();
		if (onInitializeExpression.size() > 0) executeExpression(onInitializeExpression);
		initialized = true;
	}

	if (isActionPerforming == true) {
		if (disabled == true) {
			isActionPerforming = false;
			return;
		}
		node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMING, dynamic_cast< GUIElementNode* >(node));
	}
}

void GUIElementController::onFocusGained()
{
}

void GUIElementController::onFocusLost()
{
}

bool GUIElementController::hasValue()
{
	return false;
}

const MutableString& GUIElementController::getValue()
{
	return value;
}

void GUIElementController::setValue(const MutableString& value)
{
}

void GUIElementController::executeExpression(const string& expression) {
	StringTokenizer t;
	t.tokenize(expression, "=");
	string command;
	string value;
	string nodeId;
	string subCommand;
	if (t.countTokens() > 0) {
		command = StringUtils::trim(t.nextToken());
		if (t.countTokens() > 1) value = StringUtils::trim(t.nextToken());
	}
	t.tokenize(command, ".");
	if (t.countTokens() == 2) {
		nodeId = StringUtils::trim(t.nextToken());
		subCommand = StringUtils::trim(t.nextToken());
	}
	if (subCommand == "condition") {
		auto nodeElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(nodeId));
		if (nodeElementNode != nullptr) {
			nodeElementNode->getActiveConditions().removeAll();
			nodeElementNode->getActiveConditions().add(value);
		}
	} else
	if (subCommand == "condition-") {
		auto nodeElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(nodeId));
		if (nodeElementNode != nullptr) nodeElementNode->getActiveConditions().remove(value);
	} else
	if (subCommand == "condition+") {
		auto nodeElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(nodeId));
		if (nodeElementNode != nullptr) nodeElementNode->getActiveConditions().add(value);
	}
}
