// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderPointsPool.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using tdme::engine::model::Color4;
using tdme::math::Vector3;

/** 
 * Transparent render points pool
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::TransparentRenderPointsPool final
{
private:
	vector<TransparentRenderPoint*> transparentRenderPoints {  };
	int32_t poolIdx {  };

public:

	/** 
	 * Creates an transparent render point entity in pool
	 * @param point
	 * @param color
	 */
	void addPoint(Vector3* point, Color4* color, float distanceFromCamera);

	/** 
	 * Merge another pool into this pool
	 * @param pool
	 */
	void merge(TransparentRenderPointsPool* pool2);

	/** 
	 * Reset
	 */
	void reset();

	/** 
	 * @return transparent render points vector
	 */
	const vector<TransparentRenderPoint*>* getTransparentRenderPoints();

	/** 
	 * Sort transparent render points
	 */
	void sort();

	/**
	 * Public constructor
	 * @param points max
	 */
	TransparentRenderPointsPool(int32_t pointsMax);
};
