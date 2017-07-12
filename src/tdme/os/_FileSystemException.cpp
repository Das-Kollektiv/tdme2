#include <tdme/os/_FileSystemException.h>

#include "../utils/_Exception.h"

using tdme::os::_FileSystemException;
using tdme::utils::_Exception;

_FileSystemException::_FileSystemException(const wstring& message) throw() : _Exception(message) {
}
