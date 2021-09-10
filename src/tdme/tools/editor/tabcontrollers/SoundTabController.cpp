#include <tdme/tools/editor/tabcontrollers/SoundTabController.h>

#include <string>

#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/SoundTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::SoundTabController;

using std::string;

using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
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
using tdme::tools::editor::tabviews::SoundTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

SoundTabController::SoundTabController(SoundTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

SoundTabController::~SoundTabController() {
}

SoundTabView* SoundTabController::getView() {
	return view;
}

GUIScreenNode* SoundTabController::getScreenNode()
{
	return screenNode;
}

void SoundTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void SoundTabController::dispose()
{
}

void SoundTabController::save()
{
}

void SoundTabController::saveAs()
{
}

void SoundTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void SoundTabController::onValueChanged(GUIElementNode* node)
{
}

void SoundTabController::onFocus(GUIElementNode* node) {
}

void SoundTabController::onUnfocus(GUIElementNode* node) {
}

void SoundTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void SoundTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option text=\"Sound\" value=\"texture\" />\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void SoundTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void SoundTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type != GUIActionListenerType::PERFORMED) return;
	if (node->getId() == "play") {
		view->play();
	} else
	if (node->getId() == "stop") {
		view->stop();
	}
}