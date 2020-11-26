#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/environmentmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>

using std::vector;

using tdme::engine::Camera;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Environment mapping
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::environmentmapping::EnvironmentMapping final
{
	friend class tdme::engine::Engine;

private:
	Engine* engine { nullptr };
	Camera* camera { nullptr };
	int width { -1 };
	int height { -1 };
	array<FrameBuffer*, 6> frameBuffers { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	array<Vector3, 6> forwardVectors {{
		{{ -1.0f, 0.0f, 0.0f }}, // left
		{{ 1.0f, 0.0f, 0.0f }}, // right
		{{ 0.0f, -1.0f, 0.0f }}, // top
		{{ 0.0f, 1.0f, 0.0f }}, // bottom
		{{ 0.0f, 0.0f, -1.0f }}, // front
		{{ 0.0f, 0.0f, 1.0f }} // back
	}};
	array<Vector3, 6> sideVectors {{
		{{ 0.0f, 0.0f, -1.0f }}, // left
		{{ 0.0f, 0.0f, 1.0f }}, // right
		{{ -1.0f, 0.0f, 0.0f }}, // top
		{{ 1.0f, 0.0f, 0.0f }}, // bottom
		{{ 1.0f, 0.0f, 0.0f }}, // front
		{{ -1.0f, 0.0f, 0.0f }} // back
	}};
	array<Vector3, 6> upVectors {{
		{{ 0.0f, 1.0f, 0.0f }}, // left
		{{ 0.0f, 0.0f, 0.0f }}, // right
		{{ 0.0f, 0.0f, -1.0f }}, // top
		{{ 0.0f, 0.0f, 1.0f }}, // bottom
		{{ 0.0f, 1.0f, 0.0f }}, // front
		{{ 0.0f, 1.0f, 0.0f }} // back
	}};
	int32_t cubeMapTextureId { 0 };

	/**
	 * Init frame buffer
	 */
	void initialize();

	/**
	 * Reshape frame buffers
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

	/**
	 * Disposes this shadow mapping
	 */
	void dispose();

	/**
	 * Renders given objects in to environment cube map
	 * @param light light
	 */
	void render();

public:
	/**
	 * Public constructor
	 * @param engine engine
	 * @param width width
	 * @param height height
	 */
	EnvironmentMapping(Engine* engine, int32_t width, int32_t height);

	/**
	 * Destructor
	 */
	~EnvironmentMapping();

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
	 * Get frame buffer of given index
	 * @param idx index
	 * @return frame buffer of given index
	 */
	inline FrameBuffer* getFrameBuffer(int idx) {
		return frameBuffers[idx];
	}

	/**
	 * @return cube map texture id
	 */
	inline int32_t getCubeMapTextureId() {
		return cubeMapTextureId;
	}

};
