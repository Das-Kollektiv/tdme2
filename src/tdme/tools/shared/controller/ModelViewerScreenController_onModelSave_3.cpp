#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelSave_3.h>


#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>
#include <tdme/utils/Exception.h>


using tdme::tools::shared::controller::ModelViewerScreenController_onModelSave_3;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;
using tdme::utils::Exception;

ModelViewerScreenController_onModelSave_3::ModelViewerScreenController_onModelSave_3(ModelViewerScreenController* modelViewerScreenController)
	: modelViewerScreenController(modelViewerScreenController)
{
}

void ModelViewerScreenController_onModelSave_3::performAction()
{
	try {
		modelViewerScreenController->view->saveFile(
			modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(),
			modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
		);
		modelViewerScreenController->modelPath->setPath(
			modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName()
		);
		modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
	} catch (Exception& exception) {
		modelViewerScreenController->showErrorPopUp("Warning", (string(exception.what())));
	}
}
