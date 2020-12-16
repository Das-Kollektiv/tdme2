#include <tdme/tools/shared/views/PrototypeSoundsView.h>

#include <string>
#include <vector>


#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/shared/controller/PrototypeSoundsSubScreenController.h>
#include <tdme/engine/prototype/Prototype.h>

using tdme::tools::shared::views::PrototypeSoundsView;

using std::vector;
using std::string;


using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::shared::controller::PrototypeDisplaySubScreenController;
using tdme::engine::prototype::Prototype;

PrototypeSoundsView::PrototypeSoundsView(PrototypeSoundsSubScreenController* prototypeSoundsSubScreenController, PopUps* popUps)
{
	this->engine = Engine::getInstance();
	this->prototypeSoundsSubScreenController = prototypeSoundsSubScreenController;
	this->popUps = popUps;
}

PopUps* PrototypeSoundsView::getPopUpsViews() {
	return popUps;
}

void PrototypeSoundsView::unsetSounds() {
	prototypeSoundsSubScreenController->unsetSounds();
}

void PrototypeSoundsView::setSounds(Prototype* prototype) {
	prototypeSoundsSubScreenController->setSounds(prototype);
}
