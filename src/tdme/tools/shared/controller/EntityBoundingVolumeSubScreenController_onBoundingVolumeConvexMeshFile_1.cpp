#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1.h>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>

using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;

EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1(EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController, int32_t idxFinal, LevelEditorEntity* entityFinal)
	: entityBoundingVolumeSubScreenController(entityBoundingVolumeSubScreenController)
	, idxFinal(idxFinal)
	, entityFinal(entityFinal)
{
}

void EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1::performAction()
{
	entityBoundingVolumeSubScreenController->boundingvolumeConvexMeshFile[idxFinal]->getController()->setValue(entityBoundingVolumeSubScreenController->value->set(entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()));
	entityBoundingVolumeSubScreenController->onBoundingVolumeConvexMeshApply(entityFinal, idxFinal);
	entityBoundingVolumeSubScreenController->modelPath->setPath(entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}
