#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Post processing shader sky rendering implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderSkyImplementation: public PostProcessingShaderBaseImplementation
{
public:
	// overridden methods
	virtual void initialize() override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	PostProcessingShaderSkyImplementation(GLRenderer* renderer);

};
