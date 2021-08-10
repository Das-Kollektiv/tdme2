#include <tdme/tools/editor/tabcontrollers/UITabController.h>

#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/UITabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using std::string;

using tdme::tools::editor::tabcontrollers::UITabController;

using tdme::utilities::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::UITabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

UITabController::UITabController(UITabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

UITabController::~UITabController() {
}

UITabView* UITabController::getView() {
	return view;
}

GUIScreenNode* UITabController::getScreenNode()
{
	return screenNode;
}

void UITabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void UITabController::dispose()
{
}

void UITabController::save()
{
}

void UITabController::saveAs()
{
}

void UITabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void UITabController::onValueChanged(GUIElementNode* node)
{
}

void UITabController::onFocus(GUIElementNode* node) {
}

void UITabController::onUnfocus(GUIElementNode* node) {
}

void UITabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void UITabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
