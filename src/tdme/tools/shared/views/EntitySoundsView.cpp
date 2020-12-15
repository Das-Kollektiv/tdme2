#include <tdme/tools/shared/views/EntitySoundsView.h>

#include <string>
#include <vector>


#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/shared/controller/EntitySoundsSubScreenController.h>
#include <tdme/engine/prototype/Prototype.h>

using tdme::tools::shared::views::EntitySoundsView;

using std::vector;
using std::string;


using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::engine::prototype::Prototype;

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

void EntitySoundsView::setSounds(Prototype* entity) {
	entitySoundsSubScreenController->setSounds(entity);
}
