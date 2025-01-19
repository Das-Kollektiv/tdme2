#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::vector;

using tdme::engine::Decal;
using tdme::engine::Engine;

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
	// forbid class copy
	FORBID_CLASS_COPY(GeometryBuffer)

	/**
	 * Public constructor
	 * @param width width
	 * @param height height
	 */
	GeometryBuffer(int32_t width, int32_t height);

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
	 * @returns depth buffer texture
	 */
	inline int32_t getDepthBufferTextureId() {
		return depthBufferTextureId;
	}

	/**
	 * @returns geometry buffer texture 1
	 */
	inline int32_t getGeometryBufferTextureId1() {
		return geometryBufferTextureId1;
	}

	/**
	 * @returns geometry buffer texture 2
	 */
	inline int32_t getGeometryBufferTextureId2() {
		return geometryBufferTextureId2;
	}

	/**
	 * @returns geometry buffer texture 2
	 */
	inline int32_t getGeometryBufferTextureId3() {
		return geometryBufferTextureId3;
	}

	/**
	 * @returns color buffer texture 1
	 */
	inline int32_t getColorBufferTextureId1() {
		return colorBufferTextureId1;
	}

	/**
	 * @returns color buffer texture 2
	 */
	inline int32_t getColorBufferTextureId2() {
		return colorBufferTextureId2;
	}

	/**
	 * @returns color buffer texture 3
	 */
	inline int32_t getColorBufferTextureId3() {
		return colorBufferTextureId3;
	}

	/**
	 * @returns color buffer texture 4
	 */
	inline int32_t getColorBufferTextureId4() {
		return colorBufferTextureId4;
	}

	/**
	 * @returns color buffer texture 5
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
	 * @param decalObjects decal entities
	 */
	void renderToScreen(Engine* engine, vector<Decal*>& decalEntities);

};
