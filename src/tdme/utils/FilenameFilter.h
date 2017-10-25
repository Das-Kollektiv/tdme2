
#pragma once

#include <tdme.h>

#include <string>

using std::string;

struct tdme::utils::FilenameFilter
{
	virtual bool accept(const string& path, const string& file) = 0;
};
