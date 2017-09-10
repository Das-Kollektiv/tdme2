#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>

#include <java/lang/String.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/shared/views/EntityDisplayView.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using java::lang::String;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::utils::MutableString;
using tdme::utils::_Console;
using tdme::utils::_Exception;

MutableString* EntityDisplaySubScreenController::CHECKBOX_CHECKED = new MutableString(L"1");

MutableString* EntityDisplaySubScreenController::CHECKBOX_UNCHECKED = new MutableString(L"");

EntityDisplaySubScreenController::EntityDisplaySubScreenController() 
{
	view = new EntityDisplayView(this);
}

EntityDisplayView* EntityDisplaySubScreenController::getView()
{
	return view;
}

void EntityDisplaySubScreenController::initialize(GUIScreenNode* screenNode)
{
	try {
		displayBoundingVolume = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"display_boundingvolume"_j));
		displayShadowing = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"display_shadowing"_j));
		displayGround = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"display_ground"_j));
	} catch (_Exception& exception) {
		_Console::print(string("EntityDisplaySubScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
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
	view->setDisplayShadowing(displayShadowing->getController()->getValue()->equals(CHECKBOX_CHECKED));
	view->setDisplayGroundPlate(displayGround->getController()->getValue()->equals(CHECKBOX_CHECKED));
	view->setDisplayBoundingVolume(displayBoundingVolume->getController()->getValue()->equals(CHECKBOX_CHECKED));
}

bool EntityDisplaySubScreenController::getDisplayShadowing()
{
	return displayShadowing->getController()->getValue()->equals(CHECKBOX_CHECKED);
}

bool EntityDisplaySubScreenController::getDisplayGround()
{
	return displayGround->getController()->getValue()->equals(CHECKBOX_CHECKED);
}

bool EntityDisplaySubScreenController::getDisplayBoundingVolume()
{
	return displayBoundingVolume->getController()->getValue()->equals(CHECKBOX_CHECKED);
}

void EntityDisplaySubScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
			{
				if (node->getId().compare(L"button_display_apply") == 0) {
					onDisplayApply();
				} else {
					_Console::println(
						wstring(
							L"ModelViewerScreenController::onActionPerformed()::unknown, type='" +
							type->toWString() +
							L"', id = '" +
							node->getId() +
							L"'" +
							L", name = '" +
							node->getName() +
							L"'"
						)
					);
				}
				goto end_switch0;;
			}
		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
			{
				goto end_switch0;;
			}
		}
		end_switch0:;
	}

}
