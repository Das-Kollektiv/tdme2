#include <minitscript/utilities/ExceptionBase.h>

#include <minitscript/minitscript.h>

#include <string>

using std::string;

using minitscript::utilities::ExceptionBase;

ExceptionBase::ExceptionBase(const string& message) throw(): runtime_error(message) {
}

ExceptionBase::~ExceptionBase() throw() {
}
