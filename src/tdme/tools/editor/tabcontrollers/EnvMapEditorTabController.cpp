#include <tdme/tools/editor/tabcontrollers/EnvMapEditorTabController.h>

#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/EnvMapEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using std::string;

using tdme::tools::editor::tabcontrollers::EnvMapEditorTabController;

using tdme::utilities::Action;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::EnvMapEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

EnvMapEditorTabController::EnvMapEditorTabController(EnvMapEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

EnvMapEditorTabController::~EnvMapEditorTabController() {
}

EnvMapEditorTabView* EnvMapEditorTabController::getView() {
	return view;
}

GUIScreenNode* EnvMapEditorTabController::getScreenNode()
{
	return screenNode;
}

void EnvMapEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void EnvMapEditorTabController::dispose()
{
}

void EnvMapEditorTabController::save()
{
}

void EnvMapEditorTabController::saveAs()
{
}

void EnvMapEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void EnvMapEditorTabController::onValueChanged(GUIElementNode* node)
{
}

void EnvMapEditorTabController::onFocus(GUIElementNode* node) {
}

void EnvMapEditorTabController::onUnfocus(GUIElementNode* node) {
}

void EnvMapEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void EnvMapEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}

void EnvMapEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\" />\n";
	view->getEditorView()->setOutlinerContent(xml);}

void EnvMapEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Property\" value=\"property\" />\n")
	);
}

void EnvMapEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
}
