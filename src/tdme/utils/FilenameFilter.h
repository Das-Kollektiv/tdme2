// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>

#include <string>

using std::wstring;

struct tdme::utils::FilenameFilter
{
	virtual bool accept(const wstring& path, const wstring& file) = 0;
};
