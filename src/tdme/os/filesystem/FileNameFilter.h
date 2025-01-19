#pragma once

#include <tdme/tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>

#include <string>

using std::string;

/**
 * File system file name filter interface
 * @author Andreas Drewke
 */
struct tdme::os::filesystem::FileNameFilter
{
	/**
	 * Destructor
	 */
	virtual ~FileNameFilter() {}

	/**
	 * Accept a file
	 * @param path path
	 * @param file file
	 * @returns if to accept file
	 */
	virtual bool accept(const string& path, const string& file) = 0;
};
