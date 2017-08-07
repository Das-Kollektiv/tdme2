// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <string>
#include <vector>

#include <tdme/utils/StringTokenizer.h>

using tdme::utils::StringTokenizer;

StringTokenizer::StringTokenizer() {
}

void StringTokenizer::tokenize(const wstring& str, const wstring& delimiters)
{
	idx = 0;
	elements.clear();
	wstring token;
	for (int i = 0; i < str.length(); i++) {
		// got a delimiter?
		if (delimiters.find(str[i]) != -1) {
			// yep, add token to elements if we have any
			if (token.length() > 0) {
				elements.push_back(token);
				token = L"";
			}
		} else {
			// no delimiter, add char to token
			token+= str[i];
		}
	}
	// do we have a token still? add it to elements
	if (token.length() > 0) {
		elements.push_back(token);
		token = L"";
	}
}

int32_t StringTokenizer::countTokens()
{
	return elements.size();
}

bool StringTokenizer::hasMoreTokens()
{
	return idx != elements.size();;
}

const wstring& StringTokenizer::nextToken()
{
	return elements[idx++];
}
