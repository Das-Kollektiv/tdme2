// Generated from /tdme/src/tdme/tools/leveleditor/controller/EmptyScreenController.java
#include <tdme/tools/leveleditor/controller/EmptyScreenController_EmptyScreenController_1.h>

#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/EmptyScreenController.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>

using tdme::tools::leveleditor::controller::EmptyScreenController_EmptyScreenController_1;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::EmptyScreenController;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::views::EmptyView;

EmptyScreenController_EmptyScreenController_1::EmptyScreenController_EmptyScreenController_1(EmptyScreenController *EmptyScreenController_this, EmptyView* finalView)
	: super(*static_cast< ::default_init_tag* >(0))
	, EmptyScreenController_this(EmptyScreenController_this)
	, finalView(finalView)
{
	clinit();
	ctor();
}

void EmptyScreenController_EmptyScreenController_1::performAction()
{
	finalView->updateGUIElements();
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EmptyScreenController_EmptyScreenController_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* EmptyScreenController_EmptyScreenController_1::getClass0()
{
	return class_();
}

