#include <tdme/gui/elements/GUISelectorHController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUISelectorHOptionController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;

using tdme::gui::elements::GUISelectorHController;
using tdme::gui::elements::GUISelectorHOptionController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUI;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

string GUISelectorHController::CONDITION_DISABLED = "disabled";
string GUISelectorHController::CONDITION_ENABLED = "enabled";

GUISelectorHController::GUISelectorHController(GUINode* node)
	: GUIElementController(node)
{
	this->disabled = required_dynamic_cast<GUIElementNode*>(node)->isDisabled();
}

bool GUISelectorHController::isDisabled()
{
	return disabled;
}

void GUISelectorHController::setDisabled(bool disabled)
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
}

void GUISelectorHController::initialize()
{
	//
	GUIElementController::initialize();

	//
	determineSelectorHOptionControllers();

	//
	innerNode  = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getInnerNodeById(node->getId()));

	//
	class GUISelectorHControllerActionListener: public virtual GUIActionListener
	{
	public:
		void onAction(GUIActionListenerType type, GUIElementNode* node) override {
			if (type != GUIActionListenerType::PERFORMED) return;
			if (node == leftArrowNode) {
				selectorHController->selectPrevious();
			} else
			if (node == rightArrowNode) {
				selectorHController->selectNext();
			}
		}

		/**
		 * Public constructor
		 * @param selectorHController selector horizontal Controller
		 * @param leftArrowNode left arrow node
		 * @param rightArrowNode right arrow node
		 */
		GUISelectorHControllerActionListener(GUISelectorHController* selectorHController, GUIElementNode* leftArrowNode, GUIElementNode* rightArrowNode)
			: selectorHController(selectorHController)
			, leftArrowNode(leftArrowNode)
			, rightArrowNode(rightArrowNode) {
		}

	private:
		GUISelectorHController* selectorHController;
		GUIElementNode* leftArrowNode;
		GUIElementNode* rightArrowNode;
	};

	//
	auto const leftArrowNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(node->getId() + "_left"));
	auto const rightArrowNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(node->getId() + "_right"));
	node->getScreenNode()->addActionListener(actionListener = new GUISelectorHControllerActionListener(this, leftArrowNode, rightArrowNode));
}

void GUISelectorHController::dispose()
{
	//
	GUIElementController::dispose();

	//
	if (actionListener != nullptr) {
		node->getScreenNode()->removeActionListener(actionListener);
		delete actionListener;
		actionListener = nullptr;
	}
}

void GUISelectorHController::postLayout()
{
}

void GUISelectorHController::unselect()
{
	if (selectedHOptionControllerIdx == -1) return;
	selectorHOptionControllers[selectedHOptionControllerIdx]->unselect();
}

void GUISelectorHController::select(int idx) {
	unselect();
	selectedHOptionControllerIdx = idx;
	if (selectedHOptionControllerIdx == -1) return;
	selectorHOptionControllers[selectedHOptionControllerIdx]->select();
}

void GUISelectorHController::select(GUIElementNode* selectedSelectorHOptionElementNode) {
	unselect();
	auto selectedSelectorHOptionElementController = selectedSelectorHOptionElementNode->getController();
	auto i = 0;
	for (auto selectorHOptionController: selectorHOptionControllers) {
		if (selectorHOptionController == selectedSelectorHOptionElementController) {
			select(i);
			break;
		}
		i++;
	}
}

void GUISelectorHController::determineSelectorHOptionControllers()
{
	vector<GUINode*> childControllerNodes;
	selectorHOptionControllers.clear();
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = dynamic_cast<GUISelectorHOptionController*>(childControllerNode->getController());
		if (childController != nullptr) selectorHOptionControllers.push_back(childController);
	}
}

