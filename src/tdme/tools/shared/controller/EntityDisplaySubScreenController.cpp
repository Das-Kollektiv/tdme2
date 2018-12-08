#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>

#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/shared/views/EntityDisplayView.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::utils::MutableString;
using tdme::utils::Console;
using tdme::utils::Exception;

MutableString EntityDisplaySubScreenController::CHECKBOX_CHECKED = MutableString("1");
MutableString EntityDisplaySubScreenController::CHECKBOX_UNCHECKED = MutableString("");

EntityDisplaySubScreenController::EntityDisplaySubScreenController() 
{
	view = new EntityDisplayView(this);
}

EntityDisplaySubScreenController::~EntityDisplaySubScreenController() {
	delete view;
}

EntityDisplayView* EntityDisplaySubScreenController::getView()
{
	return view;
}

void EntityDisplaySubScreenController::initialize(GUIScreenNode* screenNode)
{
	try {
		displayBoundingVolume = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("display_boundingvolume"));
		displayShadowing = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("display_shadowing"));
		displayGround = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("display_ground"));
	} catch (Exception& exception) {
		Console::print(string("EntityDisplaySubScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EntityDisplaySubScreenController::setupDisplay()
{
	displayShadowing->getController()->setValue(view->isDisplayShadowing() == true ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED);
	displayGround->getController()->setValue(view->isDisplayGroundPlate() == true ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED);
	displayBoundingVolume->getController()->setValue(view->isDisplayBoundingVolume() == true ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED);
}

void EntityDisplaySubScreenController::onDisplayApply()
{
	view->setDisplayShadowing(displayShadowing->getController()->getValue().equals(CHECKBOX_CHECKED));
	view->setDisplayGroundPlate(displayGround->getController()->getValue().equals(CHECKBOX_CHECKED));
	view->setDisplayBoundingVolume(displayBoundingVolume->getController()->getValue().equals(CHECKBOX_CHECKED));
}

bool EntityDisplaySubScreenController::getDisplayShadowing()
{
	return displayShadowing->getController()->getValue().equals(CHECKBOX_CHECKED);
}

bool EntityDisplaySubScreenController::getDisplayGround()
{
	return displayGround->getController()->getValue().equals(CHECKBOX_CHECKED);
}

bool EntityDisplaySubScreenController::getDisplayBoundingVolume()
{
	return displayBoundingVolume->getController()->getValue().equals(CHECKBOX_CHECKED);
}

void EntityDisplaySubScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	{
		auto v = type;
		if (v == GUIActionListener_Type::PERFORMED) {
			if (node->getId().compare("button_display_apply") == 0) {
				onDisplayApply();
			} else {
				Console::println(
					string(
						"EntityDisplaySubScreenController::onActionPerformed()::unknown, type='" +
						type->getName() +
						"', id = '" +
						node->getId() +
						"'" +
						", name = '" +
						node->getName() +
						"'"
					)
				);
			}
		}
	}
}
