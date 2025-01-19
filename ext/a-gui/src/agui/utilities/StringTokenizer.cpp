#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/utilities/StringTokenizer.h>

using std::string;

using agui::utilities::StringTokenizer;

StringTokenizer::StringTokenizer() {
}

void StringTokenizer::tokenize(const string& str, const string& delimiters, bool emptyTokens)
{
	idx = 0;
	tokens.clear();
	string token;
	for (int i = 0; i < str.length(); i++) {
		// got a delimiter?
		if (delimiters.find(str[i]) != string::npos) {
			// yep, add token to elements if we have any
			if (emptyTokens == true || token.empty() == false) {
				tokens.push_back(token);
				token.clear();
			}
		} else {
			// no delimiter, add char to token
			token+= str[i];
		}
	}
	// do we have a token still? add it to elements
	if (emptyTokens == true || token.empty() == false) {
		tokens.push_back(token);
	}
}
