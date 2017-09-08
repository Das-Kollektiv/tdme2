// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogScreenController.java
#include <tdme/tools/shared/controller/FileDialogScreenController_setupFileDialogListBox_1.h>

#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/utils/StringUtils.h>

using tdme::tools::shared::controller::FileDialogScreenController_setupFileDialogListBox_1;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::StringUtils;


FileDialogScreenController_setupFileDialogListBox_1::FileDialogScreenController_setupFileDialogListBox_1(FileDialogScreenController* fileDialogScreenController)
	: fileDialogScreenController(fileDialogScreenController)
{
}

bool FileDialogScreenController_setupFileDialogListBox_1::accept(const wstring& pathName, const wstring& fileName)
{
	if (_FileSystem::getInstance()->isPath(pathName + L"/" + fileName) == true) return true;
	for (auto& extension : fileDialogScreenController->extensions) {
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L"." + extension) == true) return true;

	}
	return false;
}
