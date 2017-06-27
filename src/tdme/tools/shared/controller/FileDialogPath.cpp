// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogPath.java
#include <tdme/tools/shared/controller/FileDialogPath.h>

#include <java/lang/String.h>

using tdme::tools::shared::controller::FileDialogPath;
using java::lang::String;

FileDialogPath::FileDialogPath(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

FileDialogPath::FileDialogPath(String* path) 
	: FileDialogPath(*static_cast< ::default_init_tag* >(0))
{
	ctor(path);
}

void FileDialogPath::ctor(String* path)
{
	super::ctor();
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

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FileDialogPath::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.FileDialogPath", 43);
    return c;
}

java::lang::Class* FileDialogPath::getClass0()
{
	return class_();
}

