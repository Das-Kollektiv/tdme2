#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderImplementation;
using tdme::math::Matrix4x4;

/** 
 * Shadow mapping shader for render shadows pass
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender final
{
private:
	ShadowMappingShaderRenderImplementation* defaultImplementation { nullptr };
	ShadowMappingShaderRenderImplementation* foliageImplementation { nullptr };
	ShadowMappingShaderRenderImplementation* implementation { nullptr };
	bool running { false };
	Matrix4x4 depthBiasMVPMatrix {  };
	int32_t lightId { -1 };

public:

	/** 
	 * @return if initialized and ready to use
	 */
	bool isInitialized();

	/** 
	 * Init shadow mapping
	 */
	void initialize();

	/** 
	 * Use render shadow mapping program
	 */
	void useProgram();

	/** 
	 * Un use render shadow mapping program
	 */
	void unUseProgram();

	/** 
	 * Set up program projection and camera matrix
	 */
	void setProgramViewMatrices();

	/**
	 * Set up program model view matrix
	 * @param model view matrix
	 */
	void setProgramMVMatrix(const Matrix4x4& mvMatrix);

	/** 
	 * Set up program mvp matrix
	 * @param mvp matrix
	 */
	void setProgramMVPMatrix(const Matrix4x4& mvpMatrix);

	/** 
	 * Set up program normal matrix
	 * @param normal matrix
	 */
	void setProgramNormalMatrix(const Matrix4x4& normalMatrix);

	/**
	 * Set up pre program texture matrix
	 * @param renderer
	 */
	void updateTextureMatrix(GLRenderer* renderer);

	/**
	 * Update material
	 * @param renderer
	 */
	void updateMaterial(GLRenderer* renderer);

	/**
	 * Update light
	 * @param renderer
	 * @param light id
	 */
	void updateLight(GLRenderer* renderer, int32_t lightId);

	/**
	 * Bind texture
	 * @param renderer
	 * @param texture id
	 */
	void bindTexture(GLRenderer* renderer, int32_t textureId);

	/** 
	 * Set up program depth bias mvp matrix
	 * @param depth bias mvp matrix
	 */
	void setProgramDepthBiasMVPMatrix(const Matrix4x4& depthBiasMVPMatrix);

	/**
	 * Set light id
	 * @param light id to render
	 */
	void setRenderLightId(int32_t lightId);

	/**
	 * Update apply foliage animation
	 * @param renderer
	 */
	void updateApplyFoliageAnimation(GLRenderer* renderer);

	/**
	 * Public constructor
	 * @param renderer
	 */
	ShadowMappingShaderRender(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMappingShaderRender();
};
