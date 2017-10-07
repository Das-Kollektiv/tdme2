#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/utils/ExceptionBase.h>

using tdme::os::filesystem::_FileSystemException;

_FileSystemException::_FileSystemException(const string& message) throw() : ExceptionBase(message) {
}
