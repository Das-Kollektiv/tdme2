#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;

/** 
 * Pre shadow mapping shader for create shadow map
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreImplementation
{
	/**
	 * Destructor
	 */
	virtual ~ShadowMappingShaderPreImplementation() {}

	/** 
	 * @return if initialized and ready to use
	 */
	virtual bool isInitialized() = 0;

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize() = 0;

	/** 
	 * Use pre render shadow mapping program
	 * @param engine engine
	 * @param context context
	 */
	virtual void useProgram(Engine* engine, void* context) = 0;

	/** 
	 * Un use pre render shadow mapping program
	 */
	virtual void unUseProgram() = 0;

	/** 
	 * Set up pre program mvp matrix
	 * @param context context
	 * @param mvpMatrix mvp matrix
	 */
	virtual void updateMatrices(void* context, const Matrix4x4& mvpMatrix) = 0;

	/**
	 * Set up pre program texture matrix
	 * @param renderer renderer
	 * @param context context
	 */
	virtual void updateTextureMatrix(Renderer* renderer, void* context) = 0;

	/**
	 * Update material
	 * @param renderer renderer
	 * @param context context
	 */
	virtual void updateMaterial(Renderer* renderer, void* context) = 0;

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param context context
	 * @param textureId texture id
	 */
	virtual void bindTexture(Renderer* renderer, void* context, int32_t textureId) = 0;
};
