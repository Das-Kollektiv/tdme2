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
	Console::println("insertStyle(): " + to_string(startIdx) + ", " + to_string(endIdx));
	//
	TextStyle newStyle;
	newStyle.startIdx = startIdx;
	newStyle.endIdx = endIdx;
	newStyle.id = id;
	//
	auto insertedChars = endIdx - startIdx;
	//
	if (styles.empty() == true) {
		styles.push_back(newStyle);
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
	// adjust styles
	Console::println("insertStyle(): initial i = " + to_string(i) + " / " + to_string(styles.size()));
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		Console::println("aaa");
		// check if the current range ins within range to be removed
		if (currentStyle.startIdx >= startIdx && currentStyle.endIdx <= endIdx) {
			// remove the overlapping range
			styles.erase(styles.begin() + i);
			i--;
		} else
		// check if the current range overlaps with the range to be removed
		if (currentStyle.startIdx < endIdx && currentStyle.endIdx > startIdx) {
			Console::println("bbb");
			Console::println("Collision: " + to_string(currentStyle.startIdx) + " ... " + to_string(currentStyle.endIdx) + " / " + to_string(newStyle.startIdx) + " ... " + to_string(newStyle.endIdx));
			auto currentStyleStartIdx = currentStyle.startIdx;
			auto currentStyleEndIdx = currentStyle.endIdx;
			auto styleA = currentStyle;
			auto styleB = currentStyle;
			// remove the overlapping range
			styles.erase(styles.begin() + i);
			// split the overlapping range into two non-overlapping ranges
			if (currentStyleStartIdx < startIdx) {
				styleA.endIdx = newStyle.startIdx;
				styles.insert(styles.begin() + i++, styleA);
			}
			//
			styles.insert(styles.begin() + i++, newStyle);
			//
			if (currentStyleEndIdx > endIdx) {
				styleB.startIdx = endIdx;
				styleB.endIdx += insertedChars;
				styles.insert(styles.begin() + i++, styleB);
			}
			//
			break;
		} else {
			Console::println("ccc");
			if (newStyle.startIdx >= currentStyle.endIdx) {
				Console::println("ddd");
				styles.insert(styles.begin() + i + 1, newStyle);
				i++;
				i++;
				//
				break;
			}
		}
	}
	Console::println("insertStyle(): advance i = " + to_string(i) + " / " + to_string(styles.size()));
	// advance next styles
	for (; i < styles.size(); i++) {
		auto &currentStyle = styles[i];
		currentStyle.startIdx += insertedChars;
		currentStyle.endIdx += insertedChars;
	}
}

void clearStyles() {
	styles.clear();
}

void dumpStyles() {
	Console::println("dumpStyles()");
	for (auto &style : styles) {
		Console::println("\t" + to_string(style.startIdx) + " ... " + to_string(style.endIdx) + "(" + style.id + ")");
	}
}

int main(int argc, char **argv) {
	Application::installExceptionHandler();
	Console::println("StylesTest: init");
	{
		//
		Console::println("StylesTest: Insert Test");
		clearStyles();
		insertStyle(0, 3, "0-3");
		insertStyle(3, 6, "3-6");
		insertStyle(6, 9, "6-9");
		insertStyle(9, 12, "9-12");
		dumpStyles();
		insertStyle(1, 2, "1-2");
		dumpStyles();
		insertStyle(5, 8, "5-8");
		dumpStyles();
		/*
		//
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
		insertStyle(3, 6);
		insertStyle(1, 2);
		dumpStyles();
		 */
	}
	Console::println("StylesTest: done");
}
