#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_ExceptionBase.h>
#include <tdme/utils/StringUtils.h>

using std::map;
using std::remove;
using std::to_wstring;
using std::vector;
using std::wstring;

using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::math::Vector3;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::utils::StringConverter;
using tdme::utils::_Console;
using tdme::utils::_ExceptionBase;
using tdme::utils::StringUtils;

constexpr int32_t LevelEditorEntityLibrary::ID_ALLOCATE;

LevelEditorEntityLibrary::LevelEditorEntityLibrary(LevelEditorLevel* level) 
{
	this->level = level;
	this->entityIdx = 0;
}

void LevelEditorEntityLibrary::clear()
{
	this->entitiesById.clear();
	this->entities.clear();
	this->entityIdx = 0;
}

int32_t LevelEditorEntityLibrary::allocateEntityId()
{
	return entityIdx++;
}

LevelEditorEntity* LevelEditorEntityLibrary::addModel(int32_t id, const wstring& name, const wstring& description, const wstring& pathName, const wstring& fileName, Vector3* pivot) /* throws(Exception) */
{
	LevelEditorEntity* levelEditorEntity = nullptr;
	if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".dae") == true) {
		auto model = DAEReader::read(
			pathName,
			fileName
		);
		levelEditorEntity = new LevelEditorEntity(
			id == ID_ALLOCATE ? allocateEntityId() : id,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			L"",
			pathName + L"/" + fileName,
			StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), L"\\", L"_"), L"/", L"_"), L":", L"_") + L".png",
			model,
			new Vector3(0.0f, 0.0f, 0.0f)
		);
	} else
	if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".tm") == true) {
		auto model = TMReader::read(
			pathName,
			fileName
		);
		levelEditorEntity = new LevelEditorEntity(
			id == ID_ALLOCATE ? allocateEntityId() : id,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			L"",
			pathName + L"/" + fileName,
			StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), L"\\", L"_"), L"/", L"_"), L":", L"_") + L".png",
			model,
			new Vector3(0.0f, 0.0f, 0.0f)
		);
	} else
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".tmm") == true) {
		levelEditorEntity = ModelMetaDataFileImport::doImport(id == ID_ALLOCATE ? allocateEntityId() : id, pathName, fileName);
	} else {
		throw _ExceptionBase(
			StringConverter::toString(pathName) +
			"/" +
			StringConverter::toString(pathName) +
			string(": Unknown model file format")
		 );
	}
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addTrigger(int32_t id, const wstring& name, const wstring& description, float width, float height, float depth) /* throws(Exception) */
{
	auto cacheId = L"leveleditor.trigger." + to_wstring(width) + L"mx" + to_wstring(height) + L"mx" + to_wstring(depth) + L"m";
	LevelEditorEntity* levelEditorEntity = nullptr;
	auto boundingBox = new BoundingBox(new Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), new Vector3(+width / 2.0f, height, +depth / 2.0f));
	auto model = PrimitiveModel::createModel(boundingBox, cacheId + L"_bv");
	levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::TRIGGER,
		name,
		description,
		L"",
		cacheId,
		StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), L"\\", L"_"), L"/", L"_"), L":", L"_") + L".png",
		model,
		new Vector3()
	);
	levelEditorEntity->addBoundingVolume(0, new LevelEditorEntityBoundingVolume(0, levelEditorEntity));
	levelEditorEntity->getBoundingVolumeAt(0)->setupAabb(boundingBox->getMin(), boundingBox->getMax());
	id = levelEditorEntity->getId();
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addEmpty(int32_t id, const wstring& name, const wstring& description) /* throws(Exception) */
{
	auto cacheId = L"leveleditor.empty";
	LevelEditorEntity* levelEditorEntity = nullptr;
	auto model = DAEReader::read(L"resources/tools/leveleditor/models", L"arrow.dae");
	levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::EMPTY,
		name,
		description,
		L"",
		cacheId,
		StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), L"\\", L"_"), L"/", L"_"), L":", L"_") + L".png",
		model,
		new Vector3()
	);
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addParticleSystem(int32_t id, const wstring& name, const wstring& description) /* throws(Exception) */
{
	auto levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::PARTICLESYSTEM,
		name,
		description,
		L"",
		L"",
		L"",
		nullptr,
		new Vector3()
	);
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

void LevelEditorEntityLibrary::addEntity(LevelEditorEntity* levelEditorEntity) /* throws(Exception) */
{

	auto entityByIdIt = entitiesById.find(levelEditorEntity->getId());
	if (entityByIdIt != entitiesById.end()) {
		throw _ExceptionBase("Entity id already in use");
	}
	entities.push_back(levelEditorEntity);
	entitiesById[levelEditorEntity->getId()] = levelEditorEntity;
	if (levelEditorEntity->getId() >= entityIdx)
		entityIdx = levelEditorEntity->getId() + 1;

}

LevelEditorEntity* LevelEditorEntityLibrary::getEntityAt(int32_t idx)
{
	return entities.at(idx);
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
	}
}

int32_t LevelEditorEntityLibrary::getEntityCount()
{
	return entities.size();
}
