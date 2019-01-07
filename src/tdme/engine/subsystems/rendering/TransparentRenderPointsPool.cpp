#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>

#include <algorithm>
#include <vector>
#include <string>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::vector;
using std::string;

using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::math::Vector3;
using tdme::utils::Console;

TransparentRenderPointsPool::TransparentRenderPointsPool(int32_t pointsMax) 
{
	poolIdx = 0;
	transparentRenderPoints.resize(pointsMax);
	for (auto i = 0; i < transparentRenderPoints.size(); i++) {
		auto& point = transparentRenderPoints[i];
		point.acquired = false;
	}
}

void TransparentRenderPointsPool::merge(TransparentRenderPointsPool* pool2)
{
	for (auto point: pool2->transparentRenderPoints) {
		// skip if point is not in use
		if (point.acquired == false)
			break;
		// check for pool overflow
		if (poolIdx >= transparentRenderPoints.size()) {
			Console::println(string("TransparentRenderPointsPool::merge(): Too many transparent render points"));
			break;
		}
		// create point in pool
		auto& transparentRenderPoint = transparentRenderPoints[poolIdx++];
		transparentRenderPoint.acquired = true;
		transparentRenderPoint.point.set(point.point);
		transparentRenderPoint.color.set(point.color);
		transparentRenderPoint.distanceFromCamera = point.distanceFromCamera;
		transparentRenderPoint.cookie = point.cookie;
	}
}

void TransparentRenderPointsPool::reset()
{
	poolIdx = 0;
	for (auto& point: transparentRenderPoints) {
		point.acquired = false;
	}
}

void TransparentRenderPointsPool::sort()
{
	std::sort(transparentRenderPoints.begin(), transparentRenderPoints.end(), TransparentRenderPoint::compare);
}
