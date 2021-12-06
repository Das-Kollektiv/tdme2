#include <tdme/tools/editor/tabviews/TextEditorTabView.h>

#include <cctype>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::tools::editor::tabviews::TextEditorTabView;

using tdme::engine::Engine;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
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
	engine = Engine::createOffScreenInstance(512, 512, false, false, false);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
	auto multiLineTextNode = required_dynamic_cast<GUIMultilineTextNode*>(screenNode->getNodeById("text"));
	if (std::find(xmlLanguage.extensions.begin(), xmlLanguage.extensions.end(), extension) != xmlLanguage.extensions.end()) {
		auto& language = xmlLanguage;
		auto code = multiLineTextNode->getText().getString();
		auto startIdx = 0;
		auto endIdx = -1;
		auto lc = '\0';
		auto llc = '\0';
		auto lllc = '\0';
		auto nc = '\0';
		auto inlineComment = false;
		auto quote = '\0';
		auto tag = false;
		auto tagMode = 0;
		auto attribute = false;
		for (auto i = 0; i < code.size(); i++) {
			auto c = code[i];
			auto nc = i + 1 < code.size()?code[i + 1]:'\0';
			auto nnc = i + 2 < code.size()?code[i + 2]:'\0';
			auto nnnc = i + 3 < code.size()?code[i + 3]:'\0';
			if (tag == false && inlineComment == false && quote == '\0') {
				if (language.commentInlineStart.empty() == false &&
					c == language.commentInlineStart[0] &&
					nc == language.commentInlineStart[1] &&
					nnc == language.commentInlineStart[2] &&
					nnnc == language.commentInlineStart[3]) {
					inlineComment = true;
					startIdx = i - 1;
					endIdx = -1;
				} else
				if (c == '<') {
					tag = true;
					tagMode = 0;
					startIdx = i;
					endIdx = -1;
				}
			} else
			if (inlineComment == true) {
				if (language.commentInlineEnd.empty() == false &&
					llc == language.commentInlineEnd[0] &&
					lc == language.commentInlineEnd[1] &&
					c == language.commentInlineEnd[2]) {
					inlineComment = false;
					endIdx = i + 1;
					multiLineTextNode->addTextStyle(startIdx, endIdx, commentInlineColor);
					startIdx = endIdx + 2;
					endIdx = -1;
				}
			} else
			if (quote != '\0') {
				if (c == quote) {
					quote = '\0';
					endIdx = i + 1;
					multiLineTextNode->addTextStyle(startIdx, endIdx, literalColor);
					startIdx = endIdx;
					endIdx = -1;
				}
			} else
			if (tag == true) {
				if (quote == '\0' && language.quotes.find(c) != string::npos) {
					endIdx = i;
					if (startIdx != endIdx) {
						multiLineTextNode->addTextStyle(startIdx, endIdx, tagMode == 0?keyword1Color:keyword2Color);
						tagMode++;
					}
					quote = c;
					startIdx = i;
					endIdx = -1;
				} else
				if (lc == '/' && c == '>') {
					endIdx = i - 1;
					if (startIdx != endIdx) {
						multiLineTextNode->addTextStyle(startIdx, endIdx, tagMode == 0?keyword1Color:keyword2Color);
					}
					multiLineTextNode->addTextStyle(endIdx, endIdx + 2, keyword1Color);
					startIdx = i + 1;
					endIdx = -1;
					tag = false;
					tagMode = 0;
				} else
				if (c == '>') {
					endIdx = i;
					if (startIdx != endIdx) {
						multiLineTextNode->addTextStyle(startIdx, endIdx, tagMode == 0?keyword1Color:keyword2Color);
					}
					multiLineTextNode->addTextStyle(endIdx, endIdx + 1, keyword1Color);
					startIdx = i + 1;
					endIdx = -1;
					tag = false;
					tagMode = 0;
				} else
				if (language.delimiters.find(c) != string::npos) {
					endIdx = i;
					if (startIdx != endIdx) {
						multiLineTextNode->addTextStyle(startIdx, endIdx, tagMode == 0?keyword1Color:keyword2Color);
					}
					startIdx = i + 1;
					endIdx = -1;
					tagMode++;
				}
			}
			lllc = llc;
			llc = lc;
			lc = c;
		}
	} else
	if (std::find(propertiesLanguage.extensions.begin(), propertiesLanguage.extensions.end(), extension) != propertiesLanguage.extensions.end()) {
		auto& language = propertiesLanguage;
		auto code = multiLineTextNode->getText().getString();
		auto commentCount = 0;
		auto delimiterCount = 0;
		auto nonWhitespaceCount = 0;
		auto startIdx = -1;
		auto endIdx = -1;
		auto commentLine = false;
		for (auto i = 0; i < code.size(); i++) {
			auto c = code[i];
			if (c == '\n') {
				endIdx = i;
				if (commentLine == true) {
					if (startIdx != -1 && endIdx != -1 && startIdx != endIdx) {
						multiLineTextNode->addTextStyle(startIdx, endIdx, commentLineColor);
					}
				} else
				if (startIdx != -1 && endIdx != -1 && startIdx != endIdx) {
					multiLineTextNode->addTextStyle(startIdx, endIdx, literalColor);
				}
				commentCount = 0;
				delimiterCount = 0;
				nonWhitespaceCount = 0;
				startIdx = -1;
				endIdx = -1;
				commentLine = false;
			} else
			if (language.whitespaces.find(c) != string::npos) {
				// no op
			} else
			if (c == language.comment && nonWhitespaceCount == 0) {
				startIdx = i;
				endIdx = -1;
				commentLine = true;
				nonWhitespaceCount++;
			} else
			if (c == language.delimiter && nonWhitespaceCount > 0) {
				endIdx = i;
				if (startIdx != -1 && startIdx != endIdx) {
					multiLineTextNode->addTextStyle(startIdx, endIdx, keyword2Color);
				}
				startIdx = i + 1;
				endIdx = -1;
				nonWhitespaceCount++;
			} else {
				if (nonWhitespaceCount == 0) startIdx = i;
				nonWhitespaceCount++;
			}
		}
		endIdx = code.size();
		if (commentLine == true) {
			multiLineTextNode->addTextStyle(startIdx, endIdx, commentLineColor);
		} else
		if (startIdx != -1 && startIdx != endIdx) {
			multiLineTextNode->addTextStyle(startIdx, endIdx, literalColor);
		}
	} else {
		for (auto& language: languages) {
			if (std::find(language.extensions.begin(), language.extensions.end(), extension) != language.extensions.end()) {
				auto code = multiLineTextNode->getText().getString();
				auto keywords1 = StringTools::tokenize(language.keywords1, " ");
				auto keywords2 = StringTools::tokenize(language.keywords2, " ");
				auto preprocessorLineKeywords = StringTools::tokenize(language.preprocessorLineKeywords, " ");
				auto datatypeLiteralSuffixes = StringTools::tokenize(language.datatypeLiteralSuffixes, " ");
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
									multiLineTextNode->addTextStyle(startIdx, endIdx, literalColor);
								} else {
									for (auto& keyword: keywords1) {
										if (word == keyword) {
											multiLineTextNode->addTextStyle(startIdx, endIdx, keyword1Color);
											break;
										}
									}
									for (auto& keyword: keywords2) {
										if (word == keyword) {
											multiLineTextNode->addTextStyle(startIdx, endIdx, keyword2Color);
											break;
										}
									}
									for (auto& keyword: preprocessorLineKeywords) {
										if (word == keyword) {
											if (c == '\n' || i == code.size() - 1) {
												multiLineTextNode->addTextStyle(startIdx, endIdx, preprocessorColor);
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
							multiLineTextNode->addTextStyle(startIdx, endIdx, commentLineColor);
							startIdx = endIdx + 1;
							endIdx = -1;
						}
					} else
					if (inlineComment == true) {
						if (language.commentInlineEnd.empty() == false && (language.commentInlineEnd.size() == 1 || lc == language.commentInlineEnd[0]) && c == language.commentInlineEnd[language.commentInlineEnd.size() - 1]) {
							inlineComment = false;
							endIdx = i;
							multiLineTextNode->addTextStyle(startIdx, endIdx, commentInlineColor);
							startIdx = endIdx + 1;
							endIdx = -1;
						}
					} else
					if (preprocessorLine == true) {
						if (c == '\n' || i == code.size() - 1) {
							preprocessorLine = false;
							endIdx = i;
							multiLineTextNode->addTextStyle(startIdx, endIdx, preprocessorColor);
							startIdx = endIdx + 1;
							endIdx = -1;
						}
					} else
					if (quote != '\0') {
						if (c == quote && (lc != '\\' || llc == '\\')) {
							quote = '\0';endIdx = -1;
							endIdx = i + 1;
							multiLineTextNode->addTextStyle(startIdx, endIdx, literalColor);
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
}

TextEditorTabView::~TextEditorTabView() {
	delete textEditorTabController;
	delete engine;
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

