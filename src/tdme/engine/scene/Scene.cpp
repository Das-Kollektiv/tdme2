#include <tdme/engine/scene/Scene.h>

#include <algorithm>
#include <memory>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>

using std::make_unique;
using std::map;
using std::remove;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::scene::SceneLight;
using tdme::engine::Transform;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Console;

Scene::Scene(const string& name, const string& description): BaseProperties(name, description)
{
	applicationRootPathName = "";
	fileName = "untitled.tscene";
	rotationOrder = RotationOrder::XYZ;
	library = make_unique<SceneLibrary>(this);
	entityIdx = 0;
	skyModelScale = Vector3(1.0f, 1.0f, 1.0f);
}

Scene::~Scene() {
}

void Scene::computeBoundingBox()
{
	dimension.set(0.0f, 0.0f, 0.0f);
	auto haveDimension = false;
	auto levelLeft = 0.0f;
	auto levelRight = 0.0f;
	auto levelNear = 0.0f;
	auto levelFar = 0.0f;
	auto levelTop = 0.0f;
	auto levelBottom = 0.0f;
	Vector3 sideVector(1.0f, 0.0f, 0.0f);
	Vector3 upVector(0.0f, 1.0f, 0.0f);
	Vector3 forwardVector(0.0f, 0.0f, 1.0f);
	Vector3 bbDimension;
	Vector3 bbMin;
	Vector3 bbMax;
	for (const auto& sceneEntity: entities) {
		BoundingBox cbv;
		// TODO: Implement me 100%
		if (sceneEntity->getPrototype()->getType() == Prototype_Type::MODEL) {
			cbv.fromBoundingVolumeWithTransform(sceneEntity->getPrototype()->getModel()->getBoundingBox(), sceneEntity->getTransform());
		} else {
			continue;
		}

		//
		bbDimension.set(
			cbv.getDimensions().getX(),
			cbv.getDimensions().getY(),
			cbv.getDimensions().getZ()
		);
		bbDimension.scale(0.5f);
		bbMin.set(cbv.getCenter());
		bbMin.sub(bbDimension);
		bbMax.set(cbv.getCenter());
		bbMax.add(bbDimension);
		auto entityLeft = bbMin.getX();
		auto entityRight = bbMax.getX();
		auto entityNear = bbMin.getZ();
		auto entityFar = bbMax.getZ();
		auto entityBottom = bbMin.getY();
		auto entityTop = bbMax.getY();
		if (haveDimension == false) {
			levelLeft = entityLeft;
			levelRight = entityRight;
			levelNear = entityNear;
			levelFar = entityFar;
			levelTop = entityTop;
			levelBottom = entityBottom;
			haveDimension = true;
		} else {
			if (entityLeft < levelLeft) levelLeft = entityLeft;
			if (entityRight > levelRight) levelRight = entityRight;
			if (entityNear < levelNear) levelNear = entityNear;
			if (entityFar > levelFar) levelFar = entityFar;
			if (entityTop > levelTop) levelTop = entityTop;
			if (entityBottom < levelBottom) levelBottom = entityBottom;
		}
	}
	for (auto prototype: library->getPrototypes()) {
		if (prototype->getType() != Prototype_Type::TERRAIN) continue;
		auto terrain = prototype->getTerrain();
		auto entityLeft = 0.0f;
		auto entityRight = terrain->getWidth();
		auto entityNear = 0.0f;
		auto entityFar = terrain->getDepth();
		if (entityLeft < levelLeft) levelLeft = entityLeft;
		if (entityRight > levelRight) levelRight = entityRight;
		if (entityNear < levelNear) levelNear = entityNear;
		if (entityFar > levelFar) levelFar = entityFar;
		for (auto terrainHeight: terrain->getHeightVector()) {
			auto entityTop = terrainHeight;
			auto entityBottom = terrainHeight;
			if (entityTop > levelTop) levelTop = entityTop;
			if (entityBottom < levelBottom) levelBottom = entityBottom;
		}
		// one terrain only, so break here
		break;
	}
	boundingBox.getMin().set(levelLeft, levelBottom, levelNear);
	boundingBox.getMax().set(levelRight, levelTop, levelFar);
	boundingBox.update();
	dimension.setX(levelRight - levelLeft);
	dimension.setZ(levelFar - levelNear);
	dimension.setY(levelTop - levelBottom);
}

void Scene::computeCenter()
{
	center = boundingBox.getMin().clone().add(boundingBox.getMax()).scale(0.5f);
}

void Scene::clearEntities()
{
	entitiesById.clear();
	entities.clear();
	environmentMappingIds.clear();
	entityIdx = 0;
}

void Scene::getEntitiesByPrototypeId(int prototypeId, vector<string>& entitiesByPrototypeId) {
	for (const auto& entity: entities) {
		if (entity->getPrototype()->getId() == prototypeId) {
			entitiesByPrototypeId.push_back(entity->getId());
		}
	}
}

void Scene::removeEntitiesByPrototypeId(int prototypeId)
{
	vector<string> entitiesToRemove;
	getEntitiesByPrototypeId(prototypeId, entitiesToRemove);
	for (const auto& entityId: entitiesToRemove) {
		removeEntity(entityId);
	}
}

void Scene::replacePrototypeByIds(int searchPrototypeId, int newEntityId)
{
	auto replaceEntity = getLibrary()->getPrototype(newEntityId);
	if (replaceEntity == nullptr)
		return;

	for (const auto& entity: entities) {
		if (entity->getPrototype()->getId() == searchPrototypeId) {
			entity->setPrototype(replaceEntity);
		}
	}
}

void Scene::addEntity(SceneEntity* entity)
{
	auto _entity = getEntity(entity->getId());
	if (_entity != nullptr) {
		removeEntity(entity->getId());
		Console::println(
			"Scene::addEntity():: entity with id '" +
			entity->getId() +
			"' already exists. Removing it!"
		);
	}
	entitiesById[entity->getId()] = entity;
	entities.push_back(unique_ptr<SceneEntity>(entity));
	if (entity->getPrototype()->getType() == Prototype_Type::ENVIRONMENTMAPPING) environmentMappingIds.insert(entity->getId());
}

bool Scene::removeEntity(const string& id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		auto entity = entityByIdIt->second;
		for (auto i = 0; i < entities.size(); i++) {
			if (entities[i].get() == entity) {
				entities.erase(entities.begin() + i);
				break;
			}
		}
		entitiesById.erase(entityByIdIt);
		if (entity->getPrototype()->getType() == Prototype_Type::ENVIRONMENTMAPPING) environmentMappingIds.erase(entity->getId());
		return true;
	} else {
		return false;
	}
}

bool Scene::renameEntity(const string& id, const string& newId) {
	if (id == newId) return true;
	if (getEntity(newId) != nullptr) return false;
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		auto entity = entityByIdIt->second;
		entitiesById.erase(entityByIdIt);
		if (entity->getPrototype()->getType() == Prototype_Type::ENVIRONMENTMAPPING) environmentMappingIds.erase(entity->getId());
		entity->setName(newId);
		entitiesById[entity->getId()] = entity;
		if (entity->getPrototype()->getType() == Prototype_Type::ENVIRONMENTMAPPING) environmentMappingIds.insert(entity->getId());
		return true;
	} else {
		return false;
	}
}

SceneEntity* Scene::getEntity(const string& id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		return entityByIdIt->second;
	}
	return nullptr;
}

void Scene::setSkyModel(Model* model) {
	this->skyModel = unique_ptr<Model>(model);
}

void Scene::update() {
	computeBoundingBox();
	computeCenter();
}
