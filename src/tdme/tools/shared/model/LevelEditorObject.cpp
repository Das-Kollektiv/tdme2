#include <tdme/tools/shared/model/LevelEditorObject.h>

#include <string>

#include <tdme/engine/Transformations.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/ModelProperties.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>

using std::string;

using tdme::tools::shared::model::LevelEditorObject;
using tdme::engine::Transformations;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::ModelProperties;
using tdme::tools::shared::model::PropertyModelClass;

LevelEditorObject::LevelEditorObject(const string& id, const string& description, const Transformations& transformations, LevelEditorEntity* entity)
{
	this->id = id;
	this->description = description;
	this->transformations.fromTransformations(transformations);
	this->entity = entity;
}

LevelEditorObject::~LevelEditorObject() {
}

ModelProperties* LevelEditorObject::getTotalProperties()
{
	auto properties = new ModelProperties();
	for (auto i = 0; i < getEntity()->getPropertyCount(); i++) {
		PropertyModelClass* entityProperty = getEntity()->getPropertyByIndex(i);
		properties->addProperty(entityProperty->getName(), entityProperty->getValue());
	}
	for (auto i = 0; i < getPropertyCount(); i++) {
		PropertyModelClass* objectProperty = getPropertyByIndex(i);
		auto property = properties->getProperty(objectProperty->getName());
		if (property != nullptr) {
			properties->updateProperty(property->getName(), objectProperty->getName(), objectProperty->getValue());
		} else {
			properties->addProperty(objectProperty->getName(), objectProperty->getValue());
		}
	}
	return properties;
}
