#pragma once

#include <tdme/tdme.h>

#include <string>

using std::string;

/**
 * Filename filter
 * @author Andreas Drewke
 */
struct tdme::utils::FilenameFilter
{
	virtual ~FilenameFilter() {
	}

	virtual bool accept(const string& path, const string& file) = 0;
};
