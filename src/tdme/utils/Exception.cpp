/**
 * @version $Id: 08dc212774a2e041a7fa2cb77f4a53bc7796559f $
 */

#include "Exception.h"

#include <string>

#include <tdme/utils/StringConverter.h>

using std::wstring;
using tdme::utils::Exception;
using tdme::utils::StringConverter;

Exception::Exception(const wstring &message) throw(): runtime_error(StringConverter::toString(message)) {
}

Exception::~Exception() throw() {
}
