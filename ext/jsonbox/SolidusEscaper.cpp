/**
 * @version $Id: 8e8073bc5866f65e7cec8aa5391a004c8280d7ac $
 */

#include "SolidusEscaper.h"

#include "Grammar.h"

using namespace tdme::ext::jsonbox;

SolidusEscaper::SolidusEscaper() : afterBackSlash(false), inString(false) {
}

std::streambuf::int_type SolidusEscaper::operator()(std::streambuf &destination,
													std::streambuf::int_type character) {
	bool notEscaped = true;
	std::streambuf::char_type tmpChar = std::streambuf::traits_type::to_char_type(character);

	// If we encounter a quotation mark.
	if (tmpChar == Strings::Json::Escape::QUOTATION_MARK) {
		// If we're not in a string, we change that. If we're in a string,
		// we change that only if we're not after an escape back slash.
		inString = !inString || (afterBackSlash);

	} else if (inString && !afterBackSlash) {
		// If we are in a string definition and we're not after a backslash
		// escape.
		if (tmpChar == Strings::Std::SOLIDUS) {
			destination.sputn(Strings::Json::SOLIDUS.c_str(), Strings::Json::SOLIDUS.size());
			notEscaped = false;

		}

	}

	// We determine if we start a backslash escape or not.
	afterBackSlash = inString && !afterBackSlash && (tmpChar == Strings::Json::Escape::BEGIN_ESCAPE);
	return (notEscaped) ? (destination.sputc(tmpChar)) : (0);
}
