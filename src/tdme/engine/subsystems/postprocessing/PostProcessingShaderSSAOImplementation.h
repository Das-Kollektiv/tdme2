#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;

/**
 * Post processing shader SSAO rendering implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOImplementation: public PostProcessingShaderBaseImplementation
{
public:
	/**
	 * Returns if shader is supported on given rendererBackend
	 * @param rendererBackend renderer backend
	 * @return if shader is supported
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(PostProcessingShaderSSAOImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	PostProcessingShaderSSAOImplementation(RendererBackend* rendererBackend);

	// overridden methods
	virtual void initialize() override;
	virtual void setShaderParameters(int contextIdx, Engine* engine) override;

};
