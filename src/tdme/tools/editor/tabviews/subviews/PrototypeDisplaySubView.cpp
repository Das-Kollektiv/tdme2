#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>

#include <string>
#include <vector>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>

using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;

using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;

PrototypeDisplaySubView::PrototypeDisplaySubView(PrototypeDisplaySubController* prototypeDisplaySubController)
{
	this->engine = Engine::getInstance();
	this->prototypeDisplaySubController = prototypeDisplaySubController;
	displayGroundPlate = true;
	displayShadowing = true;
}

PrototypeDisplaySubView::~PrototypeDisplaySubView() {
}

void PrototypeDisplaySubView::display(Prototype* prototype)
{
	if (prototype != nullptr) {
		auto model = engine->getEntity("model");
		if (model != nullptr) model->setContributesShadows(displayShadowing);
		if (model != nullptr) model->setReceivesShadows(displayShadowing);
		auto ground = engine->getEntity("ground");
		if (ground != nullptr) ground->setEnabled(displayGroundPlate);
		if (ground != nullptr) ground->setReceivesShadows(displayShadowing);
	}
}
