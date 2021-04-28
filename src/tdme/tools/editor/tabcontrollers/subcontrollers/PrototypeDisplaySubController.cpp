#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>

using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;

PrototypeDisplaySubController::PrototypeDisplaySubController(Engine* engine, PrototypePhysicsSubView* physicsView)
{
	view = new PrototypeDisplaySubView(engine, this);
	this->physicsView = physicsView;
}

PrototypeDisplaySubController::~PrototypeDisplaySubController() {
	delete view;
}

PrototypeDisplaySubView* PrototypeDisplaySubController::getView()
{
	return view;
}

void PrototypeDisplaySubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void PrototypeDisplaySubController::setupDisplay()
{
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_shadowing"))->getController()->setValue(MutableString(view->isDisplayShadowing() == true?"1":""));
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_ground"))->getController()->setValue(MutableString(view->isDisplayGroundPlate() == true?"1":""));
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_boundingvolume"))->getController()->setValue(MutableString(physicsView->isDisplayBoundingVolume() == true?"1":""));
}

void PrototypeDisplaySubController::onDisplayApply()
{
	view->setDisplayShadowing(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_shadowing"))->getController()->getValue().equals("1"));
	view->setDisplayGroundPlate(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_ground"))->getController()->getValue().equals("1"));
	physicsView->setDisplayBoundingVolume(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_boundingvolume"))->getController()->getValue().equals("1"));
}

bool PrototypeDisplaySubController::getDisplayShadowing()
{
	return required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_shadowing"))->getController()->getValue().equals("1");
}

bool PrototypeDisplaySubController::getDisplayGround()
{
	return required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_ground"))->getController()->getValue().equals("1");
}

bool PrototypeDisplaySubController::getDisplayBoundingVolume()
{
	return required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("display_boundingvolume"))->getController()->getValue().equals("1");
}

void PrototypeDisplaySubController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId().compare("button_display_apply") == 0) {
			onDisplayApply();
		}
	}
}
