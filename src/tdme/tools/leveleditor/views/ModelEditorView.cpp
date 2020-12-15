#include <tdme/tools/leveleditor/views/ModelEditorView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/Scene.h>

using std::string;

using tdme::tools::leveleditor::views::ModelEditorView;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneLibrary;

ModelEditorView::ModelEditorView(PopUps* popUps)
	: SharedModelEditorView(popUps)
{
}

void ModelEditorView::onSetEntityData()
{
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

void ModelEditorView::onLoadModel(Prototype* oldEntity, Prototype* entity)
{
	TDMELevelEditor::getInstance()->getLevel()->replaceEntity(oldEntity->getId(), entity->getId());
	TDMELevelEditor::getInstance()->getEntityLibrary()->removeEntity(oldEntity->getId());
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

void ModelEditorView::onInitAdditionalScreens()
{
	engine->getGUI()->addRenderScreen(TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->getScreenNode()->getId());
}

Prototype* ModelEditorView::loadModel(const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot) /* throws(Exception) */
{
	return TDMELevelEditor::getInstance()->getEntityLibrary()->addModel(
		SceneLibrary::ID_ALLOCATE,
		name,
		description,
		pathName,
		fileName,
		pivot
	);
}
