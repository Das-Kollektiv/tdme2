// Generated from /tdme/src/tdme/math/TriangleTriangleIntersection.java

#pragma once

#include <string>

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Enum.h>

using std::wstring;

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::math::TriangleTriangleIntersection;
using java::lang::Object;
using tdme::math::TriangleTriangleIntersection_ReturnValue;

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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::math::TriangleTriangleIntersection_ReturnValueArray;

struct default_init_tag;
class tdme::math::TriangleTriangleIntersection_ReturnValue final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static TriangleTriangleIntersection_ReturnValue *NOINTERSECTION;
	static TriangleTriangleIntersection_ReturnValue *COPLANAR_INTERSECTION;
	static TriangleTriangleIntersection_ReturnValue *INTERSECTION;

	// Generated

public:
	TriangleTriangleIntersection_ReturnValue(const wstring& name, int ordinal);
protected:
	TriangleTriangleIntersection_ReturnValue(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static TriangleTriangleIntersection_ReturnValue* valueOf(const wstring& a0);
	static TriangleTriangleIntersection_ReturnValueArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class TriangleTriangleIntersection;
};
