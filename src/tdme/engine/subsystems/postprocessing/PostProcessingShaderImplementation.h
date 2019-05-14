#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::FrameBuffer;
using tdme::engine::subsystems::renderer::Renderer;

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
	 * @param context context
	 */
	virtual void useProgram(void* context) = 0;

	/** 
	 * Unuse program
	 */
	virtual void unUseProgram() = 0;

	/**
	 * Set source buffer pixel width
	 * @param context context
	 * @param pixelWidth pixel width
	 */
	virtual void setBufferPixelWidth(void* context, float pixelWidth) = 0;

	/**
	 * Set source buffer pixel height
	 * @param context context
	 * @param pixelHeight pixel height
	 */
	virtual void setBufferPixelHeight(void* context, float pixelHeight) = 0;

};
