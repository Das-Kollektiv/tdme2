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
	 * Initialize the geometry buffer
	 */
	void initialize();

	/**
	 * Resize the geometry buffer
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

	/**
	 * Disposes this geometry buffer
	 */
	void dispose();

	/**
	 * Enables this geometry buffer to be rendered
	 */
	void enableGeometryBuffer();

	/**
	 * Switches back to non offscreen main frame buffer to be rendered
	 */
	static void disableGeometryBuffer();

	/**
	 * Render to screen or bound geometry buffer
	 * @engine engine
	 */
	void renderToScreen(Engine* engine);

};
