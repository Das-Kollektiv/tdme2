#include <tdme/tools/shared/controller/ModelEditorScreenController_onModelSave_3.h>


#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>
#include <tdme/utils/Exception.h>


using tdme::tools::shared::controller::ModelEditorScreenController_onModelSave_3;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ModelEditorScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelEditorView;
using tdme::utils::Exception;

ModelEditorScreenController_onModelSave_3::ModelEditorScreenController_onModelSave_3(ModelEditorScreenController* modelViewerScreenController)
	: modelViewerScreenController(modelViewerScreenController)
{
}

void ModelEditorScreenController_onModelSave_3::performAction()
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
