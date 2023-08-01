#pragma once

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Simple class to determine if a transform is negative
 * @author Andreas Drewke
 */
class tdme::math::Matrix4x4Negative
{
private:
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;

public:
	/**
	 * Public constructor
	 */
	inline Matrix4x4Negative() {
	}

	/**
	 * Check if matrix is negative
	 * @param matrix matrix
	 * @return negative
	 */
	inline bool isNegative(Matrix4x4& matrix) {
		// check if negative scale and rotation
		const auto& transformMatrixData = matrix.getArray();
		// copy into x,y,z axes
		xAxis.set(transformMatrixData[0], transformMatrixData[1], transformMatrixData[2]);
		yAxis.set(transformMatrixData[4], transformMatrixData[5], transformMatrixData[6]);
		zAxis.set(transformMatrixData[8], transformMatrixData[9], transformMatrixData[10]);
		// check if inverted/negative transform
		return Vector3::computeDotProduct(Vector3::computeCrossProduct(xAxis, yAxis), zAxis) < 0.0f;
	}

};
