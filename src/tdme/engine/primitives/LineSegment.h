// Generated from /tdme/src/tdme/engine/primitives/LineSegment.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Line segment
 * This class should be used on a per thread basis
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::LineSegment final
	: public Object
{

public:
	typedef Object super;

private:
	Vector3* d {  };
	Vector3* d1 {  };
	Vector3* d2 {  };
	Vector3* r {  };
	Vector3* c1 {  };
	Vector3* c2 {  };
	Vector3* n {  };
	Vector3* t {  };

public:

	/** 
	 * Does line segments collide
	 * @param p1 line 1 point 1
	 * @param q1 line 1 point 2
	 * @param p2 line 2 point 1
	 * @param q2 line 2 point 2
	 * @param p intersection point
	 * @return if collides or not
	 */
	bool doesLineSegmentsCollide(Vector3* p1, Vector3* q1, Vector3* p2, Vector3* q2, Vector3* p);

	/** 
	 * Computes closest points c1, c2 on line segment p1->q1, p2->q2
	 * based on an algorithm from "Real-Time Collision Detection" / Ericson"
	 * Credit:
	 * "From Real-Time Collision Detection by Christer Ericson
	 * published by Morgan Kaufman Publishers, (c) 2005 Elsevier Inc"
	 * @param point p1 on line segment 1
	 * @param point q1 on line segment 1
	 * @param point p2 on line segment 2
	 * @param point q2 on line segment 2
	 * @param closest point on line segment 1 c1
	 * @param closest point on line segment 2 c2
	 */
	void computeClosestPointsOnLineSegments(Vector3* p1, Vector3* q1, Vector3* p2, Vector3* q2, Vector3* c1, Vector3* c2);

	/** 
	 * Check if segment collides with bounding box
	 * based on an algorithm from "Real-Time Collision Detection" / Ericson
	 * Credit:
	 * "From Real-Time Collision Detection by Christer Ericson
	 * published by Morgan Kaufman Publishers, (c) 2005 Elsevier Inc"
	 * @param bounding box
	 * @param point p on line segment
	 * @param point q on line segment
	 * @param contact point min
	 * @param contact point max
	 * @return true if collides or false if not
	 */
	bool doesBoundingBoxCollideWithLineSegment(BoundingBox* boundingBox, Vector3* p, Vector3* q, Vector3* contactMin, Vector3* contactMax);

	/** 
	 * Check if segment collides with oriented bounding box
	 * based on an algorithm from "Real-Time Collision Detection" / Ericson
	 * Credit:
	 * "From Real-Time Collision Detection by Christer Ericson
	 * published by Morgan Kaufman Publishers, (c) 2005 Elsevier Inc"
	 * @param oriented bounding box
	 * @param point p on line segment
	 * @param point q on line segment
	 * @param contact point min
	 * @param contact point max
	 * @return true if collides or false if not
	 */
	bool doesOrientedBoundingBoxCollideWithLineSegment(OrientedBoundingBox* orientedBoundingBox, Vector3* p, Vector3* q, Vector3* contactMin, Vector3* contactMax);

	/** 
	 * Does line segment collides with triangle
	 * @param p1 triangle point 1
	 * @param p2 triangle point 2
	 * @param p3 triangle point 3
	 * @param r1 line segment point 1
	 * @param r2 line segment point 2
	 * @param point of intersection
	 * @return line segment collides with triangle
	 * @see https://gamedev.stackexchange.com/questions/5585/line-triangle-intersection-last-bits
	 */
	bool doesLineSegmentCollideWithTriangle(Vector3* p1, Vector3* p2, Vector3* p3, Vector3* r1, Vector3* r2, Vector3* contact);

	// Generated
	LineSegment();
protected:
	void ctor();
	LineSegment(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
