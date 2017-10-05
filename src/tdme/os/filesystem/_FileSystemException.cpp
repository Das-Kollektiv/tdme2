#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/utils/_ExceptionBase.h>

using tdme::os::filesystem::_FileSystemException;

_FileSystemException::_FileSystemException(const string& message) throw() : _ExceptionBase(message) {
}
