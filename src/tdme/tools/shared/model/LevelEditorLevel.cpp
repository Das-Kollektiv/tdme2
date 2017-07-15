// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorLevel.java
#include <tdme/tools/shared/model/LevelEditorLevel.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <java/util/Set.h>
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
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap.h>

using tdme::tools::shared::model::LevelEditorLevel;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using java::util::Set;
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
using tdme::utils::_ArrayList;
using tdme::utils::_Console;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

LevelEditorLevel::LevelEditorLevel(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorLevel::LevelEditorLevel() 
	: LevelEditorLevel(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LevelEditorLevel::ctor()
{
	super::ctor();
	gameRoot = u""_j;
	pathName = u"."_j;
	fileName = u"untitled.tl"_j;
	rotationOrder = RotationOrder::XYZ;
	lights = new _ArrayList();
	lights->add(new LevelEditorLight(0));
	lights->add(new LevelEditorLight(1));
	lights->add(new LevelEditorLight(2));
	lights->add(new LevelEditorLight(3));
	auto light = java_cast< LevelEditorLight* >(lights->get(0));
	light->getAmbient()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light->getDiffuse()->set(0.5f, 0.5f, 0.5f, 1.0f);
	light->getSpecular()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light->getPosition()->set(0.0f, 20000.0f, 0.0f, 1.0f);
	light->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light->getPosition()->getArray()));
	light->getSpotTo()->set(light->getPosition()->getArray())->add(light->getSpotDirection());
	light->setConstantAttenuation(0.5f);
	light->setLinearAttenuation(0.0f);
	light->setQuadraticAttenuation(0.0f);
	light->setSpotExponent(0.0f);
	light->setSpotCutOff(180.0f);
	light->setEnabled(true);
	entityLibrary = new LevelEditorEntityLibrary(this);
	objectsById = new _HashMap();
	objects = new _ArrayList();
	objectIdx = 0;
	dimension = new Vector3();
	boundingBox = new BoundingBox();
}

String* LevelEditorLevel::getGameRoot()
{
	return gameRoot;
}

void LevelEditorLevel::setGameRoot(String* gameRoot)
{
	this->gameRoot = gameRoot;
}

String* LevelEditorLevel::getPathName()
{
	return pathName;
}

void LevelEditorLevel::setPathName(String* pathName)
{
	this->pathName = pathName;
}

String* LevelEditorLevel::getFileName()
{
	return fileName;
}

void LevelEditorLevel::setFileName(String* fileName)
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
	return lights->size();
}

LevelEditorLight* LevelEditorLevel::getLightAt(int32_t i)
{
	return java_cast< LevelEditorLight* >(lights->get(i));
}

_ArrayList* LevelEditorLevel::getLights()
{
	return lights;
}

LevelEditorEntityLibrary* LevelEditorLevel::getEntityLibrary()
{
	return entityLibrary;
}

Vector3* LevelEditorLevel::getDimension()
{
	return dimension;
}

void LevelEditorLevel::computeDimension()
{
	computeBoundingBox();
}

BoundingBox* LevelEditorLevel::getBoundingBox()
{
	return boundingBox;
}

void LevelEditorLevel::computeBoundingBox()
{
	auto haveDimension = false;
	auto left = 0.0f;
	auto right = 0.0f;
	auto near = 0.0f;
	auto far = 0.0f;
	auto top = 0.0f;
	auto bottom = 0.0f;
	auto bbDimension = new Vector3();
	auto bbMin = new Vector3();
	auto bbMax = new Vector3();
	for (auto _i = objects->iterator(); _i->hasNext(); ) {
		LevelEditorObject* levelEditorObject = java_cast< LevelEditorObject* >(_i->next());
		{
			if (levelEditorObject->getEntity()->getType() != LevelEditorEntity_EntityType::MODEL)
				continue;

			auto bv = levelEditorObject->getEntity()->getModel()->getBoundingBox();
			auto cbv = bv->clone();
			cbv->fromBoundingVolumeWithTransformations(bv, levelEditorObject->getTransformations());
			bbDimension->set(cbv->computeDimensionOnAxis(new Vector3(1.0f, 0.0f, 0.0f)), cbv->computeDimensionOnAxis(new Vector3(0.0f, 1.0f, 0.0f)), cbv->computeDimensionOnAxis(new Vector3(0.0f, 0.0f, 1.0f)));
			bbDimension->scale(0.5f);
			bbMin->set(cbv->getCenter());
			bbMin->sub(bbDimension);
			bbMax->set(cbv->getCenter());
			bbMax->add(bbDimension);
			auto objectLeft = bbMin->getX();
			auto objectRight = bbMax->getX();
			auto objectNear = bbMin->getZ();
			auto objectFar = bbMax->getZ();
			auto objectBottom = bbMin->getY();
			auto objectTop = bbMax->getY();
			if (haveDimension == false) {
				left = objectLeft;
				right = objectRight;
				near = objectNear;
				far = objectFar;
				top = objectTop;
				bottom = objectBottom;
				haveDimension = true;
			} else {
				if (objectLeft < left)
					left = objectLeft;

				if (objectRight > right)
					right = objectRight;

				if (objectNear < near)
					near = objectNear;

				if (objectFar > far)
					far = objectFar;

				if (objectTop > top)
					top = objectTop;

				if (objectBottom < bottom)
					bottom = objectBottom;

			}
		}
	}
	boundingBox->getMin()->set(left, bottom, near);
	boundingBox->getMax()->set(right, top, far);
	boundingBox->update();
	dimension->setX(right - left);
	dimension->setZ(far - near);
	dimension->setY(top - bottom);
}

