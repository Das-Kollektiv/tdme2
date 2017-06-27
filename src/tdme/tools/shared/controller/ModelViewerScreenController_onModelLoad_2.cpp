// Generated from /tdme/src/tdme/tools/shared/controller/ModelViewerScreenController.java
#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelLoad_2.h>

#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>

using tdme::tools::shared::controller::ModelViewerScreenController_onModelLoad_2;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;

ModelViewerScreenController_onModelLoad_2::ModelViewerScreenController_onModelLoad_2(ModelViewerScreenController *ModelViewerScreenController_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, ModelViewerScreenController_this(ModelViewerScreenController_this)
{
	clinit();
	ctor();
}

void ModelViewerScreenController_onModelLoad_2::performAction()
{
	ModelViewerScreenController_this->view->loadFile(ModelViewerScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(), ModelViewerScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getFileName());
	ModelViewerScreenController_this->modelPath->setPath(ModelViewerScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	ModelViewerScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelViewerScreenController_onModelLoad_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* ModelViewerScreenController_onModelLoad_2::getClass0()
{
	return class_();
}

