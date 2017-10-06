#include <tdme/tools/shared/controller/FileDialogPath.h>


using tdme::tools::shared::controller::FileDialogPath;

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
