#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

/**
 * Pre shadow mapping shader for create shadow map
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderImplementation
{
	/**
	 * Destructor
	 */
	virtual ~ShadowMapCreationShaderImplementation() {}

	/**
	 * @returns shader id
	 */
	virtual const string getId() = 0;

	/**
	 * @returns if initialized and ready to use
	 */
	virtual bool isInitialized() = 0;

	/**
	 * Init shadow map creation program
	 */
	virtual void initialize() = 0;

	/**
	 * Use shadow map creation program
	 * @param engine engine
	 * @param contextIdx context index
	 */
	virtual void useProgram(Engine* engine, int contextIdx) = 0;

	/**
	 * Unuse shadow map creation program
	 * @param contextIdx context index
	 */
	virtual void unUseProgram(int contextIdx) = 0;

	/**
	 * Set up program matrices
	 * @param contextIdx context index
	 */
	virtual void updateMatrices(int contextIdx) = 0;

	/**
	 * Set up program texture matrix
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	virtual void updateTextureMatrix(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Update material
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	virtual void updateMaterial(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Update shader parameters
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
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
