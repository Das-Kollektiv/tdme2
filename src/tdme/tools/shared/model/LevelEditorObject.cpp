// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorObject.java
#include <tdme/tools/shared/model/LevelEditorObject.h>

#include <java/lang/Iterable.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/engine/Transformations.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/ModelProperties.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>

using tdme::tools::shared::model::LevelEditorObject;
using java::lang::Iterable;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::engine::Transformations;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::ModelProperties;
using tdme::tools::shared::model::PropertyModelClass;

LevelEditorObject::LevelEditorObject(String* id, String* description, Transformations* transformations, LevelEditorEntity* entity) 
{
	this->id = id;
	this->description = description;
	this->transformations = transformations;
	this->entity = entity;
}

String* LevelEditorObject::getId()
{
	return id;
}

void LevelEditorObject::setId(String* id)
{
	this->id = id;
}

String* LevelEditorObject::getDescription()
{
	return description;
}

void LevelEditorObject::setDescription(String* description)
{
	this->description = description;
}

Transformations* LevelEditorObject::getTransformations()
{
	return transformations;
}

LevelEditorEntity* LevelEditorObject::getEntity()
{
	return entity;
}

void LevelEditorObject::setEntity(LevelEditorEntity* entity)
{
	this->entity = entity;
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
