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

ParticleSystemView::ParticleSystemView(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ParticleSystemView::ParticleSystemView(PopUps* popUps) 
	: ParticleSystemView(*static_cast< ::default_init_tag* >(0))
{
	ctor(popUps);
}

void ParticleSystemView::ctor(PopUps* popUps)
{
	super::ctor(popUps);
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

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ParticleSystemView::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.leveleditor.views.ParticleSystemView", 47);
    return c;
}

java::lang::Class* ParticleSystemView::getClass0()
{
	return class_();
}

