#pragma once

#include <memory>

using std::unique_ptr;

#include <agui/agui.h>
#include <agui/os/filesystem/fwd-agui.h>

/**
 * File system singleton class
 * @author Andreas Drewke
 */
class agui::os::filesystem::FileSystem
{
private:
	AGUI_STATIC_DLL_IMPEXT static unique_ptr<FileSystemInterface> standardFileSystem;
	AGUI_STATIC_DLL_IMPEXT static unique_ptr<FileSystemInterface> fileSystem;

public:

	/**
	 * Singleton instance to retrieve file system
	 * will use standard file system by default if not set up different explicitly
	 * @returns file system
	 */
	static FileSystemInterface* getInstance();

	/**
	 * Retrieve standard file system
	 * @returns standard file system
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
