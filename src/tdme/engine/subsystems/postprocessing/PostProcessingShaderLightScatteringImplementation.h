#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Engine.h>

using std::string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

/**
 * Post processing shader implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderLightScatteringImplementation: public PostProcessingShaderBaseImplementation
{
private:
	array<int32_t, Engine::LIGHTS_MAX> uniformLightEnabled;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightPosition;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightIntensity;

public:
	/**
	 * Returns if shader is supported on given renderer
	 * @param renderer renderer
	 * @return if shader is supported
	 */
	static bool isSupported(Renderer* renderer);

	// forbid class copy
	CLASS_FORBID_COPY(PostProcessingShaderLightScatteringImplementation)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	PostProcessingShaderLightScatteringImplementation(Renderer* renderer);

	// overridden methods
	virtual void initialize() override;
	virtual void setShaderParameters(int contextIdx, Engine* engine) override;

};
