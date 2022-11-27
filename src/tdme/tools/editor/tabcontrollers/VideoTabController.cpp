#include <tdme/tools/editor/tabcontrollers/VideoTabController.h>

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
#include <tdme/tools/editor/tabviews/VideoTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using tdme::tools::editor::tabcontrollers::VideoTabController;

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
using tdme::tools::editor::tabviews::VideoTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

VideoTabController::VideoTabController(VideoTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

VideoTabController::~VideoTabController() {
}

VideoTabView* VideoTabController::getView() {
	return view;
}

GUIScreenNode* VideoTabController::getScreenNode()
{
	return screenNode;
}

void VideoTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void VideoTabController::dispose()
{
}

void VideoTabController::onCommand(TabControllerCommand command)
{
	showInfoPopUp("Warning", "This command is not supported yet");
}

void VideoTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	Console::println("VideoTabController::onDrop(): " + payload + " @ " + to_string(mouseX) + ", " + to_string(mouseY));
	showInfoPopUp("Warning", "You can not drop a file here");
}

void VideoTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void VideoTabController::onChange(GUIElementNode* node)
{
}

void VideoTabController::onFocus(GUIElementNode* node) {
}

void VideoTabController::onUnfocus(GUIElementNode* node) {
}

void VideoTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
}

void VideoTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int left, top;
	view->getEditorView()->getViewPortUnscaledOffset(left, top);
	popUps->getTooltipScreenController()->show(left + mouseX, top + mouseY, node->getToolTip());
}

void VideoTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void VideoTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option text=\"Video\" value=\"texture\" />\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void VideoTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void VideoTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
}
