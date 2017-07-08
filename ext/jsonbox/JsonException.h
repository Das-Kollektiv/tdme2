/**
 * @version $Id: 4bf21d6d9bb9b0fa83ed0ac645f115842e37c64d $
 */

#pragma once

#include <string>

#include <tdme/utils/Exception.h>

using std::wstring;

namespace tdme {
namespace ext {
namespace jsonbox {

/**
 * Base exception class for threading exceptions
 * @author Andreas Drewke
 */
class JsonException: public tdme::utils::Exception {
	public:
		/**
		 * @brief public constructor
		 * @param message exception message
		 */
		JsonException(const wstring &message) throw();
};

};
};
};

