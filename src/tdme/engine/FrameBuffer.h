#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShader;

using tdme::engine::Engine;

/**
 * Frame buffer class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::FrameBuffer final
{

public:
	static constexpr int32_t FRAMEBUFFER_DEPTHBUFFER { 1 };
	static constexpr int32_t FRAMEBUFFER_COLORBUFFER { 2 };

private:
	int32_t width;
	int32_t height;
	int32_t frameBufferId;
	int32_t depthBufferTextureId;
	int32_t colorBufferTextureId;
	int32_t buffers;
public:
	/**
	 * Public constructor
	 * @param width width
	 * @param height height
	 * @param buffers buffers (see FrameBuffer::FRAMEBUFFER_*)
	 */
	FrameBuffer(int32_t width, int32_t height, int32_t buffers);

	/**
	 * @return width
	 */
	inline int32_t getWidth() {
		return width;
	}

	/**
	 * @return height
	 */
	inline int32_t getHeight() {
		return height;
	}

	/**
	 * Init the frame buffer
	 * currently only depth buffer rendering is enabled, can be extended to color buffer easily
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
	 * @param context context
	 */
	void bindDepthBufferTexture(void* context);

	/**
	 * Bind color texture
	 * @param context context
	 */
	void bindColorBufferTexture(void* context);

	/**
	 * @return color buffer texture id
	 */
	int32_t getColorBufferTextureId();

	/**
	 * @return depth buffer texture id
	 */
	int32_t getDepthBufferTextureId();

	/**
	 * Render to screen or bound frame buffer
	 */
	void renderToScreen();

	/**
	 * Do post processing into target frame buffer (which can be screen as well when passing nullptr)
	 * @param engine engine
	 * @param source source frame buffer
	 * @param programId post processing shader id
	 * @param shaderId post processing shader id
	 * @param temporary bind additional temporary frame buffer
	 * @param blendToSource target = blendToSource + source
	 * @param fixedLightScatteringIntensity if using fixed light scattering intensity (hack until we have shader parameters)
	 * @param lightScatteringItensityValue light scattering itensity value (hack until we have shader parameters)
	 */
	static void doPostProcessing(Engine* engine, FrameBuffer* target, FrameBuffer* source, const string& programId, const string& shaderId, FrameBuffer* temporary = nullptr, FrameBuffer* blendToSource = nullptr, bool fixedLightScatteringIntensity = false, float lightScatteringItensityValue = 0.5f);

};
