// Generated from /tdme/src/tdme/tools/shared/controller/ModelViewerScreenController.java
#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelLoad_2.h>

#include <java/lang/String.h>

#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>

using java::lang::String;

using tdme::tools::shared::controller::ModelViewerScreenController_onModelLoad_2;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;

ModelViewerScreenController_onModelLoad_2::ModelViewerScreenController_onModelLoad_2(ModelViewerScreenController* modelViewerScreenController)
	: modelViewerScreenController(modelViewerScreenController)
{
}

void ModelViewerScreenController_onModelLoad_2::performAction()
{
	modelViewerScreenController->view->loadFile(
		modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(),
		modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
	);
	modelViewerScreenController->modelPath->setPath(
		modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName()
	);
	modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

