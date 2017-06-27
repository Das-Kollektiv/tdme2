// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderPoint.java
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::object::TransparentRenderPoint;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

TransparentRenderPoint::TransparentRenderPoint(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TransparentRenderPoint::TransparentRenderPoint()
	: TransparentRenderPoint(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

int32_t TransparentRenderPoint::compareTo(TransparentRenderPoint* point2)
{
	if (acquired == false && point2->acquired == false)
		return 0;
	else if (acquired == false)
		return +1;
	else if (point2->acquired == false)
		return -1;
	else if (distanceFromCamera > point2->distanceFromCamera)
		return -1;
	else if (distanceFromCamera < point2->distanceFromCamera)
		return +1;
	else
		return 0;
}

int32_t TransparentRenderPoint::compareTo(Object* arg0)
{ 
	return compareTo(dynamic_cast< TransparentRenderPoint* >(arg0));
}

String* TransparentRenderPoint::toString()
{
	return ::java::lang::StringBuilder().append(u"TransparentPoint [acquired="_j)->append(acquired)
		->append(u", point="_j)
		->append(static_cast< Object* >(point))
		->append(u", color="_j)
		->append(static_cast< Object* >(color))
		->append(u", distanceFromCamera="_j)
		->append(distanceFromCamera)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TransparentRenderPoint::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.TransparentRenderPoint", 52);
    return c;
}

java::lang::Class* TransparentRenderPoint::getClass0()
{
	return class_();
}

