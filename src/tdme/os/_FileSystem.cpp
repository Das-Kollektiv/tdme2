// Generated from /tdme/src/tdme/os/_FileSystem.java
#include <tdme/os/_FileSystem.h>

#include <tdme/os/_FileSystemInterface.h>
#include <tdme/os/_StandardFileSystem.h>

using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::os::_StandardFileSystem;

_FileSystem::_FileSystem(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_FileSystem::_FileSystem()
	: _FileSystem(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

_FileSystemInterface* _FileSystem::fileSystem;

_FileSystemInterface* _FileSystem::getInstance()
{
	clinit();
	if (fileSystem == nullptr) {
		fileSystem = new _StandardFileSystem();
	}
	return fileSystem;
}

void _FileSystem::setupFileSystem(_FileSystemInterface* fileSystem)
{
	clinit();
	_FileSystem::fileSystem = fileSystem;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _FileSystem::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.os._FileSystem", 19);
    return c;
}

void _FileSystem::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		fileSystem = nullptr;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* _FileSystem::getClass0()
{
	return class_();
}

