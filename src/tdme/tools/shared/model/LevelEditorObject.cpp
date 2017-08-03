// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorObject.java
#include <tdme/tools/shared/model/LevelEditorObject.h>

#include <java/lang/Iterable.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/engine/Transformations.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/ModelProperties.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>

using tdme::tools::shared::model::LevelEditorObject;
using java::lang::Iterable;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::engine::Transformations;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::ModelProperties;
using tdme::tools::shared::model::PropertyModelClass;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

LevelEditorObject::LevelEditorObject(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorObject::LevelEditorObject() 
	: LevelEditorObject(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

LevelEditorObject::LevelEditorObject(String* id, String* description, Transformations* transformations, LevelEditorEntity* entity) 
	: LevelEditorObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,description,transformations,entity);
}

void LevelEditorObject::ctor()
{
	super::ctor();
	id = nullptr;
	description = nullptr;
	transformations = nullptr;
	entity = nullptr;
}

void LevelEditorObject::ctor(String* id, String* description, Transformations* transformations, LevelEditorEntity* entity)
{
	super::ctor();
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

LevelEditorObject* LevelEditorObject::clone()
{
	auto object = new LevelEditorObject();
	object->id = id;
	object->description = description;
	object->transformations = transformations;
	object->entity = entity;
	return object;
}

String* LevelEditorObject::toString()
{
	return ::java::lang::StringBuilder().append(u"LevelEditorObject [id="_j)->append(id)
		->append(u", description="_j)
		->append(description)
		/*
		->append(u", transformations="_j)
		->append(static_cast< Object* >(transformations))
		*/
		->append(u", entity="_j)
		->append(static_cast< Object* >(entity))
		->append(u", objectProperties="_j)
		->append(super::toString())
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorObject::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorObject", 41);
    return c;
}

java::lang::Class* LevelEditorObject::getClass0()
{
	return class_();
}

