#include <tdme/tools/editor/tabviews/subviews/PrototypeSoundsSubView.h>

#include <string>
#include <vector>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>

using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;

using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::Entity;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;

PrototypeSoundsSubView::PrototypeSoundsSubView(PrototypeSoundsSubController* prototypeSoundsSubController, PopUps* popUps)
{
	this->prototypeSoundsSubController = prototypeSoundsSubController;
	this->popUps = popUps;
}

PopUps* PrototypeSoundsSubView::getPopUps() {
	return popUps;
}

void PrototypeSoundsSubView::unsetSounds() {
	prototypeSoundsSubController->unsetSounds();
}

void PrototypeSoundsSubView::setSounds(Prototype* prototype) {
	prototypeSoundsSubController->setSounds(prototype);
}
