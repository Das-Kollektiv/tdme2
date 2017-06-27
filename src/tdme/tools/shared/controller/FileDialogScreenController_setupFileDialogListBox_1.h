// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogScreenController.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/FilenameFilter.h>

using java::lang::Object;
using java::io::FilenameFilter;
using java::io::File;
using java::lang::String;
using tdme::tools::shared::controller::FileDialogScreenController;


struct default_init_tag;
class tdme::tools::shared::controller::FileDialogScreenController_setupFileDialogListBox_1
	: public virtual Object
	, public virtual FilenameFilter
{

public:
	typedef Object super;
	bool accept(File* directory, String* file) override;

	// Generated
	FileDialogScreenController_setupFileDialogListBox_1(FileDialogScreenController *FileDialogScreenController_this);
	static ::java::lang::Class *class_();
	FileDialogScreenController *FileDialogScreenController_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class FileDialogScreenController;
};
