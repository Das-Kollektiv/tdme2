#pragma once

#include <string>

#include <tdme/tools/editor/misc/fwd-tdme.h>

using std::string;

/**
 * File dialog path
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::misc::FileDialogPath final
{
private:
	string path;

public:
	/**
	 * Public constructor
	 */
	inline FileDialogPath() {
		this->path = ".";
	}

	/**
	 * @return path
	 */
	inline const string& getPath() {
		return path;
	}

	/**
	 * Set path
	 * @param path path
	 */
	inline void setPath(const string& path) {
		this->path = path;
	}

};
