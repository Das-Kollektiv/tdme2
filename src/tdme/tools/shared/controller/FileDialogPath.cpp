// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogPath.java
#include <tdme/tools/shared/controller/FileDialogPath.h>

#include <java/lang/String.h>

using tdme::tools::shared::controller::FileDialogPath;
using java::lang::String;

FileDialogPath::FileDialogPath(String* path) 
{
	this->path = path;
}

String* FileDialogPath::getPath()
{
	return path;
}

void FileDialogPath::setPath(String* path)
{
	this->path = path;
}
