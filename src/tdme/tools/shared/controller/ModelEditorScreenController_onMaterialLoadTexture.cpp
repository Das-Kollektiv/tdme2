#include <tdme/tools/shared/controller/ModelEditorScreenController_onMaterialLoadTexture.h>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>

using tdme::tools::shared::controller::ModelEditorScreenController_onMaterialLoadTexture;

using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::utils::MutableString;

ModelEditorScreenController_onMaterialLoadTexture::ModelEditorScreenController_onMaterialLoadTexture(ModelEditorScreenController* modelEditorScreenController, GUIElementNode* guiElementNode)
	: modelEditorScreenController(modelEditorScreenController), guiElementNode(guiElementNode)
{
}

void ModelEditorScreenController_onMaterialLoadTexture::performAction()
{
	MutableString value;
	guiElementNode->getController()->setValue(
		MutableString().
			set(modelEditorScreenController->getView()->getPopUpsViews()->getFileDialogScreenController()->getPathName()).
			append("/").
			append(modelEditorScreenController->getView()->getPopUpsViews()->getFileDialogScreenController()->getFileName())
	);
	modelEditorScreenController->getModelPath()->setPath(
		modelEditorScreenController->getView()->getPopUpsViews()->getFileDialogScreenController()->getPathName()
	);
	modelEditorScreenController->getView()->getPopUpsViews()->getFileDialogScreenController()->close();
}
