#include <tdme/gui/nodes/GUIElementController.h>

#include <string>

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
#include <tdme/utils/Console.h>
#include <tdme/utils/Time.h>

using std::string;
using std::to_string;

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
using tdme::utils::Console;
using tdme::utils::Time;

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
		} else
		if (event->getType() == GUIMouseEvent_Type::MOUSEEVENT_DRAGGED) {
			isActionPerforming = true;
		} else
		if (event->getType() == GUIMouseEvent_Type::MOUSEEVENT_RELEASED) {
			isActionPerforming = false;
			auto now = Time::getCurrentMillis();
			if (timeLastClicked != -1LL) {
				if (now - timeLastClicked < TIME_DOUBLECLICK) {
					auto onMouseDoubleClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseDoubleClickExpression();
					if (onMouseDoubleClickExpression.size() > 0) {
						dynamic_cast< GUIElementNode* >(node)->executeExpression(onMouseDoubleClickExpression);
					} else {
						auto onMouseClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseClickExpression();
						if (onMouseClickExpression.size() > 0) dynamic_cast< GUIElementNode* >(node)->executeExpression(onMouseClickExpression);
						node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMED, dynamic_cast< GUIElementNode* >(node));
					}
					timeLastClicked = -1LL;
				} else {
					auto onMouseClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseClickExpression();
					if (onMouseClickExpression.size() > 0) dynamic_cast< GUIElementNode* >(node)->executeExpression(onMouseClickExpression);
					node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMED, dynamic_cast< GUIElementNode* >(node));
					timeLastClicked = -1LL;
				}
			} else {
				auto onMouseDoubleClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseDoubleClickExpression();
				if (onMouseDoubleClickExpression.size() > 0) {
					timeLastClicked = now;
				} else {
					auto onMouseClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseClickExpression();
					if (onMouseClickExpression.size() > 0) dynamic_cast< GUIElementNode* >(node)->executeExpression(onMouseClickExpression);
					node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMED, dynamic_cast< GUIElementNode* >(node));
				}
			}
		}
	} else
	if (node == this->node && event->getType() == GUIMouseEvent_Type::MOUSEEVENT_MOVED) {
		event->setProcessed(true);
		if (node->isEventBelongingToNode(event)) {
			auto onMouseOverExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseOverExpression();
			if (onMouseOverExpression.size() > 0) dynamic_cast< GUIElementNode* >(node)->executeExpression(onMouseOverExpression);
		} else {
			auto onMouseOutExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseOutExpression();
			if (onMouseOutExpression.size() > 0) dynamic_cast< GUIElementNode* >(node)->executeExpression(onMouseOutExpression);
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
					if (onMouseClickExpression.size() > 0) dynamic_cast< GUIElementNode* >(node)->executeExpression(onMouseClickExpression);
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
	if (initialized == false) {
		auto onInitializeExpression = dynamic_cast<GUIElementNode*>(node)->getOnInitializeExpression();
		if (onInitializeExpression.size() > 0) dynamic_cast< GUIElementNode* >(node)->executeExpression(onInitializeExpression);
		initialized = true;
		// TODO: check me, the following code has performance relevance!!!
		// auto onMouseClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseClickExpression();
		// if (onMouseClickExpression.size() == 0) node->getScreenNode()->removeTickNode(node);
	}

	auto now = Time::getCurrentMillis();
	if (timeLastClicked != -1LL && now - timeLastClicked >= TIME_DOUBLECLICK) {
		timeLastClicked = -1LL;
		auto onMouseClickExpression = dynamic_cast<GUIElementNode*>(node)->getOnMouseClickExpression();
		if (onMouseClickExpression.size() > 0) dynamic_cast< GUIElementNode* >(node)->executeExpression(onMouseClickExpression);
		node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMED, dynamic_cast< GUIElementNode* >(node));
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
