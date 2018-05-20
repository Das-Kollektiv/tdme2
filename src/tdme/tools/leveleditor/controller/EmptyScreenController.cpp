#include <tdme/tools/leveleditor/controller/EmptyScreenController.h>

#include <string>

#include <tdme/gui/GUIParser.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/tools/leveleditor/controller/EmptyScreenController_EmptyScreenController_1.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/modeleditor/TDMEModelEditor.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::string;

using tdme::tools::leveleditor::controller::EmptyScreenController;
using tdme::gui::GUIParser;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::leveleditor::controller::EmptyScreenController_EmptyScreenController_1;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::viewer::TDMEModelEditor;
using tdme::utils::MutableString;
using tdme::utils::Console;
using tdme::utils::Exception;

EmptyScreenController::EmptyScreenController(EmptyView* view) 
{
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new EmptyScreenController_EmptyScreenController_1(this, finalView));
}

GUIScreenNode* EmptyScreenController::getScreenNode()
{
	return screenNode;
}

void EmptyScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/tools/leveleditor/gui", "screen_empty.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById("screen_caption"));
	} catch (Exception& exception) {
		Console::print(string("EmptyScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
}

void EmptyScreenController::dispose()
{
}

void EmptyScreenController::setScreenCaption(const string& text)
{
	screenCaption->setText(text);
	screenNode->layout(screenCaption);
}

void EmptyScreenController::setEntityData(const string& name, const string& description)
{
	entityBaseSubScreenController->setEntityData(name, description);
}

void EmptyScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
}

void EmptyScreenController::setEntityProperties(const string& presetId, const string& selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, selectedName);
}

void EmptyScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void EmptyScreenController::onQuit()
{
	TDMEModelEditor::getInstance()->quit();
}

void EmptyScreenController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void EmptyScreenController::onValueChanged(GUIElementNode* node)
{
	entityBaseSubScreenController->onValueChanged(node, view->getEntity());
}

void EmptyScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
}
