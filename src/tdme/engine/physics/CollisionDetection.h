// Generated from /tdme/src/tdme/engine/physics/CollisionDetection.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;

using tdme::engine::physics::CollisionResponse_Entity;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::SeparatingAxisTheorem;
using tdme::math::TriangleTriangleIntersection;
using tdme::math::Vector3;

/** 
 * Collision detection
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::CollisionDetection final
{
private:
	static constexpr bool VERBOSE { false };
	static constexpr bool CHECK_COLLISIONRESPONSE { false };
	static constexpr array<int32_t,6> LINESEGMENTSTRIANGLEINDICES {{ 0, 1, 1, 2, 2, 0 }};

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
	inline static bool doCollideAABBvsAABBFast(BoundingBox* b1, BoundingBox* b2) {
		auto b1MinXYZ = b1->getMin()->getArray();
		auto b1MaxXYZ = b1->getMax()->getArray();
		auto b2MinXYZ = b2->getMin()->getArray();
		auto b2MaxXYZ = b2->getMax()->getArray();
		if ((*b2MaxXYZ)[0] - (*b1MinXYZ)[0] < 0.0f) return false;
		if ((*b1MaxXYZ)[0] - (*b2MinXYZ)[0] < 0.0f) return false;
		if ((*b2MaxXYZ)[1] - (*b1MinXYZ)[1] < 0.0f) return false;
		if ((*b1MaxXYZ)[1] - (*b2MinXYZ)[1] < 0.0f) return false;
		if ((*b2MaxXYZ)[2] - (*b1MinXYZ)[2] < 0.0f) return false;
		if ((*b1MaxXYZ)[2] - (*b2MinXYZ)[2] < 0.0f) return false;
		return true;
	}

	/** 
	 * Returns if axis aligned bounding boxes do collide
	 * @param axis aligned bounding box 1
	 * @param axis aligned bounding box 2
	 * @param movement
	 * @param collision response
	 * @return collision 
	 */
	static bool doCollide(BoundingBox* b1, BoundingBox* b2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if axis aligned bounding box collides with sphere
	 * @param axis aligned bounding box
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(BoundingBox* aabb, Sphere* sphere, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if sphere is colliding with axis aligned bounding box
	 * @param axis aligned bounding box
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Sphere* sphere, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if axis aligned bounding box collides with capsule
	 * @param bounding box
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(BoundingBox* aabb, Capsule* capsule, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if capsule collides with axis aligned bounding box
	 * @param axis aligned bounding box
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Capsule* capsule, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if 2 spheres are colliding 
	 * @param sphere 1
	 * @param sphere 2
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Sphere* s1, Sphere* s2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if 2 capsules do collide
	 * @param capsule 1
	 * @param capsule 2
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Capsule* c1, Capsule* c2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if capsule is colliding with sphere
	 * @param capsule
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Capsule* c, Sphere* s, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if sphere is colliding with capsule
	 * @param sphere
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Sphere* s, Capsule* c, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if oriented bounding box 1 collides with oriented bounding box 2
	 * ported from "game physics - a practical introduction/ben kenwright"
	 * @param oriented bounding box 1
	 * @param oriented bounding box 2
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(OrientedBoundingBox* obb1, OrientedBoundingBox* obb2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if oriented bounding box collides with axis aligned bounding box
	 * @param oriented bounding box
	 * @param axis aligned bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(OrientedBoundingBox* obb, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if axis aligned bounding box collides with oriented bounding box
	 * @param axis aligned bounding box
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(BoundingBox* aabb, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if oriented bounding box collides with sphere
	 * @param oriented bounding box
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(OrientedBoundingBox* obb, Sphere* sphere, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if sphere collides with oriented bounding box
	 * @param sphere
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Sphere* sphere, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if oriented bounding box collides with capsule
	 * @param oriented bounding box
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(OrientedBoundingBox* obb, Capsule* capsule, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if capsule collides with oriented bounding box
	 * @param capsule
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision 
	 */
	static bool doCollide(Capsule* capsule, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if triangle collides with sphere
	 * @param triangle
	 * @param sphere
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Triangle* triangle, Sphere* sphere, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Checks if sphere collides with triangle
	 * @param sphere
	 * @param triangle
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Sphere* sphere, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if sphere collides with mesh 
	 * @param sphere
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(Sphere* sphere, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if sphere collides with mesh 
	 * @param convex mesh
	 * @param sphere
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(ConvexMesh* mesh, Sphere* sphere, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with bounding box
	 * @param triangle
	 * @param bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Triangle* triangle, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if bounding box collides with triangle
	 * @param bounding box
	 * @param triangle
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(BoundingBox* aabb, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with oriented bounding box
	 * @param triangle
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Triangle* triangle, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if oriented bounding collides with triangle box
	 * @param triangle
	 * @param oriented bounding box
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(OrientedBoundingBox* obb, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with axis aligned bounding box
	 * @param convex mesh
	 * @param axis aligned bounding box
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(ConvexMesh* mesh, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if axis aligned bounding box collides with mesh 
	 * @param axis aligned bounding box
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(BoundingBox* aabb, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with oriented bounding box
	 * @param convex mesh
	 * @param oriented bounding box
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(ConvexMesh* mesh, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if oriented bounding box collides with mesh 
	 * @param oriented bounding box
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(OrientedBoundingBox* obb, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with another triangle
	 * @param triangle 1
	 * @param triangle 2
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(Triangle* triangle1, Triangle* triangle2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with another mesh
	 * Will not yet provide hit points
	 * @param convex mesh 1
	 * @param convex mesh 2
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(ConvexMesh* mesh1, ConvexMesh* mesh2, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with mesh
	 * @param triangle
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(Triangle* triangle, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with triangle
	 * @param convex mesh
	 * @param triangle
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(ConvexMesh* mesh, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if triangle collides with capsule
	 * @param triangle
	 * @param capsule
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Triangle* triangle, Capsule* capsule, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if capsule collides with triangle
	 * @param capsule
	 * @param triangle
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	static bool doCollide(Capsule* capsule, Triangle* triangle, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if capsule collides with mesh 
	 * @param capsule
	 * @param convex mesh
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(Capsule* capsule, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Check if mesh collides with capsule 
	 * @param convex mesh
	 * @param capsule
	 * @param movement
	 * @param collision response
	 * @return if collided
	 */
	static bool doCollide(ConvexMesh* mesh, Capsule* capsule, Vector3* movement, CollisionResponse* collision);

	/** 
	 * Compute hit points for intersecting obb1 with obb2
	 * @param obb1
	 * @param obb2
	 * @param collision entity
	 */
	static void computeHitPoints(OrientedBoundingBox* obb1, OrientedBoundingBox* obb2, CollisionResponse_Entity* collisionEntity);

	/** 
	 * Compute hit points for intersecting obb1 with obb2
	 * @param obb1
	 * @param obb2
	 * @param collision entity
	 */
	static void computeHitPoints(Triangle* triangle, OrientedBoundingBox* obb, CollisionResponse_Entity* collisionEntity);

	/** 
	 * Compute hit points for intersecting obb1 with obb2
	 * @param triangle 1
	 * @param triangle 2
	 * @param collision entity
	 */
	static void computeHitPoints(Triangle* triangle1, Triangle* triangle2, CollisionResponse_Entity* collisionEntity);

private:

	/** 
	 * Compute coplanar triangles hit points
	 * @param triangle 1
	 * @param triangle 2
	 * @param collision entity
	 */
	static void computeCoplanarTrianglesHitPoints(Triangle* triangle1, Triangle* triangle2, CollisionResponse_Entity* collisionEntity);

public:

	/** 
	 * Do broad test collision detection
	 * @param bounding volume 1
	 * @param bounding volume 2
	 * @return
	 */
	static bool doBroadTest(BoundingVolume* bv1, BoundingVolume* bv2);

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
};
