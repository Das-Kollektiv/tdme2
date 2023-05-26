#include <tdme/engine/scene/Scene.h>

#include <algorithm>
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

using std::map;
using std::remove;
using std::string;
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
	lights.push_back(new SceneLight(0));
	auto light = lights[0];
	light->setAmbient(Color4(0.7f, 0.7f, 0.7f, 1.0f));
	light->setDiffuse(Color4(0.3f, 0.3f, 0.3f, 1.0f));
	light->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 1.0f));
	light->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light->getPosition().getX(), light->getPosition().getY(), light->getPosition().getZ())));
	light->setConstantAttenuation(0.5f);
	light->setLinearAttenuation(0.0f);
	light->setQuadraticAttenuation(0.0f);
	light->setSpotExponent(0.0f);
	light->setSpotCutOff(180.0f);
	light->setEnabled(true);
	library = new SceneLibrary(this);
	entityIdx = 0;
	skyModelScale = Vector3(1.0f, 1.0f, 1.0f);
}

Scene::~Scene() {
	for (auto light: lights) {
		delete light;
	}
	for (auto entity: entities) {
		delete entity;
	}
	delete library;
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
	for (auto sceneEntity: entities) {
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
	for (auto i = 0; i < library->getPrototypeCount(); i++) {
		auto prototype = library->getPrototypeAt(i);
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
	for (auto entity: entities) {
		if (entity->getPrototype()->getId() == prototypeId) {
			entitiesByPrototypeId.push_back(entity->getId());
		}
	}
}

void Scene::removeEntitiesByPrototypeId(int prototypeId)
{
	vector<string> entitiesToRemove;
	getEntitiesByPrototypeId(prototypeId, entitiesToRemove);
	for (auto entityId: entitiesToRemove) {
		removeEntity(entityId);
	}
}

void Scene::replacePrototypeByIds(int searchPrototypeId, int newEntityId)
{
	auto replaceEntity = getLibrary()->getPrototype(newEntityId);
	if (replaceEntity == nullptr)
		return;

	for (auto entity: entities) {
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
	entities.push_back(entity);
	if (entity->getPrototype()->getType() == Prototype_Type::ENVIRONMENTMAPPING) environmentMappingIds.insert(entity->getId());
}

bool Scene::removeEntity(const string& id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		auto entity = entityByIdIt->second;
		entitiesById.erase(entityByIdIt);
		entities.erase(remove(entities.begin(), entities.end(), entity), entities.end());
		if (entity->getPrototype()->getType() == Prototype_Type::ENVIRONMENTMAPPING) environmentMappingIds.erase(entity->getId());
		delete entity;
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
	if (this->skyModel== model) return;
	delete this->skyModel;
	this->skyModel = model;
}

void Scene::update() {
	computeBoundingBox();
	computeCenter();
}
