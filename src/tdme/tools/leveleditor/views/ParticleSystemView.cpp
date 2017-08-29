// Generated from /tdme/src/tdme/tools/leveleditor/views/ParticleSystemView.java
#include <tdme/tools/leveleditor/views/ParticleSystemView.h>

#include <java/lang/String.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>


using tdme::tools::leveleditor::views::ParticleSystemView;
using java::lang::String;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;

ParticleSystemView::ParticleSystemView(PopUps* popUps) 
	: SharedParticleSystemView(popUps)
{
}

void ParticleSystemView::onSetEntityData()
{
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

void ParticleSystemView::onLoadParticleSystem(LevelEditorEntity* oldEntity, LevelEditorEntity* newEntity)
{
	TDMELevelEditor::getInstance()->getLevel()->replaceEntity(oldEntity->getId(), newEntity->getId());
	TDMELevelEditor::getInstance()->getEntityLibrary()->removeEntity(oldEntity->getId());
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

LevelEditorEntity* ParticleSystemView::loadParticleSystem(String* name, String* description, String* pathName, String* fileName) /* throws(Exception) */
{
	if (fileName->toLowerCase()->endsWith(u".tps"_j)) {
		auto levelEditorEntity = ModelMetaDataFileImport::doImport(LevelEditorEntityLibrary::ID_ALLOCATE, pathName, fileName);
		levelEditorEntity->setDefaultBoundingVolumes();
		TDMELevelEditor::getInstance()->getEntityLibrary()->addEntity(levelEditorEntity);
		return levelEditorEntity;
	}
	return nullptr;
}

void ParticleSystemView::onInitAdditionalScreens()
{
	engine->getGUI()->addRenderScreen(TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->getScreenNode()->getId());
}
