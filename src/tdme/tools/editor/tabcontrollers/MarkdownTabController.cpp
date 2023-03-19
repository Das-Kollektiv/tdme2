#include <tdme/tools/editor/tabcontrollers/MarkdownTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/MarkdownTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using tdme::tools::editor::tabcontrollers::MarkdownTabController;

using std::string;

using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::MarkdownTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

MarkdownTabController::MarkdownTabController(MarkdownTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

MarkdownTabController::~MarkdownTabController() {
}

MarkdownTabView* MarkdownTabController::getView() {
	return view;
}

GUIScreenNode* MarkdownTabController::getScreenNode()
{
	return screenNode;
}

void MarkdownTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void MarkdownTabController::dispose()
{
}

void MarkdownTabController::onCommand(TabControllerCommand command)
{
	showInfoPopUp("Warning", "This command is not supported yet");
}

void MarkdownTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	showInfoPopUp("Warning", "You can not drop a file here");
}

void MarkdownTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void MarkdownTabController::onChange(GUIElementNode* node)
{
}

void MarkdownTabController::onFocus(GUIElementNode* node) {
}

void MarkdownTabController::onUnfocus(GUIElementNode* node) {
}

void MarkdownTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
}

void MarkdownTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void MarkdownTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void MarkdownTabController::setOutlinerContent() {
	// TODO: markdown structure
	string xml;
	xml+= "<selectbox-option text=\"Markdown\" value=\"markdown\" />\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void MarkdownTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void MarkdownTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
}
