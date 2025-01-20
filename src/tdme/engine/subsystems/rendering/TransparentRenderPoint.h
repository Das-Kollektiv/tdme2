#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Color4;
using tdme::math::Vector3;

/**
 * Transparent point to be rendered
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::rendering::TransparentRenderPoint final
{
	uint16_t spriteIndex;
	Vector3 point;
	Color4 color;
	int particleSystemType;
	void* particleSystem;
};
