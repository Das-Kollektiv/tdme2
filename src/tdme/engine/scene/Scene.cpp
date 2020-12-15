#include <tdme/engine/scene/Scene.h>

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/engine/prototype/Prototype_EntityType.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/utilities/Console.h>

using std::map;
using std::remove;
using std::vector;
using std::string;

using tdme::engine::scene::Scene;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::engine::prototype::Prototype_EntityType;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::scene::SceneLight;
using tdme::engine::scene::SceneEntity;
using tdme::utilities::Console;

Scene::Scene()
{
	applicationRoot = "";
	pathName = ".";
	fileName = "untitled.tl";
	rotationOrder = RotationOrder::XYZ;
	lights.push_back(new SceneLight(0));
	lights.push_back(new SceneLight(1));
	lights.push_back(new SceneLight(2));
	lights.push_back(new SceneLight(3));
	auto light = lights[0];
	light->getAmbient().set(0.7f, 0.7f, 0.7f, 1.0f);
	light->getDiffuse().set(0.3f, 0.3f, 0.3f, 1.0f);
	light->getSpecular().set(1.0f, 1.0f, 1.0f, 1.0f);
	light->getPosition().set(0.0f, 20000.0f, 0.0f, 1.0f);
	light->getSpotDirection().set(0.0f, 0.0f, 0.0f).sub(Vector3(light->getPosition().getX(), light->getPosition().getY(), light->getPosition().getZ()));
	light->getSpotTo().set(light->getPosition().getX(), light->getPosition().getY(), light->getPosition().getZ()).add(light->getSpotDirection());
	light->setConstantAttenuation(0.5f);
	light->setLinearAttenuation(0.0f);
	light->setQuadraticAttenuation(0.0f);
	light->setSpotExponent(0.0f);
	light->setSpotCutOff(180.0f);
	light->setEnabled(true);
	entityLibrary = new SceneLibrary(this);
	objectIdx = 0;
	skyModelScale = Vector3(1.0f, 1.0f, 1.0f);
}

Scene::~Scene() {
	for (auto light: lights) {
		delete light;
	}
	for (auto object: objects) {
		delete object;
	}
	delete entityLibrary;
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
	for (auto levelEditorObject: objects) {
		if (levelEditorObject->getEntity()->getType() != Prototype_EntityType::MODEL) continue;
		BoundingBox cbv;
		cbv.fromBoundingVolumeWithTransformations(levelEditorObject->getEntity()->getModel()->getBoundingBox(), levelEditorObject->getTransformations());
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
		auto objectLeft = bbMin.getX();
		auto objectRight = bbMax.getX();
		auto objectNear = bbMin.getZ();
		auto objectFar = bbMax.getZ();
		auto objectBottom = bbMin.getY();
		auto objectTop = bbMax.getY();
		if (haveDimension == false) {
			levelLeft = objectLeft;
			levelRight = objectRight;
			levelNear = objectNear;
			levelFar = objectFar;
			levelTop = objectTop;
			levelBottom = objectBottom;
			haveDimension = true;
		} else {
			if (objectLeft < levelLeft) levelLeft = objectLeft;
			if (objectRight > levelRight) levelRight = objectRight;
			if (objectNear < levelNear) levelNear = objectNear;
			if (objectFar > levelFar) levelFar = objectFar;
			if (objectTop > levelTop) levelTop = objectTop;
			if (objectBottom < levelBottom) levelBottom = objectBottom;
		}
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
	center.set(0.0f, 0.0f, 0.0f);
	auto objectCount = 0;
	for (auto levelEditorObject: objects) {
		if (levelEditorObject->getEntity()->getType() != Prototype_EntityType::MODEL)
			continue;

		center.add(levelEditorObject->getTransformations().getTranslation());
		objectCount++;
	}
	if (objectCount != 0)
		center.scale(1.0f / objectCount);
}

void Scene::clearObjects()
{
	objectsById.clear();
	objects.clear();
	environmentMappingIds.clear();
	objectIdx = 0;
}

void Scene::getObjectsByEntityId(int entityId, vector<string>& objectsByEntityId) {
	for (auto object: objects) {
		if (object->getEntity()->getId() == entityId) {
			objectsByEntityId.push_back(object->getId());
		}
	}
}

void Scene::removeObjectsByEntityId(int entityId)
{
	vector<string> objectsToRemove;
	getObjectsByEntityId(entityId, objectsToRemove);
	for (auto objectId: objectsToRemove) {
		removeObject(objectId);
	}
}

void Scene::replaceEntity(int searchEntityId, int replaceEntityId)
{
	auto replaceEntity = getEntityLibrary()->getEntity(replaceEntityId);
	if (replaceEntity == nullptr)
		return;

	for (auto object: objects) {
		if (object->getEntity()->getId() == searchEntityId) {
			object->setEntity(replaceEntity);
		}
	}
}

void Scene::addObject(SceneEntity* object)
{
	auto _entity = getObjectById(object->getId());
	if (_entity != nullptr) {
		removeObject(object->getId());
		Console::println(
			"Scene::addObject():: object with id '" +
			object->getId() +
			"' already exists. Removing it!"
		);
	}
	objectsById[object->getId()] = object;
	objects.push_back(object);
	if (object->getEntity()->getType() == Prototype_EntityType::ENVIRONMENTMAPPING) environmentMappingIds.insert(object->getId());
}

void Scene::removeObject(const string& id)
{
	auto objectByIdIt = objectsById.find(id);
	if (objectByIdIt != objectsById.end()) {
		auto object = objectByIdIt->second;
		objectsById.erase(objectByIdIt);
		objects.erase(remove(objects.begin(), objects.end(), object), objects.end());
		if (object->getEntity()->getType() == Prototype_EntityType::ENVIRONMENTMAPPING) environmentMappingIds.erase(object->getId());
		delete object;
	}
}

SceneEntity* Scene::getObjectById(const string& id)
{
	auto objectByIdIt = objectsById.find(id);
	if (objectByIdIt != objectsById.end()) {
		return objectByIdIt->second;
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
