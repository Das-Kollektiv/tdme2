
#pragma once

#include <string>

#include <tdme/tools/shared/controller/fwd-tdme.h>

using std::string;


/** 
 * File dialog path
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::FileDialogPath
{
private:
	string path {  };

public:

	/** 
	 * @return path
	 */
	virtual const string& getPath();

	/** 
	 * Set path
	 * @param path
	 */
	virtual void setPath(const string& path);

	/**
	 * Public constructor
	 */
	FileDialogPath(const string& path);
};
