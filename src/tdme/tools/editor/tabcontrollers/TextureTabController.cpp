#include <tdme/tools/editor/tabcontrollers/TextureTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/TextureTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using tdme::tools::editor::tabcontrollers::TextureTabController;

using std::string;

using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TextureTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

TextureTabController::TextureTabController(TextureTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

TextureTabController::~TextureTabController() {
}

TextureTabView* TextureTabController::getView() {
	return view;
}

GUIScreenNode* TextureTabController::getScreenNode()
{
	return screenNode;
}

void TextureTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void TextureTabController::dispose()
{
}

void TextureTabController::executeCommand(TabControllerCommand command)
{
	showErrorPopUp("Warning", "This command is not supported yet");
}

void TextureTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void TextureTabController::onValueChanged(GUIElementNode* node)
{
}

void TextureTabController::onFocus(GUIElementNode* node) {
}

void TextureTabController::onUnfocus(GUIElementNode* node) {
}

void TextureTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void TextureTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option text=\"Texture\" value=\"texture\" />\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void TextureTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void TextureTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
