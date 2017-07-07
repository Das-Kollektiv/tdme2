// Generated from /tdme/src/tdme/engine/physics/CollisionDetection.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Cloneable;
using tdme::engine::physics::CollisionResponse_Entity;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::LineSegment;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::SeparatingAxisTheorem;
using tdme::math::TriangleTriangleIntersection;
using tdme::math::Vector3;
using tdme::utils::_ArrayList;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::BoundingVolume, ::java::lang::ObjectArray > BoundingVolumeArray;
typedef ::SubArray< ::tdme::engine::primitives::Triangle, ::java::lang::ObjectArray, BoundingVolumeArray > TriangleArray;
}  // namespace primitives
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math

namespace engine {
namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::TriangleArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > TriangleArrayArray;
}  // namespace primitives
}  // namespace engine
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::CloneableArray;
using java::lang::ObjectArray;
using tdme::engine::primitives::BoundingVolumeArray;
using tdme::engine::primitives::TriangleArray;
using tdme::engine::primitives::TriangleArrayArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * Collision detection
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::CollisionDetection final
	: public Object
{

public:
	typedef Object super;

private:
	static constexpr bool VERBOSE { false };
	static constexpr int32_t SAT_AXES_TEST_MAX { 20 };
	static constexpr int32_t TRIANGLES_TEST_MAX { 10000 };
	static CollisionDetection* instance;
	static Object* synchronizeObject;
	static Vector3* zeroVector;
	static int32_tArray* lineSegmentsTriangleIndices;
	LineSegment* lineSegment {  };
	Vector3* closestPointOnCapsule1 {  };
	Vector3* closestPointOnCapsule2 {  };
	Vector3* closestPoint {  };
	Vector3* axis {  };
	OrientedBoundingBox* obbExtended {  };
	Vector3* contactMin {  };
	Vector3* contactMax {  };
	Vector3* contactAvg {  };
	Vector3* contactAvgCollisionNormal {  };
	Vector3* contactAvgSubContactMin {  };
	Vector3* contactOptimal {  };
	Sphere* sphere1 {  };
	Sphere* sphere2 {  };
	OrientedBoundingBox* obbConverted1 {  };
	OrientedBoundingBox* obbConverted2 {  };
	Vector3* pointOnFaceNearest {  };
	Vector3* pointOnFaceOpposite {  };
	Vector3* triangle1Edge1 {  };
	Vector3* triangle1Edge2 {  };
	Vector3* triangle1Edge3 {  };
	Vector3* triangle1Normal {  };
	Vector3* triangle2Edge1 {  };
	Vector3* triangle2Edge2 {  };
	Vector3* triangle2Edge3 {  };
	Vector3* triangle2Normal {  };
	Vector3Array* closestPointsOnCapsuleSegment {  };
	Vector3Array* closestPointsOnTriangleSegments {  };
	int32_t testTriangleCount {  };
	TriangleArrayArray* testTriangles {  };
	Vector3* satAxis {  };
	int32_t satAxesCount {  };
	floatArray* satPenetrations {  };
	Vector3Array* satAxes {  };
	bool haveSatAxisBestFit {  };
	Vector3* satAxisBestFit {  };
	float satAxisBestFitPenetration {  };
	SeparatingAxisTheorem* separatingAxisTheorem {  };
	Vector3* hitPoint {  };
	TriangleTriangleIntersection* triangleTriangleIntersection {  };
	Triangle* triangle1 {  };
	Triangle* triangle2 {  };
	Vector3* hitPointTriangle1 {  };
	Vector3* hitPointTriangle2 {  };
	CollisionResponse* collision1 {  };
	static constexpr bool CHECK_COLLISIONRESPONSE { false };

public:

	/** 
	 * Singleton method
	 * @return collision detection for current thread
	 */
	static CollisionDetection* getInstance();

protected:

	/** 
	 * Constructor
	 */
	void ctor();

private:

	/** 
	 * Reset SAT axes
	 */
	void resetSATAxes();

	/** 
	 * Add axis to SAT test
	 * @param axis
	 */
	void addSATAxis(Vector3* axis);

	/** 
	 * Determine sat axis best fit
	 */
	void determineSatAxisBestFit();

	/** 
	 * Reset triangles to test
	 */
	void resetTriangles();

public:

	/** 
	 * Returns if axis aligned bounding boxes do collide
	 * Will not provide hit points
	 * @param axis aligned bounding box 1
	 * @param axis aligned bounding box 2
	 * @param movement
	 * @param collision response
	 * @return collision 
	 */
	static bool doCollideAABBvsAABBFast(BoundingBox* b1, BoundingBox* b2);

	/** 
	 * Returns if axis aligned bounding boxes do collide
	 * @param axis aligned bounding box 1
	 * @param axis aligned bounding box 2
	 * @param movement
	 * @param collision response
	 * @return collision 
	 */
	bool doCollide(BoundingBox* b1, BoundingBox* b2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if axis aligned bounding box collides with sphere
	 * @param axis aligned bounding box
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(BoundingBox* aabb, Sphere* sphere, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if sphere is colliding with axis aligned bounding box
	 * @param axis aligned bounding box
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Sphere* sphere, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if axis aligned bounding box collides with capsule
	 * @param bounding box
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(BoundingBox* aabb, Capsule* capsule, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if capsule collides with axis aligned bounding box
	 * @param axis aligned bounding box
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Capsule* capsule, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if 2 spheres are colliding 
	 * @param sphere 1
	 * @param sphere 2
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Sphere* s1, Sphere* s2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if 2 capsules do collide
	 * @param capsule 1
	 * @param capsule 2
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Capsule* c1, Capsule* c2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if capsule is colliding with sphere
	 * @param capsule
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Capsule* c, Sphere* s, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if sphere is colliding with capsule
	 * @param sphere
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Sphere* s, Capsule* c, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if oriented bounding box 1 collides with oriented bounding box 2
	 * ported from "game physics - a practical introduction/ben kenwright"
	 * @param oriented bounding box 1
	 * @param oriented bounding box 2
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(OrientedBoundingBox* obb1, OrientedBoundingBox* obb2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if oriented bounding box collides with axis aligned bounding box
	 * @param oriented bounding box
	 * @param axis aligned bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(OrientedBoundingBox* obb, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if axis aligned bounding box collides with oriented bounding box
	 * @param axis aligned bounding box
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(BoundingBox* aabb, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if oriented bounding box collides with sphere
	 * @param oriented bounding box
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(OrientedBoundingBox* obb, Sphere* sphere, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if sphere collides with oriented bounding box
	 * @param sphere
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Sphere* sphere, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if oriented bounding box collides with capsule
	 * @param oriented bounding box
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(OrientedBoundingBox* obb, Capsule* capsule, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if capsule collides with oriented bounding box
	 * @param capsule
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision 
	 */
	bool doCollide(Capsule* capsule, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if triangle collides with sphere
	 * @param triangle
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Triangle* triangle, Sphere* sphere, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if sphere collides with triangle
	 * @param sphere
	 * @param triangle
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Sphere* sphere, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if sphere collides with mesh 
	 * @param sphere
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(Sphere* sphere, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if sphere collides with mesh 
	 * @param convex mesh
	 * @param sphere
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(ConvexMesh* mesh, Sphere* sphere, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with bounding box
	 * @param triangle
	 * @param bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Triangle* triangle, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if bounding box collides with triangle
	 * @param bounding box
	 * @param triangle
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(BoundingBox* aabb, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with oriented bounding box
	 * @param triangle
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Triangle* triangle, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if oriented bounding collides with triangle box
	 * @param triangle
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(OrientedBoundingBox* obb, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with axis aligned bounding box
	 * @param convex mesh
	 * @param axis aligned bounding box
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(ConvexMesh* mesh, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if axis aligned bounding box collides with mesh 
	 * @param axis aligned bounding box
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(BoundingBox* aabb, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with oriented bounding box
	 * @param convex mesh
	 * @param oriented bounding box
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(ConvexMesh* mesh, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if oriented bounding box collides with mesh 
	 * @param oriented bounding box
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(OrientedBoundingBox* obb, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with another triangle
	 * @param triangle 1
	 * @param triangle 2
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(Triangle* triangle1, Triangle* triangle2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with another mesh
	 * Will not yet provide hit points
	 * @param convex mesh 1
	 * @param convex mesh 2
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(ConvexMesh* mesh1, ConvexMesh* mesh2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with mesh
	 * @param triangle
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(Triangle* triangle, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with triangle
	 * @param convex mesh
	 * @param triangle
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(ConvexMesh* mesh, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with capsule
	 * @param triangle
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Triangle* triangle, Capsule* capsule, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if capsule collides with triangle
	 * @param capsule
	 * @param triangle
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doCollide(Capsule* capsule, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if capsule collides with mesh 
	 * @param capsule
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(Capsule* capsule, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with capsule 
	 * @param convex mesh
	 * @param capsule
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	bool doCollide(ConvexMesh* mesh, Capsule* capsule, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Compute hit points for intersecting obb1 with obb2
	 * @param obb1
	 * @param obb2
	 * @param collision entity
	 */
	void computeHitPoints(OrientedBoundingBox* obb1, OrientedBoundingBox* obb2, CollisionResponse_Entity* collisionEntity);

	/** 
	 * Compute hit points for intersecting obb1 with obb2
	 * @param obb1
	 * @param obb2
	 * @param collision entity
	 */
	void computeHitPoints(Triangle* triangle, OrientedBoundingBox* obb, CollisionResponse_Entity* collisionEntity);

	/** 
	 * Compute hit points for intersecting obb1 with obb2
	 * @param triangle 1
	 * @param triangle 2
	 * @param collision entity
	 */
	void computeHitPoints(Triangle* triangle1, Triangle* triangle2, CollisionResponse_Entity* collisionEntity);

private:

	/** 
	 * Compute coplanar triangles hit points
	 * @param triangle 1
	 * @param triangle 2
	 * @param collision entity
	 */
	void computeCoplanarTrianglesHitPoints(Triangle* triangle1, Triangle* triangle2, CollisionResponse_Entity* collisionEntity);

public:

	/** 
	 * Do broad test collision detection
	 * @param bounding volume 1
	 * @param bounding volume 2
	 * @return
	 */
	bool doBroadTest(BoundingVolume* bv1, BoundingVolume* bv2);

private:

	/** 
	 * Checks if movement candidate if valid otherwise take movement for collision response computation
	 * @param normal candidate
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool checkMovementFallback(Vector3* normalCandidate, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check collision validity
	 * @param collision
	 */
	static void checkCollision(CollisionResponse* collision);

	// Generated
	CollisionDetection();
protected:
	CollisionDetection(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
