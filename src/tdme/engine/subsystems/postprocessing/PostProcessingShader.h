#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::FrameBuffer;
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Post processing shader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShader final
{
private:
	map<string, PostProcessingShaderImplementation*> shader;
	PostProcessingShaderImplementation* implementation { nullptr };

	bool running {  };

public:

	/** 
	 * @return initialized and ready to be used
	 */
	bool isInitialized();

	/** 
	 * Initialize renderer
	 */
	void initialize();

	/** 
	 * Use program
	 */
	void useProgram();

	/** 
	 * Unuse program
	 */
	void unUseProgram();

	/**
	 * Has post processing shader
	 * @param id shader id
	 * @return if shader exists and is initialized
	 */
	bool hasShader(const string& id);

	/**
	 * Set post processing shader
	 */
	void setShader(const string& id);

	/**
	 * Set source buffer pixel width
	 * @param pixelWidth pixel width
	 */
	void setBufferPixelWidth(float pixelWidth);

	/**
	 * Set source buffer pixel height
	 * @param pixelHeight pixel height
	 */
	void setBufferPixelHeight(float pixelHeight);

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	PostProcessingShader(GLRenderer* renderer);

	/**
	 * Public destructor
	 */
	~PostProcessingShader();

};
