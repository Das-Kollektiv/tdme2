#include <agui/os/filesystem/FileSystem.h>

#include <memory>

using std::make_unique;
using std::unique_ptr;

#include <agui/agui.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/os/filesystem/StandardFileSystem.h>

using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;
using agui::os::filesystem::StandardFileSystem;

unique_ptr<FileSystemInterface> FileSystem::fileSystem;
unique_ptr<FileSystemInterface> FileSystem::standardFileSystem;

FileSystemInterface* FileSystem::getInstance()
{
	if (fileSystem == nullptr) return getStandardFileSystem();
	return fileSystem.get();
}

FileSystemInterface* FileSystem::getStandardFileSystem()
{
	if (standardFileSystem == nullptr) standardFileSystem = make_unique<StandardFileSystem>();
	return standardFileSystem.get();
}

void FileSystem::setupFileSystem(FileSystemInterface* fileSystem)
{
	FileSystem::fileSystem = unique_ptr<FileSystemInterface>(fileSystem);
}

void FileSystem::unsetFileSystem()
{
	FileSystem::fileSystem = nullptr;
}
