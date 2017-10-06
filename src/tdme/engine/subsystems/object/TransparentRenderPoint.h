
#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using tdme::engine::model::Color4;
using tdme::math::Vector3;

/** 
 * Transparent point to be rendered
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::object::TransparentRenderPoint final
{
	bool acquired {  };
	Vector3 point {  };
	Color4 color {  };
	float distanceFromCamera {  };

	/**
	 * Compare
	 * @param point 1
	 * @param point 2
	 */
	static bool compare(TransparentRenderPoint& point1, TransparentRenderPoint& point2);
};
