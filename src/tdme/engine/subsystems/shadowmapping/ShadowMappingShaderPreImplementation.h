
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

/** 
 * Pre shadow mapping shader for render shadow map pass 
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
	 */
	virtual void useProgram() = 0;

	/** 
	 * Un use pre render shadow mapping program
	 */
	virtual void unUseProgram() = 0;

	/** 
	 * Set up pre program mvp matrix
	 * @param mvpMatrix mvp matrix
	 */
	virtual void updateMatrices(const Matrix4x4& mvpMatrix) = 0;

	/**
	 * Set up pre program texture matrix
	 * @param renderer renderer
	 */
	virtual void updateTextureMatrix(GLRenderer* renderer) = 0;

	/**
	 * Update material
	 * @param renderer renderer
	 */
	virtual void updateMaterial(GLRenderer* renderer) = 0;

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param textureId texture id
	 */
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId) = 0;
};
