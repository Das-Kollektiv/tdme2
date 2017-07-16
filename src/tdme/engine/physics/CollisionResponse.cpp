// Generated from /tdme/src/tdme/engine/physics/CollisionResponse.java
#include <tdme/engine/physics/CollisionResponse.h>

#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/physics/CollisionResponse_Entity.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using tdme::engine::physics::CollisionResponse;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::physics::CollisionResponse_Entity;
using tdme::math::MathTools;
using tdme::math::Vector3;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

CollisionResponse::CollisionResponse(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

CollisionResponse::CollisionResponse() 
	: CollisionResponse(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void CollisionResponse::init()
{
	selectedEntity = nullptr;
}

constexpr int32_t CollisionResponse::ENTITY_COUNT;

constexpr int32_t CollisionResponse::HITPOINT_COUNT;

void CollisionResponse::ctor()
{
	super::ctor();
	init();
	selectedEntity = nullptr;
	entityCount = 0;
	for (auto i = 0; i < ENTITY_COUNT; i++) {
		auto entity = new CollisionResponse_Entity();
		entity->distance = 0.0f;
		entity->normal = new Vector3();
		entity->hitPointsCount = 0;
		for (auto j = 0; j < HITPOINT_COUNT; j++) {
			entity->hitPoints.push_back(new Vector3());
		}
		entities.push_back(entity);
	}
}

void CollisionResponse::reset()
{
	for (auto i = 0; i < entityCount; i++) {
		auto entity = entities.at(i);
		entity->getNormal()->set(0.0f, 0.0f, 0.0f);
		entity->setDistance(0.0f);
		for (auto j = 0; j < entity->hitPointsCount; j++) {
			entity->hitPoints.at(j)->set(0.0f, 0.0f, 0.0f);
		}
		entity->hitPointsCount = 0;
	}
	entityCount = 0;
	selectedEntity = nullptr;
}

CollisionResponse_Entity* CollisionResponse::addResponse(float distance)
{
	if (entityCount == ENTITY_COUNT) {
		_Console::println(static_cast< Object* >(u"CollisionResponse::too many entities"_j));
		return nullptr;
	}
	auto entity = entities.at(entityCount);
	entity->distance = distance;
	if (selectedEntity == nullptr || distance > selectedEntity->distance) {
		selectedEntity = entity;
	}
	entityCount++;
	return entity;
}

int32_t CollisionResponse::getEntityCount()
{
	return entityCount;
}

CollisionResponse_Entity* CollisionResponse::getSelectedEntity()
{
	return selectedEntity;
}

CollisionResponse_Entity* CollisionResponse::getEntityAt(int32_t idx)
{
	if (idx < 0 || idx >= entityCount)
		return nullptr;

	return entities.at(idx);
}

CollisionResponse* CollisionResponse::selectEntityAt(int32_t idx)
{
	if (idx < 0 || idx >= entityCount)
		return this;

	selectedEntity = entities.at(idx);
	return this;
}

CollisionResponse* CollisionResponse::selectEntityExcludeAxis(Vector3* axis, bool respectDirection)
{
	selectedEntity = nullptr;
	for (auto i = 0; i < entityCount; i++) {
		auto entity = entities.at(i);
		auto distanceOnAxis = Vector3::computeDotProduct(entity->normal, axis);
		if (respectDirection == false)
			distanceOnAxis = Math::abs(distanceOnAxis);

		if (distanceOnAxis > MathTools::EPSILON)
			continue;

		if (selectedEntity == nullptr || entity->distance > selectedEntity->distance) {
			selectedEntity = entity;
		}
	}
	return this;
}

CollisionResponse* CollisionResponse::selectEntityOnAxis(Vector3* axis, bool respectDirection)
{
	selectedEntity = nullptr;
	auto selectedEntityDistanceOnAxis = 0.0f;
	for (auto i = 0; i < entityCount; i++) {
		auto entity = entities.at(i);
		auto distanceOnAxis = Vector3::computeDotProduct(entity->normal, axis);
		if (respectDirection == false)
			distanceOnAxis = Math::abs(distanceOnAxis);

		if (distanceOnAxis < MathTools::EPSILON)
			continue;

		distanceOnAxis *= entity->distance;
		if (selectedEntity == nullptr || distanceOnAxis > selectedEntityDistanceOnAxis) {
			selectedEntity = entity;
			selectedEntityDistanceOnAxis = distanceOnAxis;
		}
	}
	return this;
}

bool CollisionResponse::hasEntitySelected()
{
	return selectedEntity != nullptr;
}

float CollisionResponse::getDistance()
{
	if (selectedEntity == nullptr)
		return 0.0f;

	return selectedEntity->distance;
}

bool CollisionResponse::hasPenetration()
{
	if (selectedEntity == nullptr)
		return false;

	return selectedEntity->distance < -MathTools::EPSILON;
}

float CollisionResponse::getPenetration()
{
	if (selectedEntity == nullptr)
		return 0.0f;

	return -selectedEntity->distance;
}

Vector3* CollisionResponse::getNormal()
{
	if (selectedEntity == nullptr)
		return nullptr;

	return selectedEntity->normal;
}

int32_t CollisionResponse::getHitPointsCount()
{
	if (selectedEntity == nullptr)
		return 0;

	return selectedEntity->hitPointsCount;
}

Vector3* CollisionResponse::getHitPointAt(int32_t i)
{
	if (selectedEntity == nullptr)
		return nullptr;

	return selectedEntity->hitPoints.at(i);
}

void CollisionResponse::invertNormals()
{
	for (auto i = 0; i < entityCount; i++) {
		entities.at(i)->getNormal()->scale(-1.0f);
	}
}

CollisionResponse* CollisionResponse::fromResponse(CollisionResponse* response)
{
	reset();
	entityCount = response->entityCount;
	for (auto i = 0; i < response->entityCount; i++) {
		auto srcEntity = response->entities.at(i);
		auto dstEntity = entities.at(i);
		if (srcEntity == response->selectedEntity) {
			selectedEntity = dstEntity;
		}
		dstEntity->distance = srcEntity->distance;
		dstEntity->normal->set(srcEntity->normal);
		dstEntity->hitPointsCount = srcEntity->hitPointsCount;
		for (auto j = 0; j < srcEntity->hitPointsCount; j++) {
			dstEntity->hitPoints.at(j)->set(srcEntity->hitPoints.at(j));
		}
	}
	return this;
}

CollisionResponse* CollisionResponse::mergeResponse(CollisionResponse* response)
{
	for (auto i = 0; i < response->entityCount; i++) {
		auto srcEntity = response->entities.at(i);
		CollisionResponse_Entity* dstEntity = nullptr;
		if (entityCount > 0)
			dstEntity = entities.at(0);

		if (dstEntity == nullptr || srcEntity->distance > dstEntity->distance) {
			if (dstEntity == nullptr)
				dstEntity = entities.at(entityCount++);

			dstEntity->distance = srcEntity->distance;
			dstEntity->normal->set(srcEntity->normal);
		}
		selectedEntity = entities.at(0);
		for (auto j = 0; j < srcEntity->hitPointsCount; j++) {
			dstEntity->addHitPoint(srcEntity->hitPoints.at(j));
		}
	}
	return this;
}

String* CollisionResponse::toString()
{
	auto tmp = new String();
	for (auto i = 0; i < entityCount; i++) {
		if (tmp->length() > 0)
			tmp = ::java::lang::StringBuilder(tmp).append(u","_j)->toString();

		tmp = ::java::lang::StringBuilder(tmp).append(entities.at(i)->toString())->toString();
	}
	tmp = ::java::lang::StringBuilder(tmp).append(u"]"_j)->toString();
	return ::java::lang::StringBuilder().append(u"CollisionResponseMultiple [selected="_j)->append(selectedEntity)
		->append(u", entities="_j)
		->append(tmp)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* CollisionResponse::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.CollisionResponse", 37);
    return c;
}

java::lang::Class* CollisionResponse::getClass0()
{
	return class_();
}

