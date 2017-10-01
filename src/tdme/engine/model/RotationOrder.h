// Generated from /tdme/src/tdme/engine/model/RotationOrder.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <java/lang/Enum.h>

using std::wstring;

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using tdme::math::Vector3;
using java::lang::Object;
using tdme::engine::model::RotationOrder;

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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::engine::model::RotationOrderArray;

struct default_init_tag;
class tdme::engine::model::RotationOrder final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static RotationOrder *XYZ;
	static RotationOrder *YZX;
	static RotationOrder *ZYX;

private:
	Vector3 axis0 {  };
	Vector3 axis1 {  };
	Vector3 axis2 {  };
	int32_t axis0VectorIndex {  };
	int32_t axis1VectorIndex {  };
	int32_t axis2VectorIndex {  };
	int32_t axisXIndex {  };
	int32_t axisYIndex {  };
	int32_t axisZIndex {  };
protected:

	/** 
	 * Constructor
	 * @param axis 0
	 * @param axis 1
	 * @param axis 2
	 * @param axis 0 vector (data) index
	 * @param axis 1 vector (data) index
	 * @param axis 2 vector (data) index
	 * @param axis X index
	 * @param axis Y index
	 * @param axis Z index
	 */
	void ctor(const wstring& name, int ordinal, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, int32_t axis0VectorIndex, int32_t axis1VectorIndex, int32_t axis2VectorIndex, int32_t axisXIndex, int32_t axisYIndex, int32_t axisZIndex);

public:

	/** 
	 * @return axis 0
	 */
	const Vector3& getAxis0() const;

	/** 
	 * @return axis 1
	 */
	const Vector3& getAxis1() const;

	/** 
	 * @return axis 2
	 */
	const Vector3& getAxis2() const;

	/** 
	 * @return axis 0 vector index
	 */
	int32_t getAxis0VectorIndex() const;

	/** 
	 * @return axis 1 vector index
	 */
	int32_t getAxis1VectorIndex() const;

	/** 
	 * @return axis 2 vector index
	 */
	int32_t getAxis2VectorIndex() const;

	/** 
	 * @return axis x index
	 */
	int32_t getAxisXIndex() const;

	/** 
	 * @return axis y index
	 */
	int32_t getAxisYIndex() const;

	/** 
	 * @return axis z index
	 */
	int32_t getAxisZIndex() const;

	// Generated

private:
	RotationOrder(const wstring& name, int ordinal, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, int32_t axis0VectorIndex, int32_t axis1VectorIndex, int32_t axis2VectorIndex, int32_t axisXIndex, int32_t axisYIndex, int32_t axisZIndex);
protected:
	RotationOrder(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static RotationOrder* valueOf(const wstring& a0);
	static RotationOrderArray* values();

private:
	virtual ::java::lang::Class* getClass0();
};
