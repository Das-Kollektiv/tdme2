#include <tdme/engine/scene/SceneLibrary.h>

#include <algorithm>
#include <string>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_EntityType.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/StringTools.h>

using std::remove;
using std::to_string;
using std::string;

using tdme::engine::scene::SceneLibrary;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::math::Vector3;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::engine::prototype::Prototype_EntityType;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::scene::Scene;
using tdme::utilities::Console;
using tdme::utilities::ExceptionBase;
using tdme::utilities::StringTools;

constexpr int SceneLibrary::ID_ALLOCATE;

SceneLibrary::SceneLibrary(Scene* level)
{
	this->level = level;
	this->entityIdx = 0;
}

SceneLibrary::~SceneLibrary() {
	for (auto entity: entities) {
		delete entity;
	}
}

void SceneLibrary::clear()
{
	for (auto entity: entities) {
		delete entity;
	}
	this->entitiesById.clear();
	this->entities.clear();
	this->entityIdx = 0;
}

int SceneLibrary::allocateEntityId()
{
	return entityIdx++;
}

Prototype* SceneLibrary::addModel(int id, const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot)
{
	Prototype* levelEditorEntity = nullptr;
	if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tmm") == true) {
		levelEditorEntity = ModelMetaDataFileImport::doImport(id == ID_ALLOCATE?allocateEntityId():id, pathName, fileName);
	} else {
		auto model = ModelReader::read(
			pathName,
			fileName
		);
		levelEditorEntity = new Prototype(
			id == ID_ALLOCATE?allocateEntityId():id,
			Prototype_EntityType::MODEL,
			name,
			description,
			"",
			pathName + "/" + fileName,
			StringTools::replace(StringTools::replace(StringTools::replace(model->getId(), "\\", "_"), "/", "_"), ":", "_") + ".png",
			model,
			Vector3(0.0f, 0.0f, 0.0f)
		);
	}
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

Prototype* SceneLibrary::addTrigger(int id, const string& name, const string& description, float width, float height, float depth)
{
	auto cacheId = "leveleditor.trigger." + to_string(width) + "mx" + to_string(height) + "mx" + to_string(depth) + "m";
	Prototype* levelEditorEntity = nullptr;
	auto boundingBox = new BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
	auto modelId = cacheId + "_bv";
	levelEditorEntity = new Prototype(
		id == ID_ALLOCATE?allocateEntityId():id,
		Prototype_EntityType::TRIGGER,
		name,
		description,
		"",
		cacheId,
		StringTools::replace(StringTools::replace(StringTools::replace(modelId, "\\", "_"), "/", "_"), ":", "_") + ".png",
		nullptr,
		Vector3()
	);
	levelEditorEntity->addBoundingVolume(0, new PrototypeBoundingVolume(0, levelEditorEntity));
	levelEditorEntity->getBoundingVolume(0)->setupAabb(boundingBox->getMin(), boundingBox->getMax());
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

Prototype* SceneLibrary::addEnvironmentMapping(int id, const string& name, const string& description, float width, float height, float depth)
{
	auto cacheId = "leveleditor.environmentmapping." + to_string(width) + "mx" + to_string(height) + "mx" + to_string(depth) + "m";
	Prototype* levelEditorEntity = nullptr;
	auto boundingBox = new BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
	auto modelId = cacheId + "_bv";
	levelEditorEntity = new Prototype(
		id == ID_ALLOCATE?allocateEntityId():id,
		Prototype_EntityType::ENVIRONMENTMAPPING,
		name,
		description,
		"",
		cacheId,
		StringTools::replace(StringTools::replace(StringTools::replace(cacheId, "\\", "_"), "/", "_"), ":", "_") + ".png",
		nullptr,
		Vector3()
	);
	levelEditorEntity->addBoundingVolume(0, new PrototypeBoundingVolume(0, levelEditorEntity));
	levelEditorEntity->getBoundingVolume(0)->setupAabb(boundingBox->getMin(), boundingBox->getMax());
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

Prototype* SceneLibrary::addEmpty(int id, const string& name, const string& description)
{
	auto cacheId = "leveleditor.empty";
	Prototype* levelEditorEntity = nullptr;
	auto model = ModelReader::read("resources/engine/tools/leveleditor/models", "empty.dae");
	levelEditorEntity = new Prototype(
		id == ID_ALLOCATE?allocateEntityId():id,
		Prototype_EntityType::EMPTY,
		name,
		description,
		"",
		cacheId,
		StringTools::replace(StringTools::replace(StringTools::replace(model->getId(), "\\", "_"), "/", "_"), ":", "_") + ".png",
		model,
		Vector3()
	);
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

Prototype* SceneLibrary::addParticleSystem(int id, const string& name, const string& description)
{
	auto levelEditorEntity = new Prototype(
		id == ID_ALLOCATE?allocateEntityId():id,
		Prototype_EntityType::PARTICLESYSTEM,
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

void SceneLibrary::addEntity(Prototype* levelEditorEntity)
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

Prototype* SceneLibrary::getEntityAt(int idx)
{
	return entities[idx];
}

Prototype* SceneLibrary::getEntity(int id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		return entityByIdIt->second;
	}
	return nullptr;
}

void SceneLibrary::removeEntity(int id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		entities.erase(remove(entities.begin(), entities.end(), entityByIdIt->second), entities.end());
		delete entityByIdIt->second;
		entitiesById.erase(entityByIdIt);
	}
}

int SceneLibrary::getEntityCount()
{
	return entities.size();
}
