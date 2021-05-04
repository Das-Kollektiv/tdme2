#include <tdme/tools/editor/tabviews/subviews/PrototypeSoundsSubView.h>

#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>

using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;

PrototypeSoundsSubView::PrototypeSoundsSubView(PrototypeSoundsSubController* prototypeSoundsSubController, PopUps* popUps)
{
	this->prototypeSoundsSubController = prototypeSoundsSubController;
	this->popUps = popUps;
}

PopUps* PrototypeSoundsSubView::getPopUps() {
	return popUps;
}
