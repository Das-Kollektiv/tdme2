#include <tdme/gui/elements/GUISelectBoxParentOptionController.h>

#include <memory>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>

using std::make_unique;
using std::unique_ptr;

using tdme::gui::elements::GUISelectBoxParentOptionController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;

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
