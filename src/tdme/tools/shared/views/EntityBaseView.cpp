#include <tdme/tools/shared/views/EntityBaseView.h>

#include <string>

#include <tdme/tools/shared/controller/PrototypeBaseSubScreenController.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/ScenePropertyPresets.h>
#include <tdme/engine/prototype/PrototypeProperty.h>

using std::string;

using tdme::tools::shared::views::EntityBaseView;
using tdme::tools::shared::controller::PrototypeBaseSubScreenController;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::engine::prototype::PrototypeProperty;

EntityBaseView::EntityBaseView(PrototypeBaseSubScreenController* prototypeBaseSubScreenController)
{
	this->prototypeBaseSubScreenController = prototypeBaseSubScreenController;
}

void EntityBaseView::initialize()
{
	prototypeBaseSubScreenController->setEntityPresetIds(ScenePropertyPresets::getInstance()->getEntityPropertiesPresets());
}

void EntityBaseView::entityPropertiesPreset(Prototype* entity, const string& presetId)
{
	if (entity == nullptr)
		return;

	entity->clearProperties();
	auto& objectPropertiesPreset = ScenePropertyPresets::getInstance()->getEntityPropertiesPresets();
	const vector<PrototypeProperty*>* entityPropertyPresetArrayList = nullptr;
	auto entityPropertyPresetArrayListIt = objectPropertiesPreset.find(presetId);
	if (entityPropertyPresetArrayListIt != objectPropertiesPreset.end()) {
		entityPropertyPresetArrayList = &entityPropertyPresetArrayListIt->second;
	}
	if (entityPropertyPresetArrayList != nullptr) {
		for (auto entityPropertyPreset: *entityPropertyPresetArrayList) {
			entity->addProperty(entityPropertyPreset->getName(), entityPropertyPreset->getValue());
		}
	}
	prototypeBaseSubScreenController->setEntityProperties(entity, presetId, "");
}

bool EntityBaseView::entityPropertySave(Prototype* entity, const string& oldName, const string& name, const string& value)
{
	if (entity == nullptr)
		return false;

	if (entity->updateProperty(oldName, name, value) == true) {
		prototypeBaseSubScreenController->setEntityProperties(entity, "", name);
		return true;
	}
	return false;
}

bool EntityBaseView::entityPropertyAdd(Prototype* entity)
{
	if (entity == nullptr)
		return false;

	if (entity->addProperty("new.property", "new.value")) {
		prototypeBaseSubScreenController->setEntityProperties(entity, "", "new.property");
		return true;
	}
	return false;
}

bool EntityBaseView::entityPropertyRemove(Prototype* entity, const string& name)
{
	if (entity == nullptr)
		return false;

	auto idx = entity->getPropertyIndex(name);
	if (idx != -1 && entity->removeProperty(name) == true) {
		auto property = entity->getPropertyByIndex(idx);
		if (property == nullptr) {
			property = entity->getPropertyByIndex(idx - 1);
		}
		prototypeBaseSubScreenController->setEntityProperties(entity, "", property == nullptr ? "" : property->getName());
		return true;
	}
	return false;
}

void EntityBaseView::setEntityData(Prototype* entity, const string& name, const string& description)
{
	if (entity == nullptr)
		return;

	entity->setName(name);
	entity->setDescription(description);
}
