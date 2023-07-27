#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

/**
 * Post processing shader desaturation implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderDesaturationImplementation: public PostProcessingShaderBaseImplementation
{
private:
	int32_t uniformIntensity { -1 };

public:
	/**
	 * Returns if shader is supported on given renderer
	 * @param renderer renderer
	 * @return if shader is supported
	 */
	static bool isSupported(Renderer* renderer);

	// forbid class copy
	FORBID_CLASS_COPY(PostProcessingShaderDesaturationImplementation)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	PostProcessingShaderDesaturationImplementation(Renderer* renderer);

	// overridden methods
	virtual void initialize() override;
	virtual void setShaderParameters(int contextIdx, Engine* engine) override;

};
