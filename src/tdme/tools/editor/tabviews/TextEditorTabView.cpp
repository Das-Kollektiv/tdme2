#include <tdme/tools/editor/tabviews/TextEditorTabView.h>

#include <algorithm>
#include <cctype>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIFrameBufferNode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/StringTools.h>

using std::sort;
using std::string;

using tdme::tools::editor::tabviews::TextEditorTabView;

using tdme::engine::model::Color4;
using tdme::engine::Engine;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIFrameBufferNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::tabcontrollers::TextEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::StringTools;

TextEditorTabView::TextEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& fileName)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->tabScreenNode = screenNode;
	this->extension = extension;
	this->textNode = required_dynamic_cast<GUIStyledTextNode*>(screenNode->getInnerNodeById("text"));
	this->fileName = fileName;
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);
	this->extension = StringTools::substring(fileNameLowerCase, fileNameLowerCase.rfind('.') + 1, fileNameLowerCase.size());
	engine = Engine::createOffScreenInstance(512, 512, false, false, false);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
	// enable code mode
	setCodeEditor();

	// initial text format
	TextFormatter::getInstance()->format(extension, textNode);
	// load code completion
	codeCompletion = TextFormatter::getInstance()->loadCodeCompletion(extension);

	//
	{
		// add text node change listener
		class TextChangeListener: public GUIStyledTextNodeController::ChangeListener {
		public:
			TextChangeListener(TextEditorTabView* textEditorTabView): textEditorTabView(textEditorTabView) {
			}

			virtual ~TextChangeListener() {
			}

			virtual void onRemoveText(int idx, int count) override {
				TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, idx, idx + count);
			}
			virtual void onInsertText(int idx, int count) override {
				TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, idx, idx + count);
			}
		private:
			TextEditorTabView* textEditorTabView;
		};
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->addChangeListener(textNodeChangeListener = new TextChangeListener(this));
	}

	//
	{
		// add code completion listener
		class TextCodeCompletionListener: public GUIStyledTextNodeController::CodeCompletionListener {
		public:
			TextCodeCompletionListener(TextEditorTabView* textEditorTabView): textEditorTabView(textEditorTabView) {
			}

			virtual ~TextCodeCompletionListener() {
			}

			virtual void onCodeCompletion(int idx) override {
				auto codeCompletion = textEditorTabView->codeCompletion;
				if (codeCompletion == nullptr) return;
				if (codeCompletion->delimiters.find(textEditorTabView->textNode->getText().getCharAt(idx)) != string::npos) {
					if (idx > 0) idx--;
				}
				auto previousDelimiterPos = textEditorTabView->textNode->getPreviousDelimiter(idx, codeCompletion->delimiters);
				string search = StringTools::substring(textEditorTabView->textNode->getText().getString(), previousDelimiterPos == 0?0:previousDelimiterPos + 1, idx);
				vector<CodeCompletionSymbol> codeCompletionSymbolCandidates;
				#define MAX_ENTRIES	40
				for (auto& symbol: codeCompletion->symbols) {
					if (StringTools::startsWith(symbol.name, search) == true) {
						if (symbol.overloadList.empty() == true) {
							if (codeCompletionSymbolCandidates.size() == MAX_ENTRIES) {
								codeCompletionSymbolCandidates.push_back(
									{
										.type = CodeCompletionSymbol::TYPE_NONE,
										.display = "...",
										.name = {},
										.parameters = {},
										.returnValue = {}
									}
								);
								break;
							} else {
								codeCompletionSymbolCandidates.push_back(
									{
										.type = CodeCompletionSymbol::TYPE_SYMBOL,
										.display = symbol.name,
										.name = symbol.name,
										.parameters = {},
										.returnValue = {}
									}
								);
							}
						} else {
							for (auto& overload: symbol.overloadList) {
								if (codeCompletionSymbolCandidates.size() == MAX_ENTRIES) {
									codeCompletionSymbolCandidates.push_back(
										{
											.type = CodeCompletionSymbol::TYPE_NONE,
											.display = "...",
											.name = {},
											.parameters = {},
											.returnValue = {}
										}
									);
									break;
								} else {
									string parameters;
									for (auto& parameter: overload.parameters) {
										if (parameters.empty() == false) parameters+= ", ";
										parameters+= parameter;
									}
									codeCompletionSymbolCandidates.push_back(
										{
											.type = CodeCompletionSymbol::TYPE_FUNCTION,
											.display = symbol.name + "(" + parameters + ") = " + overload.returnValue,
											.name = symbol.name,
											.parameters = overload.parameters,
											.returnValue = overload.returnValue
										}
									);
								}
							}
							if (codeCompletionSymbolCandidates.size() == MAX_ENTRIES + 1) break;
						}
					}
				}
				auto popUps = textEditorTabView->getPopUps();
				// clear
				popUps->getContextMenuScreenController()->clear();
				//
				sort(codeCompletionSymbolCandidates.begin(), codeCompletionSymbolCandidates.begin() + (Math::min(codeCompletionSymbolCandidates.size(), MAX_ENTRIES)), compareCodeCompletionStruct);
				//
				{
					auto i = 0;
					for (auto& codeCompletionSymbolCandidate: codeCompletionSymbolCandidates) {
						// add light
						class OnCodeCompletionAction: public virtual Action
						{
						public:
							OnCodeCompletionAction(TextEditorTabView* textEditorTabView, int idx, const CodeCompletionSymbol& symbol): textEditorTabView(textEditorTabView), idx(idx), symbol(symbol) {}
							void performAction() override {
								if (symbol.name.empty() == true) return;
								auto codeCompletion = textEditorTabView->codeCompletion;
								if (codeCompletion == nullptr) return;
								auto previousDelimiterPos = textEditorTabView->textNode->getPreviousDelimiter(idx, codeCompletion->delimiters);
								auto nextDelimiterPos = textEditorTabView->textNode->getNextDelimiter(idx, codeCompletion->delimiters);
								auto withoutWhiteSpaceDelimiters = codeCompletion->delimiters;
								if (withoutWhiteSpaceDelimiters.find(' ') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find(' '), 1);
								if (withoutWhiteSpaceDelimiters.find('\t') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find('\t'), 1);
								if (withoutWhiteSpaceDelimiters.find('\n') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find('\n'), 1);
								auto nextDelimiterPos2 = textEditorTabView->textNode->getNextDelimiter(idx, withoutWhiteSpaceDelimiters);
								auto idxToDelimiterString = StringTools::trim(StringTools::substring(textEditorTabView->textNode->getText().getString(), idx + 1 < textEditorTabView->textNode->getTextLength()?idx + 1:idx, nextDelimiterPos2));
								string parameterString;
								if (symbol.type == CodeCompletionSymbol::TYPE_FUNCTION && textEditorTabView->textNode->getText().getCharAt(nextDelimiterPos2) != '(') {
									for (auto parameter: symbol.parameters) {
										auto parameterTokenized = StringTools::tokenize(parameter, " \t\n");
										if (parameterString.empty() == false) parameterString+= ", ";
										parameterString+= parameterTokenized[parameterTokenized.size() - 1];
									}
									parameterString = "(" + parameterString + ")"/* + codeCompletion->statementDelimiter*/;
								}
								textEditorTabView->textNode->removeText(previousDelimiterPos == 0?0:previousDelimiterPos + 1, nextDelimiterPos - (previousDelimiterPos == 0?0:previousDelimiterPos + 1));
								textEditorTabView->textNode->insertText(previousDelimiterPos == 0?0:previousDelimiterPos + 1, symbol.name + parameterString);
								TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, previousDelimiterPos == 0?0:previousDelimiterPos + 1, (previousDelimiterPos == 0?0:previousDelimiterPos + 1) + symbol.name.size() + parameterString.size());
							}
						private:
							TextEditorTabView* textEditorTabView;
							int idx;
							CodeCompletionSymbol symbol;
						};
						popUps->getContextMenuScreenController()->addMenuItem(codeCompletionSymbolCandidate.display, "contextmenu_codecompletion_" + to_string(i), new OnCodeCompletionAction(textEditorTabView, idx, codeCompletionSymbolCandidate));
						//
						i++;
					}
				}
				if (codeCompletionSymbolCandidates.empty() == false) {
					//
					int left, top, width, height;
					auto selectedTab = textEditorTabView->getEditorView()->getScreenController()->getSelectedTab();
					if (selectedTab != nullptr) {
						textEditorTabView->getEditorView()->getViewPort(selectedTab->getFrameBufferNode(), left, top, width, height);
						popUps->getContextMenuScreenController()->show(
							left + textEditorTabView->textNode->getIndexPositionX() - textEditorTabView->textNode->computeParentChildrenRenderOffsetXTotal(),
							top + textEditorTabView->textNode->getIndexPositionY() - textEditorTabView->textNode->computeParentChildrenRenderOffsetYTotal()
						);
					}
				}
			}
		private:
			TextEditorTabView* textEditorTabView;
		};
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->addCodeCompletionListener(textNodeCodeCompletionListener = new TextCodeCompletionListener(this));
	}
}

