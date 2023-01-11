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
	Console::println("unsetStyle(): " + to_string(startIdx) + ", " + to_string(endIdx));
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
	Console::println("unsetStyle(): initial i = " + to_string(i) + " / " + to_string(styles.size()));
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
			Console::println("Collision: " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx) + " / " + to_string(startIdx) + " ... " + to_string(endIdx));
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
		}
	}
}

void removeStyles(int startIdx, int endIdx) {
	Console::println("removeStyle(): " + to_string(startIdx) + ", " + to_string(endIdx));
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
	Console::println("removeStyle(): initial i = " + to_string(i) + " / " + to_string(styles.size()));
	//
	auto hadCollision = false;
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		Console::println("Test@" + to_string(i) + ": " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx) + " / " + to_string(startIdx) + " ... " + to_string(endIdx) + " / " + currentStyle.id);
		// check if remove range is in current style range
		if (currentStyle.startIdx >= startIdx && currentStyle.endIdx <= endIdx) {
			Console::println("Deletion: " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx) + " / " + to_string(startIdx) + " ... " + to_string(endIdx) + " / " + currentStyle.id);
			styles.erase(styles.begin() + i);
			i--;
		} else
		// check if the current range overlaps with the range to be removed
		if (currentStyle.startIdx < endIdx && currentStyle.endIdx > startIdx) {
			Console::println("Collision: " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx) + " / " + to_string(startIdx) + " ... " + to_string(endIdx) + " / " + currentStyle.id);
			auto currentStyleStartIdx = currentStyle.startIdx;
			auto currentStyleEndIdx = currentStyle.endIdx;
			auto styleA = currentStyle;
			auto styleB = currentStyle;
			// remove the overlapping range
			styles.erase(styles.begin() + i);
			// split the overlapping range into two non-overlapping ranges
			styleA.endIdx = startIdx;
			//if (styleA.endIdx > styleA.startIdx) {
				Console::println("\tAdding left: " + to_string(styleA.startIdx) + " ... " + to_string(styleA.endIdx) + " / " + styleA.id);
				styles.insert(styles.begin() + i++, styleA);
			//}
			styleB.startIdx = endIdx - 1;
			styleB.endIdx -= charsToRemove;
			//if (styleB.endIdx > styleB.startIdx) {
				Console::println("\tAdding right: " + to_string(styleB.startIdx) + " ... " + to_string(styleB.endIdx) + " / " + styleB.id);
				styles.insert(styles.begin() + i++, styleB);
			//}
			// stop here, readvance next styles
			hadCollision = true;
			//
		} else {
			if (hadCollision == true) {
				Console::println("Done: " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx) + " / " + to_string(startIdx) + " ... " + to_string(endIdx) + " / " + currentStyle.id);
				//
				i--;
				//
				break;
			}
		}
	}
	Console::println("removeStyle(): unadvance i = " + to_string(i) + " / " + to_string(styles.size()) + " / " + to_string(charsToRemove));
	// unadvance next styles
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		Console::println("removeStyle(): unadvancing i = " + to_string(i) + " / " + to_string(styles.size()) + " from " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx) + " / " + to_string(currentStyle.startIdx - charsToRemove) + " ... " + to_string(currentStyle.endIdx - charsToRemove));
		currentStyle.startIdx -= charsToRemove;
		currentStyle.endIdx -= charsToRemove;
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
	Console::println("insertStyle(): " + to_string(startIdx) + ", " + to_string(endIdx) + " / " + id);
	//
	TextStyle newStyle;
	newStyle.startIdx = startIdx;
	newStyle.endIdx = endIdx;
	newStyle.id = id;
	//
	auto charsToAdvance = endIdx - startIdx;
	//
	// can we put this style to the beginning
	if (styles.empty() == true || endIdx < styles[0].startIdx) {
		// yup
		styles.insert(styles.begin(), newStyle);
		// advance next styles
		for (auto i = 1; i < styles.size(); i++) {
			auto &currentStyle = styles[i];
			currentStyle.startIdx += charsToAdvance;
			currentStyle.endIdx += charsToAdvance;
		}
		//
		return;
	}
	// can we put this style to the end
	if (startIdx >= styles[styles.size() - 1].endIdx) {
		// yup
		styles.insert(styles.end(), newStyle);
		//
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
	// are we advanced over new style end index
	//	means we have a gap after a style to put our new style in
	if (endIdx <= styles[i].startIdx) {
		//
		styles.insert(styles.begin() + i++, newStyle);
		// advance next styles
		for (; i < styles.size(); i++) {
			auto &currentStyle = styles[i];
			currentStyle.startIdx += charsToAdvance;
			currentStyle.endIdx += charsToAdvance;
		}
		return;
	}
	//
	// adjust styles
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		// check if the current range overlaps with the range to be removed
		if (currentStyle.startIdx < endIdx && currentStyle.endIdx > startIdx) {
			//
			auto currentStyleLength = currentStyle.endIdx - currentStyle.startIdx;
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
				//
				currentStyleLength-= styleA.endIdx - styleA.startIdx;
			}
			// insert new style
			//
			styles.insert(styles.begin() + i++, newStyle);
			//	range from new style end index to current style end index
			styleB.startIdx = endIdx + (currentStyleStartIdx - startIdx);
			styleB.endIdx = styleB.startIdx + currentStyleLength;
			if (styleB.endIdx > styleB.startIdx) {
				styles.insert(styles.begin() + i++, styleB);
				//
				charsToAdvance = styleB.endIdx - currentStyleEndIdx;
			}
			//
			break;
		} else {
			//
			if (newStyle.startIdx >= currentStyle.endIdx) {
				//
				styles.insert(styles.begin() + i + 1, newStyle);
				i++;
				i++;
				//
				break;
			}
		}
	}
	Console::println("insertStyle(): advance i = " + to_string(i) + " / " + to_string(styles.size()) + " / advance: " + to_string(charsToAdvance));
	// advance next styles
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		currentStyle.startIdx += charsToAdvance;
		currentStyle.endIdx += charsToAdvance;
	}
}

