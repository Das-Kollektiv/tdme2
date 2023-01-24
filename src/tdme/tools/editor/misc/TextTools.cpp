#include <tdme/tools/editor/misc/TextTools.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;

using tdme::tools::editor::misc::TextTools;

using tdme::gui::GUI;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::utilities::Character;
using tdme::utilities::StringTools;

bool TextTools::find(GUIStyledTextNode* textNode, const string& findString, bool matchCase, bool wholeWord, bool selection, bool firstSearch, int& index) {
	auto success = false;
	auto findStringLowerCase = matchCase == false?StringTools::toLowerCase(findString):findString;
	auto textMutableString = textNode->getText();
	auto textLowerCase = matchCase == false?StringTools::toLowerCase(textNode->getText().getString()):textNode->getText().getString();
	auto textNodeController = required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController());
	auto inSelectionAvailable = textNodeController->getIndex() != -1 && textNodeController->getSelectionIndex() != -1;
	auto i = selection == true && inSelectionAvailable == true?textMutableString.getUtf8BinaryIndex(Math::min(textNodeController->getIndex(), textNodeController->getSelectionIndex())):0;
	auto fi = -1;
	auto ni = textMutableString.getUtf8BinaryIndex(index);
	auto l = selection == true && inSelectionAvailable == true?textMutableString.getUtf8BinaryIndex(Math::max(textNodeController->getIndex(), textNodeController->getSelectionIndex())):textMutableString.size();
	while (i < l) {
		auto p = StringTools::indexOf(textLowerCase, findStringLowerCase, i);
		if (p != string::npos && p < l) {
			i = p + findStringLowerCase.size();
			if (wholeWord == true) {
				auto textCharIdxBefore = textMutableString.getUtf8CharacterIndex(p) - 1;
				auto textCharIdxAfter = textMutableString.getUtf8CharacterIndex(p + findStringLowerCase.size());
				auto textCharBefore = textMutableString.getUTF8CharAt(textCharIdxBefore);
				auto textCharAfter = textMutableString.getUTF8CharAt(textCharIdxAfter);
				if (Character::isAlphaNumeric(textCharBefore) == true || Character::isAlphaNumeric(textCharAfter) == true) {
					continue;
				}
			}
			if (fi == -1) fi = p;
			if (ni != -1 && (firstSearch == true?p >= ni:p > ni)) {
				index = p;
				textNode->setTextStyle(p, p + findStringLowerCase.size() - 1, GUIColor("#ff0000"));
				textNode->scrollToIndex(index);
				ni = -1;
				firstSearch = false;
				success = true;
				//
				break;
			}
		} else {
			break;
		}
	}
	if (ni != -1 && fi != -1) {
		textNode->setTextStyle(fi, fi + findStringLowerCase.size() - 1, GUIColor("#ff0000"));
		index = fi;
		textNode->scrollToIndex(index);
		success = true;
	}
	//
	return success;
}

int TextTools::count(GUIStyledTextNode* textNode, const string& findString, bool matchCase, bool wholeWord, bool selection) {
	auto findStringLowerCase = matchCase == false?StringTools::toLowerCase(findString):findString;
	auto textMutableString = textNode->getText();
	auto textLowerCase = matchCase == false?StringTools::toLowerCase(textNode->getText().getString()):textNode->getText().getString();
	auto textNodeController = required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController());
	auto inSelectionAvailable = textNodeController->getIndex() != -1 && textNodeController->getSelectionIndex() != -1;
	auto i = selection == true && inSelectionAvailable == true?textMutableString.getUtf8BinaryIndex(Math::min(textNodeController->getIndex(), textNodeController->getSelectionIndex())):0;
	auto l = selection == true && inSelectionAvailable == true?textMutableString.getUtf8BinaryIndex(Math::max(textNodeController->getIndex(), textNodeController->getSelectionIndex())):textMutableString.size();
	auto c = 0;
	while (i < l) {
		auto p = StringTools::indexOf(textLowerCase, findStringLowerCase, i);
		if (p != string::npos && p < l) {
			i = p + findStringLowerCase.size();
			if (wholeWord == true) {
				auto textCharIdxBefore = textMutableString.getUtf8CharacterIndex(p) - 1;
				auto textCharIdxAfter = textMutableString.getUtf8CharacterIndex(p + findStringLowerCase.size());
				auto textCharBefore = textMutableString.getUTF8CharAt(textCharIdxBefore);
				auto textCharAfter = textMutableString.getUTF8CharAt(textCharIdxAfter);
				if (Character::isAlphaNumeric(textCharBefore) == true || Character::isAlphaNumeric(textCharAfter) == true) {
					continue;
				}
			}
			textNode->setTextStyle(p, p + findStringLowerCase.size() - 1, GUIColor("#ff0000"));
			c++;
		} else {
			break;
		}
	}
	//
	return c;
}