TextEditorTabView::~TextEditorTabView() {
	delete textEditorTabController;
	delete engine;
	delete textNodeChangeListener;
	delete textNodeCodeCompletionListener;
	if (codeCompletion != nullptr) delete codeCompletion;
}

void TextEditorTabView::saveFile(const string& pathName, const string& fileName) {
	auto text = textNode->getText().getString();
	FileSystem::getStandardFileSystem()->setContentFromString(
		pathName,
		fileName,
		text
	);
}

void TextEditorTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void TextEditorTabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void TextEditorTabView::initialize()
{
	try {
		textEditorTabController = new TextEditorTabController(this);
		textEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::print(string("TextEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
}

void TextEditorTabView::dispose()
{
	required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->removeChangeListener(textNodeChangeListener);
	engine->dispose();
}

void TextEditorTabView::updateRendering() {
}

Engine* TextEditorTabView::getEngine() {
	return engine;
}

void TextEditorTabView::activate() {
	textEditorTabController->setOutlinerAddDropDownContent();
	textEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void TextEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void TextEditorTabView::reloadOutliner() {
	textEditorTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

void TextEditorTabView::setVisualEditor() {
	auto editorNode = dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen(tabScreenNode->getId())->getNodeById("editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("visualization");
}

void TextEditorTabView::setCodeEditor() {
	auto editorNode = dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen(tabScreenNode->getId())->getNodeById("editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("text");
}

void TextEditorTabView::addNodeDeltaX(const string& id, const MiniScript::StatementDescription& description, GUIParentNode* parentNode, int deltaX) {
	auto node = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("d" + id));
	node->getRequestsConstraints().left+= deltaX;
	for (auto i = 0; i < description.arguments.size(); i++) {
		addNodeDeltaX(id + "." + to_string(i), description.arguments[i], parentNode, deltaX);
	}
}

void TextEditorTabView::createNodes(const string& id, const MiniScript::StatementDescription& description, GUIParentNode* parentNode, int x, int y, int& width, int& height, int depth) {
	//
	int childMaxWidth = 0;
	for (auto i = 0; i < description.arguments.size(); i++) {
		auto childWidth = 0;
		auto childHeight = 0;
		createNodes(id + "." + to_string(i), description.arguments[i], parentNode, x, y, childWidth, childHeight, depth + 1);
		if (childWidth > childMaxWidth) childMaxWidth = childWidth;
		y+= childHeight;
		height+= childHeight;
	}
	//
	x+= childMaxWidth;
	width+= childMaxWidth;

	//
	string xml;
	xml+= "<layout id='d" + id + "' left='" + to_string(x) + "' top='" + to_string(y) + "' padding='5' width='auto' height='auto' alignment='vertical' background-color='#606060' border-color='black' border='1'>";
	switch (description.type) {
		case MiniScript::StatementDescription::STATEMENTDESCRIPTION_EXECUTE_METHOD:
		case MiniScript::StatementDescription::STATEMENTDESCRIPTION_EXECUTE_FUNCTION:
			{
				xml+= "<text id='d" + id + "_title' font='{$font.default}' size='{$fontsize.default}' text='" + GUIParser::escapeQuotes(description.value) + "()' color='{$color.font_normal}' />";
				xml+= "<space width='100%' height='5' />";
				xml+= "<space height='1' width='100%' border-top='1' border-color='#202020' />";
				xml+= "<space width='100%' height='5' />";
				auto argumentIdx = 0;
				if (description.method != nullptr) {
					auto& argumentTypes = description.method->getArgumentTypes();
					for (argumentIdx = 0; argumentIdx < argumentTypes.size(); argumentIdx++) {
						xml+= "<text id='d" + id + "_a" + to_string(argumentIdx) + "' font='{$font.default}' size='{$fontsize.default}' text='" + argumentTypes[argumentIdx].name + ": " + MiniScript::ScriptVariable::getTypeAsString(argumentTypes[argumentIdx].type)+ "' color='{$color.font_normal}' />";
					}
				}
				for (; argumentIdx < description.arguments.size(); argumentIdx++) {
					xml+= "<text id='d" + id + "_a" + to_string(argumentIdx) + "' font='{$font.default}' size='{$fontsize.default}' text='Argument " + to_string(argumentIdx) + "' color='{$color.font_normal}' />";
				}
				break;
			}
		case MiniScript::StatementDescription::STATEMENTDESCRIPTION_LITERAL:
			{
				xml+= "<text id='d" + id + "_title' font='{$font.default}' size='{$fontsize.default}' text='Literal' color='{$color.font_normal}' />";
				xml+= "<space width='100%' height='5' />";
				xml+= "<space height='1' width='100%' border-top='1' border-color='#202020' />";
				xml+= "<space width='100%' height='5' />";
				xml+= "<text id='" + id + "_value' font='{$font.default}' size='{$fontsize.default}' text='" + GUIParser::escapeQuotes(description.value) + "' color='{$color.font_normal}' />";
				break;
			}
	}
	if (depth == 0) {
		xml+= "<space width='100%' height='5' />";
		xml+= "<space height='1' width='100%' border-top='1' border-color='#202020' />";
		xml+= "<space width='100%' height='5' />";
		xml+= "<text id='d" + id + "_flow' font='{$font.default}' size='{$fontsize.default}' text='Flow' color='{$color.font_normal}' width='100%' horizontal-align='right'/>";
	}
	xml+= "</layout>";

	try {
		GUIParser::parse(parentNode, xml);
	} catch (Exception& exception) {
		Console::println("TextEditorTabView::visualizeDescription(): " + string(exception.what()));
	}

	//
	auto node = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("d" + id));
	width+= 200; //node->getContentWidth();
	height+= 100; //node->getContentHeight();

	// post layout, move first level child argument nodes from from left to right according to the closest one
	auto rootDistanceMax = Integer::MAX_VALUE;
	auto nextLevelXBestFit = -1;
	for (auto i = 0; i < description.arguments.size(); i++) {
		auto nextLevelNode = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("d" + id + "." + to_string(i)));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto rootDistance = Math::abs(x - nodeXPosition);
		if (rootDistance < rootDistanceMax) {
			rootDistanceMax = rootDistance;
			nextLevelXBestFit = nodeXPosition;
		}
	}
	for (auto i = 0; i < description.arguments.size(); i++) {
		auto subNodeId = id + "." + to_string(i);
		auto nextLevelNode = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("d" + id + "." + to_string(i)));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto deltaX = nextLevelXBestFit - nodeXPosition;
		if (deltaX == 0) continue;
		addNodeDeltaX(subNodeId, description.arguments[i], parentNode, deltaX);
	}
}

void TextEditorTabView::setMiniScriptDescription(const vector<MiniScript::StatementDescription>& description) {
	this->description = description;
	auto visualisationNode = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("visualization"));
	auto x = 200;
	auto y = 200;
	for (auto i = 0; i < description.size(); i++) {
		auto width = 0;
		auto height = 0;
		createNodes(to_string(i), description[i], visualisationNode, x, y, width, height);
		x+= width + 100;
	}
}
