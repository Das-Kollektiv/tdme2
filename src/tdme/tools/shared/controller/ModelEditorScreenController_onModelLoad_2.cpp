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

ModelEditorScreenController_onModelLoad_2::ModelEditorScreenController_onModelLoad_2(ModelEditorScreenController* modelViewerScreenController)
	: modelViewerScreenController(modelViewerScreenController)
{
}

void ModelEditorScreenController_onModelLoad_2::performAction()
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

