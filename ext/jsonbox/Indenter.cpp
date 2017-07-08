/**
 * @version $Id: 29ac69ff596f36271f9b77ffb4097be094290c35 $
 */

#include "Indenter.h"

#include "Grammar.h"

using namespace tdme::ext::jsonbox;

Indenter::Indenter() : atStartOfLine(true) {
}

std::streambuf::int_type Indenter::operator()(std::streambuf &destination,
											  std::streambuf::int_type character) {
	std::streambuf::char_type tmpChar = std::streambuf::traits_type::to_char_type(character);

	if (atStartOfLine && tmpChar != Whitespace::NEW_LINE) {
		destination.sputc(Whitespace::HORIZONTAL_TAB);
	}

	atStartOfLine = (tmpChar == Whitespace::NEW_LINE);
	return destination.sputc(tmpChar);
}
