// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntity.java
#include <tdme/tools/shared/model/LevelEditorEntity.h>

#include <vector>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Model.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem.h>

using std::vector;

using tdme::tools::shared::model::LevelEditorEntity;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;

constexpr int32_t LevelEditorEntity::ID_NONE;

LevelEditorEntity::LevelEditorEntity(int32_t id, LevelEditorEntity_EntityType* entityType, String* name, String* description, String* entityFileName, String* fileName, String* thumbnail, Model* model, Vector3* pivot) 
{
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

Vector3* LevelEditorEntity::getPivot()
{
	return pivot;
}

int32_t LevelEditorEntity::getBoundingVolumeCount()
{
	return boundingVolumes.size();
}

LevelEditorEntityBoundingVolume* LevelEditorEntity::getBoundingVolumeAt(int32_t idx)
{
	return boundingVolumes.at(idx);
}

bool LevelEditorEntity::addBoundingVolume(int32_t idx, LevelEditorEntityBoundingVolume* levelEditorEntityBoundingVolume)
{
	if (idx < 0)
		return false;

	if (idx > boundingVolumes.size())
		return false;

	if (idx == boundingVolumes.size()) {
		boundingVolumes.push_back(levelEditorEntityBoundingVolume);
	}
	return false;
}

void LevelEditorEntity::setDefaultBoundingVolumes()
{
	for (auto i = boundingVolumes.size(); i < 8; i++) {
		auto bv = new LevelEditorEntityBoundingVolume(i, this);
		addBoundingVolume(i, bv);
	}
}

LevelEditorEntityParticleSystem* LevelEditorEntity::getParticleSystem()
{
	return particleSystem;
}
