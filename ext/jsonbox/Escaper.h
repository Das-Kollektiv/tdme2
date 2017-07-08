/**
 * @version $Id: 9d45f4d1fe21f2adf7c86a54d17a44a846849ee4 $
 */

#pragma once

#include <streambuf>

namespace tdme {
namespace ext {
namespace jsonbox {

class Escaper {
public:
	Escaper();

	std::streambuf::int_type operator()(std::streambuf &destination,
										std::streambuf::int_type character);
private:
	bool afterBackSlash;
	bool inString;
};

};
};
};

