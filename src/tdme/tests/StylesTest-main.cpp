#include <algorithm>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::upper_bound;

using tdme::application::Application;
using tdme::utilities::Console;

struct TextStyle {
	string id;
	int startIdx;
	int endIdx;
};

vector<TextStyle> styles;

void unsetStyle(int startIdx, int endIdx) {
	// find first style that is before new style or has collision
	auto i = 0;
	while (true == true) {
		auto &currentStyle = styles[i];
		//
		if (startIdx > currentStyle.endIdx) {
			// no op
		} else {
			break;
		}
		i++;
	}
	//
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		// check if the current range ins within range to be removed
		if (currentStyle.startIdx >= startIdx && currentStyle.endIdx <= endIdx) {
			// remove the overlapping range
			styles.erase(styles.begin() + i);
			i--;
		} else
		// check if the current range overlaps with the range to be removed
		if (currentStyle.startIdx < endIdx && currentStyle.endIdx > startIdx) {
			auto currentStyleStartIdx = currentStyle.startIdx;
			auto currentStyleEndIdx = currentStyle.endIdx;
			auto styleA = currentStyle;
			auto styleB = currentStyle;
			// remove the overlapping range
			styles.erase(styles.begin() + i);
			// split the overlapping range into two non-overlapping ranges
			if (currentStyleStartIdx < startIdx) {
				styleA.endIdx = startIdx;
				styles.insert(styles.begin() + i, styleA);
			}
			if (currentStyleEndIdx > endIdx) {
				styleB.startIdx = endIdx;
				styles.insert(styles.begin() + i, styleB);
			}
		} else
		// done?
		if (currentStyle.startIdx > endIdx) {
			break;
		}
	}
}

void removeStyles(int startIdx, int endIdx, bool xxx = false) {
	Console::println("remove style: " + to_string(startIdx) + " ... " + to_string(endIdx));
	//
	auto charsToRemove = endIdx - startIdx;
	// find first style that is before new style or has collision
	auto i = 0;
	while (true == true) {
		auto &currentStyle = styles[i];
		//
		if (startIdx > currentStyle.endIdx) {
			// no op
		} else {
			break;
		}
		i++;
	}
	//
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		// check if remove range is in current style range
		if (currentStyle.startIdx >= startIdx && currentStyle.endIdx <= endIdx) {
			Console::println("delete style: " + to_string(i) + " / " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx));
			styles.erase(styles.begin() + i);
			i--;
		} else
		// check if the current range overlaps with the range to be removed
		if (currentStyle.startIdx < endIdx && currentStyle.endIdx > startIdx) {
			Console::println("part style: " + to_string(i) + " / " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx));
			auto currentStyleStartIdx = currentStyle.startIdx;
			auto currentStyleEndIdx = currentStyle.endIdx;
			auto styleA = currentStyle;
			auto styleB = currentStyle;
			// remove the overlapping range
			styles.erase(styles.begin() + i);
			// split the overlapping range into two non-overlapping ranges
			styleA.endIdx = startIdx;
			if (styleA.endIdx > styleA.startIdx) {
				Console::println("\tpart style a: " + to_string(styleA.startIdx) + " ... " + to_string(styleA.endIdx));
				styles.insert(styles.begin() + i++, styleA);
			}
			styleB.startIdx = endIdx - 1;
			styleB.endIdx -= charsToRemove;
			if (styleB.endIdx > styleB.startIdx) {
				Console::println("\tpart style b: " + to_string(styleB.startIdx) + " ... " + to_string(styleB.endIdx));
				styles.insert(styles.begin() + i++, styleB);
			}
		} else
		if (currentStyle.startIdx >= endIdx) {
			Console::println("end of: " + to_string(i));
			i--;
			break;
		}
	}
	// unadvance next style
	if (i == -1) i = 0;
	Console::println("adjusting style: " + to_string(i));
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		Console::println("adjusting style: " + to_string(i) + " / " + to_string(charsToRemove) + ", " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx) + "(" + currentStyle.id + ")");
		//
		currentStyle.startIdx -= charsToRemove;
		if (currentStyle.startIdx < startIdx) currentStyle.startIdx = startIdx;
		currentStyle.endIdx -= charsToRemove;
		if (currentStyle.startIdx == currentStyle.endIdx) {
			currentStyle.endIdx++;
			charsToRemove-= 1;
		}
	}
}

