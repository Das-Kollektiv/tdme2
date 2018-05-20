#include <tdme/tools/shared/views/EntityDisplayView.h>

#include <string>
#include <vector>


#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>

using tdme::tools::shared::views::EntityDisplayView;

using std::vector;
using std::string;


using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

vector<string> EntityDisplayView::MODEL_BOUNDINGVOLUME_IDS = {
	"model_bv.0",
	"model_bv.1",
	"model_bv.2",
	"model_bv.3",
	"model_bv.4",
	"model_bv.5",
	"model_bv.6",
	"model_bv.7"
};

EntityDisplayView::EntityDisplayView(EntityDisplaySubScreenController* entityDisplaySubScreenController) 
{
	this->engine = Engine::getInstance();
	this->entityDisplaySubScreenController = entityDisplaySubScreenController;
	displayGroundPlate = false;
	displayShadowing = false;
	displayBoundingVolume = false;
}

bool EntityDisplayView::isDisplayGroundPlate()
{
	return displayGroundPlate;
}

void EntityDisplayView::setDisplayGroundPlate(bool groundPlate)
{
	this->displayGroundPlate = groundPlate;
}

bool EntityDisplayView::isDisplayShadowing()
{
	return displayShadowing;
}

void EntityDisplayView::setDisplayShadowing(bool shadowing)
{
	this->displayShadowing = shadowing;
}

bool EntityDisplayView::isDisplayBoundingVolume()
{
	return displayBoundingVolume;
}

void EntityDisplayView::setDisplayBoundingVolume(bool displayBoundingVolume)
{
	this->displayBoundingVolume = displayBoundingVolume;
}

void EntityDisplayView::display(LevelEditorEntity* entity)
{
	if (entity != nullptr) {
		auto model = engine->getEntity("model");
		if (model != nullptr) {
			model->setDynamicShadowingEnabled(displayShadowing);
		}
		auto ground = engine->getEntity("ground");
		ground->setEnabled(displayGroundPlate);
		for (auto i = 0; i < MODEL_BOUNDINGVOLUME_IDS.size(); i++) {
			auto modelBoundingVolume = engine->getEntity(MODEL_BOUNDINGVOLUME_IDS[i]);
			if (modelBoundingVolume != nullptr) {
				modelBoundingVolume->setEnabled(displayBoundingVolume);
			}
		}
	}
}
