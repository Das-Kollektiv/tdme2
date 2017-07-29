// Generated from /tdme/src/tdme/math/SeparatingAxisTheorem.java

#pragma once

#include <vector>

#include <Array.h>
#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using std::vector;

using tdme::math::Vector3;

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
	bool checkAxis(Vector3* axis);

private:

	/** 
	 * Projects the point on given axis and returns its value
	 * @param point
	 * @param axis
	 * @return
	 */
	float doCalculatePoint(Vector3* point, Vector3* axis);

	/** 
	 * Projects the vertices onto the plane and returns the minimum and maximum values
	 * ported from "game physics - a practical introduction/ben kenwright"
	 * @param obb
	 * @param axis
	 * @return float[] containing min and max
	 */
	void doCalculateInterval(vector<Vector3*>* vertices, Vector3* axis, float& min, float& max);

public:

	/** 
	 * Check if point is in vertices on given axis
	 * @param vertices
	 * @param point
	 * @param axis
	 * @return point in vertices
	 */
	bool checkPointInVerticesOnAxis(vector<Vector3*>* vertices, Vector3* point, Vector3* axis);

	/** 
	 * Determines penetration of given vertices for both objects on a given axis
	 * based on an algorithm from "game physics - a practical introduction/ben kenwright"
	 * @param vertices 1
	 * @param vertices 2
	 * @param axis test
	 * @param axis penetration
	 * @return penetration or negative / -1 if none
	 */
	bool doSpanIntersect(vector<Vector3*>* vertices1, vector<Vector3*>* vertices2, Vector3* axisTest, floatArray* resultArray, int32_t resultOffset);

	/**
	 * Public constructor
	 */
	SeparatingAxisTheorem();
};
