/**
 * @version $Id: 4bf21d6d9bb9b0fa83ed0ac645f115842e37c64d $
 */

#pragma once

#include <string>

#include <tdme/utils/ExceptionBase.h>

using std::wstring;

using tdme::utils::ExceptionBase;

namespace tdme {
namespace ext {
namespace jsonbox {

/**
 * Base exception class for threading exceptions
 * @author Andreas Drewke
 */
class JsonException: public ExceptionBase {
	public:
		/**
		 * @brief public constructor
		 * @param message exception message
		 */
		JsonException(const string& message) throw();
};

};
};
};

