#include <tdme/tools/shared/model/LevelEditorObject.h>

#include <string>

#include <java/lang/String.h>
#include <tdme/engine/Transformations.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/ModelProperties.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>

using std::wstring;

using tdme::tools::shared::model::LevelEditorObject;
using java::lang::String;
using tdme::engine::Transformations;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::ModelProperties;
using tdme::tools::shared::model::PropertyModelClass;

LevelEditorObject::LevelEditorObject(const wstring& id, const wstring& description, Transformations* transformations, LevelEditorEntity* entity)
{
	this->id = id;
	this->description = description;
	this->transformations = transformations;
	this->entity = entity;
}

const wstring& LevelEditorObject::getId()
{
	return id;
}

void LevelEditorObject::setId(const wstring& id)
{
	this->id = id;
}

const wstring& LevelEditorObject::getDescription()
{
	return description;
}

void LevelEditorObject::setDescription(const wstring& description)
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
