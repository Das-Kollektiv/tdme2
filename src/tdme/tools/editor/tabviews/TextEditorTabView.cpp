#include <tdme/tools/editor/tabviews/TextEditorTabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::tools::editor::tabviews::TextEditorTabView;

using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::TextEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

TextEditorTabView::TextEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	engine = Engine::createOffScreenInstance(512, 512, false);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
	auto multiLineTextNode = required_dynamic_cast<GUIMultilineTextNode*>(screenNode->getNodeById("text"));
	auto keywords1 = StringTools::tokenize(cppKeywords1, " ");
	auto keywords2 = StringTools::tokenize(cppKeywords2, " ");
	auto documentationTags = StringTools::tokenize(cppDocumentationTags, " ");
	for (auto& documentationTag: documentationTags) {
		documentationTag = "@" + documentationTag;
	}
	auto code = multiLineTextNode->getText().getString();
	auto startIdx = 0;
	auto endIdx = -1;
	for (auto i = 0; i < code.size(); i++) {
		auto c = code[i];
		// delimiter
		if (cppKeywordDelimiters.find(c) != string::npos) {
			endIdx = i;
		}
		if (startIdx != -1 && endIdx != -1 && startIdx != endIdx) {
			auto word = StringTools::trim(StringTools::substring(code, startIdx, endIdx));
			for (auto keyword: keywords1) {
				if (word == keyword) {
					multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor::GUICOLOR_RED);
				}
			}
			for (auto keyword: keywords2) {
				if (word == keyword) {
					multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor::GUICOLOR_GREEN);
				}
			}
			for (auto documentationTag: documentationTags) {
				if (word == documentationTag) {
					multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor::GUICOLOR_BLUE);
				}
			}
			startIdx = endIdx + 1;
			endIdx = -1;
		}
	}
}

TextEditorTabView::~TextEditorTabView() {
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
	// TODO: reloadTabOutliner
}

void TextEditorTabView::dispose()
{
	engine->reset();
	delete textEditorTabController;
}

void TextEditorTabView::updateRendering() {
}

Engine* TextEditorTabView::getEngine() {
	return engine;
}

void TextEditorTabView::activate() {
	// uiTabController->setOutlinerAddDropDownContent();
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

