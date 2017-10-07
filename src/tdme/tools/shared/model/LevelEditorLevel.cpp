#include <tdme/tools/shared/model/LevelEditorLevel.h>

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
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLight.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/utils/Console.h>

using std::map;
using std::remove;
using std::vector;
using std::wstring;

using tdme::tools::shared::model::LevelEditorLevel;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::utils::Console;

LevelEditorLevel::LevelEditorLevel() 
{
	gameRoot = L"";
	pathName = L".";
	fileName = L"untitled.tl";
	rotationOrder = RotationOrder::XYZ;
	lights.push_back(new LevelEditorLight(0));
	lights.push_back(new LevelEditorLight(1));
	lights.push_back(new LevelEditorLight(2));
	lights.push_back(new LevelEditorLight(3));
	auto light = lights.at(0);
	light->getAmbient().set(1.0f, 1.0f, 1.0f, 1.0f);
	light->getDiffuse().set(0.5f, 0.5f, 0.5f, 1.0f);
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
	entityLibrary = new LevelEditorEntityLibrary(this);
	objectIdx = 0;
}

const wstring& LevelEditorLevel::getGameRoot()
{
	return gameRoot;
}

void LevelEditorLevel::setGameRoot(const wstring& gameRoot)
{
	this->gameRoot = gameRoot;
}

const wstring& LevelEditorLevel::getPathName()
{
	return pathName;
}

void LevelEditorLevel::setPathName(const wstring& pathName)
{
	this->pathName = pathName;
}

const wstring& LevelEditorLevel::getFileName()
{
	return fileName;
}

void LevelEditorLevel::setFileName(const wstring& fileName)
{
	this->fileName = fileName;
}

RotationOrder* LevelEditorLevel::getRotationOrder()
{
	return rotationOrder;
}

void LevelEditorLevel::setRotationOrder(RotationOrder* rotationOrder)
{
	this->rotationOrder = rotationOrder;
}

int32_t LevelEditorLevel::getLightCount()
{
	return lights.size();
}

LevelEditorLight* LevelEditorLevel::getLightAt(int32_t i)
{
	return lights.at(i);
}

LevelEditorEntityLibrary* LevelEditorLevel::getEntityLibrary()
{
	return entityLibrary;
}

const Vector3& LevelEditorLevel::getDimension()
{
	return dimension;
}

BoundingBox* LevelEditorLevel::getBoundingBox()
{
	return &boundingBox;
}

void LevelEditorLevel::computeBoundingBox()
{
	dimension.set(0.0f, 0.0f, 0.0f);
	auto haveDimension = false;
	auto left = 0.0f;
	auto right = 0.0f;
	auto near = 0.0f;
	auto far = 0.0f;
	auto top = 0.0f;
	auto bottom = 0.0f;
	Vector3 sideVector(1.0f, 0.0f, 0.0f);
	Vector3 upVector(0.0f, 1.0f, 0.0f);
	Vector3 forwardVector(0.0f, 0.0f, 1.0f);
	Vector3 bbDimension;
	Vector3 bbMin;
	Vector3 bbMax;
	for (auto levelEditorObject: objects) {
		if (levelEditorObject->getEntity()->getType() != LevelEditorEntity_EntityType::MODEL)
			continue;

		auto bv = levelEditorObject->getEntity()->getModel()->getBoundingBox();
		auto cbv = bv->clone();
		cbv->fromBoundingVolumeWithTransformations(bv, levelEditorObject->getTransformations());
		bbDimension.set(cbv->computeDimensionOnAxis(sideVector), cbv->computeDimensionOnAxis(upVector), cbv->computeDimensionOnAxis(forwardVector));
		bbDimension.scale(0.5f);
		bbMin.set(cbv->getCenter());
		bbMin.sub(bbDimension);
		bbMax.set(cbv->getCenter());
		bbMax.add(bbDimension);
		auto objectLeft = bbMin.getX();
		auto objectRight = bbMax.getX();
		auto objectNear = bbMin.getZ();
		auto objectFar = bbMax.getZ();
		auto objectBottom = bbMin.getY();
		auto objectTop = bbMax.getY();
		if (haveDimension == false) {
			left = objectLeft;
			right = objectRight;
			near = objectNear;
			far = objectFar;
			top = objectTop;
			bottom = objectBottom;
			haveDimension = true;
		} else {
			if (objectLeft < left) left = objectLeft;
			if (objectRight > right) right = objectRight;
			if (objectNear < near) near = objectNear;
			if (objectFar > far) far = objectFar;
			if (objectTop > top) top = objectTop;
			if (objectBottom < bottom) bottom = objectBottom;
		}
	}

	boundingBox.getMin().set(left, bottom, near);
	boundingBox.getMax().set(right, top, far);
	boundingBox.update();
	dimension.setX(right - left);
	dimension.setZ(far - near);
	dimension.setY(top - bottom);
}

