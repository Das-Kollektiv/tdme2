#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Console.h>

using std::vector;

using tdme::engine::Color4;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::math::Vector3;
using tdme::utilities::Console;

/**
 * Transparent render points pool
 * @author andreas.drewke
 */
class tdme::engine::subsystems::rendering::TransparentRenderPointsPool final
{
	friend class RenderTransparentRenderPointsPool;

private:
	vector<TransparentRenderPoint*> transparentRenderPoints;
	int32_t poolIdx;

public:
	// forbid class copy
	FORBID_CLASS_COPY(TransparentRenderPointsPool)

	/**
	 * Public constructor
	 * @param pointsMax points max
	 */
	TransparentRenderPointsPool(int32_t pointsMax);

	/**
	 * Destructor
	 */
	~TransparentRenderPointsPool();

	/**
	 * Creates an transparent render point entity in pool
	 * @param point point
	 * @param spriteIndex sprite index
	 * @param color color
	 * @param particleSystemType particle system type
	 * @param particleSystem particle system
	 */
	inline void addPoint(const Vector3& point, uint16_t spriteIndex, const Color4& color, int particleSystemType, void* particleSystem) {
		// check for pool overflow
		if (poolIdx >= transparentRenderPoints.size()) {
			Console::println(string("TransparentRenderPointsPool::createTransparentRenderPoint(): Too many transparent render points"));
			return;
		}
		// create point in pool
		auto transparentRenderPoint = transparentRenderPoints[poolIdx++];
		transparentRenderPoint->point = point;
		transparentRenderPoint->spriteIndex = spriteIndex;
		transparentRenderPoint->color = color;
		transparentRenderPoint->particleSystemType = particleSystemType;
		transparentRenderPoint->particleSystem = particleSystem;
	}

	/**
	 * Reset
	 */
	inline void reset() {
		poolIdx = 0;
	}

	/**
	 * @return transparent render points count
	 */
	inline int getTransparentRenderPointsCount() {
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
