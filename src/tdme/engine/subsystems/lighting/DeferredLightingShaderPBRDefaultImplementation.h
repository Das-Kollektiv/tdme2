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
class tdme::engine::subsystems::lighting::DeferredLightingShaderPBRDefaultImplementation: public LightingShaderPBRBaseImplementation
{
public:
	// forbid class copy
	CLASS_FORBID_COPY(DeferredLightingShaderPBRDefaultImplementation)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	DeferredLightingShaderPBRDefaultImplementation(Renderer* renderer);

	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(Renderer* renderer);

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void registerShader() override;
	virtual void updateShaderParameters(Renderer* renderer, int contextIdx) override;

};
