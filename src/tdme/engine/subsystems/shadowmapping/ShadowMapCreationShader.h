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

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderImplementation;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

/**
 * Shadow mapping shader to create a shadow map
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapCreationShader final
{
private:
	struct ShadowMapCreationShaderContext {
		ShadowMapCreationShaderImplementation* implementation { nullptr };
	};
	unordered_map<string, ShadowMapCreationShaderImplementation*> shaders;
	bool running { false };
	Engine* engine { nullptr };
	RendererBackend* rendererBackend { nullptr };
	vector<ShadowMapCreationShaderContext> contexts;

public:
	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapCreationShader)

	/**
	 * Constructor
	 * @param rendererBackend renderer backend
	 */
	ShadowMapCreationShader(RendererBackend* rendererBackend);

	/**
	 * Destructor
	 */
	~ShadowMapCreationShader();

	/**
	 * @return if initialized and ready to use
	 */
	bool isInitialized();

	/**
	 * Init shadow map creation shader program
	 */
	void initialize();

	/**
	 * Use shadow map creation shader program
	 * @param engine engine
	 */
	void useProgram(Engine* engine);

	/**
	 * Unuse shadow map creation shader program
	 */
	void unUseProgram();

	/**
	 * Set up matrices
	 * @param contextIdx context index
	 */
	void updateMatrices(int contextIdx);

	/**
	 * Set up texture matrix
	 * @param contextIdx context index
	 */
	void updateTextureMatrix(int contextIdx);

	/**
	 * Update material
	 * @param contextIdx context index
	 */
	void updateMaterial(int contextIdx);

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
	 * Set shader
	 * @param context
	 * @param id shader id
	 */
	void setShader(int contextIdx, const string& id);

	/**
	 * Load textures
	 * @param pathName path name
	 */
	void loadTextures(const string& pathName);

};
