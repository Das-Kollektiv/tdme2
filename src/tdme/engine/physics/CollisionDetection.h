#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using tdme::engine::primitives::BoundingBox;

/** 
 * Collision detection
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::CollisionDetection final
{
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
		// see
		//	http://www.gamedev.net/topic/567310-platform-game-collision-detection/
		auto& b1MinXYZ = b1->getMin().getArray();
		auto& b1MaxXYZ = b1->getMax().getArray();
		auto& b2MinXYZ = b2->getMin().getArray();
		auto& b2MaxXYZ = b2->getMax().getArray();
		// face distances
		if (b2MaxXYZ[0] - b1MinXYZ[0] < 0.0f) return false; // b2 collides into b1 on x
		if (b1MaxXYZ[0] - b2MinXYZ[0] < 0.0f) return false; // b1 collides into b2 on x
		if (b2MaxXYZ[1] - b1MinXYZ[1] < 0.0f) return false; // b2 collides into b1 on y
		if (b1MaxXYZ[1] - b2MinXYZ[1] < 0.0f) return false; // b1 collides into b2 on y
		if (b2MaxXYZ[2] - b1MinXYZ[2] < 0.0f) return false; // b2 collides into b1 on z
		if (b1MaxXYZ[2] - b2MinXYZ[2] < 0.0f) return false; // b1 collides into b2 on z
		return true;
	}

};
