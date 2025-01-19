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
class tdme::engine::subsystems::lighting::LightingShaderLightScatteringTreeImplementation: public LightingShaderBaseImplementation
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(LightingShaderLightScatteringTreeImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	LightingShaderLightScatteringTreeImplementation(RendererBackend* rendererBackend);

	/**
	 * @return if supported by rendererBackend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// overridden methods
	virtual const string getId() override;
	virtual void registerShader() override;
	virtual void initialize() override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;

};
