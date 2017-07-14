/**
 * @version $Id$
 */
#include "_ExceptionBase.h"

#include <string>

#include <tdme/utils/StringConverter.h>

using std::wstring;

using tdme::utils::_ExceptionBase;

_ExceptionBase::_ExceptionBase(const string& message) throw(): runtime_error(message) {
}

_ExceptionBase::~_ExceptionBase() throw() {
}
