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

ModelEditorScreenController_onModelSave_3::ModelEditorScreenController_onModelSave_3(ModelEditorScreenController* modelEditorScreenController)
	: modelEditorScreenController(modelEditorScreenController)
{
}

void ModelEditorScreenController_onModelSave_3::performAction()
{
	try {
		modelEditorScreenController->view->saveFile(
			modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(),
			modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
		);
		modelEditorScreenController->modelPath->setPath(
			modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName()
		);
		modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
	} catch (Exception& exception) {
		modelEditorScreenController->showErrorPopUp("Warning", (string(exception.what())));
	}
}
