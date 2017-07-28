// Generated from /tdme/src/tdme/engine/primitives/Plane.java
#include <tdme/engine/primitives/Plane.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/math/Vector3.h>

using tdme::engine::primitives::Plane;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::math::Vector3;

Plane::Plane(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Plane::Plane() 
	: Plane(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Plane::Plane(Vector3* normal, float distance) 
	: Plane(*static_cast< ::default_init_tag* >(0))
{
	ctor(normal,distance);
}

void Plane::ctor()
{
	super::ctor();
	normal = new Vector3();
	distance = 0.0f;
}

void Plane::ctor(Vector3* normal, float distance)
{
	super::ctor();
	this->normal = normal;
	this->distance = distance;
}

float Plane::getDistance()
{
	return distance;
}

void Plane::setDistance(float distance)
{
	this->distance = distance;
}

Vector3* Plane::getNormal()
{
	return normal;
}

String* Plane::toString()
{
	return ::java::lang::StringBuilder().append(u"Plane [normal="_j)
		/*
		->append(static_cast< Object* >(normal))
		*/
		->append(u", distance="_j)
		->append(distance)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Plane::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.primitives.Plane", 28);
    return c;
}

java::lang::Class* Plane::getClass0()
{
	return class_();
}

