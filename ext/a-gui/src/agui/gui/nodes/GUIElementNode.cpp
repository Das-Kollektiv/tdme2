#include <agui/gui/nodes/GUIElementNode.h>

#include <algorithm>
#include <set>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementIgnoreEventsController.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINode_Alignments.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIParentNode_Overflow.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIApplication.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/Float.h>
#include <agui/utilities/Integer.h>
#include <agui/utilities/RTTI.h>
#include <agui/utilities/StringTokenizer.h>
#include <agui/utilities/StringTools.h>
#include <agui/utilities/Time.h>

using std::begin;
using std::end;
using std::find;
using std::set;
using std::to_string;

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementIgnoreEventsController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIParentNode_Overflow;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::gui::GUIApplication;
using agui::utilities::Console;
using agui::utilities::Float;
using agui::utilities::Integer;
using agui::utilities::RTTI;
using agui::utilities::StringTokenizer;
using agui::utilities::StringTools;
using agui::utilities::Time;

string GUIElementNode::CONDITION_ALWAYS = "always";
string GUIElementNode::CONDITION_ONMOUSEOVER = "mouseover";
string GUIElementNode::CONDITION_CLICK = "click";
string GUIElementNode::CONDITION_FOCUS = "focus";

GUIElementNode::GUIElementNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	GUIParentNode_Overflow* overflowX,
	GUIParentNode_Overflow* overflowY,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScaleGrid,
	const GUIColor& backgroundImageEffectColorMul,
	const GUIColor& backgroundImageEffectColorAdd,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& tooltip,
	const string& name,
	const string& value,
	bool selected,
	bool disabled,
	bool focusable,
	bool ignoreEvents,
	const string& onInitializeExpression,
	const string& onMouseClickExpression,
	const string& onMouseDoubleClickExpression,
	const string& onMouseOverExpression,
	const string& onMouseOutExpression,
	const string& onChangeExpression,
	const string& parentElementId,
	const string& options
	) :
	GUILayerNode(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScaleGrid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip),
	activeConditions(this)
{
	this->name = name;
	this->value = value;
	this->selected = selected;
	this->disabled = disabled;
	this->focusable = focusable;
	this->ignoreEvents = ignoreEvents;
	this->onInitializeExpression = onInitializeExpression;
	this->onMouseClickExpression = onMouseClickExpression;
	this->onMouseDoubleClickExpression = onMouseDoubleClickExpression;
	this->onMouseOverExpression = onMouseOverExpression;
	this->onMouseOutExpression = onMouseOutExpression;
	this->onChangeExpression = onChangeExpression;
	this->parentElementId = parentElementId;
	// controller
	auto controller = ignoreEvents == true?static_cast<GUINodeController*>(new GUIElementIgnoreEventsController(this)):static_cast<GUINodeController*>(new GUIElementController(this));
	controller->initialize();
	setController(controller);
	//
	{
		StringTokenizer t;
		t.tokenize(StringTools::trim(options), ",");
		while (t.hasMoreTokens() == true) this->options.push_back(StringTools::toLowerCase(StringTools::trim(t.nextToken())));

	}
}

const string GUIElementNode::getNodeType()
{
	return "element";
}

bool GUIElementNode::isContentNode()
{
	return false;
}

