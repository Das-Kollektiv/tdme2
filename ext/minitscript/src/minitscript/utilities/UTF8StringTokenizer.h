#pragma once

#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/fwd-minitscript.h>

using std::string;
using std::vector;

/**
 * UTF8 string tokenizer class
 * @author Andreas Drewke
 */
class minitscript::utilities::UTF8StringTokenizer
{

private:
	vector<string> tokens;
	int idx { 0 };

public:
	/**
	 * Public constructor
	 */
	UTF8StringTokenizer() {};

	/**
	 * Tokenize
	 * @param str string to tokenize
	 * @param delimiters delimiters
	 * @param emptyTokens include empty tokens
	 */
	void tokenize(const string& str, const string& delimiters, bool emptyTokens = false);

	/**
	 * @return number of tokens
	 */
	inline int32_t countTokens() {
		return tokens.size();
	}

	/**
	 * @return has more tokens
	 */
	inline bool hasMoreTokens() {
		return idx != tokens.size();
	}

	/**
	 * @return next token
	 */
	inline const string& nextToken() {
		return tokens[idx++];
	}

	/**
	 * @return tokens
	 */
	inline const vector<string>& getTokens() {
		return tokens;
	}

};
