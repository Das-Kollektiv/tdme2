// Generated from /tdme/src/tdme/tools/shared/controller/ModelViewerScreenController.java
#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelSave_3.h>

#include <java/lang/Exception.h>
#include <java/lang/String.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>

using tdme::tools::shared::controller::ModelViewerScreenController_onModelSave_3;
using java::lang::Exception;
using java::lang::String;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;

ModelViewerScreenController_onModelSave_3::ModelViewerScreenController_onModelSave_3(ModelViewerScreenController *ModelViewerScreenController_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, ModelViewerScreenController_this(ModelViewerScreenController_this)
{
	clinit();
	ctor();
}

void ModelViewerScreenController_onModelSave_3::performAction()
{
	try {
		ModelViewerScreenController_this->view->saveFile(ModelViewerScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(), ModelViewerScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getFileName());
		ModelViewerScreenController_this->modelPath->setPath(ModelViewerScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
		ModelViewerScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->close();
	} catch (Exception* ioe) {
		ModelViewerScreenController_this->showErrorPopUp(u"Warning"_j, ioe->getMessage());
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelViewerScreenController_onModelSave_3::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* ModelViewerScreenController_onModelSave_3::getClass0()
{
	return class_();
}

