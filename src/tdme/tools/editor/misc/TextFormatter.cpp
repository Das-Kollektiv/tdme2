#include <tdme/tools/editor/misc/TextFormatter.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;

using tdme::tools::editor::misc::TextFormatter;

using tdme::gui::nodes::GUIStyledTextNode;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;

TextFormatter* TextFormatter::instance = nullptr;

void TextFormatter::format(const string& extension, GUIStyledTextNode* textNode, int charStartIdx, int charEndIdx) {
	if (std::find(xmlLanguage.extensions.begin(), xmlLanguage.extensions.end(), extension) != xmlLanguage.extensions.end()) {
		textNode->unsetStyles();
		auto& language = xmlLanguage;
		auto& code = textNode->getText().getString();
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
					textNode->setTextStyle(startIdx, endIdx - 1, commentInlineColor);
					startIdx = endIdx + 2;
					endIdx = -1;
				}
			} else
			if (quote != '\0') {
				if (c == quote) {
					quote = '\0';
					endIdx = i + 1;
					textNode->setTextStyle(startIdx, endIdx - 1, literalColor);
					startIdx = endIdx;
					endIdx = -1;
				}
			} else
			if (tag == true) {
				if (quote == '\0' && language.quotes.find(c) != string::npos) {
					endIdx = i;
					if (startIdx != endIdx) {
						textNode->setTextStyle(startIdx, endIdx - 1, tagMode == 0?keyword1Color:keyword2Color);
						tagMode++;
					}
					quote = c;
					startIdx = i;
					endIdx = -1;
				} else
				if (lc == '/' && c == '>') {
					endIdx = i - 1;
					if (startIdx != endIdx) {
						textNode->setTextStyle(startIdx, endIdx - 1, tagMode == 0?keyword1Color:keyword2Color);
					}
					textNode->setTextStyle(endIdx, endIdx - 1 + 2, keyword1Color);
					startIdx = i + 1;
					endIdx = -1;
					tag = false;
					tagMode = 0;
				} else
				if (c == '>') {
					endIdx = i;
					if (startIdx != endIdx) {
						textNode->setTextStyle(startIdx, endIdx - 1, tagMode == 0?keyword1Color:keyword2Color);
					}
					textNode->setTextStyle(endIdx, endIdx - 1 + 1, keyword1Color);
					startIdx = i + 1;
					endIdx = -1;
					tag = false;
					tagMode = 0;
				} else
				if (language.delimiters.find(c) != string::npos) {
					endIdx = i;
					if (startIdx != endIdx) {
						textNode->setTextStyle(startIdx, endIdx - 1, tagMode == 0?keyword1Color:keyword2Color);
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
		auto& code = textNode->getText().getString();
		auto commentCount = 0;
		auto delimiterCount = 0;
		auto nonWhitespaceCount = 0;
		auto startIdx = -1;
		auto endIdx = -1;
		auto commentLine = false;
		if (charStartIdx == -1) {
			charStartIdx = 0;
		} else {
			// find index of previous newline and store difference
			auto previousNewLineIndex = charStartIdx;
			while (previousNewLineIndex >= 0 && code[previousNewLineIndex] != '\n') previousNewLineIndex--;
			previousNewLineIndex = Math::min(previousNewLineIndex + 1, code.size() - 1);
			charStartIdx = previousNewLineIndex;
		}
		if (charEndIdx == -1) {
			charEndIdx = code.size() - 1;
		} else {
			// find index of next newline
			auto nextNewLineIndex = Math::min(code[charEndIdx] == '\n'?charEndIdx + 1:charEndIdx, code.size() - 1);
			while (nextNewLineIndex < code.size() && code[nextNewLineIndex] != '\n') nextNewLineIndex++;
			nextNewLineIndex = Math::min(nextNewLineIndex + 1, code.size() - 1);
			charEndIdx = nextNewLineIndex;
		}
		textNode->unsetTextStyle(charStartIdx, charEndIdx);
		for (auto i = charStartIdx; i >= 0 && i <= charEndIdx; i++) {
			auto c = code[i];
			if (c == '\n') {
				endIdx = i;
				if (commentLine == true) {
					if (startIdx != -1 && endIdx != -1 && startIdx != endIdx) {
						textNode->setTextStyle(startIdx, endIdx - 1, commentLineColor);
					}
				} else
				if (startIdx != -1 && endIdx != -1 && startIdx != endIdx) {
					textNode->setTextStyle(startIdx, endIdx - 1, literalColor);
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
					textNode->setTextStyle(startIdx, endIdx - 1, keyword2Color);
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
			textNode->setTextStyle(startIdx, endIdx - 1, commentLineColor);
		} else
		if (startIdx != -1 && startIdx != endIdx) {
			textNode->setTextStyle(startIdx, endIdx - 1, literalColor);
		}
	} else {
		auto foundLanguage = false;
		for (auto& language: languages) {
			if (std::find(language.extensions.begin(), language.extensions.end(), extension) != language.extensions.end()) {
				foundLanguage = true;
				auto& code = textNode->getText().getString();
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
				if (charStartIdx == -1) {
					charStartIdx = 0;
				} else {
					// find index of previous newline and store difference
					auto previousNewLineIndex = charStartIdx;
					while (previousNewLineIndex >= 0 && code[previousNewLineIndex] != '\n') previousNewLineIndex--;
					previousNewLineIndex = Math::min(previousNewLineIndex + 1, code.size() - 1);
					charStartIdx = previousNewLineIndex;
				}
				if (charEndIdx == -1) {
					charEndIdx = code.size() - 1;
				} else {
					// find index of next newline
					auto nextNewLineIndex = Math::min(code[charEndIdx] == '\n'?charEndIdx + 1:charEndIdx, code.size() - 1);
					while (nextNewLineIndex < code.size() && code[nextNewLineIndex] != '\n') nextNewLineIndex++;
					nextNewLineIndex = Math::min(nextNewLineIndex + 1, code.size() - 1);
					charEndIdx = nextNewLineIndex;
				}
				textNode->unsetTextStyle(charStartIdx, charEndIdx);
				for (auto i = charStartIdx; i >= 0 && i <= charEndIdx; i++) {
					auto c = code[i];
					auto nc = i + 1 < code.size()?code[i + 1]:'\0';
					if (inlineComment == false && lineComment == false && preprocessorLine == false && quote == '\0') {
						if (language.commentLine.empty() == false && (language.commentLine.size() == 1 || c == language.commentLine[0]) && nc == language.commentLine[language.commentLine.size() - 1]) {
							lineComment = true;
							startIdx = i;
							endIdx = -1;
						} else
						if (language.commentInlineStart.empty() == false && (language.commentInlineStart.size() == 1 || c == language.commentInlineStart[0]) && nc == language.commentInlineStart[language.commentInlineStart.size() - 1]) {
							inlineComment = true;
							startIdx = i;
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
							} else
							if (i == code.size() - 1) {
								endIdx = code.size();
							}
							if (startIdx != -1 && endIdx != -1 && startIdx != endIdx) {
								while (code[startIdx] == ' ' || code[startIdx] == '\t') startIdx++;
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
								if (Integer::is(literalWord) == true || Float::is(literalWord) == true) {
									textNode->setTextStyle(startIdx, endIdx - 1, literalColor);
								} else {
									for (auto& keyword: keywords1) {
										if (word == keyword) {
											textNode->setTextStyle(startIdx, endIdx - 1, keyword1Color);
											break;
										}
									}
									for (auto& keyword: keywords2) {
										if (word == keyword) {
											textNode->setTextStyle(startIdx, endIdx - 1, keyword2Color);
											break;
										}
									}
									for (auto& keyword: preprocessorLineKeywords) {
										if (word == keyword) {
											if (c == '\n' || i == code.size() - 1) {
												textNode->setTextStyle(startIdx, endIdx - 1, preprocessorColor);
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
							textNode->setTextStyle(startIdx, endIdx, commentLineColor);
							startIdx = endIdx + 1;
							endIdx = -1;
						}
					} else
					if (inlineComment == true) {
						if (language.commentInlineEnd.empty() == false && (language.commentInlineEnd.size() == 1 || lc == language.commentInlineEnd[0]) && c == language.commentInlineEnd[language.commentInlineEnd.size() - 1]) {
							inlineComment = false;
							endIdx = i;
							textNode->setTextStyle(startIdx, endIdx - 1, commentInlineColor);
							startIdx = endIdx + 1;
							endIdx = -1;
						}
					} else
					if (preprocessorLine == true) {
						if (c == '\n' || i == code.size() - 1) {
							preprocessorLine = false;
							endIdx = i;
							textNode->setTextStyle(startIdx, endIdx, preprocessorColor);
							startIdx = endIdx + 1;
							endIdx = -1;
						}
					} else
					if (quote != '\0') {
						if (c == quote && (lc != '\\' || llc == '\\')) {
							quote = '\0';endIdx = -1;
							endIdx = i + 1;
							textNode->setTextStyle(startIdx, endIdx - 1, literalColor);
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
		// unset styles if no language found
		if (foundLanguage == false) textNode->unsetStyles();
	}
}
