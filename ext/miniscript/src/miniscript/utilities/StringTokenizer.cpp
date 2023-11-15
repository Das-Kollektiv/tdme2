#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/StringTokenizer.h>

using std::string;

using miniscript::utilities::StringTokenizer;

StringTokenizer::StringTokenizer() {
}

void StringTokenizer::tokenize(const string& str, const string& delimiters)
{
	idx = 0;
	tokens.clear();
	string token;
	for (int i = 0; i < str.length(); i++) {
		// got a delimiter?
		if (delimiters.find(str[i]) != string::npos) {
			// yep, add token to elements if we have any
			if (token.length() > 0) {
				tokens.push_back(token);
				token.clear();
			}
		} else {
			// no delimiter, add char to token
			token+= str[i];
		}
	}
	// do we have a token still? add it to elements
	if (token.empty() == false) {
		tokens.push_back(token);
	}
}