void GUIElementNode::executeExpression(GUIScreenNode* screenNode, const string& expression) {
	if (StringTools::startsWith(expression, "http://") == true || StringTools::startsWith(expression, "https://") == true) {
		GUI::getApplication()->openBrowser(expression);
		return;
	}
	StringTokenizer t1;
	StringTokenizer t2;
	t1.tokenize(expression, ";");
	while (t1.hasMoreTokens()) {
		t2.tokenize(t1.nextToken(), "=");
		string command;
		string value;
		string nodeId;
		string subCommand;
		if (t2.countTokens() > 0) {
			command = StringTools::trim(t2.nextToken());
			if (t2.countTokens() > 1) value = StringTools::trim(t2.nextToken());
		}
		t2.tokenize(command, ".");
		if (t2.countTokens() == 2) {
			nodeId = StringTools::trim(t2.nextToken());
			subCommand = StringTools::trim(t2.nextToken());
		}
		// element (controller) values
		if (subCommand == "value") {
			auto nodeElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(nodeId));
			auto nodeController = nodeElementNode != nullptr?nodeElementNode->getController():nullptr;
			if (StringTools::startsWith(value, "'") == true && StringTools::endsWith(value, "'") == true) {
				if (nodeController != nullptr) nodeController->setValue(MutableString(StringTools::substring(value, 1, value.size() - 1)));
			} else
			if (StringTools::endsWith(value, ".value") == true) {
				auto nodeValueElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(StringTools::substring(value, 0, value.length() - string(".value").size())));
				auto nodeValueController = nodeValueElementNode != nullptr?nodeValueElementNode->getController():nullptr;
				if (nodeController != nullptr && nodeValueController != nullptr) nodeController->setValue(nodeValueController->getValue());
			} else {
				Console::printLine("GUIElementController::executeExpression(): Unknown value in expression: " + value);
			}
		} else
		// element conditions
		if (subCommand == "condition") {
			auto nodeElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(nodeId));
			if (nodeElementNode != nullptr) {
				if (value.find('?') != string::npos &&
					value.find(':') != string::npos &&
					value.find(':') > value.find('?')) {
					t2.tokenize(value, "?:");
					string testCondition = t2.hasMoreTokens() == true?t2.nextToken():"";
					string setOnTrueCondition = t2.hasMoreTokens() == true?t2.nextToken():"";
					string setOnFalseCondition = t2.hasMoreTokens() == true?t2.nextToken():"";
					if (testCondition.empty() == true ||
						setOnTrueCondition.empty() == true ||
						setOnFalseCondition.empty() == true) {
						Console::printLine("GUIElementController::executeExpression(): = ternary operator requires the following format 'node.condition=a?b:c'");
					} else {
						auto nodeElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(nodeId));
						if (nodeElementNode != nullptr) {
							if (nodeElementNode->getActiveConditions().has(testCondition) == true) {
								nodeElementNode->getActiveConditions().removeAll();
								nodeElementNode->getActiveConditions().add(setOnTrueCondition);
							} else {
								nodeElementNode->getActiveConditions().removeAll();
								nodeElementNode->getActiveConditions().add(setOnFalseCondition);
							}
						}
					}
				} else {
					nodeElementNode->getActiveConditions().removeAll();
					nodeElementNode->getActiveConditions().add(value);
				}
			}
		} else
		if (subCommand == "condition-") {
			auto nodeElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(nodeId));
			if (nodeElementNode != nullptr) nodeElementNode->getActiveConditions().remove(value);
		} else
		if (subCommand == "condition+") {
			auto nodeElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(nodeId));
			if (nodeElementNode != nullptr) nodeElementNode->getActiveConditions().add(value);
		} else
		if (subCommand == "condition!") {
			auto nodeElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(nodeId));
			if (nodeElementNode != nullptr) {
				if (nodeElementNode->getActiveConditions().has(value) == true) {
					nodeElementNode->getActiveConditions().remove(value);
				} else {
					nodeElementNode->getActiveConditions().add(value);
				}
			}
		} else
		if (subCommand == "condition?") {
			t2.tokenize(value, "?:");
			string testCondition = t2.hasMoreTokens() == true?t2.nextToken():"";
			string setOnTrueCondition = t2.hasMoreTokens() == true?t2.nextToken():"";
			string setOnFalseCondition = t2.hasMoreTokens() == true?t2.nextToken():"";
			if (value.find('?') == string::npos ||
				value.find(':') == string::npos ||
				value.find(':') < value.find('?') ||
				testCondition.empty() == true ||
				setOnTrueCondition.empty() == true ||
				setOnFalseCondition.empty() == true) {
				Console::printLine("GUIElementController::executeExpression(): ?= ternary operator requires the following format 'node.condition?=a?b:c'");
			}
			auto nodeElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(nodeId));
			if (nodeElementNode != nullptr) {
				if (nodeElementNode->getActiveConditions().has(testCondition) == true) {
					nodeElementNode->getActiveConditions().remove(setOnFalseCondition);
					nodeElementNode->getActiveConditions().add(setOnTrueCondition);
				} else {
					nodeElementNode->getActiveConditions().remove(setOnTrueCondition);
					nodeElementNode->getActiveConditions().add(setOnFalseCondition);
				}
			}
		} else
		// image node specific data
		if (subCommand == "maskmaxvalue") {
			auto imageNode = dynamic_cast<GUIImageNode*>(screenNode->getNodeById(nodeId));
			if (imageNode != nullptr) {
				if (StringTools::endsWith(value, ".value") == true) {
					auto nodeValueElementNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(StringTools::substring(value, 0, value.length() - string(".value").size())));
					auto nodeValueController = nodeValueElementNode != nullptr?nodeValueElementNode->getController():nullptr;
					if (nodeValueController != nullptr) imageNode->setMaskMaxValue(Float::parse(nodeValueController->getValue().getString()));
				} else {
					imageNode->setMaskMaxValue(Float::parse(value));
				}
			}
		} else
		if (StringTools::startsWith(command,"delay(") == true &&
			StringTools::endsWith(command,")") == true) {
			int64_t delay = Integer::parse(StringTools::substring(command, command.find('(') + 1, command.rfind(')')));
			while(t1.hasMoreTokens() == true) value+= t1.nextToken() + ";";
			screenNode->addTimedExpression(Time::getCurrentMillis() + delay, value);
		} else {
			Console::printLine("GUIElementController::executeExpression(): Unknown sub command in expression: expression = " + expression + ", sub command = " + subCommand);
		}
	}
}

const string GUIElementNode::getOptionValue(const string& option) {
	StringTokenizer t;
	for (const auto& v: options) {
		t.tokenize(v, "=");
		if (t.hasMoreTokens() == false) continue;
		auto optionName = StringTools::trim(t.nextToken());
		if (optionName != option) continue;
		if (t.hasMoreTokens() == false) continue;
		return StringTools::trim(t.nextToken());
	}
	return string();
}

void GUIElementNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	if (ignoreEvents == true)
		return;

	if (conditionsMet == false)
		return;

	vector<GUINode*> childControllerNodes;
	getChildControllerNodes(childControllerNodes, true);
	if (controller != nullptr) {
		controller->handleKeyboardEvent(event);
	}
	if (event->isProcessed() == false) {
		for (auto childControllerNode: childControllerNodes) {
			childControllerNode->getController()->handleKeyboardEvent(event);
			if (event->isProcessed() == true) break;
		}
	}
}
