// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntity.java
#include <tdme/tools/shared/model/LevelEditorEntity.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Model.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem.h>
#include <tdme/utils/_ArrayList.h>

using tdme::tools::shared::model::LevelEditorEntity;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

LevelEditorEntity::LevelEditorEntity(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntity::LevelEditorEntity(int32_t id, LevelEditorEntity_EntityType* entityType, String* name, String* description, String* entityFileName, String* fileName, String* thumbnail, Model* model, Vector3* pivot) 
	: LevelEditorEntity(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,entityType,name,description,entityFileName,fileName,thumbnail,model,pivot);
}

constexpr int32_t LevelEditorEntity::ID_NONE;

void LevelEditorEntity::ctor(int32_t id, LevelEditorEntity_EntityType* entityType, String* name, String* description, String* entityFileName, String* fileName, String* thumbnail, Model* model, Vector3* pivot)
{
	super::ctor();
	this->id = id;
	this->type = entityType;
	this->name = name;
	this->description = description;
	this->entityFileName = entityFileName;
	this->fileName = fileName;
	this->thumbnail = thumbnail;
	this->model = model;
	this->pivot = pivot;
	if (this->type == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		this->particleSystem = new LevelEditorEntityParticleSystem();
	}
	this->boundingVolumes = new _ArrayList();
}

int32_t LevelEditorEntity::getId()
{
	return id;
}

LevelEditorEntity_EntityType* LevelEditorEntity::getType()
{
	return type;
}

String* LevelEditorEntity::getName()
{
	return name;
}

void LevelEditorEntity::setName(String* name)
{
	this->name = name;
}

String* LevelEditorEntity::getDescription()
{
	return description;
}

void LevelEditorEntity::setDescription(String* description)
{
	this->description = description;
}

String* LevelEditorEntity::getEntityFileName()
{
	return entityFileName;
}

void LevelEditorEntity::setEntityFileName(String* entityFileName)
{
	this->entityFileName = entityFileName;
}

String* LevelEditorEntity::getFileName()
{
	return fileName;
}

String* LevelEditorEntity::getThumbnail()
{
	return thumbnail;
}

Model* LevelEditorEntity::getModel()
{
	return model;
}

_ArrayList* LevelEditorEntity::getBoundingVolumes()
{
	return boundingVolumes;
}

Vector3* LevelEditorEntity::getPivot()
{
	return pivot;
}

int32_t LevelEditorEntity::getBoundingVolumeCount()
{
	return boundingVolumes->size();
}

LevelEditorEntityBoundingVolume* LevelEditorEntity::getBoundingVolumeAt(int32_t idx)
{
	return java_cast< LevelEditorEntityBoundingVolume* >(boundingVolumes->get(idx));
}

bool LevelEditorEntity::addBoundingVolume(int32_t idx, LevelEditorEntityBoundingVolume* levelEditorEntityBoundingVolume)
{
	if (idx < 0)
		return false;

	if (idx > boundingVolumes->size())
		return false;

	if (idx == boundingVolumes->size()) {
		boundingVolumes->add(levelEditorEntityBoundingVolume);
	}
	return false;
}

void LevelEditorEntity::setDefaultBoundingVolumes()
{
	for (auto i = boundingVolumes->size(); i < 8; i++) {
		auto bv = new LevelEditorEntityBoundingVolume(i, this);
		addBoundingVolume(i, bv);
	}
}

LevelEditorEntityParticleSystem* LevelEditorEntity::getParticleSystem()
{
	return particleSystem;
}

String* LevelEditorEntity::toString()
{
	return ::java::lang::StringBuilder().append(u"LevelEditorEntity [id="_j)->append(id)
		->append(u", type="_j)
		->append(static_cast< Object* >(type))
		->append(u", name="_j)
		->append(name)
		->append(u", description="_j)
		->append(description)
		->append(u", entityFileName="_j)
		->append(entityFileName)
		->append(u", fileName="_j)
		->append(fileName)
		->append(u", thumbnail="_j)
		->append(thumbnail)
		->append(u", model="_j)
		->append(static_cast< Object* >(model))
		->append(u", boundingVolumes="_j)
		->append(static_cast< Object* >(boundingVolumes))
		->append(u", pivot="_j)
		->append(static_cast< Object* >(pivot))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntity::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntity", 41);
    return c;
}

java::lang::Class* LevelEditorEntity::getClass0()
{
	return class_();
}

