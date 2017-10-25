#include <tdme/tools/shared/controller/FileDialogScreenController_setupFileDialogListBox_1.h>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/utils/StringUtils.h>

using tdme::tools::shared::controller::FileDialogScreenController_setupFileDialogListBox_1;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::StringUtils;


FileDialogScreenController_setupFileDialogListBox_1::FileDialogScreenController_setupFileDialogListBox_1(FileDialogScreenController* fileDialogScreenController)
	: fileDialogScreenController(fileDialogScreenController)
{
}

bool FileDialogScreenController_setupFileDialogListBox_1::accept(const string& pathName, const string& fileName)
{
	if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
	for (auto& extension : fileDialogScreenController->extensions) {
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), "." + extension) == true) return true;

	}
	return false;
}
