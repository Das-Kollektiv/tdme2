#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Post processing shader blur implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderBlurImplementation: public PostProcessingShaderBaseImplementation
{
public:
	// overridden methods
	virtual void initialize() override;

	/**
	 * Public constructor
	 * @param renderer
	 */
	PostProcessingShaderBlurImplementation(GLRenderer* renderer);

};
