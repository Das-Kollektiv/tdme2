#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

/**
 * Post processing shader default implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderDefaultImplementation: public PostProcessingShaderBaseImplementation
{
public:
	/**
	 * Returns if shader is supported on given renderer
	 * @param renderer renderer
	 * @return if shader is supported
	 */
	static bool isSupported(Renderer* renderer);

	// forbid class copy
	CLASS_FORBID_COPY(PostProcessingShaderDefaultImplementation)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	PostProcessingShaderDefaultImplementation(Renderer* renderer);

	// overridden methods
	virtual void initialize() override;
	virtual void setShaderParameters(int contextIdx, Engine* engine) override;

};
