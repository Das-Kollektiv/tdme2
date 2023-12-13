#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/UTF8StringTokenizer.h>
#include <miniscript/utilities/UTF8CharacterIterator.h>

using std::string;

using miniscript::utilities::Character;
using miniscript::utilities::UTF8StringTokenizer;
using miniscript::utilities::UTF8CharacterIterator;

void UTF8StringTokenizer::tokenize(const string& str, const string& delimiters, bool emptyTokens)
{
	idx = 0;
	tokens.clear();
	//
	string token;
	//
	UTF8CharacterIterator u8It(str);
	UTF8CharacterIterator delimiterU8It(delimiters);
	// iterate string value
	for (; u8It.hasNext(); ) {
		auto c = u8It.next();
		// iterate delimiters
		delimiterU8It.reset();
		//
		auto foundDelimiter = false;
		for (; delimiterU8It.hasNext(); ) {
			// check if delimiter character is our current string value char
			auto dc = delimiterU8It.next();
			// got a delimiter?
			if (c == dc) {
				foundDelimiter = true;
				// yep, add token to elements if we have any
				if (emptyTokens == true || token.empty() == false) {
					tokens.push_back(token);
					token.clear();
				}
				//
				break;
			}
		}
		//
		if (foundDelimiter == false) {
			// no delimiter, add char to token
			token+= Character::toString(c);
		}
	}
	// do we have a token still? add it to elements
	if (emptyTokens == true || token.empty() == false) {
		tokens.push_back(token);
	}
}
