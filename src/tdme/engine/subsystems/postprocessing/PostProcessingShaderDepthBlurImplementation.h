#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;

/**
 * Post processing shader depth blur implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderDepthBlurImplementation: public PostProcessingShaderBaseImplementation
{
public:
	/**
	 * Returns if shader is supported in given renderer backend
	 * @param rendererBackend renderer backend
	 * @returns if shader is supported
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(PostProcessingShaderDepthBlurImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	PostProcessingShaderDepthBlurImplementation(RendererBackend* rendererBackend);

	// overridden methods
	virtual void initialize() override;
	virtual void setShaderParameters(int contextIdx, Engine* engine) override;

};
