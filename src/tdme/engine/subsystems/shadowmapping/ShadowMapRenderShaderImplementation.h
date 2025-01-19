#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

/**
 * Shadow mapping shader interface to render shadow map
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderImplementation
{
	/**
	 * Destructor
	 */
	virtual ~ShadowMapRenderShaderImplementation() {}

	/**
	 * @returns shader id
	 */
	virtual const string getId() = 0;

	/**
	 * @returns if initialized and ready to use
	 */
	virtual bool isInitialized() = 0;

	/**
	 * Init shadow mapping
	 */
	virtual void initialize() = 0;

	/**
	 * Use shadow map render shader program
	 * @param engine engine
	 * @param contextIdx context index
	 */
	virtual void useProgram(Engine* engine, int contextIdx) = 0;

	/**
	 * Un use shadow map render shader program
	 * @param contextIdx context index
	 */
	virtual void unUseProgram(int contextIdx) = 0;

	/**
	 * Update matrices
	 * @param contextIdx context index
	 */
	virtual void updateMatrices(int contextIdx) = 0;

	/**
	 * Update texture matrix
	 * @param rendererBackend renderer backend
	 * @param context contet
	 */
	virtual void updateTextureMatrix(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Update material
	 * @param rendererBackend renderer backend
	 * @param context contet
	 */
	virtual void updateMaterial(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Update light
	 * @param rendererBackend renderer backend
	 * @param context contet
	 * @param lightId light id
	 */
	virtual void updateLight(RendererBackend* rendererBackend, int contextIdx, int32_t lightId) = 0;

	/**
	 * Update shader parameters
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) = 0;

	/**
	 * Bind texture
	 * @param rendererBackend renderer backend
	 * @param context contet
	 * @param textureId texture id
	 */
	virtual void bindTexture(RendererBackend* rendererBackend, int contextIdx, int32_t textureId) = 0;

	/**
	 * Set up program depth bias mvp matrix
	 * @param context contet
	 * @param depthBiasMVPMatrix depth bias mvp matrix
	 */
	virtual void setDepthBiasMVPMatrix(int contextIdx, const Matrix4x4& depthBiasMVPMatrix) = 0;

	/**
	 * Set light id
	 * @param lightId light id to render
	 */
	virtual void setRenderLightId(int32_t lightId) = 0;

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
