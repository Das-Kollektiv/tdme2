#include <tdme/tools/editor/tabcontrollers/SceneEditorTabController.h>

#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using std::string;

using tdme::tools::editor::tabcontrollers::SceneEditorTabController;

using tdme::utilities::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::SceneEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

SceneEditorTabController::SceneEditorTabController(SceneEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

SceneEditorTabController::~SceneEditorTabController() {
}

SceneEditorTabView* SceneEditorTabController::getView() {
	return view;
}

GUIScreenNode* SceneEditorTabController::getScreenNode()
{
	return screenNode;
}

void SceneEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void SceneEditorTabController::dispose()
{
}

void SceneEditorTabController::save()
{
}

void SceneEditorTabController::saveAs()
{
}

void SceneEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void SceneEditorTabController::onValueChanged(GUIElementNode* node)
{
}

void SceneEditorTabController::onFocus(GUIElementNode* node) {
}

void SceneEditorTabController::onUnfocus(GUIElementNode* node) {
}

void SceneEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void SceneEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