void clearStyles() {
	styles.clear();
}

void dumpStyles() {
	Console::println();
	Console::println("dumpStyles()");
	Console::println();
	for (auto &style : styles) {
		Console::println(to_string(style.startIdx) + " ... " + to_string(style.endIdx) + "(" + style.id + "), chars = " + to_string(style.endIdx - style.startIdx));
	}
	for (auto i = 0; i < 30; i++) {
		Console::print(string() + (char)((i % 10) + '0'));
	}
	Console::println();
	auto multipleStyles = false;
	for (auto i = 0; i < 30; i++) {
		auto styleCount = 0;
		for (auto j = 0; j < styles.size(); j++) {
			auto& currentStyle = styles[j];
			if (i >= currentStyle.startIdx && i < currentStyle.endIdx) {
				styleCount++;
				if (styleCount == 1) {
					Console::print(currentStyle.id);
				}
			}
		}
		if (styleCount == 0) {
			Console::print(" ");
		} else
		if (styleCount > 1) {
			multipleStyles = true;
		}
	}
	Console::println();
	if (multipleStyles == true) {
		Console::println("Multiple styles!");
	}
	Console::println();
}

int main(int argc, char **argv) {
	Application::installExceptionHandler();
	Console::println("StylesTest: init");
	{
		//
		/*
		Console::println("StylesTest: Insert Test");
		clearStyles();
		Console::println();
		insertStyle(6, 9, "A");
		insertStyle(16, 19, "B");
		dumpStyles();
		insertStyle(1, 2, "C");
		dumpStyles();
		Console::println();
		insertStyle(5, 8, "D");
		dumpStyles();
		Console::println();
		insertStyle(16, 20, "E");
		dumpStyles();
		Console::println();
		insertStyle(0, 7, "F");
		dumpStyles();
		*/
		Console::println("StylesTest: Insert Test");
		clearStyles();
		Console::println();
		insertStyle(1, 10, "A");
		insertStyle(5, 10, "B");
		dumpStyles();
		insertStyle(16, 20, "C");
		dumpStyles();
		/*
		//
		Console::println("StylesTest: Insert Test + Unset Test");
		clearStyles();
		insertStyle(0, 3, "A");
		insertStyle(3, 6, "B");
		insertStyle(6, 9, "C");
		insertStyle(9, 12, "D");
		dumpStyles();
		unsetStyle(2, 4);
		dumpStyles();
		unsetStyle(1, 11);
		dumpStyles();
		*/
		Console::println("StylesTest: Insert Test + Remove Test");
		/*
		clearStyles();
		 	 01234567890123456789
		 	 AAABBBCCCDDD
		 	     XXXXX
		insertStyle(0, 3, "A");
		insertStyle(3, 6, "B");
		insertStyle(6, 9, "C");
		insertStyle(9, 12, "D");
		dumpStyles();
		removeStyles(0, 4);
		dumpStyles();
		*/
	}
	Console::println("StylesTest: done");
}
