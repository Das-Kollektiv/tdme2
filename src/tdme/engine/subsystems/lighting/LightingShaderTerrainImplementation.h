#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::Renderer;

/** 
 * Lighting shader implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::LightingShaderTerrainImplementation: public LightingShaderBaseImplementation
{
public:

	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(Renderer* renderer);

	// overriden methods
	virtual void initialize() override;
	virtual void useProgram(Engine* engine, void* context) override;
	virtual void unUseProgram(void* context) override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	LightingShaderTerrainImplementation(Renderer* renderer);

private:
	int uniformGrasTextureUnit { -1 };
	int uniformDirtTextureUnit { -1 };
	int uniformSnowTextureUnit { -1 };
	int uniformStoneTextureUnit { -1 };
	int grasTextureId { 0 };
	int dirtTextureId { 0 };
	int snowTextureId { 0 };
	int stoneTextureId { 0 };

};
