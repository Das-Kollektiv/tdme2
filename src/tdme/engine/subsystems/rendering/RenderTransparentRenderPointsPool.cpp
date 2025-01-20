#include <tdme/engine/subsystems/rendering/RenderTransparentRenderPointsPool.h>

#include <algorithm>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>
#include <tdme/engine/Color4.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::vector;

using tdme::engine::subsystems::rendering::RenderTransparentRenderPointsPool;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::Color4;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

RenderTransparentRenderPointsPool::RenderTransparentRenderPointsPool(int32_t pointsMax)
{
	transparentRenderPoints.resize(pointsMax);
	reset();
}

RenderTransparentRenderPointsPool::~RenderTransparentRenderPointsPool() {
}

void RenderTransparentRenderPointsPool::merge(TransparentRenderPointsPool* pool2, const Matrix4x4& cameraMatrix)
{
	auto pool2Points = pool2->getTransparentRenderPoints();
	for (auto i = 0; i < pool2->getTransparentRenderPointsCount(); i++) {
		auto point = pool2Points[i];
		// check for pool overflow
		if (poolIdx >= transparentRenderPoints.size()) {
			Console::printLine(string("RenderTransparentRenderPointsPool::merge(): Too many transparent render points"));
			return;
		}
		//
		point->point = cameraMatrix.multiply(point->point);
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
	std::sort(
		transparentRenderPoints.begin(),
		transparentRenderPoints.begin() + poolIdx,
		[](const TransparentRenderPoint* point1, const TransparentRenderPoint* point2) {
			return -point1->point.getZ() > -point2->point.getZ();
		}
	);
}