Vector3* LevelEditorLevel::computeCenter()
{
	auto center = new Vector3();
	auto objectCount = 0;
	for (auto _i = objects->iterator(); _i->hasNext(); ) {
		LevelEditorObject* levelEditorObject = java_cast< LevelEditorObject* >(_i->next());
		{
			if (levelEditorObject->getEntity()->getType() != LevelEditorEntity_EntityType::MODEL)
				continue;

			center->add(levelEditorObject->getTransformations()->getTranslation());
			objectCount++;
		}
	}
	if (objectCount != 0)
		center->scale(1.0f / objectCount);

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
	objectsById->clear();
	objects->clear();
	objectIdx = 0;
}

void LevelEditorLevel::removeObjectsByEntityId(int32_t entityId)
{
	auto objectsToRemove = new _ArrayList();
	for (auto _i = objects->iterator(); _i->hasNext(); ) {
		LevelEditorObject* object = java_cast< LevelEditorObject* >(_i->next());
		{
			if (object->getEntity()->getId() == entityId) {
				objectsToRemove->add(object->getId());
			}
		}
	}
	for (auto _i = objectsToRemove->iterator(); _i->hasNext(); ) {
		String* objectId = java_cast< String* >(_i->next());
		{
			removeObject(objectId);
		}
	}
}

void LevelEditorLevel::replaceEntity(int32_t searchEntityId, int32_t replaceEntityId)
{
	auto replaceEntity = getEntityLibrary()->getEntity(replaceEntityId);
	if (replaceEntity == nullptr)
		return;

	for (auto _i = objects->iterator(); _i->hasNext(); ) {
		LevelEditorObject* object = java_cast< LevelEditorObject* >(_i->next());
		{
			if (object->getEntity()->getId() == searchEntityId) {
				object->setEntity(replaceEntity);
			}
		}
	}
}

void LevelEditorLevel::updatePivot(int32_t modelId, Vector3* pivot)
{
	for (auto _i = objects->iterator(); _i->hasNext(); ) {
		LevelEditorObject* object = java_cast< LevelEditorObject* >(_i->next());
		{
			if (object->getEntity()->getId() == modelId) {
				object->getTransformations()->getPivot()->set(pivot);
				object->getTransformations()->update();
			}
		}
	}
}

void LevelEditorLevel::addObject(LevelEditorObject* object)
{
	auto _entity = java_cast< LevelEditorObject* >(objectsById->put(object->getId(), object));
	if (_entity != nullptr) {
		objects->remove(static_cast< Object* >(_entity));
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"LevelEditorLevel::addObject():: object with id '"_j)->append(object->getId())
			->append(u"' already exists"_j)->toString()));
	}
	objects->add(object);
}

void LevelEditorLevel::removeObject(String* id)
{
	auto _entity = java_cast< LevelEditorObject* >(objectsById->remove(id));
	objects->remove(static_cast< Object* >(_entity));
}

LevelEditorObject* LevelEditorLevel::getObjectById(String* id)
{
	return java_cast< LevelEditorObject* >(objectsById->get(id));
}

int32_t LevelEditorLevel::getObjectCount()
{
	return objects->size();
}

LevelEditorObject* LevelEditorLevel::getObjectAt(int32_t idx)
{
	return java_cast< LevelEditorObject* >(objects->get(idx));
}

_HashMap* LevelEditorLevel::getObjectsByIds()
{
	return objectsById;
}

LevelEditorLevel* LevelEditorLevel::clone(String* objectIdPrefix)
{
	auto level = new LevelEditorLevel();
	level->propertiesByName = propertiesByName;
	level->properties = properties;
	level->gameRoot = gameRoot;
	level->pathName = pathName;
	level->fileName = fileName;
	level->rotationOrder = rotationOrder;
	level->lights = lights;
	level->entityLibrary = entityLibrary;
	level->objectsById = new _HashMap();
	level->objects = new _ArrayList();
	for (auto i = 0; i < getObjectCount(); i++) {
		auto object = getObjectAt(i)->clone();
		object->setId(objectIdPrefix != nullptr ? ::java::lang::StringBuilder().append(objectIdPrefix)->append(object->getId())->toString() : object->getId());
		level->objectsById->put(object->getId(), object);
		level->objects->add(object);
	}
	level->objectIdx = objectIdx;
	level->boundingBox = boundingBox;
	level->dimension = dimension;
	return level;
}

String* LevelEditorLevel::toString()
{
	return ::java::lang::StringBuilder().append(u"LevelEditorLevel [gameRoot="_j)->append(gameRoot)
		->append(u", pathName="_j)
		->append(pathName)
		->append(u", fileName="_j)
		->append(fileName)
		->append(u", rotationOrder="_j)
		->append(static_cast< Object* >(rotationOrder))
		->append(u", lights="_j)
		->append(static_cast< Object* >(lights))
		->append(u", entityLibrary="_j)
		->append(static_cast< Object* >(entityLibrary))
		->append(u", objectsById="_j)
		->append(static_cast< Object* >(objectsById))
		->append(u", objects="_j)
		->append(static_cast< Object* >(objects))
		->append(u", objectIdx="_j)
		->append(objectIdx)
		->append(u", boundingBox="_j)
		->append(static_cast< Object* >(boundingBox))
		->append(u", dimension="_j)
		->append(static_cast< Object* >(dimension))
		->append(u", propertiesByName="_j)
		->append(static_cast< Object* >(propertiesByName))
		->append(u", properties="_j)
		->append(static_cast< Object* >(properties))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorLevel::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorLevel", 40);
    return c;
}

Object* LevelEditorLevel::clone()
{
	return super::clone();
}

java::lang::Class* LevelEditorLevel::getClass0()
{
	return class_();
}

