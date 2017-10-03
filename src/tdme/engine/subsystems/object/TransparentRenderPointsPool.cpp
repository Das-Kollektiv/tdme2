#include <tdme/engine/subsystems/object/TransparentRenderPointsPool.h>

#include <algorithm>
#include <vector>
#include <string>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using std::vector;
using std::wstring;

using tdme::engine::subsystems::object::TransparentRenderPointsPool;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::math::Vector3;
using tdme::utils::_Console;

TransparentRenderPointsPool::TransparentRenderPointsPool(int32_t pointsMax) 
{
	poolIdx = 0;
	transparentRenderPoints.resize(pointsMax);
	for (auto i = 0; i < transparentRenderPoints.size(); i++) {
		auto& point = transparentRenderPoints[i];
		point.acquired = false;
	}
}

void TransparentRenderPointsPool::addPoint(const Vector3& point, Color4* color, float distanceFromCamera)
{
	if (poolIdx >= transparentRenderPoints.size()) {
		_Console::println(wstring(L"TransparentRenderPointsPool::createTransparentRenderPoint(): Too many transparent render points"));
		return;
	}
	auto& transparentRenderPoint = transparentRenderPoints.at(poolIdx++);
	transparentRenderPoint.acquired = true;
	transparentRenderPoint.point.set(point);
	transparentRenderPoint.color.set(*color);
	transparentRenderPoint.distanceFromCamera = distanceFromCamera;
}

void TransparentRenderPointsPool::merge(TransparentRenderPointsPool* pool2)
{
	for (auto point: pool2->transparentRenderPoints) {
		if (point.acquired == false)
			break;

		if (poolIdx >= transparentRenderPoints.size()) {
			_Console::println(wstring(L"TransparentRenderPointsPool::merge(): Too many transparent render points"));
			break;
		}
		auto& transparentRenderPoint = transparentRenderPoints.at(poolIdx++);
		transparentRenderPoint.acquired = true;
		transparentRenderPoint.point.set(point.point);
		transparentRenderPoint.color.set(point.color);
		transparentRenderPoint.distanceFromCamera = point.distanceFromCamera;
	}
}

void TransparentRenderPointsPool::reset()
{
	poolIdx = 0;
	for (auto& point: transparentRenderPoints) {
		point.acquired = false;
	}
}

vector<TransparentRenderPoint>* TransparentRenderPointsPool::getTransparentRenderPoints()
{
	return &transparentRenderPoints;
}

void TransparentRenderPointsPool::sort()
{
	std::sort(transparentRenderPoints.begin(), transparentRenderPoints.end(), TransparentRenderPoint::compare);
}
