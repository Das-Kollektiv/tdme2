#include <tdme/engine/physics/CollisionResponse.h>

#include <java/lang/Math.h>
#include <tdme/engine/physics/CollisionResponse_Entity.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using tdme::engine::physics::CollisionResponse;
using java::lang::Math;
using tdme::engine::physics::CollisionResponse_Entity;
using tdme::math::MathTools;
using tdme::math::Vector3;
using tdme::utils::_Console;

CollisionResponse::CollisionResponse() 
{
}

void CollisionResponse::reset()
{
	entities.clear();
	selectedEntity = nullptr;
}

CollisionResponse_Entity* CollisionResponse::addResponse(float distance)
{
	entities.push_back(CollisionResponse_Entity());
	auto& entity = entities.at(entities.size() - 1);
	entity.distance = distance;
	if (selectedEntity == nullptr || distance > selectedEntity->distance) {
		selectedEntity = &entity;
	}
	return &entity;
}

int32_t CollisionResponse::getEntityCount()
{
	return entities.size();
}

CollisionResponse_Entity* CollisionResponse::getSelectedEntity()
{
	return selectedEntity;
}

CollisionResponse_Entity* CollisionResponse::getEntityAt(int32_t idx)
{
	if (idx < 0 || idx >= entities.size()) return nullptr;
	return &entities.at(idx);
}

CollisionResponse* CollisionResponse::selectEntityAt(int32_t idx)
{
	if (idx < 0 || idx >= entities.size()) return this;
	selectedEntity = &entities.at(idx);
	return this;
}

CollisionResponse* CollisionResponse::selectEntityExcludeAxis(Vector3* axis, bool respectDirection)
{
	selectedEntity = nullptr;
	for (auto i = 0; i < entities.size(); i++) {
		auto& entity = entities.at(i);
		auto distanceOnAxis = Vector3::computeDotProduct(&entity.normal, axis);
		if (respectDirection == false) distanceOnAxis = Math::abs(distanceOnAxis);
		if (distanceOnAxis > MathTools::EPSILON) continue;
		if (selectedEntity == nullptr || entity.distance > selectedEntity->distance) {
			selectedEntity = &entity;
		}
	}
	return this;
}

CollisionResponse* CollisionResponse::selectEntityOnAxis(Vector3* axis, bool respectDirection)
{
	selectedEntity = nullptr;
	auto selectedEntityDistanceOnAxis = 0.0f;
	for (auto i = 0; i < entities.size(); i++) {
		auto& entity = entities.at(i);
		auto distanceOnAxis = Vector3::computeDotProduct(&entity.normal, axis);
		if (respectDirection == false) distanceOnAxis = Math::abs(distanceOnAxis);
		if (distanceOnAxis < MathTools::EPSILON) continue;
		distanceOnAxis *= entity.distance;
		if (selectedEntity == nullptr || distanceOnAxis > selectedEntityDistanceOnAxis) {
			selectedEntity = &entity;
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
	if (selectedEntity == nullptr) return 0.0f;
	return selectedEntity->distance;
}

bool CollisionResponse::hasPenetration()
{
	if (selectedEntity == nullptr) return false;
	return selectedEntity->distance < -MathTools::EPSILON;
}

float CollisionResponse::getPenetration()
{
	if (selectedEntity == nullptr) return 0.0f;
	return -selectedEntity->distance;
}

Vector3* CollisionResponse::getNormal()
{
	if (selectedEntity == nullptr) return nullptr;
	return &selectedEntity->normal;
}

vector<Vector3>* CollisionResponse::getHitPoints() {
	if (selectedEntity == nullptr) return nullptr;
	return &selectedEntity->hitPoints;
}

int32_t CollisionResponse::getHitPointsCount()
{
	if (selectedEntity == nullptr) return 0;
	return selectedEntity->hitPoints.size();
}

Vector3* CollisionResponse::getHitPointAt(int32_t i)
{
	if (selectedEntity == nullptr) return nullptr;
	return &selectedEntity->hitPoints.at(i);
}

void CollisionResponse::invertNormals()
{
	for (auto i = 0; i < entities.size(); i++) {
		entities.at(i).getNormal()->scale(-1.0f);
	}
}

CollisionResponse* CollisionResponse::fromResponse(CollisionResponse* response)
{
	selectedEntity = nullptr;
	entities = response->entities;
	if (response->selectedEntity != nullptr)
	for (auto i = 0; i < response->entities.size(); i++) {
		if (&response->entities.at(i) == response->selectedEntity) {
			selectedEntity = &entities.at(i);
			return this;
		}
	}
	return this;
}

CollisionResponse* CollisionResponse::mergeResponse(CollisionResponse* response)
{
	for (auto i = 0; i < response->entities.size(); i++) {
		auto& srcEntity = response->entities.at(i);
		CollisionResponse_Entity* dstEntity = nullptr;
		if (entities.size() > 0) dstEntity = &entities.at(0);
		if (dstEntity == nullptr || srcEntity.distance > dstEntity->distance) {
			if (dstEntity == nullptr) {
				entities.push_back(CollisionResponse_Entity());
				dstEntity = &entities.at(entities.size() - 1);
			}
			dstEntity->distance = srcEntity.distance;
			dstEntity->normal.set(&srcEntity.normal);
		}
		selectedEntity = &entities.at(0);
		for (auto j = 0; j < srcEntity.hitPoints.size(); j++) {
			dstEntity->addHitPoint(&srcEntity.hitPoints.at(j));
		}
	}
	return this;
}
