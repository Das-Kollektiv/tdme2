#pragma once

#include <memory>

using std::unique_ptr;

#include <tdme/tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>

using tdme::os::filesystem::FileSystemInterface;

/**
 * File system singleton class
 * @author Andreas Drewke
 */
class tdme::os::filesystem::FileSystem
{
private:
	STATIC_DLL_IMPEXT static unique_ptr<FileSystemInterface> standardFileSystem;
	STATIC_DLL_IMPEXT static unique_ptr<FileSystemInterface> fileSystem;

public:

	/**
	 * Singleton instance to retrieve file system
	 * will use standard file system by default if not set up different explicitly
	 * @return file system
	 */
	static FileSystemInterface* getInstance();

	/**
	 * Retrieve standard file system
	 * @return standard file system
	 */
	static FileSystemInterface* getStandardFileSystem();

	/**
	 * Set up file system
	 * @param fileSystem file system
	 */
	static void setupFileSystem(FileSystemInterface* fileSystem);

	/**
	 * Unset file system, which means disposing the old one and unset internal file system to use
	 */
	static void unsetFileSystem();

};
