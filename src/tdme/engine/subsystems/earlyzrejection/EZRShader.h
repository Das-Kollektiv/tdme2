#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/earlyzrejection/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::subsystems::earlyzrejection::EZRShaderImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

/**
 * Early z rejection shader
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::earlyzrejection::EZRShader final
{
private:
	struct EZRShaderContext {
		EZRShaderImplementation* implementation { nullptr };
	};

	unordered_map<string, EZRShaderImplementation*> shader;
	bool running { false };
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };
	vector<EZRShaderContext> contexts;

public:
	/**
	 * Constructor
	 * @param renderer renderer
	 */
	EZRShader(Renderer* renderer);

	/**
	 * Destructor
	 */
	~EZRShader();

	/**
	 * @return if initialized and ready to use
	 */
	bool isInitialized();

	/**
	 * Init EZR shader
	 */
	void initialize();

	/**
	 * Use EZR render shader program
	 * @param engine engine
	 */
	void useProgram(Engine* engine);

	/**
	 * Unuse EZR render shader program
	 */
	void unUseProgram();

	/**
	 * Update program matrices
	 * @param renderer renderer
	 * @param contextIdx context index
	 */
	void updateMatrices(int contextIdx);

	/**
	 * Set up program texture matrix
	 * @param contextIdx context index
	 * @param renderer renderer
	 */
	void updateTextureMatrix(int contextIdx);

	/**
	 * Update material
	 * @param renderer renderer
	 * @param contextIdx context index
	 */
	void updateMaterial(int contextIdx);

	/**
	 * Bind texture
	 * @param renderer renderer
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
	 * Update shader parameters
	 * @param context
	 */
	void updateShaderParameters(int contextIdx);

};
