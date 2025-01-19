#pragma once

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/environmentmapping/fwd-tdme.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::unique_ptr;
using std::vector;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::FrameBuffer;
using tdme::engine::GeometryBuffer;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Environment mapping
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::environmentmapping::EnvironmentMappingRenderer final
{
	friend class tdme::engine::EnvironmentMapping;

private:
	Engine* engine { nullptr };
	unique_ptr<Camera> camera { nullptr };
	int width { -1 };
	int height { -1 };
	array<Vector3, 6> forwardVectors;
	array<Vector3, 6> sideVectors;
	array<array<unique_ptr<FrameBuffer>, 6>, 2> frameBuffers;
	array<int32_t, 2> cubeMapTextureIds { 0, 0 };
	int64_t timeRenderLast { -1LL };
	int reflectionCubeMapTextureIdx { 0 };
	int renderCubeMapTextureIdx { 0 };
	STATIC_DLL_IMPEXT static unique_ptr<GeometryBuffer> geometryBuffer;
	int64_t timeRenderUpdateFrequency { 100LL };
	int32_t renderPassMask { Entity::RENDERPASS_ALL - Entity::RENDERPASS_WATER - Entity::RENDERPASS_GIZMO};
	Engine::DecomposedEntities visibleDecomposedEntities;

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
	 * @param position position
	 */
	void render(const Vector3& position);

public:
	// forbid class copy
	FORBID_CLASS_COPY(EnvironmentMappingRenderer)

	/**
	 * Public constructor
	 * @param engine engine
	 * @param width width
	 * @param height height
	 */
	EnvironmentMappingRenderer(Engine* engine, int32_t width, int32_t height);

	/**
	 * Destructor
	 */
	~EnvironmentMappingRenderer();

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
	 * @returns render pass mask
	 */
	inline int32_t getRenderPassMask() {
		return renderPassMask;
	}

	/**
	 * Set up render pass mask
	 * @param renderPassMask render pass mask
	 */
	inline void setRenderPassMask(int32_t renderPassMask) {
		this->renderPassMask = renderPassMask;
	}

	/**
	 * @returns render update time frequency in milliseconds
	 */
	inline int64_t getTimeRenderUpdateFrequency() {
		return timeRenderUpdateFrequency;
	}

	/**
	 * Set up render update time frequency
	 * @param frequency frequency in milliseconds
	 */
	inline void setTimeRenderUpdateFrequency(int64_t frequency) {
		timeRenderUpdateFrequency = frequency;
	}

	/**
	 * @returns cube map texture id
	 */
	inline int32_t getCubeMapTextureId() {
		return timeRenderLast == -1LL?0:cubeMapTextureIds[reflectionCubeMapTextureIdx];
	}

};
