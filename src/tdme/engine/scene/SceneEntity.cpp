#include <tdme/engine/scene/SceneEntity.h>

#include <string>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/prototype/BaseProperties.h>
#include <tdme/engine/prototype/BaseProperty.h>

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::scene::SceneEntity;
using tdme::engine::Transformations;

SceneEntity::SceneEntity(const string& id, const string& description, const Transformations& transformations, Prototype* prototype): BaseProperties(id, name)
{
	this->transformations.fromTransformations(transformations);
	this->prototype = prototype;
}

SceneEntity::~SceneEntity() {
}

const BaseProperties SceneEntity::getTotalProperties()
{
	BaseProperties totalProperties(name, description);
	for (auto i = 0; i < getPrototype()->getPropertyCount(); i++) {
		auto prototypeProperty = getPrototype()->getPropertyByIndex(i);
		totalProperties.addProperty(prototypeProperty->getName(), prototypeProperty->getValue());
	}
	for (auto i = 0; i < getPropertyCount(); i++) {
		auto entityProperty = getPropertyByIndex(i);
		auto totalProperty = totalProperties.getProperty(entityProperty->getName());
		if (totalProperty != nullptr) {
			totalProperties.updateProperty(totalProperty->getName(), entityProperty->getName(), entityProperty->getValue());
		} else {
			totalProperties.addProperty(entityProperty->getName(), entityProperty->getValue());
		}
	}
	return totalProperties;
}
