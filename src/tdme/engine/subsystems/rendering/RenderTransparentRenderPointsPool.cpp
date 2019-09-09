#include <tdme/engine/subsystems/rendering/RenderTransparentRenderPointsPool.h>

#include <algorithm>
#include <vector>
#include <string>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::vector;
using std::string;

using tdme::engine::subsystems::rendering::RenderTransparentRenderPointsPool;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::math::Vector3;
using tdme::utils::Console;

RenderTransparentRenderPointsPool::RenderTransparentRenderPointsPool(int32_t pointsMax)
{
	transparentRenderPoints.resize(pointsMax);
	reset();
}

RenderTransparentRenderPointsPool::~RenderTransparentRenderPointsPool() {
}

void RenderTransparentRenderPointsPool::merge(TransparentRenderPointsPool* pool2)
{
	for (auto point: pool2->transparentRenderPoints) {
		// skip if point is not in use
		if (point->acquired == false) break;
		// check for pool overflow
		if (poolIdx >= transparentRenderPoints.size()) {
			Console::println(string("RenderTransparentRenderPointsPool::merge(): Too many transparent render points"));
			break;
		}
		// create point in pool
		transparentRenderPoints[poolIdx++] = point;
	}
}

void RenderTransparentRenderPointsPool::reset()
{
	poolIdx = 0;
	for (auto i = 0; i < transparentRenderPoints.size(); i++) transparentRenderPoints[i] = nullptr;
}

void RenderTransparentRenderPointsPool::sort()
{
	std::sort(transparentRenderPoints.begin(), transparentRenderPoints.begin() + poolIdx, TransparentRenderPoint::compare);
}
