#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Console.h>

using std::vector;

using tdme::engine::Color4;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::math::Matrix4x4;
using tdme::utilities::Console;

/**
 * Render transparent render points pool
 * @author andreas.drewke
 */
class tdme::engine::subsystems::rendering::RenderTransparentRenderPointsPool final
{
private:
	vector<TransparentRenderPoint*> transparentRenderPoints;
	int32_t poolIdx;

public:
	// forbid class copy
	FORBID_CLASS_COPY(RenderTransparentRenderPointsPool)

	/**
	 * Public constructor
	 * @param pointsMax points max
	 */
	RenderTransparentRenderPointsPool(int32_t pointsMax);

	/**
	 * Destructor
	 */
	~RenderTransparentRenderPointsPool();

	/**
	 * Merge another pool into this pool
	 * @param pool2 pool
	 * @param cameraMatrix cameraMatrix
	 */
	void merge(TransparentRenderPointsPool* pool2, const Matrix4x4& cameraMatrix);

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

};
