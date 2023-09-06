#include <tdme/engine/scene/SceneEntity.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/BaseProperties.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Transform.h>

using std::string;

using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::SceneEntity;
using tdme::engine::Transform;

SceneEntity::SceneEntity(const string& id, const string& description, const Transform& transform, Prototype* prototype): BaseProperties(id, description)
{
	this->transform.setTransform(transform);
	this->prototype = prototype;
}

SceneEntity::~SceneEntity() {
}

const BaseProperties* SceneEntity::getTotalProperties()
{
	auto totalProperties = new BaseProperties(name, description);
	for (auto prototypeProperty: getPrototype()->getProperties()) {
		totalProperties->addProperty(prototypeProperty->getName(), prototypeProperty->getValue());
	}
	for (auto entityProperty: getProperties()) {
		auto totalProperty = totalProperties->getProperty(entityProperty->getName());
		if (totalProperty != nullptr) {
			totalProperties->updateProperty(totalProperty->getName(), entityProperty->getName(), entityProperty->getValue());
		} else {
			totalProperties->addProperty(entityProperty->getName(), entityProperty->getValue());
		}
	}
	return totalProperties;
}
