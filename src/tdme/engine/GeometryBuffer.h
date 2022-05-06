#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::vector;

using tdme::engine::Engine;
using tdme::engine::DecalObject;

/**
 * Geometry buffer class
 * @author Andreas Drewke
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
	 * @return frame buffer id
	 */
	inline int32_t getId() {
		return frameBufferId;
	}

	/**
	 * @return depth buffer texture
	 */
	inline int32_t getDepthBufferTextureId() {
		return depthBufferTextureId;
	}

	/**
	 * @return geometry buffer texture 1
	 */
	inline int32_t getGeometryBufferTextureId1() {
		return geometryBufferTextureId1;
	}

	/**
	 * @return geometry buffer texture 2
	 */
	inline int32_t getGeometryBufferTextureId2() {
		return geometryBufferTextureId2;
	}

	/**
	 * @return geometry buffer texture 2
	 */
	inline int32_t getGeometryBufferTextureId3() {
		return geometryBufferTextureId3;
	}

	/**
	 * @return color buffer texture 1
	 */
	inline int32_t getColorBufferTextureId1() {
		return colorBufferTextureId1;
	}

	/**
	 * @return color buffer texture 2
	 */
	inline int32_t getColorBufferTextureId2() {
		return colorBufferTextureId2;
	}

	/**
	 * @return color buffer texture 3
	 */
	inline int32_t getColorBufferTextureId3() {
		return colorBufferTextureId3;
	}

	/**
	 * @return color buffer texture 4
	 */
	inline int32_t getColorBufferTextureId4() {
		return colorBufferTextureId4;
	}

	/**
	 * @return color buffer texture 5
	 */
	inline int32_t getColorBufferTextureId5() {
		return colorBufferTextureId5;
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
	 * @param decalObjects decal objects
	 */
	void renderToScreen(Engine* engine, vector<DecalObject*>& decalObjects);

};
