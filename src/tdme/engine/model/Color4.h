
#pragma once

#include <array>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4Base.h>

using std::array;

using tdme::engine::model::Color4Base;

/** 
 * Color 4 definition
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::model::Color4 final
	: public Color4Base
{
public:
	Color4();
	Color4(const Color4& color);
	Color4(float r, float g, float b, float a);
	Color4(const array<float, 4>& color);
};
