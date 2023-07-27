#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

/**
 * Interface to lighting shader program
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::lighting::LightingShader final
{
private:
	struct LightingShaderContext {
		LightingShaderImplementation* implementation { nullptr };
	};
	unordered_map<string, LightingShaderImplementation*> shader;
	Renderer* renderer { nullptr };
	Engine* engine { nullptr };
	bool running { false };
	vector<LightingShaderContext> contexts;

public:
	// forbid class copy
	FORBID_CLASS_COPY(LightingShader)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	LightingShader(Renderer* renderer);

	/**
	 * Destructor
	 */
	~LightingShader();

	/**
	 * @return initialized and ready to be used
	 */
	bool isInitialized();

	/**
	 * Initialize renderer
	 */
	void initialize();

	/**
	 * Use lighting program
	 * @param engine engine
	 */
	void useProgram(Engine* engine);

	/**
	 * Unuse lighting program
	 */
	void unUseProgram();

	/**
	 * Update effect to program
	 * @param contextIdx context index
	 */
	void updateEffect(int contextIdx);

	/**
	 * Update material to program
	 * @param contextIdx context index
	 */
	void updateMaterial(int contextIdx);

	/**
	 * Update light to program
	 * @param contextIdx context index
	 * @param lightId light id
	 */
	void updateLight(int contextIdx, int32_t lightId);

	/**
	 * Update matrices to program
	 * @param contextIdx context index
	 */
	void updateMatrices(int contextIdx);

	/**
	 * Update texture matrix to program
	 * @param contextIdx context index
	 */
	void updateTextureMatrix(int contextIdx);

	/**
	 * Update shader parameters
	 * @param context
	 */
	void updateShaderParameters(int contextIdx);

	/**
	 * Set shader
	 * @param contextIdx context index
	 * @param id id
	 */
	void setShader(int contextIdx, const string& id);

	/**
	 * Bind texture
	 * @param contextIdx context index
	 * @param textureId texture id
	 */
	void bindTexture(int contextIdx, int32_t textureId);

	/**
	 * Returns if shader with given shader id does exist
	 * @param shaderId shader id
	 * @return if shader exists
	 */
	bool hasShader(const string& shaderId) {
		return shader.find(shaderId) != shader.end();
	}

	/**
	 * Returns shader for given shader id
	 * @param shaderId shader id
	 * @return if shader exists
	 */
	LightingShaderImplementation* getShader(const string& shaderId) {
		auto shaderIt = shader.find(shaderId);
		if (shaderIt == shader.end()) return nullptr;
		return shaderIt->second;
	}

	/**
	 * Load textures
	 * @param pathName path name
	 */
	void loadTextures(const string& pathName);

};
