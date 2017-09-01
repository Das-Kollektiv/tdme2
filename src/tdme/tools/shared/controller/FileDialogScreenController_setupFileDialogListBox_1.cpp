// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogScreenController.java
#include <tdme/tools/shared/controller/FileDialogScreenController_setupFileDialogListBox_1.h>

#include <SubArray.h>
#include <ObjectArray.h>
#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/String.h>

#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/utils/StringUtils.h>

using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;

using tdme::tools::shared::controller::FileDialogScreenController_setupFileDialogListBox_1;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::StringUtils;

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

FileDialogScreenController_setupFileDialogListBox_1::FileDialogScreenController_setupFileDialogListBox_1(FileDialogScreenController* fileDialogScreenController)
	: fileDialogScreenController(fileDialogScreenController)
{
}

bool FileDialogScreenController_setupFileDialogListBox_1::accept(const wstring& pathName, const wstring& fileName)
{
	if (_FileSystem::getInstance()->isPath(pathName + L"/" + fileName) == true) return true;
	for (auto extension : *fileDialogScreenController->extensions) {
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L"." + extension->getCPPWString()) == true) return true;

	}
	return false;
}
