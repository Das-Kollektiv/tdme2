#include <tdme/os/_FileSystemException.h>
#include <tdme/utils/_ExceptionBase.h>

using tdme::os::_FileSystemException;

_FileSystemException::_FileSystemException(const string& message) throw() : _ExceptionBase(message) {
}
