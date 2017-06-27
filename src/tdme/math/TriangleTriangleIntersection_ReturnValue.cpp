// Generated from /tdme/src/tdme/math/TriangleTriangleIntersection.java
#include <tdme/math/TriangleTriangleIntersection_ReturnValue.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/IllegalArgumentException.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::math::TriangleTriangleIntersection_ReturnValue;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::Comparable;
using java::lang::Enum;
using java::lang::IllegalArgumentException;
using java::lang::String;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::TriangleTriangleIntersection_ReturnValue, ::java::lang::EnumArray > TriangleTriangleIntersection_ReturnValueArray;
}  // namespace math
}  // namespace tdme

TriangleTriangleIntersection_ReturnValue::TriangleTriangleIntersection_ReturnValue(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TriangleTriangleIntersection_ReturnValue::TriangleTriangleIntersection_ReturnValue(::java::lang::String* name, int ordinal)
	: TriangleTriangleIntersection_ReturnValue(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

TriangleTriangleIntersection_ReturnValue* tdme::math::TriangleTriangleIntersection_ReturnValue::NOINTERSECTION = new TriangleTriangleIntersection_ReturnValue(u"NOINTERSECTION"_j, 0);
TriangleTriangleIntersection_ReturnValue* tdme::math::TriangleTriangleIntersection_ReturnValue::COPLANAR_INTERSECTION = new TriangleTriangleIntersection_ReturnValue(u"COPLANAR_INTERSECTION"_j, 1);
TriangleTriangleIntersection_ReturnValue* tdme::math::TriangleTriangleIntersection_ReturnValue::INTERSECTION = new TriangleTriangleIntersection_ReturnValue(u"INTERSECTION"_j, 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TriangleTriangleIntersection_ReturnValue::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.math.TriangleTriangleIntersection.ReturnValue", 50);
    return c;
}

TriangleTriangleIntersection_ReturnValue* TriangleTriangleIntersection_ReturnValue::valueOf(String* a0)
{
	if (COPLANAR_INTERSECTION->toString()->equals(a0))
		return COPLANAR_INTERSECTION;
	if (INTERSECTION->toString()->equals(a0))
		return INTERSECTION;
	if (NOINTERSECTION->toString()->equals(a0))
		return NOINTERSECTION;
	throw new IllegalArgumentException(a0);
}

TriangleTriangleIntersection_ReturnValueArray* TriangleTriangleIntersection_ReturnValue::values()
{
	return new TriangleTriangleIntersection_ReturnValueArray({
		COPLANAR_INTERSECTION,
		INTERSECTION,
		NOINTERSECTION,
	});
}

java::lang::Class* TriangleTriangleIntersection_ReturnValue::getClass0()
{
	return class_();
}

