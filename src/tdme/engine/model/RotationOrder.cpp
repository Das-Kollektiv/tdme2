// Generated from /tdme/src/tdme/engine/model/RotationOrder.java
#include <tdme/engine/model/RotationOrder.h>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <tdme/math/Vector3.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::model::RotationOrder;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::Enum;
using tdme::math::Vector3;

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
typedef ::SubArray< ::tdme::engine::model::RotationOrder, ::java::lang::EnumArray > RotationOrderArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

RotationOrder::RotationOrder(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

RotationOrder::RotationOrder(const wstring& name, int ordinal, Vector3* axis0, Vector3* axis1, Vector3* axis2, int32_t axis0VectorIndex, int32_t axis1VectorIndex, int32_t axis2VectorIndex, int32_t axisXIndex, int32_t axisYIndex, int32_t axisZIndex)
	: RotationOrder(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal, axis0,axis1,axis2,axis0VectorIndex,axis1VectorIndex,axis2VectorIndex,axisXIndex,axisYIndex,axisZIndex);
}

RotationOrder* tdme::engine::model::RotationOrder::XYZ = new RotationOrder(L"XYZ", 0, new Vector3(1.0f, 0.0f, 0.0f), new Vector3(0.0f, 1.0f, 0.0f), new Vector3(0.0f, 0.0f, 1.0f), 0, 1, 2, 0, 1, 2);
RotationOrder* tdme::engine::model::RotationOrder::YZX = new RotationOrder(L"YZX", 1, new Vector3(0.0f, 1.0f, 0.0f), new Vector3(0.0f, 0.0f, 1.0f), new Vector3(1.0f, 0.0f, 0.0f), 1, 2, 0, 2, 0, 1);
RotationOrder* tdme::engine::model::RotationOrder::ZYX = new RotationOrder(L"ZYX", 2, new Vector3(0.0f, 0.0f, 1.0f), new Vector3(0.0f, 1.0f, 0.0f), new Vector3(1.0f, 0.0f, 0.0f), 2, 1, 0, 2, 1, 0);
void RotationOrder::ctor(const wstring& name, int ordinal, Vector3* axis0, Vector3* axis1, Vector3* axis2, int32_t axis0VectorIndex, int32_t axis1VectorIndex, int32_t axis2VectorIndex, int32_t axisXIndex, int32_t axisYIndex, int32_t axisZIndex)
{
	super::ctor(name, ordinal);
	this->axis0 = axis0;
	this->axis1 = axis1;
	this->axis2 = axis2;
	this->axis0VectorIndex = axis0VectorIndex;
	this->axis1VectorIndex = axis1VectorIndex;
	this->axis2VectorIndex = axis2VectorIndex;
	this->axisXIndex = axisXIndex;
	this->axisYIndex = axisYIndex;
	this->axisZIndex = axisZIndex;
}

Vector3* RotationOrder::getAxis0()
{
	return axis0;
}

Vector3* RotationOrder::getAxis1()
{
	return axis1;
}

Vector3* RotationOrder::getAxis2()
{
	return axis2;
}

int32_t RotationOrder::getAxis0VectorIndex()
{
	return axis0VectorIndex;
}

int32_t RotationOrder::getAxis1VectorIndex()
{
	return axis1VectorIndex;
}

int32_t RotationOrder::getAxis2VectorIndex()
{
	return axis2VectorIndex;
}

int32_t RotationOrder::getAxisXIndex()
{
	return axisXIndex;
}

int32_t RotationOrder::getAxisYIndex()
{
	return axisYIndex;
}

int32_t RotationOrder::getAxisZIndex()
{
	return axisZIndex;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* RotationOrder::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.RotationOrder", 31);
    return c;
}

RotationOrder* RotationOrder::valueOf(const wstring& a0)
{
	if (XYZ->name() == a0) return XYZ;
	if (YZX->name() == a0) return YZX;
	if (ZYX->name() == a0) return ZYX;
	// TODO: throw exception here maybe
	return nullptr;
}

RotationOrderArray* RotationOrder::values()
{
	return new RotationOrderArray({
		XYZ,
		YZX,
		ZYX,
	});
}

java::lang::Class* RotationOrder::getClass0()
{
	return class_();
}

