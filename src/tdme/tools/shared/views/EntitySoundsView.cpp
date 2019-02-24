#include <tdme/tools/shared/views/EntitySoundsView.h>

#include <string>
#include <vector>


#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/shared/controller/EntitySoundsSubScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>

using tdme::tools::shared::views::EntitySoundsView;

using std::vector;
using std::string;


using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

EntitySoundsView::EntitySoundsView(EntitySoundsSubScreenController* entitySoundsSubScreenController, PopUps* popUps)
{
	this->engine = Engine::getInstance();
	this->entitySoundsSubScreenController = entitySoundsSubScreenController;
	this->popUps = popUps;
}

PopUps* EntitySoundsView::getPopUpsViews() {
	return popUps;
}

void EntitySoundsView::unsetSounds() {
	entitySoundsSubScreenController->unsetSounds();
}

void EntitySoundsView::setSounds(LevelEditorEntity* entity) {
	entitySoundsSubScreenController->setSounds(entity);
}