/*
012345678901234567890123456789
    AAA BBB CCC
	 XXXXX

012345678901234567890123456789
    AAA BBB CCC
	 XXXXX
    AB CCC
	 XXXXX

*/

void insertStyle(int startIdx, int endIdx, const string &id) {
	//
	TextStyle newStyle;
	newStyle.startIdx = startIdx;
	newStyle.endIdx = endIdx;
	newStyle.id = id;
	//
	auto charsToAdvance = endIdx - startIdx;
	// can we put this style to the beginning?
	if (styles.empty() == true || endIdx < styles[0].startIdx) {
		// yup
		styles.insert(styles.begin(), newStyle);
		// advance next styles
		for (auto i = 1; i < styles.size(); i++) {
			auto &currentStyle = styles[i];
			currentStyle.startIdx += charsToAdvance;
			currentStyle.endIdx += charsToAdvance;
		}
		// done
		return;
	} else
	// can we put this style to the end?
	if (startIdx >= styles[styles.size() - 1].endIdx) {
		// yup
		styles.insert(styles.end(), newStyle);
		// done
		return;
	}
	// find first style that is before new style or has collision
	auto i = 0;
	while (true == true) {
		auto &currentStyle = styles[i];
		//
		if (newStyle.startIdx > currentStyle.endIdx) {
			// no op
		} else {
			break;
		}
		i++;
	}
	//
	auto &currentStyle = styles[i];
	// are we advanced over new style end index
	//	means we have a gap after a style to put our new style in
	if (endIdx <= styles[i].startIdx) {
		//
		styles.insert(styles.begin() + i++, newStyle);
		//
	} else
	// check if the new style overlaps with the current style
	if (currentStyle.startIdx < endIdx && currentStyle.endIdx > startIdx) {
		auto currentStyleStartIdx = currentStyle.startIdx;
		auto currentStyleEndIdx = currentStyle.endIdx;
		auto styleA = currentStyle;
		auto styleB = currentStyle;
		// remove the overlapping range
		styles.erase(styles.begin() + i);
		// split the overlapping range into two non-overlapping ranges
		//	range from current style start index to new style start index
		styleA.endIdx = newStyle.startIdx;
		//	do we have a feasible range?
		if (styleA.endIdx > styleA.startIdx) {
			// yes
			styles.insert(styles.begin() + i++, styleA);
		}
		// insert new style
		styles.insert(styles.begin() + i++, newStyle);
		//	range from new style end index to current style end index
		styleB.startIdx = newStyle.endIdx;
		styleB.endIdx = styleB.endIdx + (newStyle.endIdx - newStyle.startIdx);
		if (styleB.endIdx > styleB.startIdx) {
			styles.insert(styles.begin() + i++, styleB);
		}
	} else
	// gap after current style
	if (startIdx >= currentStyle.endIdx) {
		styles.insert(styles.begin() + i + 1, newStyle);
		i++;
		i++;
	}
	// advance next styles
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		currentStyle.startIdx += charsToAdvance;
		currentStyle.endIdx += charsToAdvance;
	}
}

const string getStylesString() {
	string stylesString;
	auto multipleStyles = false;
	for (auto i = 0; i < 50; i++) {
		auto styleCount = 0;
		for (auto j = 0; j < styles.size(); j++) {
			auto& currentStyle = styles[j];
			if (i >= currentStyle.startIdx && i < currentStyle.endIdx) {
				styleCount++;
				if (styleCount == 1) {
					stylesString+= currentStyle.id;
				}
			}
		}
		if (styleCount == 0) {
			stylesString+= " ";
		} else
		if (styleCount > 1) {
			// invalid
		}
	}
	return stylesString;
}

