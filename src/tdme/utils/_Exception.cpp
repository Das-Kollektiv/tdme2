/**
 * @version $Id: 08dc212774a2e041a7fa2cb77f4a53bc7796559f $
 */

#include <string>

#include <tdme/utils/StringConverter.h>
#include "_Exception.h"

using std::wstring;
using tdme::utils::_Exception;
using tdme::utils::StringConverter;

_Exception::_Exception(const wstring &message) throw(): runtime_error(StringConverter::toString(message)) {
}

_Exception::~_Exception() throw() {
}
