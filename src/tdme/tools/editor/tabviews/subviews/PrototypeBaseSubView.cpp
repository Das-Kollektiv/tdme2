#include <tdme/tools/editor/tabviews/subviews/PrototypeBaseSubView.h>

#include <string>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/engine/scene/ScenePropertyPresets.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeBaseSubController.h>

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeProperty;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;
using tdme::tools::editor::tabviews::subviews::PrototypeBaseSubView;

PrototypeBaseSubView::PrototypeBaseSubView(PrototypeBaseSubController* prototypeBaseSubController)
{
	this->prototypeBaseSubController = prototypeBaseSubController;
}

void PrototypeBaseSubView::initialize()
{
	prototypeBaseSubController->setPrototypePresetIds(ScenePropertyPresets::getInstance()->getEntityPropertiesPresets());
}

void PrototypeBaseSubView::prototypePropertiesPreset(Prototype* prototype, const string& presetId)
{
	if (prototype == nullptr)
		return;

	prototype->clearProperties();
	auto& entityPropertiesPresets = ScenePropertyPresets::getInstance()->getEntityPropertiesPresets();
	const vector<PrototypeProperty*>* entityPropertyPresetArrayList = nullptr;
	auto entityPropertyPresetArrayListIt = entityPropertiesPresets.find(presetId);
	if (entityPropertyPresetArrayListIt != entityPropertiesPresets.end()) {
		entityPropertyPresetArrayList = &entityPropertyPresetArrayListIt->second;
	}
	if (entityPropertyPresetArrayList != nullptr) {
		for (auto entityPropertyPreset: *entityPropertyPresetArrayList) {
			prototype->addProperty(entityPropertyPreset->getName(), entityPropertyPreset->getValue());
		}
	}
	prototypeBaseSubController->setPrototypeProperties(prototype, presetId, "");
}

bool PrototypeBaseSubView::prototypePropertySave(Prototype* prototype, const string& oldName, const string& name, const string& value)
{
	if (prototype == nullptr)
		return false;

	if (prototype->updateProperty(oldName, name, value) == true) {
		prototypeBaseSubController->setPrototypeProperties(prototype, "", name);
		return true;
	}
	return false;
}

bool PrototypeBaseSubView::prototypePropertyAdd(Prototype* prototype)
{
	if (prototype == nullptr)
		return false;

	if (prototype->addProperty("new.property", "new.value")) {
		prototypeBaseSubController->setPrototypeProperties(prototype, "", "new.property");
		return true;
	}
	return false;
}

bool PrototypeBaseSubView::prototypePropertyRemove(Prototype* prototype, const string& name)
{
	if (prototype == nullptr)
		return false;

	auto idx = prototype->getPropertyIndex(name);
	if (idx != -1 && prototype->removeProperty(name) == true) {
		auto property = prototype->getPropertyByIndex(idx);
		if (property == nullptr) {
			property = prototype->getPropertyByIndex(idx - 1);
		}
		prototypeBaseSubController->setPrototypeProperties(prototype, "", property == nullptr ? "" : property->getName());
		return true;
	}
	return false;
}

void PrototypeBaseSubView::setPrototypeData(Prototype* prototype, const string& name, const string& description)
{
	if (prototype == nullptr)
		return;

	prototype->setName(name);
	prototype->setDescription(description);
}
