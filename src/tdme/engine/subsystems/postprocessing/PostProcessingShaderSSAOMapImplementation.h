#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::array;

using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Post processing shader SSAO map generation implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderSSAOMapImplementation: public PostProcessingShaderBaseImplementation
{
public:
	/**
	 * Returns if shader is supported on given renderer
	 * @param renderer renderer
	 * @return if shader is supported
	 */
	static bool isSupported(GLRenderer* renderer);

	// overridden methods
	virtual void initialize() override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	PostProcessingShaderSSAOMapImplementation(GLRenderer* renderer);

	// overriden methods
	virtual void useProgram() override;

private:
	array<int32_t, 16> uniformSphere;
	int32_t uniformRandomTextureUnit { -1 };
	int32_t randomTextureId { -1 };
};
