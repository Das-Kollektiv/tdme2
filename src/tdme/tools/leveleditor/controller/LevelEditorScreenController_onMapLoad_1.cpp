// Generated from /tdme/src/tdme/tools/leveleditor/controller/LevelEditorScreenController.java
#include <tdme/tools/leveleditor/controller/LevelEditorScreenController_onMapLoad_1.h>

#include <tdme/tools/leveleditor/controller/LevelEditorScreenController.h>
#include <tdme/tools/leveleditor/views/LevelEditorView.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>

using tdme::tools::leveleditor::controller::LevelEditorScreenController_onMapLoad_1;
using tdme::tools::leveleditor::controller::LevelEditorScreenController;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::views::PopUps;

LevelEditorScreenController_onMapLoad_1::LevelEditorScreenController_onMapLoad_1(LevelEditorScreenController *LevelEditorScreenController_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, LevelEditorScreenController_this(LevelEditorScreenController_this)
{
	clinit();
	ctor();
}

void LevelEditorScreenController_onMapLoad_1::performAction()
{
	LevelEditorScreenController_this->view->loadMap(LevelEditorScreenController_this->view->getPopUps()->getFileDialogScreenController()->getPathName(), LevelEditorScreenController_this->view->getPopUps()->getFileDialogScreenController()->getFileName());
	LevelEditorScreenController_this->mapPath->setPath(LevelEditorScreenController_this->view->getPopUps()->getFileDialogScreenController()->getPathName());
	LevelEditorScreenController_this->view->getPopUps()->getFileDialogScreenController()->close();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorScreenController_onMapLoad_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* LevelEditorScreenController_onMapLoad_1::getClass0()
{
	return class_();
}

