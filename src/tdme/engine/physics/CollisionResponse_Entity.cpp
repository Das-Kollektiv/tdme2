#include <tdme/engine/physics/CollisionResponse_Entity.h>

#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using tdme::engine::physics::CollisionResponse_Entity;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;
using tdme::utils::_Console;

CollisionResponse_Entity::CollisionResponse_Entity()
{
}

float CollisionResponse_Entity::getDistance()
{
	return distance;
}

void CollisionResponse_Entity::setDistance(float distance)
{
	this->distance = distance;
}

float CollisionResponse_Entity::getPenetration()
{
	return -distance;
}

Vector3* CollisionResponse_Entity::getNormal()
{
	return &normal;
}

void CollisionResponse_Entity::addHitPoint(Vector3* hitPoint)
{
	for (auto i = 0; i < hitPoints.size(); i++) {
		if (hitPoints.at(i).equals(hitPoint, 0.1f))
			return;
	}
	hitPoints.push_back(*hitPoint);
}

int32_t CollisionResponse_Entity::getHitPointsCount()
{
	return hitPoints.size();
}

Vector3* CollisionResponse_Entity::getHitPointAt(int32_t i)
{
	return &hitPoints.at(i);
}
