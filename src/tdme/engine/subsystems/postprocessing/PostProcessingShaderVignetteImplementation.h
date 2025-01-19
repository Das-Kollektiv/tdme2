#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;

/**
 * Post processing shader vignette implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderVignetteImplementation: public PostProcessingShaderBaseImplementation
{
private:
	int32_t uniformIntensity { -1 };
	int32_t uniformBorderColor { -1 };

public:
	/**
	 * Returns if shader is supported on given renderer backend
	 * @param rendererBackend renderer backend
	 * @return if shader is supported
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(PostProcessingShaderVignetteImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	PostProcessingShaderVignetteImplementation(RendererBackend* rendererBackend);

	// overridden methods
	virtual void initialize() override;
	virtual void setShaderParameters(int contextIdx, Engine* engine) override;

};
