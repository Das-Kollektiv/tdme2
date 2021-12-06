#include <tdme/utilities/ExceptionBase.h>

#include <tdme/tdme.h>

#include <string>

using std::string;

using tdme::utilities::ExceptionBase;

ExceptionBase::ExceptionBase(const string& message) throw(): runtime_error(message) {
}

ExceptionBase::~ExceptionBase() throw() {
}
