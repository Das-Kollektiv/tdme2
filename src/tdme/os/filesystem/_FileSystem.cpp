#include <tdme/os/filesystem/_FileSystem.h>

#include <tdme/os/filesystem/_FileSystemInterface.h>
#include <tdme/os/filesystem/_StandardFileSystem.h>

using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemInterface;
using tdme::os::filesystem::_StandardFileSystem;

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
