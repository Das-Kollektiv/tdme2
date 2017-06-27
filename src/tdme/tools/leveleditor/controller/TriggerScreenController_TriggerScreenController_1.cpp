// Generated from /tdme/src/tdme/tools/leveleditor/controller/TriggerScreenController.java
#include <tdme/tools/leveleditor/controller/TriggerScreenController_TriggerScreenController_1.h>

#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/leveleditor/controller/TriggerScreenController.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>

using tdme::tools::leveleditor::controller::TriggerScreenController_TriggerScreenController_1;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::tools::leveleditor::views::TriggerView;

TriggerScreenController_TriggerScreenController_1::TriggerScreenController_TriggerScreenController_1(TriggerScreenController *TriggerScreenController_this, TriggerView* finalView)
	: super(*static_cast< ::default_init_tag* >(0))
	, TriggerScreenController_this(TriggerScreenController_this)
	, finalView(finalView)
{
	clinit();
	ctor();
}

void TriggerScreenController_TriggerScreenController_1::performAction()
{
	finalView->updateGUIElements();
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TriggerScreenController_TriggerScreenController_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* TriggerScreenController_TriggerScreenController_1::getClass0()
{
	return class_();
}

