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
using tdme::engine::subsystems::renderer::RendererBackend;
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
	 * @returns shader id
	 */
	virtual const string getId() = 0;

	/**
	 * @returns initialized and ready to be used
	 */
	virtual bool isInitialized() = 0;

	/**
	 * Initialize
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
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	virtual void updateEffect(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Update material to program
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	virtual void updateMaterial(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Update light to program
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param lightId light id
	 */
	virtual void updateLight(RendererBackend* rendererBackend, int contextIdx, int32_t lightId) = 0;

	/**
	 * Update matrices to program
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	virtual void updateMatrices(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Update texture matrix to program
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	virtual void updateTextureMatrix(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Update shader parameters
	 * @param rendererBackend renderer backend
	 * @param context
	 */
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Bind texture
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param textureId texture id
	 */
	virtual void bindTexture(RendererBackend* rendererBackend, int contextIdx, int32_t textureId) = 0;

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
