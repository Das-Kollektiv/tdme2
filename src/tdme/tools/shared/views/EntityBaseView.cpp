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
	prototypeBaseSubScreenController->setPrototypePresetIds(ScenePropertyPresets::getInstance()->getEntityPropertiesPresets());
}

void EntityBaseView::prototypePropertiesPreset(Prototype* entity, const string& presetId)
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
	prototypeBaseSubScreenController->setPrototypeProperties(entity, presetId, "");
}

bool EntityBaseView::prototypePropertySave(Prototype* entity, const string& oldName, const string& name, const string& value)
{
	if (entity == nullptr)
		return false;

	if (entity->updateProperty(oldName, name, value) == true) {
		prototypeBaseSubScreenController->setPrototypeProperties(entity, "", name);
		return true;
	}
	return false;
}

bool EntityBaseView::prototypePropertyAdd(Prototype* entity)
{
	if (entity == nullptr)
		return false;

	if (entity->addProperty("new.property", "new.value")) {
		prototypeBaseSubScreenController->setPrototypeProperties(entity, "", "new.property");
		return true;
	}
	return false;
}

bool EntityBaseView::prototypePropertyRemove(Prototype* entity, const string& name)
{
	if (entity == nullptr)
		return false;

	auto idx = entity->getPropertyIndex(name);
	if (idx != -1 && entity->removeProperty(name) == true) {
		auto property = entity->getPropertyByIndex(idx);
		if (property == nullptr) {
			property = entity->getPropertyByIndex(idx - 1);
		}
		prototypeBaseSubScreenController->setPrototypeProperties(entity, "", property == nullptr ? "" : property->getName());
		return true;
	}
	return false;
}

void EntityBaseView::setPrototypeData(Prototype* entity, const string& name, const string& description)
{
	if (entity == nullptr)
		return;

	entity->setName(name);
	entity->setDescription(description);
}
