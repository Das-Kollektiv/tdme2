#pragma once

#include <tdme/engine/subsystems/lighting/fwd-tdme.h>

/** 
 * Lighting shader constants
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::lighting::LightingShaderConstants final
{
	static constexpr int32_t SPECULAR_TEXTUREUNIT_DIFFUSE { 0 };
	static constexpr int32_t SPECULAR_TEXTUREUNIT_SPECULAR { 1 };
	static constexpr int32_t SPECULAR_TEXTUREUNIT_NORMAL { 3 };
	static constexpr int32_t SPECULAR_TEXTUREUNIT_TERRAIN_GRAS { 4 };
	static constexpr int32_t SPECULAR_TEXTUREUNIT_TERRAIN_DIRT { 5 };
	static constexpr int32_t SPECULAR_TEXTUREUNIT_TERRAIN_STONE { 6 };
	static constexpr int32_t SPECULAR_TEXTUREUNIT_TERRAIN_SNOW { 7 };
};
