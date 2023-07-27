#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderImplementation;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

/**
 * Shadow mapping shader to render shadow maps
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapRenderShader final
{
private:
	struct ShadowMapRenderShaderContext {
		ShadowMapRenderShaderImplementation* implementation { nullptr };
	};
	unordered_map<string, ShadowMapRenderShaderImplementation*> shader;
	bool running { false };
	Matrix4x4 depthBiasMVPMatrix;
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };
	vector<ShadowMapRenderShaderContext> contexts;
	int32_t lightId { -1 };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapRenderShader)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	ShadowMapRenderShader(Renderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMapRenderShader();

	/**
	 * @return if initialized and ready to use
	 */
	bool isInitialized();

	/**
	 * Initialize shadow map render shader program
	 */
	void initialize();

	/**
	 * Use shadow map render shader program
	 * @param engine engine
	 */
	void useProgram(Engine* engine);

	/**
	 * Unuse shadow map render shader program
	 */
	void unUseProgram();

	/**
	 * Update matrices
	 * @param contextIdx context index
	 */
	void updateMatrices(int contextIdx);

	/**
	 * Update up texture matrix
	 * @param contextIdx context index
	 */
	void updateTextureMatrix(int contextIdx);

	/**
	 * Update material
	 * @param contextIdx context index
	 */
	void updateMaterial(int contextIdx);

	/**
	 * Update light
	 * @param contextIdx context index
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
	 * @param contextIdx context index
	 * @param textureId texture id
	 */
	void bindTexture(int contextIdx, int32_t textureId);

	/**
	 * Set up program depth bias mvp matrix
	 * @param contextIdx context index
	 * @param depthBiasMVPMatrix depth bias mvp matrix
	 */
	void setDepthBiasMVPMatrix(int contextIdx, const Matrix4x4& depthBiasMVPMatrix);

	/**
	 * Set light id
	 * @param lightId light id to render
	 */
	void setRenderLightId(int32_t lightId);

	/**
	 * Set shader
	 * @param id id
	 */
	void setShader(int contextIdx, const string& id);

	/**
	 * Load textures
	 * @param pathName path name
	 */
	void loadTextures(const string& pathName);

};
