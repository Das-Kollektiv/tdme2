#include <tdme/tools/leveleditor/views/ModelEditorView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>

using std::string;

using tdme::tools::leveleditor::views::ModelEditorView;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;

ModelEditorView::ModelEditorView(PopUps* popUps)
	: SharedModelEditorView(popUps)
{
}

void ModelEditorView::onSetEntityData()
{
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

void ModelEditorView::onLoadModel(LevelEditorEntity* oldEntity, LevelEditorEntity* entity)
{
	TDMELevelEditor::getInstance()->getLevel()->replaceEntity(oldEntity->getId(), entity->getId());
	TDMELevelEditor::getInstance()->getEntityLibrary()->removeEntity(oldEntity->getId());
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

void ModelEditorView::onInitAdditionalScreens()
{
	engine->getGUI()->addRenderScreen(TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->getScreenNode()->getId());
}

LevelEditorEntity* ModelEditorView::loadModel(const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot) /* throws(Exception) */
{
	return TDMELevelEditor::getInstance()->getEntityLibrary()->addModel(
		LevelEditorEntityLibrary::ID_ALLOCATE,
		name,
		description,
		pathName,
		fileName,
		pivot
	);
}
