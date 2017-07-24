// Generated from /tdme/src/tdme/engine/model/Model.java
#include <tdme/engine/model/Model_UpVector.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::engine::model::Model_UpVector;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::Enum;

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

Model_UpVector::Model_UpVector(const wstring& name, int ordinal)
	: Model_UpVector(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

Model_UpVector* tdme::engine::model::Model_UpVector::Y_UP = new Model_UpVector(L"Y_UP", 0);
Model_UpVector* tdme::engine::model::Model_UpVector::Z_UP = new Model_UpVector(L"Z_UP", 1);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Model_UpVector::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Model.UpVector", 32);
    return c;
}

Model_UpVector* Model_UpVector::valueOf(const wstring& a0)
{
	if (Y_UP->name() == a0) return Y_UP;
	if (Z_UP->name() == a0) return Z_UP;
	// TODO: throw exception here maybe
	return nullptr;
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

