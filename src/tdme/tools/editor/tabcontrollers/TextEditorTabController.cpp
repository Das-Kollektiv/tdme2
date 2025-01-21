#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>

#include <array>
#include <memory>
#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/scripting/GUIMinitScript.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicMinitScript.h>
#include <tdme/engine/tools/FileSystemTools.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Texture.h>
#include <tdme/minitscript/EngineMinitScript.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/FindReplaceDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/TextEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TextEditorTabController;

using std::array;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::unordered_map;

using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::scripting::GUIMinitScript;
using agui::gui::GUI;
using agui::gui::GUIParser;

using tdme::engine::logics::LogicMinitScript;
using tdme::engine::tools::FileSystemTools;
using tdme::engine::Engine;
using tdme::engine::Texture;
using tdme::minitscript::EngineMinitScript;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TextEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

TextEditorTabController::TextEditorTabController(TextEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->view->getTabScreenNode()->addChangeListener(this);
	this->view->getTabScreenNode()->addActionListener(this);
	this->view->getTabScreenNode()->addFocusListener(this);
}

TextEditorTabController::~TextEditorTabController() {
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
		case COMMAND_REDO:
			view->redo();
			break;
		case COMMAND_UNDO:
			view->undo();
			break;
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
						FileSystemTools::getPathName(fileName),
						FileSystemTools::getFileName(fileName)
					);
				} catch (Exception& exception) {
					showInfoPopUp("Warning", string(exception.what()));
				}
			}
			break;
		case COMMAND_SAVEAS:
			{
				class OnTextSave: public Action
				{
				public:
					void performAction() override {
						try {
							textEditorTabController->view->saveFile(
								textEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								textEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							textEditorTabController->showInfoPopUp("Warning", string(exception.what()));
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
					FileSystemTools::getPathName(fileName),
					"Save to: ",
					extensions,
					FileSystemTools::getFileName(fileName),
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
				class FindAction: public Action
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
				class CountAction: public Action
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
				class ReplaceAction: public Action
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
				class ReplaceAllAction: public Action
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
				class CompleteAction: public Action
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
		if (StringTools::startsWith(outlinerNode, "minitscript.script.") == true) {
			auto scriptIdx = Integer::parse(StringTools::substring(outlinerNode, string("minitscript.script.").size()));
			if (view->isVisualEditor() == true) {
				updateMinitScriptSyntaxTree(scriptIdx);
			} else {
				// TODO: jump to line
			}
		}
	} else
	if (node->getId() == view->getTabId() + "_tab_checkbox_visualcode" == true) {
		auto visual = node->getController()->getValue().equals("1");
		if (visual == true) {
			view->setVisualEditor();
			updateMinitScriptSyntaxTree(view->getMinitScriptScriptIdx());
		} else {
			view->setCodeEditor();
		}
	}
}

void TextEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
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
		Console::printLine("TextEditorTabController::onFocus(): Unknown screen node");
	}
}

void TextEditorTabController::onUnfocus(GUIElementNode* node) {
}

void TextEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	if (view->isVisualEditor() == false) return;
	//
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, contextMenuX, contextMenuY) == false) return;
	//
	auto nodeValue = node->getValue();
	//
	if (StringTools::startsWith(nodeValue, "node_") == true) {
		contextMenuType = CONTEXTMENUTYPE_NODE;
		contextMenuNodeId = StringTools::substring(nodeValue, string("node_").size());
	} else
	if (contextMenuType != CONTEXTMENUTYPE_NODE) {
		//
		contextMenuType = CONTEXTMENUTYPE_CANVAS;
		addNodeX = mouseX;
		addNodeY = mouseY;

	}
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
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"EngineMinitScript\" value=\"minitscript.script." + to_string(-1) + "\">\n";
	auto scriptIdx = 0;
	for (const auto& minitScriptSyntaxTree: minitScriptSyntaxTrees) {
		xml+= "<selectbox-option text=\"" + GUIParser::escape(minitScriptSyntaxTree.name) + "\" value=\"minitscript.script." + to_string(scriptIdx) + "\" />\n";
		scriptIdx++;
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void TextEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void TextEditorTabController::updateMinitScriptSyntaxTree(int minitScriptScriptIdx) {
	auto scriptFileName = view->getFileName();

	// we need to detect EngineMinitScript variant
	vector<string> scriptAsStringArray;
	try {
		FileSystem::getInstance()->getContentAsStringArray(FileSystemTools::getPathName(scriptFileName), FileSystemTools::getFileName(scriptFileName), scriptAsStringArray);
	} catch (Exception& exception) {
		minitScriptSyntaxTrees.clear();
		view->setMinitScriptMethodOperatorMap({});
		view->updateMinitScriptSyntaxTree(minitScriptScriptIdx);
		//
		showInfoPopUp("Warning", "Could not load script");
		//
		return;
	}

	// load specific EngineMinitScript
	scriptInstance = unique_ptr<MinitScript>(EngineMinitScript::loadScript(FileSystemTools::getPathName(scriptFileName), FileSystemTools::getFileName(scriptFileName)));

	//
	if (scriptInstance->isValid() == false)  {
		scriptInstance = nullptr;
		minitScriptSyntaxTrees.clear();
		view->setMinitScriptMethodOperatorMap({});
		view->updateMinitScriptSyntaxTree(minitScriptScriptIdx);
		//
		showInfoPopUp("Warning", "Could not load script. Script not valid!");
		//
		return;
	}

	//
	unordered_map<string, string> methodOperatorMap;
	for (auto operatorMethod: scriptInstance->getOperatorMethods()) {
		methodOperatorMap[operatorMethod->getMethodName()] = EngineMinitScript::getOperatorAsString(operatorMethod->getOperator());
	}

	//
	auto scriptIdx = 0;
	minitScriptSyntaxTrees.clear();
	for (auto script: scriptInstance->getScripts()) {
		// determine name
		string name;
		string argumentsString;
		switch(script.type) {
			case EngineMinitScript::Script::TYPE_FUNCTION: {
				for (const auto& argument: script.arguments) {
					if (argumentsString.empty() == false) argumentsString+= ", ";
					if (argument.reference == true) argumentsString+= "=";
					argumentsString+= argument.name;
				}
				argumentsString = "(" + argumentsString + ")";
				name+= "function: "; break;
			}
			case EngineMinitScript::Script::TYPE_ON: name+= "on: "; break;
			case EngineMinitScript::Script::TYPE_ONENABLED: name+= "on-enabled: "; break;
		}
		if (script.name.empty() == false) {
			name+= script.name;
		} else
		if (script.condition.empty() == false)
			name+= script.condition + (argumentsString.empty() == false?": " + argumentsString:"");
		//
		minitScriptSyntaxTrees.push_back(
			{
				.type = script.type,
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
	view->setMinitScriptMethodOperatorMap(methodOperatorMap);
	view->updateMinitScriptSyntaxTree(minitScriptScriptIdx);

	//
	setOutlinerContent();
}

void TextEditorTabController::closeFindReplaceWindow() {
	popUps->getFindReplaceDialogScreenController()->close();
}
