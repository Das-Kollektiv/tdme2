// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogScreenController.java
#include <tdme/tools/shared/controller/FileDialogScreenController_setupFileDialogListBox_1.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::controller::FileDialogScreenController_setupFileDialogListBox_1;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::NullPointerException;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

FileDialogScreenController_setupFileDialogListBox_1::FileDialogScreenController_setupFileDialogListBox_1(FileDialogScreenController *FileDialogScreenController_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, FileDialogScreenController_this(FileDialogScreenController_this)
{
	clinit();
	ctor();
}

bool FileDialogScreenController_setupFileDialogListBox_1::accept(String* directory, String* file)
{
	if (_FileSystem::getInstance()->isPath(new String(directory->getCPPWString() + L"/" + file->getCPPWString())) == true)
		return true;

	for (auto extension : *FileDialogScreenController_this->extensions) {
		if (file->toLowerCase()->endsWith(::java::lang::StringBuilder().append(u"."_j)->append(extension)->toString()))
			return true;

	}
	return false;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FileDialogScreenController_setupFileDialogListBox_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* FileDialogScreenController_setupFileDialogListBox_1::getClass0()
{
	return class_();
}

