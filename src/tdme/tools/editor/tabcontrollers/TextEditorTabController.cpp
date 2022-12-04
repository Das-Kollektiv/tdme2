#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/FindReplaceDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/TextEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/StringTools.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TextEditorTabController;

using std::string;
using std::unordered_map;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::logics::LogicMiniScript;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TextEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Integer;
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

void TextEditorTabController::onCommand(TabControllerCommand command)
{
	switch (command) {
		case COMMAND_CUT:
			view->cut();
			break;
		case COMMAND_COPY:
			view->copy();
			break;
		case COMMAND_PASTE:
			view->paste();
			break;
		case COMMAND_DELETE:
			view->delete_();
			break;
		case COMMAND_SELECTALL:
			view->selectAll();
			break;
		case COMMAND_SAVE:
			{
				auto fileName = view->getFileName();
				try {
					if (fileName.empty() == true) throw ExceptionBase("Could not save file. No filename known");
					view->saveFile(
						Tools::getPathName(fileName),
						Tools::getFileName(fileName)
					);
				} catch (Exception& exception) {
					showInfoPopUp("Warning", (string(exception.what())));
				}
			}
			break;
		case COMMAND_SAVEAS:
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
							textEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
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
			break;
		case COMMAND_FINDREPLACE:
			{
				//
				firstSearch = true;
				searchIndex = view->getTextIndex();

				//
				class FindAction: public virtual Action
				{
				public:
					void performAction() override {
						if (textEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText().empty() == true) {
							textEditorTabController->showInfoPopUp("Find", "No find string given.");
						} else {
							if (textEditorTabController->view->find(
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isMatchCase(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isWholeWordOnly(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isInSelectionOnly(),
								textEditorTabController->firstSearch,
								textEditorTabController->searchIndex
							) == false) {
								textEditorTabController->showInfoPopUp("Find", "Text not found.");
							}
							textEditorTabController->firstSearch = false;
						}
					}
					FindAction(TextEditorTabController* textEditorTabController): textEditorTabController(textEditorTabController) {
					}
				private:
					TextEditorTabController* textEditorTabController;
				};
				//
				class CountAction: public virtual Action
				{
				public:
					void performAction() override {
						if (textEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText().empty() == true) {
							textEditorTabController->showInfoPopUp("Count", "No find string given.");
						} else {
							auto count = textEditorTabController->view->count(
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isMatchCase(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isWholeWordOnly(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isInSelectionOnly()
							);
							textEditorTabController->showInfoPopUp("Count", "The text occurred " + to_string(count) + " times.");
						}
					}
					CountAction(TextEditorTabController* textEditorTabController): textEditorTabController(textEditorTabController) {
					}
				private:
					TextEditorTabController* textEditorTabController;
				};
				//
				class ReplaceAction: public virtual Action
				{
				public:
					void performAction() override {
						if (textEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText().empty() == true) {
							textEditorTabController->showInfoPopUp("Replace", "No find string given.");
						} else {
							if (textEditorTabController->view->replace(
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->getReplaceText(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isMatchCase(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isWholeWordOnly(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isInSelectionOnly(),
								textEditorTabController->searchIndex
							) == false) {
								textEditorTabController->showInfoPopUp("Replace", "Text not found.");
							}
						}
					}
					ReplaceAction(TextEditorTabController* textEditorTabController): textEditorTabController(textEditorTabController) {
					}
				private:
					TextEditorTabController* textEditorTabController;
				};
				//
				class ReplaceAllAction: public virtual Action
				{
				public:
					void performAction() override {
						if (textEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText().empty() == true) {
							textEditorTabController->showInfoPopUp("Replace All", "No find string given.");
						} else {
							if (textEditorTabController->view->replaceAll(
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->getReplaceText(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isMatchCase(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isWholeWordOnly(),
								textEditorTabController->popUps->getFindReplaceDialogScreenController()->isInSelectionOnly()
							) == false) {
								textEditorTabController->showInfoPopUp("Replace All", "Text not found.");
							}
						}
					}
					ReplaceAllAction(TextEditorTabController* textEditorTabController): textEditorTabController(textEditorTabController) {
					}
				private:
					TextEditorTabController* textEditorTabController;
				};
				//
				class CompleteAction: public virtual Action
				{
				public:
					void performAction() override {
						textEditorTabController->view->cancelFind();
						textEditorTabController->popUps->getFindReplaceDialogScreenController()->close();
					}
					CompleteAction(TextEditorTabController* textEditorTabController): textEditorTabController(textEditorTabController) {
					}
				private:
					TextEditorTabController* textEditorTabController;
				};
				//
				popUps->getFindReplaceDialogScreenController()->show(
					new FindAction(this),
					new CountAction(this),
					new ReplaceAction(this),
					new ReplaceAllAction(this),
					new CompleteAction(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void TextEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	Console::println("TextEditorTabController::onDrop(): " + payload + " @ " + to_string(mouseX) + ", " + to_string(mouseY));
	showInfoPopUp("Warning", "You can not drop a file here");
}

void TextEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void TextEditorTabController::onChange(GUIElementNode* node)
{
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "miniscript.script.") == true) {
			auto scriptIdx = Integer::parse(StringTools::substring(outlinerNode, string("miniscript.script.").size()));
			if (view->isVisualEditor() == true) {
				updateMiniScriptSyntaxTree(scriptIdx);
			} else {
				// TODO: jump to line
			}
		}
	} else
	if (node->getId() == view->getTabId() + "_tab_checkbox_visualcode" == true) {
		auto visual = node->getController()->getValue().equals("1");
		if (visual == true) {
			view->setVisualEditor();
			updateMiniScriptSyntaxTree(view->getMiniScriptScriptIdx());
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

void TextEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
}

void TextEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void TextEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void TextEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"MiniScript\" value=\"miniscript.script." + to_string(-1) + "\">\n";
	auto scriptIdx = 0;
	for (auto& miniScriptSyntaxTree: miniScriptSyntaxTrees) {
		xml+= "<selectbox-option text=\"" + GUIParser::escapeQuotes(miniScriptSyntaxTree.name) + "\" value=\"miniscript.script." + to_string(scriptIdx) + "\" />\n";
		scriptIdx++;
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void TextEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void TextEditorTabController::updateMiniScriptSyntaxTree(int miniScriptScriptIdx) {
	auto scriptFileName = view->getFileName();
	//
	LogicMiniScript* scriptInstance = new LogicMiniScript();
	scriptInstance->loadScript(Tools::getPathName(scriptFileName), Tools::getFileName(scriptFileName));

	//
	unordered_map<string, string> methodOperatorMap;
	for (auto operatorMethod: scriptInstance->getOperatorMethods()) {
		methodOperatorMap[operatorMethod->getMethodName()] = MiniScript::getOperatorAsString(operatorMethod->getOperator());
	}

	//
	auto scriptIdx = 0;
	miniScriptSyntaxTrees.clear();
	for (auto script: scriptInstance->getScripts()) {
		// determine name
		string name;
		string argumentsString;
		switch(script.scriptType) {
			case MiniScript::Script::SCRIPTTYPE_FUNCTION: {
				for (auto& argument: script.arguments) {
					if (argumentsString.empty() == false) argumentsString+= ", ";
					if (argument.assignBack == true) argumentsString+= "=";
					argumentsString+= argument.name;
				}
				argumentsString = "(" + argumentsString + ")";
				name+= "function: "; break;
			}
			case MiniScript::Script::SCRIPTTYPE_ON: name+= "on: "; break;
			case MiniScript::Script::SCRIPTTYPE_ONENABLED: name+= "on-enabled: "; break;
		}
		if (script.name.empty() == false) {
			name+= script.name;
		} else
		if (script.condition.empty() == false)
			name+= script.condition + (argumentsString.empty() == false?": " + argumentsString:"");
		//
		miniScriptSyntaxTrees.push_back(
			{
				.type = script.scriptType,
				.condition = script.condition,
				.name = name,
				.conditionSyntaxTree = script.conditionSyntaxTree,
				.syntaxTree = script.syntaxTree
			}
		);

		//
		scriptIdx++;
	}

	// pass it to view
	view->setMiniScriptMethodOperatorMap(methodOperatorMap);
	view->updateMiniScriptSyntaxTree(miniScriptScriptIdx);

	//
	setOutlinerContent();
}

void TextEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
}

void TextEditorTabController::closeFindReplaceWindow() {
	popUps->getFindReplaceDialogScreenController()->close();
}
