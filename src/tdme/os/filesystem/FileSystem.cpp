#include <tdme/os/filesystem/FileSystem.h>

#include <tdme/tdme.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/filesystem/StandardFileSystem.h>

using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::filesystem::StandardFileSystem;

FileSystemInterface* FileSystem::fileSystem = nullptr;
FileSystemInterface* FileSystem::standardFileSystem = nullptr;

FileSystemInterface* FileSystem::getInstance()
{
	if (fileSystem == nullptr) {
		if (standardFileSystem == nullptr) standardFileSystem = new StandardFileSystem();
		fileSystem = standardFileSystem;
	}
	return fileSystem;
}

FileSystemInterface* FileSystem::getStandardFileSystem()
{
	if (standardFileSystem == nullptr) {
		standardFileSystem = new StandardFileSystem();
	}
	return standardFileSystem;
}

void FileSystem::setupFileSystem(FileSystemInterface* fileSystem)
{
	FileSystem::fileSystem = fileSystem;
}

void FileSystem::unsetFileSystem()
{
	if (FileSystem::fileSystem != nullptr) delete FileSystem::fileSystem;
	FileSystem::fileSystem = nullptr;
}
