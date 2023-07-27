#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
using tdme::engine::subsystems::renderer::Renderer;

/**
 * Lighting shader implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::lighting::DeferredLightingShaderPBRTreeImplementation: public LightingShaderPBRBaseImplementation
{
private:
	int32_t uniformTime { -1 };
	int32_t uniformSpeed { -1 };

public:
	// forbid class copy
	FORBID_CLASS_COPY(DeferredLightingShaderPBRTreeImplementation)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	DeferredLightingShaderPBRTreeImplementation(Renderer* renderer);

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
	virtual void updateShaderParameters(Renderer* renderer, int contextIdx) override;

};
