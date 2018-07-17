
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
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre
{
private:
	GLRenderer* renderer {  };
	int32_t vertexShaderGlId {  };
	int32_t geometryShaderGlId {  };
	int32_t fragmentShaderGlId {  };
	int32_t programGlId {  };
	int32_t uniformProjectionMatrix { -1 };
	int32_t uniformCameraMatrix { -1 };
	int32_t uniformMVPMatrix { -1 };
	int32_t uniformTextureMatrix { -1 };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformDiffuseTextureAvailable { -1 };
	int32_t uniformDiffuseTextureMaskedTransparency { -1 };
	int32_t uniformDiffuseTextureMaskedTransparencyThreshold { -1 };
	int32_t uniformApplyFoliageAnimation { -1 };
	int32_t uniformFrame { -1 };
	bool initialized {  };

public:

	/** 
	 * @return if initialized and ready to use
	 */
	virtual bool isInitialized();

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize();

	/** 
	 * Use pre render shadow mapping program
	 */
	virtual void useProgram();

	/** 
	 * Un use pre render shadow mapping program
	 */
	virtual void unUseProgram();

	/** 
	 * Set up pre program mvp matrix
	 * @param mvp matrix
	 */
	virtual void updateMatrices(const Matrix4x4& mvpMatrix);

	/**
	 * Set up pre program texture matrix
	 * @param renderer
	 */
	virtual void updateTextureMatrix(GLRenderer* renderer);

	/**
	 * Update material
	 * @param renderer
	 */
	virtual void updateMaterial(GLRenderer* renderer);

	/**
	 * Bind texture
	 * @param renderer
	 * @param texture id
	 */
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId);

	/**
	 * Update apply foliage animation
	 * @param renderer
	 */
	virtual void updateApplyFoliageAnimation(GLRenderer* renderer);

	/**
	 * Constructor
	 * @param renderer
	 */
	ShadowMappingShaderPre(GLRenderer* renderer);
};
