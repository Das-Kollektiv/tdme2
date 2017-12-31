#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile.h>

#include <string>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>

using std::string;
using std::to_string;

using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;

EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile(EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController, LevelEditorEntity* entityFinal)
	: entityBoundingVolumeSubScreenController(entityBoundingVolumeSubScreenController)
	, entityFinal(entityFinal)
{
}

void EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile::performAction()
{
	entityBoundingVolumeSubScreenController->convexMeshesFile->getController()->setValue(
		entityBoundingVolumeSubScreenController->value->set(
			entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName() +
			"/" +
			entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
		)
	);
	entityBoundingVolumeSubScreenController->modelPath->setPath(entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

