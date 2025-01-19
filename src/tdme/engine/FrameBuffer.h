#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/ColorTexture.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShader;

using tdme::engine::ColorTexture;
using tdme::engine::Engine;

/**
 * Frame buffer class
 * @author Andreas Drewke
 */
class tdme::engine::FrameBuffer final: public ColorTexture
{

public:
	static constexpr int32_t FRAMEBUFFER_DEPTHBUFFER { 1 };
	static constexpr int32_t FRAMEBUFFER_COLORBUFFER { 2 };

	static constexpr int32_t TEXTUREID_NONE { 0 };

	static constexpr int32_t CUBEMAPTEXTUREINDEX_NONE { 0 };
	static constexpr int32_t CUBEMAPTEXTUREINDEX_NEGATIVE_X { 1 };
	static constexpr int32_t CUBEMAPTEXTUREINDEX_POSITIVE_X { 2 };
	static constexpr int32_t CUBEMAPTEXTUREINDEX_POSITIVE_Y { 3 };
	static constexpr int32_t CUBEMAPTEXTUREINDEX_NEGATIVE_Y { 4 };
	static constexpr int32_t CUBEMAPTEXTUREINDEX_POSITIVE_Z { 5 };
	static constexpr int32_t CUBEMAPTEXTUREINDEX_NEGATIVE_Z { 6 };

private:
	int32_t buffers;
	int32_t width;
	int32_t height;
	int32_t frameBufferId;
	int32_t depthBufferTextureId;
	int32_t colorBufferTextureId;
	int32_t cubeMapTextureId;
	int32_t cubeMapTextureIndex;
	bool ownsDepthBufferTexture;
	bool ownsColorBufferTexture;

	/**
	 * Render given depth texture and color buffer texture to screen
	 * @parma engine engine
	 * @param depthBufferTextureId depth buffer texture id
	 * @param colorBufferTextureId color buffer texture id
	 */
	void renderToScreen(Engine* engine, int32_t depthBufferTextureId, int32_t colorBufferTextureId);

public:
	// forbid class copy
	FORBID_CLASS_COPY(FrameBuffer)

	/**
	 * Public constructor
	 * @param width width
	 * @param height height
	 * @param buffers buffers (see FrameBuffer::FRAMEBUFFER_*)
	 * @param cubeMapTextureId cube map texture id
	 * @param cubeMapTextureIndex cube map texture index
	 */
	FrameBuffer(int32_t width, int32_t height, int32_t buffers, int32_t cubeMapTextureId = TEXTUREID_NONE, int32_t cubeMapTextureIndex = TEXTUREID_NONE);

	/**
	 * Destructor
	 */
	virtual ~FrameBuffer();

	/**
	 * @returns width
	 */
	inline int32_t getWidth() {
		return width;
	}

	/**
	 * @returns height
	 */
	inline int32_t getHeight() {
		return height;
	}

	/**
	 * @returns frame buffer id
	 */
	inline int32_t getId() {
		return frameBufferId;
	}

	/**
	 * @returns depth buffer texture id
	 */
	inline int32_t getDepthBufferTextureId() {
		return depthBufferTextureId;
	}

	/**
	 * Set depth buffer texture id
	 * @param texture id depth buffer texture id
	 */
	inline void setDepthBufferTextureId(int32_t textureId) {
		depthBufferTextureId = textureId;
	}

	/**
	 * @returns color buffer texture id
	 */
	inline int32_t getColorBufferTextureId() {
		return colorBufferTextureId;
	}

	/**
	 * Set color buffer texture id
	 * @param textureId color buffer texture id
	 */
	inline void setColorBufferTextureId(int32_t textureId) {
		colorBufferTextureId = textureId;
	}

	/**
	 * Initialize the frame buffer
	 */
	void initialize();

	/**
	 * Resize the frame buffer
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

	/**
	 * Disposes this frame buffer
	 */
	void dispose();

	/**
	 * Enables this frame buffer to be rendered
	 */
	void enableFrameBuffer();

	/**
	 * Switches back to non offscreen main frame buffer to be rendered
	 */
	static void disableFrameBuffer();

	/**
	 * Bind depth texture
	 * @param contextIdx context index
	 */
	void bindDepthBufferTexture(int contextIdx);

	/**
	 * Bind color texture
	 * @param contextIdx context index
	 */
	void bindColorBufferTexture(int contextIdx);

	/**
	 * Render to screen or bound frame buffer
	 * @param engine engine
	 */
	inline void renderToScreen(Engine* engine) {
		renderToScreen(engine, depthBufferTextureId, colorBufferTextureId);
	}

	/**
	 * Render depth buffer to screen or bound frame buffer
	 * @param engine engine
	 */
	inline void renderDepthBufferToScreen(Engine* engine) {
		renderToScreen(engine, depthBufferTextureId, depthBufferTextureId);
	}

	/**
	 * Do post processing into target frame buffer (which can be screen as well when passing nullptr)
	 * @param engine engine
	 * @param source source frame buffer
	 * @param programId post processing shader id
	 * @param shaderId post processing shader id
	 * @param temporary bind additional temporary frame buffer
	 * @param blendToSource target = blendToSource + source
	 */
	static void doPostProcessing(Engine* engine, FrameBuffer* target, FrameBuffer* source, const string& programId, const string& shaderId, FrameBuffer* temporary = nullptr, FrameBuffer* blendToSource = nullptr);

	// overridden methods
	inline int32_t getColorTextureId() override {
		return colorBufferTextureId;
	}

};
