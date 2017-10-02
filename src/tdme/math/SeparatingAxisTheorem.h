// Generated from /tdme/src/tdme/math/SeparatingAxisTheorem.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Float.h>

using std::vector;

using tdme::math::SeparatingAxisTheorem;

using tdme::math::Vector3;
using tdme::math::Math;
using tdme::math::MathTools;
using tdme::math::Vector3;
using tdme::utils::Float;

/** 
 * Separated axis test
 * ported from "game physics - a practical introduction/ben kenwright"
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::SeparatingAxisTheorem final
{
public:
	/**
	 * Check axix
	 * @param axis
	 * @return valididy
	 */
	inline static bool checkAxis(const Vector3& axis) {
		auto& axisXYZ = axis.getArray();
		if (Float::isNaN(axisXYZ[0]) || Float::isNaN(axisXYZ[1]) || Float::isNaN(axisXYZ[2])) {
			return false;
		}
		if (Math::abs(axisXYZ[0]) < MathTools::EPSILON && Math::abs(axisXYZ[1]) < MathTools::EPSILON && Math::abs(axisXYZ[2]) < MathTools::EPSILON) {
			return false;
		}
		return true;
	}

private:

	/** 
	 * Projects the point on given axis and returns its value
	 * @param point
	 * @param axis
	 * @return
	 */
	inline static float doCalculatePoint(const Vector3& point, const Vector3& axis) {
		auto distance = Vector3::computeDotProduct(point, axis);
		return distance;
	}

	/** 
	 * Projects the vertices onto the plane and returns the minimum and maximum values
	 * ported from "game physics - a practical introduction/ben kenwright"
	 * @param obb
	 * @param axis
	 * @return float[] containing min and max
	 */
	inline static void doCalculateInterval(const vector<Vector3>* vertices, const Vector3& axis, float& min, float& max) {
		auto distance = Vector3::computeDotProduct((*vertices)[0], axis);
		min = distance;
		max = distance;
		for (auto i = 1; i < vertices->size(); i++) {
			distance = Vector3::computeDotProduct((*vertices)[i], axis);
			if (distance < min) min = distance;
			if (distance > max) max = distance;
		}
	}

public:

	/** 
	 * Check if point is in vertices on given axis
	 * @param vertices
	 * @param point
	 * @param axis
	 * @return point in vertices
	 */
	inline static bool checkPointInVerticesOnAxis(const vector<Vector3>* vertices, const Vector3& point, const Vector3& axis) {
		if (checkAxis(axis) == false) return true;
		float min;
		float max;
		doCalculateInterval(vertices, axis, min, max);
		auto pOnAxis = doCalculatePoint(point, axis);
		return pOnAxis >= min && pOnAxis <= max;
	}

	/** 
	 * Determines penetration of given vertices for both objects on a given axis
	 * based on an algorithm from "game physics - a practical introduction/ben kenwright"
	 * @param vertices 1
	 * @param vertices 2
	 * @param axis test
	 * @param axis penetration
	 * @return penetration or negative / -1 if none
	 */
	inline static bool doSpanIntersect(const vector<Vector3>* vertices1, const vector<Vector3>* vertices2, Vector3& axisTest, float& satPenetration) {
		Vector3 axis;
		axis.set(axisTest).normalize();
		float min1;
		float max1;
		float min2;
		float max2;
		doCalculateInterval(vertices1, axis, min1, max1);
		doCalculateInterval(vertices2, axis, min2, max2);
		auto len1 = max1 - min1;
		auto len2 = max2 - min2;
		auto min = Math::min(min1, min2);
		auto max = Math::max(max1, max2);
		auto len = max - min;
		if (len > len1 + len2) {
			return false;
		}
		if (min2 < min1) {
			axisTest.scale(-1.0f);
		}
		satPenetration = len1 + len2 - len;
		return true;
	}

};
