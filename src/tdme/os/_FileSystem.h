// Generated from /tdme/src/tdme/os/_FileSystem.java

#pragma once

#include <tdme/os/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::os::_FileSystemInterface;


struct default_init_tag;

/** 
 * File system 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::os::_FileSystem
	: public virtual Object
{

public:
	typedef Object super;

private:
	static _FileSystemInterface* fileSystem;

public:

	/** 
	 * Singleton instance to retrieve file system
	 * will use standard file system by default if not set up different explicitly
	 * @return
	 */
	static _FileSystemInterface* getInstance();

	/** 
	 * Set up file system
	 * @param file system
	 */
	static void setupFileSystem(_FileSystemInterface* fileSystem);

	// Generated
	_FileSystem();
protected:
	_FileSystem(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
