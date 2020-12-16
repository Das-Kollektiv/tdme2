#include <tdme/tools/shared/views/PrototypeDisplayView.h>

#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/shared/controller/PrototypeDisplaySubScreenController.h>
#include <tdme/engine/prototype/Prototype.h>

using tdme::tools::shared::views::PrototypeDisplayView;

using std::vector;
using std::string;

using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::shared::controller::PrototypeDisplaySubScreenController;
using tdme::engine::prototype::Prototype;

PrototypeDisplayView::PrototypeDisplayView(PrototypeDisplaySubScreenController* prototypeDisplaySubScreenController)
{
	this->engine = Engine::getInstance();
	this->prototypeDisplaySubScreenController = prototypeDisplaySubScreenController;
	displayGroundPlate = true;
	displayShadowing = true;
}

PrototypeDisplayView::~PrototypeDisplayView() {
}

void PrototypeDisplayView::display(Prototype* prototype)
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
