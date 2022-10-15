#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/TextEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/StringTools.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TextEditorTabController;

using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TextEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::MiniScript;
using tdme::utilities::StringTools;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

TextEditorTabController::TextEditorTabController(TextEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->view->getTabScreenNode()->addFocusListener(this);
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
	this->view->getTabScreenNode()->removeFocusListener(this);
}

void TextEditorTabController::save()
{
	auto fileName = view->getFileName();
	try {
		if (fileName.empty() == true) throw ExceptionBase("Could not save file. No filename known");
		view->saveFile(
			Tools::getPathName(fileName),
			Tools::getFileName(fileName)
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}

}

void TextEditorTabController::saveAs()
{
	class OnTextSave: public virtual Action
	{
	public:
		void performAction() override {
			try {
				textEditorTabController->view->saveFile(
					textEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
					textEditorTabController->popUps->getFileDialogScreenController()->getFileName()
				);
			} catch (Exception& exception) {
				textEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
			}
			textEditorTabController->popUps->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param textEditorTabController text editor tab controller
		 */
		OnTextSave(TextEditorTabController* textEditorTabController): textEditorTabController(textEditorTabController) {
		}

	private:
		TextEditorTabController* textEditorTabController;
	};

	auto fileName = view->getFileName();
	vector<string> extensions = {
		view->getExtension()
	};
	popUps->getFileDialogScreenController()->show(
		Tools::getPathName(fileName),
		"Save to: ",
		extensions,
		Tools::getFileName(fileName),
		false,
		new OnTextSave(this)
	);
}

void TextEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void TextEditorTabController::onValueChanged(GUIElementNode* node)
{
	if (StringTools::endsWith(node->getId(), "_checkbox_visualcode") == true) {
		auto visual = node->getController()->getValue().equals("1");
		if (visual == true) {
			view->setVisualEditor();
			describeMiniScript();
		} else {
			view->setCodeEditor();
		}
	}
}

void TextEditorTabController::onFocus(GUIElementNode* node) {
	// if a node in this tab gets focussed, invalidate focus in main engine GUI
	if (node->getScreenNode() == view->getTabScreenNode()) {
		Engine::getInstance()->getGUI()->invalidateFocussedNode();
	} else
	// if a node in main engine GUI got focussed, invalidate tab focus
	if (node->getScreenNode() == screenNode) {
		view->getEngine()->getGUI()->invalidateFocussedNode();
	} else {
		Console::println("TextEditorTabController::onFocus(): Unknown screen node");
	}
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

void TextEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void TextEditorTabController::describeMiniScript() {
	auto scriptFileName = view->getFileName();
	//
	MiniScript* scriptInstance = new MiniScript();
	scriptInstance->loadScript(Tools::getPathName(scriptFileName), Tools::getFileName(scriptFileName));

	// TODO: testing: script 0 is hard coded right now
	//	also script conditions need to be select
	vector<MiniScript::StatementDescription> description;
	scriptInstance->describeScript(0, description);

	// pass it to view
	view->setMiniScriptDescription(description);
}

void TextEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
