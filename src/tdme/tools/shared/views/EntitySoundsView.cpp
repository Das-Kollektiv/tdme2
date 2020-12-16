#include <tdme/tools/shared/views/EntitySoundsView.h>

#include <string>
#include <vector>


#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/shared/controller/PrototypeSoundsSubScreenController.h>
#include <tdme/engine/prototype/Prototype.h>

using tdme::tools::shared::views::EntitySoundsView;

using std::vector;
using std::string;


using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::shared::controller::PrototypeDisplaySubScreenController;
using tdme::engine::prototype::Prototype;

EntitySoundsView::EntitySoundsView(PrototypeSoundsSubScreenController* prototypeSoundsSubScreenController, PopUps* popUps)
{
	this->engine = Engine::getInstance();
	this->prototypeSoundsSubScreenController = prototypeSoundsSubScreenController;
	this->popUps = popUps;
}

PopUps* EntitySoundsView::getPopUpsViews() {
	return popUps;
}

void EntitySoundsView::unsetSounds() {
	prototypeSoundsSubScreenController->unsetSounds();
}

void EntitySoundsView::setSounds(Prototype* entity) {
	prototypeSoundsSubScreenController->setSounds(entity);
}
