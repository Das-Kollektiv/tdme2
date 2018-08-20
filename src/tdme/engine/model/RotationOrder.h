
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::utils::Enum;
using tdme::math::Vector3;
using tdme::engine::model::RotationOrder;

class tdme::engine::model::RotationOrder final
	: public Enum
{
public:
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

	/**
	 * @return rotation order by string
	 */
	static RotationOrder* valueOf(const string& a0);

	/**
	 * Constructor
	 * @param name name
	 * @param ordinal ordinal
	 * @param axis0 axis 0
	 * @param axis1 axis 1
	 * @param axis2 axis 2
	 * @param axis0VectorIndex axis 0 vector (data) index
	 * @param axis1VectorIndex axis 1 vector (data) index
	 * @param axis2VectorIndex axis 2 vector (data) index
	 * @param axisXIndex axis X index
	 * @param axisYIndex axis Y index
	 * @param axisZIndex axis Z index
	 */
	RotationOrder(const string& name, int ordinal, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, int32_t axis0VectorIndex, int32_t axis1VectorIndex, int32_t axis2VectorIndex, int32_t axisXIndex, int32_t axisYIndex, int32_t axisZIndex);
};
