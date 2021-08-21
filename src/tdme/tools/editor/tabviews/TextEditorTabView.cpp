#include <tdme/tools/editor/tabviews/TextEditorTabView.h>

#include <cctype>
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
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
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
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;

TextEditorTabView::TextEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& extension)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	engine = Engine::createOffScreenInstance(512, 512, false);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
	for (auto& language: languages) {
		if (std::find(language.extensions.begin(), language.extensions.end(), extension) != language.extensions.end()) {
			auto multiLineTextNode = required_dynamic_cast<GUIMultilineTextNode*>(screenNode->getNodeById("text"));
			auto keywords1 = StringTools::tokenize(language.keywords1, " ");
			auto keywords2 = StringTools::tokenize(language.keywords2, " ");
			auto preprocessorLineKeywords = StringTools::tokenize(language.preprocessorLineKeywords, " ");
			auto datatypeLiteralSuffixes = StringTools::tokenize(language.datatypeLiteralSuffixes, " ");
			auto code = multiLineTextNode->getText().getString();
			auto startIdx = 0;
			auto endIdx = -1;
			auto lc = '\0';
			auto llc = '\0';
			auto nc = '\0';
			auto inlineComment = false;
			auto lineComment = false;
			auto preprocessorLine = false;
			auto quote = '\0';
			for (auto i = 0; i < code.size(); i++) {
				auto c = code[i];
				auto nc = i + 1 < code.size()?code[i + 1]:'\0';
				if (inlineComment == false && lineComment == false && preprocessorLine == false && quote == '\0') {
					if (language.commentLine.empty() == false && (language.commentLine.size() == 1 || c == language.commentLine[0]) && nc == language.commentLine[language.commentLine.size() - 1]) {
						lineComment = true;
						startIdx = i - 1;
						endIdx = -1;
					} else
					if (language.commentInlineStart.empty() == false && (language.commentInlineStart.size() == 1 || c == language.commentInlineStart[0]) && nc == language.commentInlineStart[language.commentInlineStart.size() - 1]) {
						inlineComment = true;
						startIdx = i - 1;
						endIdx = -1;
					} else
					if (quote == '\0' && language.keywordQuotes.find(c) != string::npos) {
						quote = c;
						startIdx = i;
						endIdx = -1;
					} else {
						// delimiter
						if (language.keywordDelimiters.find(c) != string::npos) {
							endIdx = i;
						}
						if (startIdx != -1 && endIdx != -1 && startIdx != endIdx) {
							auto word = StringTools::trim(StringTools::substring(code, startIdx, endIdx));
							if (word.empty() == true) continue;
							auto literalWord = word;
							for (auto& datatypeLiteralSuffix: datatypeLiteralSuffixes) {
								if (StringTools::endsWith(word, datatypeLiteralSuffix) == true) {
									auto dotCount = 0;
									auto valid = true;
									for (auto j = 0; j < word.size() - datatypeLiteralSuffix.size(); j++) {
										if (word[j] == '.') {
											dotCount++;
											if (dotCount > 1) {
												valid = false;
												break;
											}
										} else
										if (isdigit(word[j]) == false) {
											valid = false;
											break;
										}
									}
									if (valid == true) {
										literalWord = StringTools::substring(word, 0, word.size() - datatypeLiteralSuffix.size());
										break;
									}
								}
							}
							if (Integer::isInt(literalWord) == true || Float::isFloat(literalWord) == true) {
								multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor("#eabc19"));
							} else {
								for (auto& keyword: keywords1) {
									if (word == keyword) {
										multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor("#cb551a"));
										break;
									}
								}
								for (auto& keyword: keywords2) {
									if (word == keyword) {
										multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor("#8ae234"));
										break;
									}
								}
								for (auto& keyword: preprocessorLineKeywords) {
									if (word == keyword) {
										if (c == '\n' || i == code.size() - 1) {
											multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor("#ab7779"));
										} else {
											preprocessorLine = true;
											endIdx = startIdx - 1;
										}
										break;
									}
								}
							}
							startIdx = endIdx + 1;
							endIdx = -1;
						}
					}
				} else
				if (lineComment == true) {
					if (c == '\n' || i == code.size() - 1) {
						lineComment = false;
						endIdx = i;
						multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor("#888a85"));
						startIdx = endIdx + 1;
						endIdx = -1;
					}
				} else
				if (inlineComment == true) {
					if (language.commentInlineEnd.empty() == false && (language.commentInlineEnd.size() == 1 || lc == language.commentInlineEnd[0]) && c == language.commentInlineEnd[language.commentInlineEnd.size() - 1]) {
						inlineComment = false;
						endIdx = i;
						multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor("#888a85"));
						startIdx = endIdx + 1;
						endIdx = -1;
					}
				} else
				if (preprocessorLine == true) {
					if (c == '\n' || i == code.size() - 1) {
						preprocessorLine = false;
						endIdx = i;
						multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor("#ab7779"));
						startIdx = endIdx + 1;
						endIdx = -1;
					}
				} else
				if (quote != '\0') {
					if (c == quote && (lc != '\\' || llc == '\\')) {
						quote = '\0';
						endIdx = i + 1;
						multiLineTextNode->addTextStyle(startIdx, endIdx, GUIColor("#eabc19"));
						startIdx = endIdx + 1;
						endIdx = -1;
					}
				}
				llc = lc;
				lc = c;
			}

			// done
			break;
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

