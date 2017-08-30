// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogScreenController.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <java/io/FilenameFilter.h>

using java::io::FilenameFilter;
using java::io::File;
using java::lang::String;
using tdme::tools::shared::controller::FileDialogScreenController;

class tdme::tools::shared::controller::FileDialogScreenController_setupFileDialogListBox_1
	: public virtual FilenameFilter
{
	friend class FileDialogScreenController;

public:
	bool accept(String* directory, String* file) override;

	// Generated
	FileDialogScreenController_setupFileDialogListBox_1(FileDialogScreenController* fileDialogScreenController);

private:
	FileDialogScreenController* fileDialogScreenController;
};
