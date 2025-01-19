#pragma once

#include <agui/agui.h>
#include <agui/os/filesystem/fwd-agui.h>

#include <string>

using std::string;

/**
 * File system file name filter interface
 * @author Andreas Drewke
 */
struct agui::os::filesystem::FileNameFilter
{
	/**
	 * Destructor
	 */
	virtual ~FileNameFilter() {}

	/**
	 * Accept a file
	 * @param path path
	 * @param file file
	 * @return if to accept file
	 */
	virtual bool accept(const string& path, const string& file) = 0;
};
