/**
 * @version $Id: 51a356f87aa9eaf8c6dcd1b7de8c5a4ffb327c4b $
 */

#pragma once

#include <streambuf>

namespace tdme {
namespace ext {
namespace jsonbox {

class SolidusEscaper {
public:
	SolidusEscaper();

	std::streambuf::int_type operator()(std::streambuf &destination,
										std::streambuf::int_type character);
private:
	bool afterBackSlash;
	bool inString;
};

};
};
};
