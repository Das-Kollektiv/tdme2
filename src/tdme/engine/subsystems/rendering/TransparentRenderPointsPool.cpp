#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>

#include <algorithm>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/Color4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::vector;

using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::Color4;
using tdme::math::Vector3;
using tdme::utilities::Console;

TransparentRenderPointsPool::TransparentRenderPointsPool(int32_t pointsMax)
{
	poolIdx = 0;
	transparentRenderPoints.resize(pointsMax);
	for (auto i = 0; i < transparentRenderPoints.size(); i++) {
		transparentRenderPoints[i] = new TransparentRenderPoint();
	}
}

TransparentRenderPointsPool::~TransparentRenderPointsPool() {
	for (auto i = 0; i < transparentRenderPoints.size(); i++) delete transparentRenderPoints[i];
}

void TransparentRenderPointsPool::sort()
{
	std::sort(
		transparentRenderPoints.begin(),
		transparentRenderPoints.begin() + poolIdx,
		[](const TransparentRenderPoint* point1, const TransparentRenderPoint* point2) {
			return -point1->point.getZ() > -point2->point.getZ();
		}
	);
}
