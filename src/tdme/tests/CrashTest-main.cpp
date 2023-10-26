#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>

using tdme::application::Application;
using tdme::utilities::Character;
using tdme::utilities::Console;

/**
 * Returns if a given string is a inline function
 * @param candidate candidate
 * @param arguments arguments
 * @param functionScriptCode function script code
 * @return if candidate is a inline function
 */
inline bool viewIsInlineFunction(const string_view& candidate, vector<string_view>& arguments, string_view& functionScriptCode) {
	if (candidate.size() == 0) return false;
	//
	auto i = 0;
	// (
	if (candidate[i++] != '(') return false;
	// spaces
	for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++); if (i >= candidate.size()) return false;
	//
	auto argumentStartIdx = string::npos;
	auto argumentEndIdx = string::npos;
	//
	for (; i < candidate.size(); i++) {
		auto c = candidate[i];
		if (c == '=') {
			if (argumentStartIdx == string::npos) {
				argumentStartIdx = i;
			} else {
				return false;
			}
		} else
		if (c == '$') {
			if (argumentStartIdx == string::npos) {
				argumentStartIdx = i;
			} else
			if (argumentStartIdx == i - 1 && candidate[argumentStartIdx] == '=') {
				// no op
			} else {
				return false;
			}
		} else
		if (c == ',' || c == ')') {
			if (argumentEndIdx == string::npos) {
				if (argumentStartIdx != string::npos) {
					argumentEndIdx = i;
					arguments.push_back(string_view(&candidate[argumentStartIdx], argumentEndIdx - argumentStartIdx));
				}
				//
				argumentStartIdx = string::npos;
				argumentEndIdx = string::npos;
			} else {
				return false;
			}
			if (c == ')') {
				i++;
				break;
			}
		} else
		if (argumentStartIdx != string::npos && Character::isAlphaNumeric(candidate[i]) == false && c != '_') {
			return false;
		}
	}
	//
	if (i >= candidate.size()) return false;
	// spaces
	for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++); if (i >= candidate.size()) return false;
	// -
	if (candidate[i++] != '-') return false;
	//
	if (i >= candidate.size()) return false;
	// >
	if (candidate[i++] != '>') return false;
	// spaces
	for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++); if (i >= candidate.size()) return false;
	//
	if (candidate[i++] != '{') return false;
	//
	auto scriptCodeStartIdx = i;
	auto scriptCodeEndIdx = string::npos;
	//
	for (auto j = candidate.size() - 1; j > i; j--) {
		if (candidate[j] == '}') {
			scriptCodeEndIdx = j;
			break;
		} else
		if (Character::isSpace(candidate[j]) == false) {
			return false;
		}
	}
	//
	if (scriptCodeEndIdx == string::npos) return false;
	//
	functionScriptCode = string_view(&candidate[scriptCodeStartIdx], scriptCodeEndIdx - scriptCodeStartIdx);
	//
	return true;
}


int main(int argc, char** argv) {
	string_view candidate = "($penis, =$penisName) -> { console.log($penis, " ", $penisName); $penisName = \"xxx\"}";
	vector<string_view> arguments;
	string_view functionScriptCode;
	if (viewIsInlineFunction(candidate, arguments, functionScriptCode) == true) {
		Console::println("xxx");
		for (const auto& argument: arguments) Console::println(argument);
		Console::println(functionScriptCode);
	} else {
		Console::println("yyy");
	}
	//

	Console::shutdown();
	return 0;
}
