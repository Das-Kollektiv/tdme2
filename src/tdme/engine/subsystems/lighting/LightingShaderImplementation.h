#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

/**
 * Lighting shader implementation interface
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::lighting::LightingShaderImplementation
{
	/**
	 * Destructor
	 */
	virtual ~LightingShaderImplementation() {}

	/**
	 * @return shader id
	 */
	virtual const string getId() = 0;

	/**
	 * @return initialized and ready to be used
	 */
	virtual bool isInitialized() = 0;

	/**
	 * Initialize renderer
	 */
	virtual void initialize() = 0;

	/**
	 * Register shader
	 */
	virtual void registerShader() = 0;

	/**
	 * Use lighting program
	 * @param engine engine
	 * @param contextIdx context index
	 */
	virtual void useProgram(Engine* engine, int contextIdx) = 0;

	/**
	 * Unuse lighting program
	 * @param contextIdx context index
	 */
	virtual void unUseProgram(int contextIdx) = 0;

	/**
	 * Update effect to program
	 * @param renderer renderer
	 * @param contextIdx context index
	 */
	virtual void updateEffect(Renderer* renderer, int contextIdx) = 0;

	/**
	 * Update material to program
	 * @param renderer renderer
	 * @param contextIdx context index
	 */
	virtual void updateMaterial(Renderer* renderer, int contextIdx) = 0;

	/**
	 * Update light to program
	 * @param renderer renderer
	 * @param contextIdx context index
	 * @param lightId light id
	 */
	virtual void updateLight(Renderer* renderer, int contextIdx, int32_t lightId) = 0;

	/**
	 * Update matrices to program
	 * @param renderer renderer
	 * @param contextIdx context index
	 */
	virtual void updateMatrices(Renderer* renderer, int contextIdx) = 0;

	/**
	 * Update texture matrix to program
	 * @param renderer renderer
	 * @param contextIdx context index
	 */
	virtual void updateTextureMatrix(Renderer* renderer, int contextIdx) = 0;

	/**
	 * Update shader parameters
	 * @param renderer renderer
	 * @param context
	 */
	virtual void updateShaderParameters(Renderer* renderer, int contextIdx) = 0;

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param contextIdx context index
	 * @param textureId texture id
	 */
	virtual void bindTexture(Renderer* renderer, int contextIdx, int32_t textureId) = 0;

	/**
	 * Unload textures
	 */
	virtual void unloadTextures() = 0;

	/**
	 * Load textures
	 * @param pathName path name
	 */
	virtual void loadTextures(const string& pathName) = 0;

};
