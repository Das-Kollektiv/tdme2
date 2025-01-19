#include <agui/agui.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/utilities/ExceptionBase.h>

using agui::os::filesystem::FileSystemException;

FileSystemException::FileSystemException(const string& message) throw() : ExceptionBase(message) {
}
