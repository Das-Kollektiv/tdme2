#include <tdme/os/filesystem/FileSystem.h>

#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/filesystem/StandardFileSystem.h>

using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::filesystem::StandardFileSystem;

FileSystemInterface* FileSystem::fileSystem = nullptr;

FileSystemInterface* FileSystem::getInstance()
{
	if (fileSystem == nullptr) {
		fileSystem = new StandardFileSystem();
	}
	return fileSystem;
}

void FileSystem::setupFileSystem(FileSystemInterface* fileSystem)
{
	FileSystem::fileSystem = fileSystem;
}