bool TextTools::replace(GUIStyledTextNode* textNode, const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection, int& index) {
	auto success = false;
	auto findStringLowerCase = matchCase == false?StringTools::toLowerCase(findString):findString;
	auto findStringLength = StringTools::getUtf8Length(findString);
	auto textMutableString = textNode->getText();
	auto textLowerCase = matchCase == false?StringTools::toLowerCase(textMutableString.getString()):textMutableString.getString();
	auto textNodeController = required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController());
	auto inSelectionAvailable = textNodeController->getIndex() != -1 && textNodeController->getSelectionIndex() != -1;
	auto i = selection == true && inSelectionAvailable == true?textMutableString.getUtf8BinaryIndex(Math::min(textNodeController->getIndex(), textNodeController->getSelectionIndex())):0;
	auto fi = -1;
	auto ni = textMutableString.getUtf8BinaryIndex(index);
	auto l = selection == true && inSelectionAvailable == true?textMutableString.getUtf8BinaryIndex(Math::max(textNodeController->getIndex(), textNodeController->getSelectionIndex())):textMutableString.size();
	while (i < l) {
		auto p = StringTools::indexOf(textLowerCase, findStringLowerCase, i);
		if (p != string::npos && p < l) {
			i = p + findStringLowerCase.size();
			if (wholeWord == true) {
				auto textCharIdxBefore = textMutableString.getUtf8CharacterIndex(p) - 1;
				auto textCharIdxAfter = textMutableString.getUtf8CharacterIndex(p + findStringLowerCase.size());
				auto textCharBefore = textMutableString.getUTF8CharAt(textCharIdxBefore);
				auto textCharAfter = textMutableString.getUTF8CharAt(textCharIdxAfter);
				if (Character::isAlphaNumeric(textCharBefore) == true || Character::isAlphaNumeric(textCharAfter) == true) {
					continue;
				}
			}
			if (fi == -1) fi = p;
			if (ni != -1 && p >= ni) {
				//
				auto replaceIndex = textMutableString.getUtf8CharacterIndex(p);
				textNodeController->replace(replaceString, replaceIndex, findStringLength);
				//
				index = replaceIndex + findStringLength;
				textNode->scrollToIndex(index);
				ni = -1;
				success = true;
				//
				break;
			}
		} else {
			break;
		}
	}
	if (ni != -1 && fi != -1) {
		//
		auto replaceIndex = textMutableString.getUtf8CharacterIndex(fi);
		textNodeController->replace(replaceString, replaceIndex, findStringLength);
		//
		index = replaceIndex + findStringLength;
		textNode->scrollToIndex(index);
		success = true;
	}
	//
	return success;
}

bool TextTools::replaceAll(GUIStyledTextNode* textNode, const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection) {
	auto success = false;
	auto findStringLowerCase = matchCase == false?StringTools::toLowerCase(findString):findString;
	auto findStringLength = StringTools::getUtf8Length(findString);
	auto textMutableString = textNode->getText();
	auto textLowerCase = matchCase == false?StringTools::toLowerCase(textNode->getText().getString()):textNode->getText().getString();
	auto textNodeController = required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController());
	auto inSelectionAvailable = textNodeController->getIndex() != -1 && textNodeController->getSelectionIndex() != -1;
	auto i = selection == true && inSelectionAvailable == true?textMutableString.getUtf8BinaryIndex(Math::min(textNodeController->getIndex(), textNodeController->getSelectionIndex())):0;
	auto l = selection == true && inSelectionAvailable == true?textMutableString.getUtf8BinaryIndex(Math::max(textNodeController->getIndex(), textNodeController->getSelectionIndex())):textMutableString.size();
	while (i < l) {
		auto p = StringTools::indexOf(textLowerCase, findStringLowerCase, i);
		if (p != string::npos && p < l) {
			i = p + replaceString.size();
			if (wholeWord == true) {
				auto textCharIdxBefore = textMutableString.getUtf8CharacterIndex(p) - 1;
				auto textCharIdxAfter = textMutableString.getUtf8CharacterIndex(p + findStringLowerCase.size());
				auto textCharBefore = textMutableString.getUTF8CharAt(textCharIdxBefore);
				auto textCharAfter = textMutableString.getUTF8CharAt(textCharIdxAfter);
				if (Character::isAlphaNumeric(textCharBefore) == true || Character::isAlphaNumeric(textCharAfter) == true) {
					continue;
				}
			}
			//
			auto replaceIndex = textMutableString.getUtf8CharacterIndex(p);
			textNodeController->replace(replaceString, replaceIndex, findStringLength);
			//
			textMutableString = textNode->getText();
			textLowerCase = matchCase == false?StringTools::toLowerCase(textNode->getText().getString()):textNode->getText().getString();
			success = true;
		} else {
			break;
		}
	}
	return success;
}
