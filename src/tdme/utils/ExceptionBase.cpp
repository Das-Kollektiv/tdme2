/**
 * @version $Id$
 */
#include "ExceptionBase.h"

#include <string>

#include <tdme/utils/StringConverter.h>

using std::wstring;

using tdme::utils::ExceptionBase;

ExceptionBase::ExceptionBase(const string& message) throw(): runtime_error(message) {
}

ExceptionBase::~ExceptionBase() throw() {
}
