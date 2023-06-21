
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::engine::model::RotationOrder;
using tdme::math::Vector3;
using tdme::utilities::Enum;

/**
 * Represents rotation orders of a model
 */
class tdme::engine::model::RotationOrder final
	: public Enum
{
public:
	STATIC_DLL_IMPEXT static RotationOrder *XYZ;
	STATIC_DLL_IMPEXT static RotationOrder *YZX;
	STATIC_DLL_IMPEXT static RotationOrder *ZYX;

private:
	Vector3 axis0;
	Vector3 axis1;
	Vector3 axis2;
	int axis0VectorIndex;
	int axis1VectorIndex;
	int axis2VectorIndex;
	int axisXIndex;
	int axisYIndex;
	int axisZIndex;

public:
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
	RotationOrder(const string& name, int ordinal, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, int axis0VectorIndex, int axis1VectorIndex, int axis2VectorIndex, int axisXIndex, int axisYIndex, int axisZIndex);

	/**
	 * @return axis 0
	 */
	inline const Vector3& getAxis0() const {
		return axis0;
	}

	/**
	 * @return axis 1
	 */
	inline const Vector3& getAxis1() const {
		return axis1;
	}

	/**
	 * @return axis 2
	 */
	inline const Vector3& getAxis2() const {
		return axis2;
	}

	/**
	 * @return axis 0 vector index
	 */
	inline int getAxis0VectorIndex() const {
		return axis0VectorIndex;
	}

	/**
	 * @return axis 1 vector index
	 */
	inline int getAxis1VectorIndex() const {
		return axis1VectorIndex;
	}

	/**
	 * @return axis 2 vector index
	 */
	inline int getAxis2VectorIndex() const {
		return axis2VectorIndex;
	}

	/**
	 * @return axis x index
	 */
	inline int getAxisXIndex() const {
		return axisXIndex;
	}

	/**
	 * @return axis y index
	 */
	inline int getAxisYIndex() const {
		return axisYIndex;
	}

	/**
	 * @return axis z index
	 */
	inline int getAxisZIndex() const {
		return axisZIndex;
	}

	/**
	 * @return rotation order by string
	 */
	static RotationOrder* valueOf(const string& a0);

};