void LevelEditorLevel::computeCenter()
{
	center.set(0.0f, 0.0f, 0.0f);
	auto objectCount = 0;
	for (auto levelEditorObject: objects) {
		if (levelEditorObject->getEntity()->getType() != LevelEditorEntity_EntityType::MODEL)
			continue;

		center.add(levelEditorObject->getTransformations()->getTranslation());
		objectCount++;
	}
	if (objectCount != 0)
		center.scale(1.0f / objectCount);
}

const Vector3& LevelEditorLevel::getCenter() {
	return center;
}

int32_t LevelEditorLevel::allocateObjectId()
{
	return objectIdx++;
}

int32_t LevelEditorLevel::getObjectIdx()
{
	return objectIdx;
}

void LevelEditorLevel::setObjectIdx(int32_t entityIdx)
{
	this->objectIdx = entityIdx;
}

void LevelEditorLevel::clearObjects()
{
	objectsById.clear();
	objects.clear();
	objectIdx = 0;
}

void LevelEditorLevel::removeObjectsByEntityId(int32_t entityId)
{
	vector<wstring> objectsToRemove;
	for (auto object: objects) {
		if (object->getEntity()->getId() == entityId) {
			objectsToRemove.push_back(object->getId());
		}
	}
	for (auto objectId: objectsToRemove) {
		removeObject(objectId);
	}
}

void LevelEditorLevel::replaceEntity(int32_t searchEntityId, int32_t replaceEntityId)
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

void LevelEditorLevel::updatePivot(int32_t modelId, const Vector3& pivot)
{
	for (auto object: objects) {
		if (object->getEntity()->getId() == modelId) {
			object->getTransformations()->getPivot().set(pivot);
			object->getTransformations()->update();
		}
	}
}

void LevelEditorLevel::addObject(LevelEditorObject* object)
{
	auto _entity = getObjectById(object->getId());
	if (_entity != nullptr) {
		removeObject(object->getId());
		Console::println(
			L"LevelEditorLevel::addObject():: object with id '" +
			object->getId() +
			L"' already exists. Removing it!"
		);
	}
	objectsById[object->getId()] = object;
	objects.push_back(object);
}

void LevelEditorLevel::removeObject(const wstring& id)
{
	auto objectByIdIt = objectsById.find(id);
	if (objectByIdIt != objectsById.end()) {
		objectsById.erase(objectByIdIt);
		objects.erase(remove(objects.begin(), objects.end(), objectByIdIt->second), objects.end());
	}
}

LevelEditorObject* LevelEditorLevel::getObjectById(const wstring& id)
{
	auto objectByIdIt = objectsById.find(id);
	if (objectByIdIt != objectsById.end()) {
		return objectByIdIt->second;
	}
	return nullptr;
}

int32_t LevelEditorLevel::getObjectCount()
{
	return objects.size();
}

LevelEditorObject* LevelEditorLevel::getObjectAt(int32_t idx)
{
	return objects.at(idx);
}

void LevelEditorLevel::update() {
	computeBoundingBox();
	computeCenter();
}
