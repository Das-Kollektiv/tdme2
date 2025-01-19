#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;

/**
 * Lighting shader implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::lighting::DeferredLightingShaderDefaultImplementation: public LightingShaderBaseImplementation
{
public:
	/**
	 * @returns if supported by renderer backend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(DeferredLightingShaderDefaultImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	DeferredLightingShaderDefaultImplementation(RendererBackend* rendererBackend);

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void registerShader() override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;

};
