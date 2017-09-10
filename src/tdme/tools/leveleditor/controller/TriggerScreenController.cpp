#include <tdme/tools/leveleditor/controller/TriggerScreenController.h>

#include <string>

#include <java/lang/Float.h>
#include <java/lang/String.h>
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
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using std::wstring;

using tdme::tools::leveleditor::controller::TriggerScreenController;
using java::lang::Float;
using java::lang::String;
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
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
using tdme::utils::_Console;
using tdme::utils::_Exception;

MutableString* TriggerScreenController::TEXT_EMPTY = new MutableString(L"");

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
		screenNode = GUIParser::parse(u"resources/tools/leveleditor/gui"_j, u"screen_trigger.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById(u"screen_caption"_j));
		triggerWidth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"trigger_width"_j));
		triggerHeight = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"trigger_height"_j));
		triggerDepth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"trigger_depth"_j));
		triggerApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_trigger_apply"_j));
	} catch (_Exception& exception) {
		_Console::print(string("TriggerScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
}

void TriggerScreenController::dispose()
{
}

void TriggerScreenController::setScreenCaption(const wstring& text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void TriggerScreenController::setEntityData(const wstring& name, const wstring& description)
{
	entityBaseSubScreenController->setEntityData(name, description);
}

void TriggerScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
}

void TriggerScreenController::setEntityProperties(const wstring& presetId, const wstring& selectedName)
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
		auto width = Float::parseFloat(triggerWidth->getController()->getValue()->toString());
		auto height = Float::parseFloat(triggerHeight->getController()->getValue()->toString());
		auto depth = Float::parseFloat(triggerDepth->getController()->getValue()->toString());
		view->triggerApply(width, height, depth);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
}

void TriggerScreenController::showErrorPopUp(const wstring& caption, const wstring& message)
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
				if (node->getId().compare(L"button_trigger_apply") == 0) {
					onTriggerApply();
				} else {
					_Console::println(
						wstring(
							L"TriggerScreenController::onActionPerformed()::unknown, type='" +
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
