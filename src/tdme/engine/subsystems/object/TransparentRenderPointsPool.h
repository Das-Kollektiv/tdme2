
#pragma once

#include <vector>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Console.h>

using std::vector;

using tdme::engine::model::Color4;
using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::math::Vector3;
using tdme::utils::Console;

/** 
 * Transparent render points pool
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::TransparentRenderPointsPool final
{
private:
	vector<TransparentRenderPoint> transparentRenderPoints {  };
	int32_t poolIdx {  };

public:

	/** 
	 * Creates an transparent render point entity in pool
	 * @param point
	 * @param color
	 */
	inline void addPoint(const Vector3& point, const Color4& color, float distanceFromCamera) {
		if (poolIdx >= transparentRenderPoints.size()) {
			Console::println(string("TransparentRenderPointsPool::createTransparentRenderPoint(): Too many transparent render points"));
			return;
		}
		auto& transparentRenderPoint = transparentRenderPoints.at(poolIdx++);
		transparentRenderPoint.acquired = true;
		transparentRenderPoint.point.set(point);
		transparentRenderPoint.color.set(color);
		transparentRenderPoint.distanceFromCamera = distanceFromCamera;
	}

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
	vector<TransparentRenderPoint>* getTransparentRenderPoints();

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
