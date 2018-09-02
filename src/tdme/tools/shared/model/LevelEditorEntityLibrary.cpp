#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>

#include <algorithm>
#include <string>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/ExceptionBase.h>
#include <tdme/utils/StringUtils.h>

using std::remove;
using std::to_string;
using std::string;

using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::math::Vector3;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::utils::Console;
using tdme::utils::ExceptionBase;
using tdme::utils::StringUtils;

constexpr int32_t LevelEditorEntityLibrary::ID_ALLOCATE;

LevelEditorEntityLibrary::LevelEditorEntityLibrary(LevelEditorLevel* level) 
{
	this->level = level;
	this->entityIdx = 0;
}

LevelEditorEntityLibrary::~LevelEditorEntityLibrary() {
	for (auto entity: entities) {
		delete entity;
	}
}

void LevelEditorEntityLibrary::clear()
{
	for (auto entity: entities) {
		delete entity;
	}
	this->entitiesById.clear();
	this->entities.clear();
	this->entityIdx = 0;
}

int32_t LevelEditorEntityLibrary::allocateEntityId()
{
	return entityIdx++;
}

LevelEditorEntity* LevelEditorEntityLibrary::addModel(int32_t id, const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot) /* throws(Exception) */
{
	LevelEditorEntity* levelEditorEntity = nullptr;
	if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tmm") == true) {
		levelEditorEntity = ModelMetaDataFileImport::doImport(id == ID_ALLOCATE ? allocateEntityId() : id, pathName, fileName);
	} else {
		auto model = ModelReader::read(
			pathName,
			fileName
		);
		levelEditorEntity = new LevelEditorEntity(
			id == ID_ALLOCATE ? allocateEntityId() : id,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			"",
			pathName + "/" + fileName,
			StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), "\\", "_"), "/", "_"), ":", "_") + ".png",
			model,
			Vector3(0.0f, 0.0f, 0.0f)
		);
	}
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addTrigger(int32_t id, const string& name, const string& description, float width, float height, float depth) /* throws(Exception) */
{
	auto cacheId = "leveleditor.trigger." + to_string(width) + "mx" + to_string(height) + "mx" + to_string(depth) + "m";
	LevelEditorEntity* levelEditorEntity = nullptr;
	auto boundingBox = new BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
	auto model = PrimitiveModel::createModel(boundingBox, cacheId + "_bv");
	levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::TRIGGER,
		name,
		description,
		"",
		cacheId,
		StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), "\\", "_"), "/", "_"), ":", "_") + ".png",
		model,
		Vector3()
	);
	levelEditorEntity->addBoundingVolume(0, new LevelEditorEntityBoundingVolume(0, levelEditorEntity));
	levelEditorEntity->getBoundingVolumeAt(0)->setupAabb(boundingBox->getMin(), boundingBox->getMax());
	id = levelEditorEntity->getId();
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addEmpty(int32_t id, const string& name, const string& description) /* throws(Exception) */
{
	auto cacheId = "leveleditor.empty";
	LevelEditorEntity* levelEditorEntity = nullptr;
	auto model = ModelReader::read("resources/tools/leveleditor/models", "arrow.dae");
	levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::EMPTY,
		name,
		description,
		"",
		cacheId,
		StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), "\\", "_"), "/", "_"), ":", "_") + ".png",
		model,
		Vector3()
	);
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addParticleSystem(int32_t id, const string& name, const string& description) /* throws(Exception) */
{
	auto levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::PARTICLESYSTEM,
		name,
		description,
		"",
		"",
		"",
		nullptr,
		Vector3()
	);
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

void LevelEditorEntityLibrary::addEntity(LevelEditorEntity* levelEditorEntity) /* throws(Exception) */
{

	auto entityByIdIt = entitiesById.find(levelEditorEntity->getId());
	if (entityByIdIt != entitiesById.end()) {
		throw ExceptionBase("Entity id already in use");
	}
	entities.push_back(levelEditorEntity);
	entitiesById[levelEditorEntity->getId()] = levelEditorEntity;
	if (levelEditorEntity->getId() >= entityIdx)
		entityIdx = levelEditorEntity->getId() + 1;

}

LevelEditorEntity* LevelEditorEntityLibrary::getEntityAt(int32_t idx)
{
	return entities[idx];
}

LevelEditorEntity* LevelEditorEntityLibrary::getEntity(int32_t id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		return entityByIdIt->second;
	}
	return nullptr;
}

void LevelEditorEntityLibrary::removeEntity(int32_t id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		entitiesById.erase(entityByIdIt);
		entities.erase(remove(entities.begin(), entities.end(), entityByIdIt->second), entities.end());
		delete entityByIdIt->second;
	}
}

int32_t LevelEditorEntityLibrary::getEntityCount()
{
	return entities.size();
}
