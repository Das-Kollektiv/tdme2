
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
	string path;

public:
	/**
	 * Public constructor
	 */
	FileDialogPath(const string& path);

	/**
	 * @return path
	 */
	virtual const string& getPath();

	/**
	 * Set path
	 * @param path path
	 */
	virtual void setPath(const string& path);

};
