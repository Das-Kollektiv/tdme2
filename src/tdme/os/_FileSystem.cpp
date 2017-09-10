#include <tdme/os/_FileSystem.h>

#include <tdme/os/_FileSystemInterface.h>
#include <tdme/os/_StandardFileSystem.h>

using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::os::_StandardFileSystem;

 _FileSystemInterface* _FileSystem::fileSystem = nullptr;

_FileSystemInterface* _FileSystem::getInstance()
{
	if (fileSystem == nullptr) {
		fileSystem = new _StandardFileSystem();
	}
	return fileSystem;
}

void _FileSystem::setupFileSystem(_FileSystemInterface* fileSystem)
{
	_FileSystem::fileSystem = fileSystem;
}
