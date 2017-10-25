#include <tdme/tools/leveleditor/controller/TriggerScreenController.h>

#include <string>

#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/tools/leveleditor/controller/TriggerScreenController_TriggerScreenController_1.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/viewer/TDMEViewer.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::string;

using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::leveleditor::controller::TriggerScreenController_TriggerScreenController_1;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::viewer::TDMEViewer;
using tdme::utils::Float;
using tdme::utils::MutableString;
using tdme::utils::Console;
using tdme::utils::Exception;

MutableString* TriggerScreenController::TEXT_EMPTY = new MutableString("");

TriggerScreenController::TriggerScreenController(TriggerView* view) 
{
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new TriggerScreenController_TriggerScreenController_1(this, finalView));
}

GUIScreenNode* TriggerScreenController::getScreenNode()
{
	return screenNode;
}

void TriggerScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/tools/leveleditor/gui", "screen_trigger.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById("screen_caption"));
		triggerWidth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("trigger_width"));
		triggerHeight = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("trigger_height"));
		triggerDepth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("trigger_depth"));
		triggerApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_trigger_apply"));
	} catch (Exception& exception) {
		Console::print(string("TriggerScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
}

void TriggerScreenController::dispose()
{
}

void TriggerScreenController::setScreenCaption(const string& text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void TriggerScreenController::setEntityData(const string& name, const string& description)
{
	entityBaseSubScreenController->setEntityData(name, description);
}

void TriggerScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
}

void TriggerScreenController::setEntityProperties(const string& presetId, const string& selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, selectedName);
}

void TriggerScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void TriggerScreenController::setTrigger(float width, float height, float depth)
{
	triggerWidth->getController()->setDisabled(false);
	triggerWidth->getController()->getValue()->set(Tools::formatFloat(width));
	triggerHeight->getController()->setDisabled(false);
	triggerHeight->getController()->getValue()->set(Tools::formatFloat(height));
	triggerDepth->getController()->setDisabled(false);
	triggerDepth->getController()->getValue()->set(Tools::formatFloat(depth));
	triggerApply->getController()->setDisabled(false);
}

void TriggerScreenController::unsetTrigger()
{
	triggerWidth->getController()->setDisabled(true);
	triggerWidth->getController()->getValue()->set(TEXT_EMPTY);
	triggerHeight->getController()->setDisabled(true);
	triggerHeight->getController()->getValue()->set(TEXT_EMPTY);
	triggerDepth->getController()->setDisabled(true);
	triggerDepth->getController()->getValue()->set(TEXT_EMPTY);
	triggerApply->getController()->setDisabled(true);
}

void TriggerScreenController::onQuit()
{
	TDMEViewer::getInstance()->quit();
}

void TriggerScreenController::onTriggerApply()
{
	try {
		auto width = Float::parseFloat(triggerWidth->getController()->getValue()->getString());
		auto height = Float::parseFloat(triggerHeight->getController()->getValue()->getString());
		auto depth = Float::parseFloat(triggerDepth->getController()->getValue()->getString());
		view->triggerApply(width, height, depth);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TriggerScreenController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void TriggerScreenController::onValueChanged(GUIElementNode* node)
{
	entityBaseSubScreenController->onValueChanged(node, view->getEntity());
}

void TriggerScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
			{
				if (node->getId().compare("button_trigger_apply") == 0) {
					onTriggerApply();
				} else {
					Console::println(
						string(
							"TriggerScreenController::onActionPerformed()::unknown, type='" +
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
