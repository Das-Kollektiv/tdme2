#pragma once

#include <tdme/engine/subsystems/lighting/fwd-tdme.h>

/** 
 * Lighting shader constants
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::lighting::LightingShaderConstants final
{
	static constexpr int32_t MAX_LIGHTS { 8 };
	static constexpr int32_t TEXTUREUNIT_DIFFUSE { 0 };
	static constexpr int32_t TEXTUREUNIT_SPECULAR { 1 };
	static constexpr int32_t TEXTUREUNIT_DISPLACEMENT { 2 };
	static constexpr int32_t TEXTUREUNIT_NORMAL { 3 };
	static constexpr int32_t TEXTUREUNIT_TERRAIN_GRAS { 4 };
	static constexpr int32_t TEXTUREUNIT_TERRAIN_DIRT { 5 };
	static constexpr int32_t TEXTUREUNIT_TERRAIN_STONE { 6 };
	static constexpr int32_t TEXTUREUNIT_TERRAIN_SNOW { 7 };

};
