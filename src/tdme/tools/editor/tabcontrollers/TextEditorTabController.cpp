#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>

#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/TextEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TextEditorTabController;

using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::utilities::Action;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TextEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

TextEditorTabController::TextEditorTabController(TextEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

TextEditorTabController::~TextEditorTabController() {
}

TextEditorTabView* TextEditorTabController::getView() {
	return view;
}

GUIScreenNode* TextEditorTabController::getScreenNode()
{
	return screenNode;
}

void TextEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void TextEditorTabController::dispose()
{
}

void TextEditorTabController::save()
{
}

void TextEditorTabController::saveAs()
{
}

void TextEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void TextEditorTabController::onValueChanged(GUIElementNode* node)
{
}

void TextEditorTabController::onFocus(GUIElementNode* node) {
}

void TextEditorTabController::onUnfocus(GUIElementNode* node) {
}

void TextEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void TextEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option text=\"Text\" value=\"texture\" />\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void TextEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
