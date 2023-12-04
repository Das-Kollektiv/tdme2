#include <miniscript/utilities/ExceptionBase.h>

#include <miniscript/miniscript.h>

#include <string>

using std::string;

using miniscript::utilities::ExceptionBase;

ExceptionBase::ExceptionBase(const string& message) throw(): runtime_error(message) {
}

ExceptionBase::~ExceptionBase() throw() {
}
