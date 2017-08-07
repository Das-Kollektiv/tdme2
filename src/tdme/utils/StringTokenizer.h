// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <string>
#include <vector>

#include <tdme/utils/fwd-tdme.h>

using std::vector;
using std::wstring;

/**
 * String tokenizer class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::StringTokenizer
{

private:
	vector<wstring> elements;
	int idx { 0 };

public:
	/**
	 * Tokenize
	 * @param string to tokenize
	 * @param delimiters
	 */
	void tokenize(const wstring& str, const wstring& delimiters);

	/**
	 * @return number of tokens
	 */
	int32_t countTokens();

	/**
	 * @return has more tokens
	 */
	bool hasMoreTokens();

	/**
	 * @return next token
	 */
	const wstring& nextToken();

	/**
	 * Public constructor
	 */
	StringTokenizer();
};
