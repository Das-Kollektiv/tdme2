#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

/** 
 * Shadow mapping shader for render shadows pass
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderImplementation
{
	/**
	 * Destructor
	 */
	virtual ~ShadowMappingShaderRenderImplementation() {}

	/** 
	 * @return if initialized and ready to use
	 */
	virtual bool isInitialized() = 0;

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize() = 0;

	/** 
	 * Use render shadow mapping program
	 * @param engine engine
	 */
	virtual void useProgram(Engine* engine) = 0;

	/** 
	 * Un use render shadow mapping program
	 */
	virtual void unUseProgram() = 0;

	/** 
	 * Set up program projection and camera matrix
	 */
	virtual void setProgramViewMatrices() = 0;

	/**
	 * Set up program model view matrix
	 * @param mvMatrix model view matrix
	 */
	virtual void setProgramMVMatrix(const Matrix4x4& mvMatrix) = 0;

	/** 
	 * Set up program mvp matrix
	 * @param mvpMatrix mvp matrix
	 */
	virtual void setProgramMVPMatrix(const Matrix4x4& mvpMatrix) = 0;

	/** 
	 * Set up program normal matrix
	 * @param normalMatrix normal matrix
	 */
	virtual void setProgramNormalMatrix(const Matrix4x4& normalMatrix) = 0;

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
	 * Update light
	 * @param renderer renderer
	 * @param lightId light id
	 */
	virtual void updateLight(GLRenderer* renderer, int32_t lightId) = 0;

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param textureId texture id
	 */
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId) = 0;

	/** 
	 * Set up program depth bias mvp matrix
	 * @param depthBiasMVPMatrix depth bias mvp matrix
	 */
	virtual void setProgramDepthBiasMVPMatrix(const Matrix4x4& depthBiasMVPMatrix) = 0;

	/**
	 * Set light id
	 * @param lightId light id to render
	 */
	virtual void setRenderLightId(int32_t lightId) = 0;
};
