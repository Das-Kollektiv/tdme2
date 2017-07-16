// Generated from /tdme/src/tdme/engine/physics/CollisionResponse.java
#include <tdme/engine/physics/CollisionResponse_Entity.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using tdme::engine::physics::CollisionResponse_Entity;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

CollisionResponse_Entity::CollisionResponse_Entity(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

CollisionResponse_Entity::CollisionResponse_Entity()
	: CollisionResponse_Entity(*static_cast< ::default_init_tag* >(0))
{
	ctor();
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
	return normal;
}

void CollisionResponse_Entity::addHitPoint(Vector3* hitPoint)
{
	for (auto i = 0; i < hitPointsCount; i++) {
		if (hitPoints.at(i)->equals(hitPoint, 0.1f))
			return;

	}
	if (hitPointsCount == CollisionResponse::HITPOINT_COUNT) {
		_Console::println(static_cast< Object* >(u"CollisionResponse::Entity::too many hit points"_j));
		return;
	}
	hitPoints.at(hitPointsCount++)->set(hitPoint);
}

int32_t CollisionResponse_Entity::getHitPointsCount()
{
	return hitPointsCount;
}

Vector3* CollisionResponse_Entity::getHitPointAt(int32_t i)
{
	return hitPoints.at(i);
}

String* CollisionResponse_Entity::toString()
{
	auto tmp = new String();
	for (auto i = 0; i < hitPointsCount; i++) {
		if (tmp->length() > 0)
			tmp = ::java::lang::StringBuilder(tmp).append(u","_j)->toString();

		tmp = ::java::lang::StringBuilder(tmp).append(hitPoints.at(i)->toString())->toString();
	}
	tmp = ::java::lang::StringBuilder(tmp).append(u"]"_j)->toString();
	return ::java::lang::StringBuilder().append(u"Entity [distance="_j)->append(distance)
		->append(u", normal="_j)
		->append(static_cast< Object* >(normal))
		->append(u", hasPenetration() = "_j)
		->append((distance < 0.0f))
		->append(u", hit points="_j)
		->append(tmp)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* CollisionResponse_Entity::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.CollisionResponse.Entity", 44);
    return c;
}

java::lang::Class* CollisionResponse_Entity::getClass0()
{
	return class_();
}

