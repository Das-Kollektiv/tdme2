#include <tdme/tools/editor/tabviews/TextEditorTabView.h>

#include <algorithm>
#include <cctype>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIFrameBufferNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>

using std::sort;
using std::string;

using tdme::tools::editor::tabviews::TextEditorTabView;

using tdme::engine::model::Color4;
using tdme::engine::Engine;
using tdme::gui::nodes::GUIFrameBufferNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::tabcontrollers::TextEditorTabController;
using tdme::tools::editor::views::EditorView;

TextEditorTabView::TextEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& extension)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->tabScreenNode = screenNode;
	this->extension = extension;
	this->textNode = required_dynamic_cast<GUIStyledTextNode*>(screenNode->getInnerNodeById("text"));
	engine = Engine::createOffScreenInstance(512, 512, false, false, false);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());

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
				auto previousDelimiterPos = textEditorTabView->textNode->getPreviousDelimiter(idx, codeCompletion->delimiters);
				string search = StringTools::substring(textEditorTabView->textNode->getText().getString(), previousDelimiterPos == 0?0:previousDelimiterPos + 1, idx);
				vector<string> codeCompletionCandidates;
				Console::println("TextCodeCompletionListener::onCodeCompletion() @ " + to_string(idx) + "; searching for: " + search);
				for (auto& symbol: codeCompletion->symbols) {
					if (StringTools::startsWith(symbol.name, search) == true) {
						if (symbol.overloadList.empty() == true) {
							codeCompletionCandidates.push_back(symbol.name);
						} else {
							for (auto& overload: symbol.overloadList) {
								string parameters;
								for (auto& parameter: overload.parameters) {
									if (parameters.empty() == false) parameters+= ", ";
									parameters+= parameter;
								}
								codeCompletionCandidates.push_back(symbol.name + "(" + parameters + ") = " + overload.returnValue);
							}
						}
					}
				}
				auto popUps = textEditorTabView->getPopUps();
				// clear
				popUps->getContextMenuScreenController()->clear();
				//
				sort(codeCompletionCandidates.begin(), codeCompletionCandidates.end());
				//
				{
					auto i = 0;
					for (auto& codeCompletionCandidate: codeCompletionCandidates) {
						// add light
						class OnCodeCompletionAction: public virtual Action
						{
						public:
							OnCodeCompletionAction(TextEditorTabView* textEditorTabView): textEditorTabView(textEditorTabView) {}
							void performAction() override {
								Console::println("xxx");
							}
						private:
							TextEditorTabView* textEditorTabView;
						};
						popUps->getContextMenuScreenController()->addMenuItem(codeCompletionCandidate, "contextmenu_codecompletion_" + to_string(i), new OnCodeCompletionAction(textEditorTabView));
						//
						i++;
					}
				}
				//
				int left, top, width, height;
				auto selectedTab = textEditorTabView->getEditorView()->getScreenController()->getSelectedTab();
				if (selectedTab != nullptr) {
					textEditorTabView->getEditorView()->getViewPort(selectedTab->getFrameBufferNode(), left, top, width, height);
					popUps->getContextMenuScreenController()->show(
						left + textEditorTabView->textNode->getIndexPositionX(),
						top + textEditorTabView->textNode->getIndexPositionY()
					);
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

