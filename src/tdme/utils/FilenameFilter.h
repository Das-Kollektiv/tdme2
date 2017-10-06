
#pragma once

#include <fwd-tdme.h>

#include <string>

using std::wstring;

struct tdme::utils::FilenameFilter
{
	virtual bool accept(const wstring& path, const wstring& file) = 0;
};
