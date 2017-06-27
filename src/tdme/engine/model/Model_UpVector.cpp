// Generated from /tdme/src/tdme/engine/model/Model.java
#include <tdme/engine/model/Model_UpVector.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/IllegalArgumentException.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::model::Model_UpVector;
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
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Model_UpVector, ::java::lang::EnumArray > Model_UpVectorArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

Model_UpVector::Model_UpVector(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Model_UpVector::Model_UpVector(::java::lang::String* name, int ordinal)
	: Model_UpVector(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

Model_UpVector* tdme::engine::model::Model_UpVector::Y_UP = new Model_UpVector(u"Y_UP"_j, 0);
Model_UpVector* tdme::engine::model::Model_UpVector::Z_UP = new Model_UpVector(u"Z_UP"_j, 1);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Model_UpVector::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Model.UpVector", 32);
    return c;
}

Model_UpVector* Model_UpVector::valueOf(String* a0)
{
	if (Y_UP->toString()->equals(a0))
		return Y_UP;
	if (Z_UP->toString()->equals(a0))
		return Z_UP;
	throw new IllegalArgumentException(a0);
}

Model_UpVectorArray* Model_UpVector::values()
{
	return new Model_UpVectorArray({
		Y_UP,
		Z_UP,
	});
}

java::lang::Class* Model_UpVector::getClass0()
{
	return class_();
}

