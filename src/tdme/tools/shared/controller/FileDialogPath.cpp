#include <tdme/tools/shared/controller/FileDialogPath.h>

#include <java/lang/String.h>

using tdme::tools::shared::controller::FileDialogPath;
using java::lang::String;

FileDialogPath::FileDialogPath(const wstring& path)
{
	this->path = path;
}

const wstring& FileDialogPath::getPath()
{
	return path;
}

void FileDialogPath::setPath(const wstring& path)
{
	this->path = path;
}
