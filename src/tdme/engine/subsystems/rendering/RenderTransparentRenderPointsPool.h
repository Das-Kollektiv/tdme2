#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Console.h>

using std::vector;

using tdme::engine::model::Color4;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::math::Vector3;
using tdme::utils::Console;

/** 
 * Render transparent render points pool
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::RenderTransparentRenderPointsPool final
{
private:
	vector<TransparentRenderPoint*> transparentRenderPoints;
	int32_t poolIdx;

public:
	/** 
	 * Merge another pool into this pool
	 * @param pool2 pool
	 */
	void merge(TransparentRenderPointsPool* pool2);

	/** 
	 * Reset
	 */
	void reset();

	/**
	 * @return transparent render points count
	 */
	inline const int32_t getTransparentRenderPointsCount() {
		return poolIdx;
	}

	/** 
	 * @return transparent render points vector
	 */
	inline const vector<TransparentRenderPoint*>& getTransparentRenderPoints() {
		return transparentRenderPoints;
	}

	/** 
	 * Sort transparent render points
	 */
	void sort();

	/**
	 * Public constructor
	 * @param pointsMax points max
	 */
	RenderTransparentRenderPointsPool(int32_t pointsMax);

	/**
	 * Destructor
	 */
	~RenderTransparentRenderPointsPool();
};
