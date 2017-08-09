// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderPoint.java
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

bool TransparentRenderPoint::compare(TransparentRenderPoint& point1, TransparentRenderPoint& point2)
{
	if (point1.acquired == false && point2.acquired == false) {
		return false;
	} else
	if (point1.acquired == false) {
		return false;
	} else
	if (point2.acquired == false) {
		return true;
	} else {
		return point1.distanceFromCamera > point2.distanceFromCamera;
	}
}
