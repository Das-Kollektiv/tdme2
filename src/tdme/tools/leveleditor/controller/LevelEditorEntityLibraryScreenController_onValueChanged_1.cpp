#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController_onValueChanged_1.h>

#include <string>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Exception.h>

using std::string;

using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController_onValueChanged_1;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::math::Vector3;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;
using tdme::utils::Exception;

LevelEditorEntityLibraryScreenController_onValueChanged_1::LevelEditorEntityLibraryScreenController_onValueChanged_1(LevelEditorEntityLibraryScreenController *levelEditorEntityLibraryScreenController, LevelEditorEntityLibrary* entityLibrary)
	: levelEditorEntityLibraryScreenController(levelEditorEntityLibraryScreenController)
	, entityLibrary(entityLibrary)
{
}

void LevelEditorEntityLibraryScreenController_onValueChanged_1::performAction()
{
	try {
		auto entity = entityLibrary->addModel(
			LevelEditorEntityLibrary::ID_ALLOCATE,
			levelEditorEntityLibraryScreenController->popUps->getFileDialogScreenController()->getFileName(),
			"",
			levelEditorEntityLibraryScreenController->popUps->getFileDialogScreenController()->getPathName(),
			levelEditorEntityLibraryScreenController->popUps->getFileDialogScreenController()->getFileName(),
			Vector3(0.0f, 0.0f, 0.0f)
		);
		entity->setDefaultBoundingVolumes();
		levelEditorEntityLibraryScreenController->setEntityLibrary();
		levelEditorEntityLibraryScreenController->entityLibraryListBox->getController()->setValue(MutableString(entity->getId()));
		levelEditorEntityLibraryScreenController->onEditEntity();
	} catch (Exception& exception) {
		levelEditorEntityLibraryScreenController->popUps->getInfoDialogScreenController()->show(
			"Error",
			"An error occurred: " + string(exception.what())
		);
	}
	levelEditorEntityLibraryScreenController->modelPath = levelEditorEntityLibraryScreenController->popUps->getFileDialogScreenController()->getPathName();
	levelEditorEntityLibraryScreenController->popUps->getFileDialogScreenController()->close();
}
