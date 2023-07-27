#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>

using std::vector;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;

/**
 * Shadow mapping module
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapping final
{
	friend class tdme::engine::Engine;
	friend class ShadowMap;

private:
	enum ShadowMapping_RunState {NONE, CREATE, RENDER};

	Renderer* renderer { nullptr };
	EntityRenderer* entityRenderer { nullptr };

	Matrix4x4 shadowTransformMatrix;
	Matrix4x4 depthBiasMVPMatrix;

	Engine* engine { nullptr };

	vector<ShadowMap*> shadowMaps;
	ShadowMapping_RunState runState { NONE };

	vector<Object*> visibleObjectsReceivingShadows;

public:
	// forbid class copy
	CLASS_FORBID_COPY(ShadowMapping)

	/**
	 * Constructor
	 * @param engine engine
	 * @param renderer renderer
	 * @param entityRenderer entityRenderer
	 */
	ShadowMapping(Engine* engine, Renderer* renderer, EntityRenderer* entityRenderer);

	/**
	 * Destructor
	 */
	~ShadowMapping();

	/**
	 * @return engine
	 */
	Engine* getEngine();

	/**
	 * Reshape shadow maps
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

	/**
	 * Get shadow map
	 * @param idx index
	 * @return shadow map
	 */
	ShadowMap* getShadowMap(int idx);

	/**
	 * Create shadow maps
	 */
	void createShadowMaps();

	/**
	 * Render shadow maps to world
	 * @param visibleObjects visible objects
	 */
	void renderShadowMaps(const vector<Object*>& visibleObjects);

	/**
	 * Dispose shadow maps
	 */
	void dispose();

	/**
	 * Start object transform
	 * @param contextIdx context index
	 * @param transformMatrix transform matrix
	 */
	void startObjectTransform(int contextIdx, Matrix4x4& transformMatrix);

	/**
	 * End object transform
	 */
	void endObjectTransform();

	/**
	 * Update matrices
	 * @param contextIdx context index
	 */
	void updateMatrices(int contextIdx);

	/**
	 * Update texture matrix
	 * @param contextIdx context index
	 */
	void updateTextureMatrix(int contextIdx);

	/**
	 * Update material
	 * @param contextIdx context index
	 */
	void updateMaterial(int contextIdx);

	/**
	 * Set shader
	 * @param contextIdx context index
	 * @param id shader id
	 */
	void setShader(int contextIdx, const string& id);

	/**
	 * Update light
	 * @param lightId light id
	 */
	void updateLight(int contextIdx, int32_t lightId);

	/**
	 * Update shader parameters
	 * @param context
	 */
	void updateShaderParameters(int contextIdx);

	/**
	 * Bind texture
	 * @param textureId texture id
	 */
	void bindTexture(int contextIdx, int32_t textureId);

	/**
	 * Update depth bias mvp matrix with given matrix
	 * @param contextIdx context index
	 * @param depthBiasMVPMatrix depth bias MVP matrix
	 */
	void updateDepthBiasMVPMatrix(int contextIdx, Matrix4x4& depthBiasMVPMatrix);

	/**
	 * Update depth bias mvp matrix / upload only
	 * @param contextIdx context index
	 */
	void updateDepthBiasMVPMatrix(int contextIdx);

};
