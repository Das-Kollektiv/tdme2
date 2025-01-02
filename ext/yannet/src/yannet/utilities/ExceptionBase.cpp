#include <yannet/utilities/ExceptionBase.h>

#include <yannet/yannet.h>

#include <string>

using std::string;

using yannet::utilities::ExceptionBase;

ExceptionBase::ExceptionBase(const string& message) throw(): runtime_error(message) {
}

ExceptionBase::~ExceptionBase() throw() {
}
