#include <tdme/tools/leveleditor/controller/EmptyScreenController.h>

#include <string>

#include <java/lang/String.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/tools/leveleditor/controller/EmptyScreenController_EmptyScreenController_1.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/viewer/TDMEViewer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using std::wstring;

using tdme::tools::leveleditor::controller::EmptyScreenController;
using java::lang::String;
using tdme::gui::GUIParser;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::leveleditor::controller::EmptyScreenController_EmptyScreenController_1;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::viewer::TDMEViewer;
using tdme::utils::MutableString;
using tdme::utils::_Console;
using tdme::utils::_Exception;

MutableString* EmptyScreenController::TEXT_EMPTY = new MutableString(L"");

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
		screenNode = GUIParser::parse(u"resources/tools/leveleditor/gui"_j, u"screen_empty.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById(u"screen_caption"_j));
	} catch (_Exception& exception) {
		_Console::print(string("EmptyScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
}

void EmptyScreenController::dispose()
{
}

void EmptyScreenController::setScreenCaption(const wstring& text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void EmptyScreenController::setEntityData(const wstring& name, const wstring& description)
{
	entityBaseSubScreenController->setEntityData(name, description);
}

void EmptyScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
}

void EmptyScreenController::setEntityProperties(const wstring& presetId, const wstring& selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, selectedName);
}

void EmptyScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void EmptyScreenController::onQuit()
{
	TDMEViewer::getInstance()->quit();
}

void EmptyScreenController::showErrorPopUp(const wstring& caption, const wstring& message)
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
