#pragma once

#include <tdme/os/filesystem/fwd-tdme.h>

using tdme::os::filesystem::FileSystemInterface;

/** 
 * File system 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::os::filesystem::FileSystem
{
private:
	static FileSystemInterface* fileSystem;

public:

	/** 
	 * Singleton instance to retrieve file system
	 * will use standard file system by default if not set up different explicitly
	 * @return
	 */
	static FileSystemInterface* getInstance();

	/** 
	 * Set up file system
	 * @param fileSystem file system
	 */
	static void setupFileSystem(FileSystemInterface* fileSystem);

};
