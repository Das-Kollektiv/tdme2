#include <tdme/tools/shared/controller/ModelEditorScreenController_onLODModelLoad.h>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>
#include <tdme/utils/MutableString.h>

using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::tools::shared::controller::ModelEditorScreenController_onLODModelLoad;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ModelEditorScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelEditorView;
using tdme::utils::MutableString;

ModelEditorScreenController_onLODModelLoad::ModelEditorScreenController_onLODModelLoad(
	ModelEditorScreenController* modelEditorScreenController) : modelEditorScreenController(modelEditorScreenController)
{
}

void ModelEditorScreenController_onLODModelLoad::performAction()
{
	modelEditorScreenController->lodModelFile->getController()->setValue(
		MutableString(
			modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName() +
			"/" +
			modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
		)
	);
	modelEditorScreenController->modelPath->setPath(
		modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName()
	);
	modelEditorScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

