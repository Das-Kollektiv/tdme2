#pragma once

#include <string>

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
	 * Public constructor
	 * @param renderer renderer
	 */
	LightingShaderTerrainImplementation(Renderer* renderer);

	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(Renderer* renderer);

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void registerShader() override;
	virtual void useProgram(Engine* engine, int contextIdx) override;
	virtual void unUseProgram(int contextIdx) override;
	virtual void updateMatrices(Renderer* renderer, int contextIdx) override;
	virtual void updateShaderParameters(Renderer* renderer, int contextIdx) override;

private:
	int32_t uniformModelMatrix { -1 };
	int32_t uniformGrasTextureUnit { -1 };
	int32_t uniformDirtTextureUnit { -1 };
	int32_t uniformSnowTextureUnit { -1 };
	int32_t uniformStoneTextureUnit { -1 };
	int32_t grasTextureId { 0 };
	int32_t dirtTextureId { 0 };
	int32_t snowTextureId { 0 };
	int32_t stoneTextureId { 0 };

protected:
	string additionalDefinitions;

};
