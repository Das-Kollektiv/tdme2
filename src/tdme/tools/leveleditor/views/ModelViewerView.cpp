// Generated from /tdme/src/tdme/tools/leveleditor/views/ModelViewerView.java
#include <tdme/tools/leveleditor/views/ModelViewerView.h>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>

using tdme::tools::leveleditor::views::ModelViewerView;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;

ModelViewerView::ModelViewerView(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelViewerView::ModelViewerView(PopUps* popUps) 
	: ModelViewerView(*static_cast< ::default_init_tag* >(0))
{
	ctor(popUps);
}

void ModelViewerView::ctor(PopUps* popUps)
{
	super::ctor(popUps);
}

void ModelViewerView::onSetEntityData()
{
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

void ModelViewerView::onLoadModel(LevelEditorEntity* oldEntity, LevelEditorEntity* entity)
{
	TDMELevelEditor::getInstance()->getLevel()->replaceEntity(oldEntity->getId(), entity->getId());
	TDMELevelEditor::getInstance()->getEntityLibrary()->removeEntity(oldEntity->getId());
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

void ModelViewerView::onInitAdditionalScreens()
{
	engine->getGUI()->addRenderScreen(TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->getScreenNode()->getId());
}

LevelEditorEntity* ModelViewerView::loadModel(String* name, String* description, String* pathName, String* fileName, Vector3* pivot) /* throws(Exception) */
{
	return TDMELevelEditor::getInstance()->getEntityLibrary()->addModel(LevelEditorEntityLibrary::ID_ALLOCATE, name, description, pathName, fileName, pivot);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelViewerView::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.leveleditor.views.ModelViewerView", 44);
    return c;
}

java::lang::Class* ModelViewerView::getClass0()
{
	return class_();
}