void GUISelectorHController::selectNext()
{
	unselect();
	if (selectorHOptionControllers.size() == 0)
		return;

	auto disabledCount = 0;
	while (disabledCount < selectorHOptionControllers.size()) {
		selectedHOptionControllerIdx = (selectedHOptionControllerIdx + 1) % selectorHOptionControllers.size();
		if (selectorHOptionControllers[selectedHOptionControllerIdx]->isDisabled() == false &&
			selectorHOptionControllers[selectedHOptionControllerIdx]->isHidden() == false) break;
		disabledCount++;
	}
	if (disabledCount == selectorHOptionControllers.size()) {
		selectedHOptionControllerIdx = -1;
		return;
	}

	selectorHOptionControllers[selectedHOptionControllerIdx]->select();
}

void GUISelectorHController::selectPrevious()
{
	unselect();
	if (selectorHOptionControllers.size() == 0)
		return;

	if (selectedHOptionControllerIdx == -1) selectedHOptionControllerIdx = (int)selectorHOptionControllers.size() - 1;

	auto disabledCount = 0;
	while (disabledCount < selectorHOptionControllers.size()) {
		selectedHOptionControllerIdx = (selectedHOptionControllerIdx - 1) % (int)selectorHOptionControllers.size();
		if (selectedHOptionControllerIdx < 0)
			selectedHOptionControllerIdx += selectorHOptionControllers.size();
		if (selectorHOptionControllers[selectedHOptionControllerIdx]->isDisabled() == false &&
			selectorHOptionControllers[selectedHOptionControllerIdx]->isHidden() == false) break;
		disabledCount++;
	}
	if (disabledCount == selectorHOptionControllers.size()) {
		selectedHOptionControllerIdx = -1;
		return;
	}

	selectorHOptionControllers[selectedHOptionControllerIdx]->select();
}

void GUISelectorHController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (disabled == true) return;
	if (event->getButton() == MOUSE_BUTTON_LEFT) {
		if (node == innerNode && innerNode->isEventBelongingToNode(event) == true) {
			if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
				auto elementNode  = required_dynamic_cast<GUIElementNode*>(this->node);
				node->getScreenNode()->getGUI()->setFoccussedNode(elementNode);
				selectNext();
			}
		}
	}
}

void GUISelectorHController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
	if (disabled == true) return;
	switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_LEFT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					selectPrevious();
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_RIGHT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					selectNext();
				}
			}
			break;
	}
}

void GUISelectorHController::tick()
{
	GUIElementController::tick();
}

void GUISelectorHController::onFocusGained()
{
}

void GUISelectorHController::onFocusLost()
{
}

bool GUISelectorHController::hasValue()
{
	return true;
}

const MutableString& GUISelectorHController::getValue()
{
	value.reset();
	if (selectedHOptionControllerIdx != -1) value.append(required_dynamic_cast<GUIElementNode*>(selectorHOptionControllers[selectedHOptionControllerIdx]->getNode())->getValue());
	return value;
}

void GUISelectorHController::setValue(const MutableString& value)
{
	unselect();
	auto i = 0;
	for (auto selectorHOptionController: selectorHOptionControllers) {
		auto selectorHOptionNode = required_dynamic_cast<GUIElementNode*>(selectorHOptionController->getNode());
		if (value.equals(selectorHOptionNode->getValue())) {
			select(i);
			break;
		}
		i++;
	}
}

void GUISelectorHController::onSubTreeChange() {
	determineSelectorHOptionControllers();
	selectedHOptionControllerIdx = -1;
	auto i = 0;
	for (auto selectorHOptionController: selectorHOptionControllers) {
		auto selectorHOptionNode = required_dynamic_cast<GUIElementNode*>(selectorHOptionController->getNode());
		selectorHOptionController->unselect();
		if (selectorHOptionNode->isSelected() == true) {
			selectedHOptionControllerIdx = i;
			break;
		}
		i++;
	}
	if (selectedHOptionControllerIdx == -1 && selectorHOptionControllers.empty() == false) selectedHOptionControllerIdx = 0;
	if (selectedHOptionControllerIdx != -1) select(selectedHOptionControllerIdx);
}
