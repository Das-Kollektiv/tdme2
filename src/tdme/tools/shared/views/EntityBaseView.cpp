// Generated from /tdme/src/tdme/tools/shared/views/EntityBaseView.java
#include <tdme/tools/shared/views/EntityBaseView.h>

#include <java/lang/String.h>
#include <java/util/Iterator.h>
#include <java/util/Set.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelPropertyPresets.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>

using tdme::tools::shared::views::EntityBaseView;
using java::lang::String;
using java::util::Iterator;
using java::util::Set;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelPropertyPresets;
using tdme::tools::shared::model::PropertyModelClass;

EntityBaseView::EntityBaseView(EntityBaseSubScreenController* entityBaseSubScreenController) 
{
	this->entityBaseSubScreenController = entityBaseSubScreenController;
}

void EntityBaseView::initialize()
{
	entityBaseSubScreenController->setEntityPresetIds(LevelPropertyPresets::getInstance()->getObjectPropertiesPresets());
}

void EntityBaseView::entityPropertiesPreset(LevelEditorEntity* entity, String* presetId)
{
	if (entity == nullptr)
		return;

	entity->clearProperties();
	auto objectPropertiesPreset = LevelPropertyPresets::getInstance()->getObjectPropertiesPresets();
	const vector<PropertyModelClass*>* entityPropertyPresetArrayList = nullptr;
	auto entityPropertyPresetArrayListIt = objectPropertiesPreset->find(presetId->getCPPWString());
	if (entityPropertyPresetArrayListIt != objectPropertiesPreset->end()) {
		entityPropertyPresetArrayList = &entityPropertyPresetArrayListIt->second;
	}
	if (entityPropertyPresetArrayList != nullptr) {
		for (auto entityPropertyPreset: *entityPropertyPresetArrayList) {
			entity->addProperty(entityPropertyPreset->getName(), entityPropertyPreset->getValue());
		}
	}
	entityBaseSubScreenController->setEntityProperties(entity, presetId, nullptr);
}

bool EntityBaseView::entityPropertySave(LevelEditorEntity* entity, String* oldName, String* name, String* value)
{
	if (entity == nullptr)
		return false;

	if (entity->updateProperty(oldName, name, value) == true) {
		entityBaseSubScreenController->setEntityProperties(entity, nullptr, name);
		return true;
	}
	return false;
}

bool EntityBaseView::entityPropertyAdd(LevelEditorEntity* entity)
{
	if (entity == nullptr)
		return false;

	if (entity->addProperty(u"new.property"_j, u"new.value"_j)) {
		entityBaseSubScreenController->setEntityProperties(entity, nullptr, u"new.property"_j);
		return true;
	}
	return false;
}

bool EntityBaseView::entityPropertyRemove(LevelEditorEntity* entity, String* name)
{
	if (entity == nullptr)
		return false;

	auto idx = entity->getPropertyIndex(name);
	if (idx != -1 && entity->removeProperty(name) == true) {
		auto property = entity->getPropertyByIndex(idx);
		if (property == nullptr) {
			property = entity->getPropertyByIndex(idx - 1);
		}
		entityBaseSubScreenController->setEntityProperties(entity, nullptr, property == nullptr ? static_cast< String* >(nullptr) : property->getName());
		return true;
	}
	return false;
}

void EntityBaseView::setEntityData(LevelEditorEntity* entity, const wstring& name, const wstring& description)
{
	if (entity == nullptr)
		return;

	entity->setName(name);
	entity->setDescription(description);
}