void validateStyles(const string& stylesString) {
	auto multipleStyles = false;
	for (auto i = 0; i < 50; i++) {
		auto styleCount = 0;
		for (auto j = 0; j < styles.size(); j++) {
			auto& currentStyle = styles[j];
			if (i >= currentStyle.startIdx && i < currentStyle.endIdx) {
				styleCount++;
			}
		}
		if (styleCount > 1) {
			multipleStyles = true;
		}
	}
	if (multipleStyles == true) {
		Console::println("Multiple styles!");
		Console::println();
		for (auto &style : styles) {
			Console::println(to_string(style.startIdx) + " ... " + to_string(style.endIdx) + "(" + style.id + "), chars = " + to_string(style.endIdx - style.startIdx));
		}
		for (auto i = 0; i < 50; i++) {
			Console::print(string() + (char)((i % 10) + '0'));
		}
		Console::println();
	}
	auto computedStylesString = getStylesString();
	Console::println(string() + "Styles " + (computedStylesString != stylesString?"mismatch!":"match!"));
	Console::println("\texpected: '" + stylesString + "'");
	Console::println("\tcomputed: '" + computedStylesString + "'");
	Console::println();
}

void showStyles() {
	Console::println("Styles:");
	for (auto &style : styles) {
		Console::println(to_string(style.startIdx) + " ... " + to_string(style.endIdx) + "(" + style.id + "), chars = " + to_string(style.endIdx - style.startIdx));
	}
	for (auto i = 0; i < 50; i++) {
		Console::print(string() + (char)((i % 10) + '0'));
	}
	Console::println();
	Console::println(getStylesString());
	Console::println();
}

int main(int argc, char **argv) {
	Application::installExceptionHandler();
	{
		Console::println("-------------------------");
		Console::println("StylesTest: Insert Test");
		Console::println("-------------------------");
		Console::println();
		// insert A (begin)
		insertStyle(5, 15, "A");
		validateStyles("     AAAAAAAAAA                                   ");
		// insert B in the middle of A (gap)
		insertStyle(10, 15, "B");
		validateStyles("     AAAAABBBBBAAAAA                              ");
		// insert 0 before of A (gap)
		insertStyle(0, 5, "0");
		validateStyles("00000     AAAAABBBBBAAAAA                         ");
		// insert 9 after A at the end (end)
		insertStyle(25, 30, "9");
		validateStyles("00000     AAAAABBBBBAAAAA99999                    ");
		// insert 8 before 9 (gap2)
		insertStyle(25, 30, "8");
		validateStyles("00000     AAAAABBBBBAAAAA8888899999               ");
		//
		showStyles();
		//
		auto filledStyles = styles;
		showStyles();
		//
		Console::println("-------------------------");
		Console::println("StylesTest: Unset Test");
		Console::println("-------------------------");
		Console::println();
		// unset part one style at beginning
		unsetStyle(2, 5);
		validateStyles("00        AAAAABBBBBAAAAA8888899999               ");
		// unset one style at beginning
		unsetStyle(0, 2);
		validateStyles("          AAAAABBBBBAAAAA8888899999               ");
		// unset part of one style at end
		unsetStyle(28, 30);
		validateStyles("          AAAAABBBBBAAAAA888  99999               ");
		// unset part of one style at beginning in the middle
		unsetStyle(25, 29);
		validateStyles("          AAAAABBBBBAAAAA     99999               ");
		// unset multiple parts
		unsetStyle(10, 25);
		validateStyles("                              99999               ");
		// unset multiple parts
		unsetStyle(0, 50);
		validateStyles("                                                  ");
		//
		showStyles();
		//
		styles = filledStyles;
		showStyles();
		//
		Console::println("-------------------------");
		Console::println("StylesTest: Remove Test");
		Console::println("-------------------------");
		Console::println();
		// remove part one style at beginning
		removeStyles(2, 5);
		validateStyles("00     AAAAABBBBBAAAAA8888899999                  ");
		// remove one style at beginning
		removeStyles(0, 2);
		validateStyles("     AAAAABBBBBAAAAA8888899999                    ");
		// remove one part of style at end
		removeStyles(27, 30);
		validateStyles("     AAAAABBBBBAAAAA8888899                       ");
		// remove one style at end
		removeStyles(25, 27);
		validateStyles("     AAAAABBBBBAAAAA88888                         ");
		// remove multiple styles
		removeStyles(6, 15);
		validateStyles("     ABAAAAA88888                                 ");
		// remove multiple styles
		removeStyles(6, 8);
		validateStyles("     AAAAA88888                                   ");
		//
		showStyles();
	}
	Console::println("StylesTest: done");
}
