// Generated from /tdme/src/tdme/tools/shared/controller/ModelViewerScreenController.java
#include <tdme/tools/shared/controller/ModelViewerScreenController_ModelViewerScreenController_1.h>

#include <tdme/tools/shared/controller/ModelViewerScreenController.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>

using tdme::tools::shared::controller::ModelViewerScreenController_ModelViewerScreenController_1;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::views::SharedModelViewerView;

ModelViewerScreenController_ModelViewerScreenController_1::ModelViewerScreenController_ModelViewerScreenController_1(ModelViewerScreenController *ModelViewerScreenController_this, SharedModelViewerView* finalView)
	: super(*static_cast< ::default_init_tag* >(0))
	, ModelViewerScreenController_this(ModelViewerScreenController_this)
	, finalView(finalView)
{
	clinit();
	ctor();
}

void ModelViewerScreenController_ModelViewerScreenController_1::performAction()
{
	finalView->updateGUIElements();
	finalView->onSetEntityData();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelViewerScreenController_ModelViewerScreenController_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* ModelViewerScreenController_ModelViewerScreenController_1::getClass0()
{
	return class_();
}

