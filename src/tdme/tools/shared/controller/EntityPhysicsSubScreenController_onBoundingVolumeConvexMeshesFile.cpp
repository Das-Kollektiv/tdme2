#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshesFile.h>

#include <string>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>

using std::string;
using std::to_string;

using tdme::tools::shared::controller::EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshesFile;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;

EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshesFile::EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshesFile(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, LevelEditorEntity* entityFinal)
	: entityPhysicsSubScreenController(entityPhysicsSubScreenController)
	, entityFinal(entityFinal)
{
}

void EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshesFile::performAction()
{
	entityPhysicsSubScreenController->convexMeshesFile->getController()->setValue(
		MutableString(
			entityPhysicsSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName() +
			"/" +
			entityPhysicsSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
		)
	);
	entityPhysicsSubScreenController->modelPath->setPath(entityPhysicsSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	entityPhysicsSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

