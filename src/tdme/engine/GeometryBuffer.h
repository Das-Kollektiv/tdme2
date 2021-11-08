#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>

using tdme::engine::Engine;

/**
 * Geometry buffer class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::GeometryBuffer final
{
private:
	int32_t width;
	int32_t height;
	int32_t frameBufferId;
	int32_t depthBufferTextureId;
	int32_t geometryBufferTextureId1;
	int32_t geometryBufferTextureId2;
	int32_t geometryBufferTextureId3;
	int32_t colorBufferTextureId1;
	int32_t colorBufferTextureId2;
	int32_t colorBufferTextureId3;
	int32_t colorBufferTextureId4;
	int32_t colorBufferTextureId5;
public:
	/**
	 * Public constructor
	 * @param width width
	 * @param height height
	 */
	GeometryBuffer(int32_t width, int32_t height);

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
	void enableGeometryBuffer();

	/**
	 * Switches back to non offscreen main frame buffer to be rendered
	 */
	static void disableGeometryBuffer();

	/**
	 * Bind depth texture
	 * @param context context
	 */
	void bindDepthBufferTexture(void* context);

	/**
	 * Bind geometry buffer textures
	 * @param context context
	 */
	void bindGeometryBufferTextures(void* context);

	/**
	 * Bind color buffer textures
	 * @param context context
	 */
	void bindColorBufferTextures(void* context);

	/**
	 * Render to screen or bound frame buffer
	 * @engine engine
	 */
	void renderToScreen(Engine* engine);

};
