#include <tdme/tools/editor/tabcontrollers/EmptyEditorTabController.h>

#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/EmptyEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using std::string;

using tdme::tools::editor::tabcontrollers::EmptyEditorTabController;

using tdme::utilities::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::EmptyEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

EmptyEditorTabController::EmptyEditorTabController(EmptyEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

EmptyEditorTabController::~EmptyEditorTabController() {
}

EmptyEditorTabView* EmptyEditorTabController::getView() {
	return view;
}

GUIScreenNode* EmptyEditorTabController::getScreenNode()
{
	return screenNode;
}

void EmptyEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void EmptyEditorTabController::dispose()
{
}

void EmptyEditorTabController::save()
{
}

void EmptyEditorTabController::saveAs()
{
}

void EmptyEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void EmptyEditorTabController::onValueChanged(GUIElementNode* node)
{
}

void EmptyEditorTabController::onFocus(GUIElementNode* node) {
}

void EmptyEditorTabController::onUnfocus(GUIElementNode* node) {
}

void EmptyEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void EmptyEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
