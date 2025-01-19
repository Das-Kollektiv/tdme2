#include <agui/gui/elements/GUISelectBoxParentOptionController.h>

#include <memory>

#include <agui/agui.h>
#include <agui/gui/elements/GUISelectBoxController.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>

using std::make_unique;
using std::unique_ptr;

using agui::gui::elements::GUISelectBoxParentOptionController;
using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;

string GUISelectBoxParentOptionController::CONDITION_EXPANDED = "expanded";
string GUISelectBoxParentOptionController::CONDITION_COLLAPSED = "collapsed";

GUISelectBoxParentOptionController::GUISelectBoxParentOptionController(GUINode* node)
	: GUISelectBoxOptionController(node), expanded(false)
{
}

void GUISelectBoxParentOptionController::initialize()
{
	class ArrowNodeActionListener: public virtual GUIActionListener
	{

	public:
		// overridden method
		void onAction(GUIActionListenerType type, GUIElementNode* node) override {
			if (node == selectBoxParentOptionController->arrowNode && type == GUIActionListenerType::PERFORMED) {
				required_dynamic_cast<GUISelectBoxController*>(selectBoxParentOptionController->selectBoxNode->getController())->toggleOpenState(required_dynamic_cast<GUIElementNode*>(selectBoxParentOptionController->node));
			}
		}

		/**
		 * Public constructor
		 * @param selectBoxParentOptionController select box parent option controller
		 */
		ArrowNodeActionListener(GUISelectBoxParentOptionController* selectBoxParentOptionController): selectBoxParentOptionController(selectBoxParentOptionController) {
		}

	private:
		GUISelectBoxParentOptionController* selectBoxParentOptionController { nullptr };
	};
	arrowNode = required_dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(node->getId() + "_arrow"));
	arrowNode->getActiveConditions().add(expanded == true?CONDITION_EXPANDED:CONDITION_COLLAPSED);
	arrowNode->getScreenNode()->addActionListener((arrowNodeActionListener = make_unique<ArrowNodeActionListener>(this)).get());
	//
	GUISelectBoxOptionController::initialize();
}

void GUISelectBoxParentOptionController::dispose() {
	if (arrowNodeActionListener != nullptr) {
		node->getScreenNode()->removeActionListener(arrowNodeActionListener.get());
		arrowNodeActionListener = nullptr;
	}
}

bool GUISelectBoxParentOptionController::isExpanded() {
	return expanded;
}

void GUISelectBoxParentOptionController::toggleExpandState()
{
	arrowNode->getActiveConditions().remove(expanded == true ?CONDITION_EXPANDED:CONDITION_COLLAPSED);
	expanded = expanded == true?false:true;
	arrowNode->getActiveConditions().add(expanded == true?CONDITION_EXPANDED:CONDITION_COLLAPSED);
}
