#include <agui/utilities/ExceptionBase.h>

#include <agui/agui.h>

#include <string>

using std::string;

using agui::utilities::ExceptionBase;

ExceptionBase::ExceptionBase(const string& message) throw(): runtime_error(message) {
}

ExceptionBase::~ExceptionBase() throw() {
}
