
#pragma once

#include <string>

#include <tdme/tools/shared/controller/fwd-tdme.h>

using std::wstring;


/** 
 * File dialog path
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::FileDialogPath
{
private:
	wstring path {  };

public:

	/** 
	 * @return path
	 */
	virtual const wstring& getPath();

	/** 
	 * Set path
	 * @param path
	 */
	virtual void setPath(const wstring& path);

	/**
	 * Public constructor
	 */
	FileDialogPath(const wstring& path);
};
