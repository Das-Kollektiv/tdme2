#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;

/**
 * Post processing shader program implementation interface
 * @author Andreas Drewke
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
	 * @param contextIdx context index
	 */
	virtual void useProgram(int contextIdx) = 0;

	/**
	 * Unuse program
	 */
	virtual void unUseProgram() = 0;

	/**
	 * Set source buffer pixel width
	 * @param contextIdx context index
	 * @param pixelWidth pixel width
	 */
	virtual void setBufferPixelWidth(int contextIdx, float pixelWidth) = 0;

	/**
	 * Set source buffer pixel height
	 * @param contextIdx context index
	 * @param pixelHeight pixel height
	 */
	virtual void setBufferPixelHeight(int contextIdx, float pixelHeight) = 0;

	/**
	 * Set shader parameters
	 * @param contextIdx context index
	 * @param engine engine
	 */
	virtual void setShaderParameters(int contextIdx, Engine* engine) = 0;

	/**
	 * Unload textures
	 */
	virtual void unloadTextures() = 0;

	/**
	 * Load textures
	 * @param pathName path name
	 */
	virtual void loadTextures(const string& pathName) = 0;
};
