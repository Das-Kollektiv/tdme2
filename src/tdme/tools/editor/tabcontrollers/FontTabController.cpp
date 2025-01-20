#include <tdme/tools/editor/tabcontrollers/FontTabController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>

#include <tdme/tdme.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/FontTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::FontTabController;

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
using tdme::tools::editor::tabviews::FontTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

FontTabController::FontTabController(FontTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

FontTabController::~FontTabController() {
}

void FontTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void FontTabController::dispose()
{
}

void FontTabController::onCommand(TabControllerCommand command)
{
	showInfoPopUp("Warning", "This command is not supported yet");
}

void FontTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	showInfoPopUp("Warning", "You can not drop a file here");
}

void FontTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void FontTabController::onChange(GUIElementNode* node)
{
}

void FontTabController::onFocus(GUIElementNode* node) {
}

void FontTabController::onUnfocus(GUIElementNode* node) {
}

void FontTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
}

void FontTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void FontTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void FontTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option text=\"Font\" value=\"font\" />\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void FontTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void FontTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
}
