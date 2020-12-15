#include <tdme/engine/scene/SceneEntity.h>

#include <string>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeProperties.h>
#include <tdme/engine/prototype/PrototypeProperty.h>

using std::string;

using tdme::engine::scene::SceneEntity;
using tdme::engine::Transformations;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeProperties;
using tdme::engine::prototype::PrototypeProperty;

SceneEntity::SceneEntity(const string& id, const string& description, const Transformations& transformations, Prototype* entity)
{
	this->id = id;
	this->description = description;
	this->transformations.fromTransformations(transformations);
	this->entity = entity;
}

SceneEntity::~SceneEntity() {
}

PrototypeProperties* SceneEntity::getTotalProperties()
{
	auto properties = new PrototypeProperties();
	for (auto i = 0; i < getEntity()->getPropertyCount(); i++) {
		PrototypeProperty* entityProperty = getEntity()->getPropertyByIndex(i);
		properties->addProperty(entityProperty->getName(), entityProperty->getValue());
	}
	for (auto i = 0; i < getPropertyCount(); i++) {
		PrototypeProperty* objectProperty = getPropertyByIndex(i);
		auto property = properties->getProperty(objectProperty->getName());
		if (property != nullptr) {
			properties->updateProperty(property->getName(), objectProperty->getName(), objectProperty->getValue());
		} else {
			properties->addProperty(objectProperty->getName(), objectProperty->getValue());
		}
	}
	return properties;
}
