/**
 * @version $Id: 2b0de0270d570e1017148238ca5e25502fda54b1 $
 */

#pragma once

#include <streambuf>

namespace tdme {
namespace ext {
namespace jsonbox {

/**
 * Adds a level of indentation to a streambuf.
 * @see TDMEJson::OutputFilter
 */
class Indenter {
public:
	/**
	 * Default constructor.
	 */
	Indenter();

	/**
	 * Inserts a tab character at the start of each line.
	 * @param destination Streambuf in which to insert the tab character.
	 * @param character Character to insert in the streambuf.
	 * @return Unspecified value not equal to traits::eof() on success,
	 * traits::eof() on failure.
	 */
	std::streambuf::int_type operator()(std::streambuf &destination,
										std::streambuf::int_type character);
private:
	/// Used to indicate if we are at the start of a new line.
	bool atStartOfLine;
};

};
};
};
