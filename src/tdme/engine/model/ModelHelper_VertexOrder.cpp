#include <tdme/engine/model/ModelHelper_VertexOrder.h>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::model::ModelHelper_VertexOrder;
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
typedef ::SubArray< ::tdme::engine::model::ModelHelper_VertexOrder, ::java::lang::EnumArray > ModelHelper_VertexOrderArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

ModelHelper_VertexOrder::ModelHelper_VertexOrder(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelHelper_VertexOrder::ModelHelper_VertexOrder(const wstring& name, int ordinal)
	: ModelHelper_VertexOrder(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

ModelHelper_VertexOrder* tdme::engine::model::ModelHelper_VertexOrder::CLOCKWISE = new ModelHelper_VertexOrder(L"CLOCKWISE", 0);
ModelHelper_VertexOrder* tdme::engine::model::ModelHelper_VertexOrder::COUNTERCLOCKWISE = new ModelHelper_VertexOrder(L"COUNTERCLOCKWISE", 1);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelHelper_VertexOrder::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.ModelHelper.VertexOrder", 41);
    return c;
}

ModelHelper_VertexOrder* ModelHelper_VertexOrder::valueOf(const wstring& a0)
{
	if (CLOCKWISE->name() == a0) return CLOCKWISE;
	if (COUNTERCLOCKWISE->name() == a0) return COUNTERCLOCKWISE;
	// TODO: throw exception here maybe
	return nullptr;
}

ModelHelper_VertexOrderArray* ModelHelper_VertexOrder::values()
{
	return new ModelHelper_VertexOrderArray({
		CLOCKWISE,
		COUNTERCLOCKWISE,
	});
}

java::lang::Class* ModelHelper_VertexOrder::getClass0()
{
	return class_();
}

