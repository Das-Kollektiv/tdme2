#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshFile.h>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>

using tdme::tools::shared::controller::EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshFile;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;

EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshFile::EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshFile(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, int32_t idxFinal, LevelEditorEntity* entityFinal)
	: entityPhysicsSubScreenController(entityPhysicsSubScreenController)
	, idxFinal(idxFinal)
	, entityFinal(entityFinal)
{
}

void EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshFile::performAction()
{
	entityPhysicsSubScreenController->boundingvolumeConvexMeshFile[idxFinal]->getController()->setValue(
		MutableString(
			entityPhysicsSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName() +
			"/" +
			entityPhysicsSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
		)
	);
	entityPhysicsSubScreenController->onBoundingVolumeConvexMeshApply(entityFinal, idxFinal);
	entityPhysicsSubScreenController->modelPath->setPath(entityPhysicsSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	entityPhysicsSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}
