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
	auto removedChars = endIdx - startIdx;
	// find first style that is before new style or has collision
	auto i = 0;
	while (true == true) {
		auto &currentStyle = styles[i];
		//
		if (startIdx > currentStyle.endIdx) {
			// no op
		} else {
			i++;
			break;
		}
		i++;
	}
	Console::println("removeStyle(): initial i = " + to_string(i) + " / " + to_string(styles.size()));
	//
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		// check if the range to be removed is within current range
		if (startIdx >= currentStyle.startIdx  && endIdx <= currentStyle.endIdx) {
			Console::println("aaa");
			// remove the overlapping range
			styles.erase(styles.begin() + i);
			// stop here, readvance next styles
			break;
		} else
		// check if the current range ins within range to be removed
		if (currentStyle.startIdx >= startIdx && currentStyle.endIdx <= endIdx) {
			// remove the overlapping range
			styles.erase(styles.begin() + i);
			//
			i--;
		} else
		// check if the current range overlaps with the range to be removed
		if (currentStyle.startIdx < endIdx && currentStyle.endIdx > startIdx) {
			Console::println("bbb");
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
				styleB.endIdx -= removedChars;
				styles.insert(styles.begin() + i, styleB);
			}
			// stop here, readvance next styles
			break;
		} else {
			Console::println("ccc");
			if (startIdx >= currentStyle.endIdx) {
				i++;
				//
				break;
			}
		}
	}
	Console::println("removeStyle(): advance i = " + to_string(i) + " / " + to_string(styles.size()));
	// unadvance next styles
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		currentStyle.startIdx -= removedChars;
		currentStyle.endIdx -= removedChars;
	}
}

void insertStyle(int startIdx, int endIdx, const string &id) {
	//
	TextStyle newStyle;
	newStyle.startIdx = startIdx;
	newStyle.endIdx = endIdx;
	newStyle.id = id;
	//
	auto charsToAdvance = endIdx - startIdx;
	//
	Console::println("insertStyle(): " + to_string(startIdx) + ", " + to_string(endIdx) + ", chars to advance: " + to_string(charsToAdvance));
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
	Console::println("xxx: " + to_string(styles[i].startIdx) + " / " + to_string(styles[i].endIdx));
	// adjust styles
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		// check if the current range overlaps with the range to be removed
		if (currentStyle.startIdx < endIdx && currentStyle.endIdx > startIdx) {
			Console::println("aaa");
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
				Console::println("aaa.1");
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
				Console::println("aaa.2");
				styles.insert(styles.begin() + i++, styleB);
				//
				charsToAdvance = styleB.endIdx - currentStyleEndIdx;
			}
			//
			break;
		} else {
			Console::println("bbb.1");
			//
			if (newStyle.startIdx >= currentStyle.endIdx) {
				//
				Console::println("bbb.2");
				//
				styles.insert(styles.begin() + i + 1, newStyle);
				i++;
				i++;
				//
				break;
			}
		}
	}
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
	Console::println("dumpStyles()");
	for (auto &style : styles) {
		Console::println("\t" + to_string(style.startIdx) + " ... " + to_string(style.endIdx) + "(" + style.id + "), chars = " + to_string(style.endIdx - style.startIdx));
	}
}

int main(int argc, char **argv) {
	Application::installExceptionHandler();
	Console::println("StylesTest: init");
	{
		//
		Console::println("StylesTest: Insert Test");
		clearStyles();
		Console::println();
		insertStyle(6, 9, "6-9");
		insertStyle(16, 19, "16-19");
		dumpStyles();
		insertStyle(1, 2, "1-2");
		dumpStyles();
		Console::println();
		insertStyle(5, 8, "5-8");
		dumpStyles();
		Console::println();
		insertStyle(16, 20, "16-20");
		dumpStyles();
		Console::println();
		insertStyle(0, 7, "0-7");
		dumpStyles();
		//
		/*
		Console::println("StylesTest: Insert Test + Unset Test");
		clearStyles();
		insertStyle(0, 3, "0-3");
		insertStyle(3, 6, "3-6");
		insertStyle(6, 9, "6-9");
		insertStyle(9, 12, "9-12");
		dumpStyles();
		unsetStyle(2, 4);
		dumpStyles();
		unsetStyle(1, 11);
		dumpStyles();
		*/
		/*
		Console::println("StylesTest: Insert Test + Remove Test");
		clearStyles();
		insertStyle(0, 3, "0-3");
		insertStyle(3, 6, "3-6");
		insertStyle(6, 9, "6-9");
		insertStyle(9, 12, "9-12");
		dumpStyles();
		removeStyles(1, 11);
		dumpStyles();
		Console::println("StylesTest: Unset all");
		unsetStyle(0, 14);
		dumpStyles();
		dumpStyles();
		*/
	}
	Console::println("StylesTest: done");
}
