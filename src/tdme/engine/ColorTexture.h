#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>

/**
 * Color texture interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::ColorTexture
{
	/**
	 * Destructor
	 */
	inline virtual ~ColorTexture() {}

	/**
	 * @return color texture id
	 */
	virtual int32_t getColorTextureId() = 0;

};
