#include <tdme/tools/editor/tabcontrollers/TextureTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
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

using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
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

void TextureTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void TextureTabController::dispose()
{
}

void TextureTabController::onCommand(TabControllerCommand command)
{
	showInfoPopUp("Warning", "This command is not supported yet");
}

void TextureTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	showInfoPopUp("Warning", "You can not drop a file here");
}

void TextureTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void TextureTabController::onChange(GUIElementNode* node)
{
}

void TextureTabController::onFocus(GUIElementNode* node) {
}

void TextureTabController::onUnfocus(GUIElementNode* node) {
}

void TextureTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
}

void TextureTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void TextureTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void TextureTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option text=\"Texture\" value=\"texture\" />\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void TextureTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void TextureTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
}
