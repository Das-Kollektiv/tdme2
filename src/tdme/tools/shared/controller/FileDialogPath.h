// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogPath.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>

using java::lang::String;

/** 
 * File dialog path
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::FileDialogPath
{
private:
	String* path {  };

public:

	/** 
	 * @return path
	 */
	virtual String* getPath();

	/** 
	 * Set path
	 * @param path
	 */
	virtual void setPath(String* path);

	/**
	 * Public constructor
	 */
	FileDialogPath(String* path);
};
