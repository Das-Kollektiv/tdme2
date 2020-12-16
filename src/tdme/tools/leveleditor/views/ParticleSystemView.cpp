#include <tdme/tools/leveleditor/views/ParticleSystemView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::tools::leveleditor::views::ParticleSystemView;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneLibrary;
using tdme::utilities::StringTools;;

ParticleSystemView::ParticleSystemView(PopUps* popUps)
	: SharedParticleSystemView(popUps)
{
}

void ParticleSystemView::onSetEntityData()
{
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

void ParticleSystemView::onLoadParticleSystem(Prototype* oldEntity, Prototype* newEntity)
{
	TDMELevelEditor::getInstance()->getScene()->replacePrototype(oldEntity->getId(), newEntity->getId());
	TDMELevelEditor::getInstance()->getSceneLibrary()->removePrototype(oldEntity->getId());
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

Prototype* ParticleSystemView::loadParticleSystem(const string& name, const string& description, const string& pathName, const string& fileName) /* throws(Exception) */
{
	if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tps") == true) {
		auto prototype = PrototypeReader::read(SceneLibrary::ID_ALLOCATE, pathName, fileName);
		prototype->setDefaultBoundingVolumes();
		TDMELevelEditor::getInstance()->getSceneLibrary()->addPrototype(prototype);
		return prototype;
	}
	return nullptr;
}

void ParticleSystemView::onInitAdditionalScreens()
{
	engine->getGUI()->addRenderScreen(TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->getScreenNode()->getId());
}
