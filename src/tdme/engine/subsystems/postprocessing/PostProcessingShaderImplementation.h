#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::FrameBuffer;
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Post processing shader program implementation interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::postprocessing::PostProcessingShaderImplementation
{

	/**
	 * Public destructor
	 */
	virtual ~PostProcessingShaderImplementation() {}

	/** 
	 * @return initialized and ready to be used
	 */
	virtual bool isInitialized() = 0;

	/** 
	 * Initialize post processing shader
	 */
	virtual void initialize() = 0;

	/** 
	 * Use program
	 */
	virtual void useProgram() = 0;

	/** 
	 * Unuse program
	 */
	virtual void unUseProgram() = 0;

	/**
	 * Set source buffer pixel width
	 * @param pixelWidth pixel width
	 */
	virtual void setBufferPixelWidth(float pixelWidth) = 0;

	/**
	 * Set source buffer pixel height
	 * @param pixelHeight pixel height
	 */
	virtual void setBufferPixelHeight(float pixelHeight) = 0;

};
