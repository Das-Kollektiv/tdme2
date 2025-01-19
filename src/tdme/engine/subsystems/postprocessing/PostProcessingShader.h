#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;
using std::unordered_map;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;

/**
 * Post processing shader
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShader final
{
private:
	unordered_map<string, PostProcessingShaderImplementation*> shaders;
	PostProcessingShaderImplementation* implementation { nullptr };

	bool running { false };

public:
	// forbid class copy
	FORBID_CLASS_COPY(PostProcessingShader)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	PostProcessingShader(RendererBackend* rendererBackend);

	/**
	 * Public destructor
	 */
	~PostProcessingShader();

	/**
	 * @returns initialized and ready to be used
	 */
	bool isInitialized();

	/**
	 * Initialize
	 */
	void initialize();

	/**
	 * Initialize
	 */
	void dispose();

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
	 * @returns if shader exists and is initialized
	 */
	bool hasShader(const string& id);

	/**
	 * Set post processing shader
	 * @param contextIdx context index
	 */
	void setShader(int contextIdx, const string& id);

	/**
	 * Set source buffer pixel width
	 * @param contextIdx context index
	 * @param pixelWidth pixel width
	 */
	void setBufferPixelWidth(int contextIdx, float pixelWidth);

	/**
	 * Set source buffer pixel height
	 * @param contextIdx context index
	 * @param pixelHeight pixel height
	 */
	void setBufferPixelHeight(int contextIdx, float pixelHeight);

	/**
	 * Set shader parameters
	 * @param engine engine
	 */
	void setShaderParameters(int contextIdx, Engine* engine);

	/**
	 * Load textures
	 * @param pathName path name
	 */
	void loadTextures(const string& pathName);

};
