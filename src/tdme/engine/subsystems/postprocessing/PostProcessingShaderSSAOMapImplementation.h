#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::array;
using std::string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

/**
 * Post processing shader SSAO map generation implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOMapImplementation: public PostProcessingShaderBaseImplementation
{
public:
	/**
	 * Returns if shader is supported on given renderer
	 * @param renderer renderer
	 * @return if shader is supported
	 */
	static bool isSupported(Renderer* renderer);

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	PostProcessingShaderSSAOMapImplementation(Renderer* renderer);

	// overridden methods
	virtual void initialize() override;
	virtual void useProgram(int contextIdx) override;
	virtual void setShaderParameters(int contextIdx, Engine* engine) override;

private:
	array<int32_t, 16> uniformSphere;
	int32_t uniformRandomTextureUnit { -1 };
	int32_t randomTextureId { -1 };
};
