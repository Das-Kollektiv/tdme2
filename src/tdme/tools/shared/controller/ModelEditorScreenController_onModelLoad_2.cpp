#include <tdme/tools/shared/controller/ModelEditorScreenController_onModelLoad_2.h>


#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>


using tdme::tools::shared::controller::ModelEditorScreenController_onModelLoad_2;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ModelEditorScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelEditorView;

ModelEditorScreenController_onModelLoad_2::ModelEditorScreenController_onModelLoad_2(ModelEditorScreenController* modelEditorScreenController)
	: modelEditorScreenController(modelEditorScreenController)
{
}

void ModelEditorScreenController_onModelLoad_2::performAction()
{
	modelEditorScreenController->view->loadFile(
		modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(),
		modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
	);
	modelEditorScreenController->modelPath->setPath(
		modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName()
	);
	modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

