// Generated from /tdme/src/tdme/math/SeparatingAxisTheorem.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * Separated axis test
 * ported from "game physics - a practical introduction/ben kenwright"
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::SeparatingAxisTheorem final
	: public Object
{

public:
	typedef Object super;

private:
	floatArray* minMax1 {  };
	floatArray* minMax2 {  };
	Vector3* axis {  };

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
	void doCalculateInterval(Vector3Array* vertices, Vector3* axis, floatArray* result);

public:

	/** 
	 * Check if point is in vertices on given axis
	 * @param vertices
	 * @param point
	 * @param axis
	 * @return point in vertices
	 */
	bool checkPointInVerticesOnAxis(Vector3Array* vertices, Vector3* point, Vector3* axis);

	/** 
	 * Determines penetration of given vertices for both objects on a given axis
	 * based on an algorithm from "game physics - a practical introduction/ben kenwright"
	 * @param vertices 1
	 * @param vertices 2
	 * @param axis test
	 * @param axis penetration
	 * @return penetration or negative / -1 if none
	 */
	bool doSpanIntersect(Vector3Array* vertices1, Vector3Array* vertices2, Vector3* axisTest, floatArray* resultArray, int32_t resultOffset);

	// Generated
	SeparatingAxisTheorem();
protected:
	void ctor();
	SeparatingAxisTheorem(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
