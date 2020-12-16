#include <tdme/tools/shared/views/EntityDisplayView.h>

#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/shared/controller/PrototypeDisplaySubScreenController.h>
#include <tdme/engine/prototype/Prototype.h>

using tdme::tools::shared::views::EntityDisplayView;

using std::vector;
using std::string;

using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::shared::controller::PrototypeDisplaySubScreenController;
using tdme::engine::prototype::Prototype;

EntityDisplayView::EntityDisplayView(PrototypeDisplaySubScreenController* prototypeDisplaySubScreenController)
{
	this->engine = Engine::getInstance();
	this->prototypeDisplaySubScreenController = prototypeDisplaySubScreenController;
	displayGroundPlate = true;
	displayShadowing = true;
}

EntityDisplayView::~EntityDisplayView() {
}

void EntityDisplayView::display(Prototype* entity)
{
	if (entity != nullptr) {
		auto model = engine->getEntity("model");
		if (model != nullptr) model->setContributesShadows(displayShadowing);
		if (model != nullptr) model->setReceivesShadows(displayShadowing);
		auto ground = engine->getEntity("ground");
		if (ground != nullptr) ground->setEnabled(displayGroundPlate);
		if (ground != nullptr) ground->setReceivesShadows(displayShadowing);
	}
}
