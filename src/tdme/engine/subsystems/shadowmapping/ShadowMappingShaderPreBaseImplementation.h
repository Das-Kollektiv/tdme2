
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreImplementation.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreImplementation;
using tdme::math::Matrix4x4;

/** 
 * Pre shadow mapping shader for render shadow map pass 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreBaseImplementation: public ShadowMappingShaderPreImplementation
{
protected:
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
	int32_t uniformFrame { -1 };
	bool initialized {  };

public:

	/** 
	 * @return if initialized and ready to use
	 */
	virtual bool isInitialized() override;

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize() override;

	/** 
	 * Use pre render shadow mapping program
	 */
	virtual void useProgram() override;

	/** 
	 * Un use pre render shadow mapping program
	 */
	virtual void unUseProgram() override;

	/** 
	 * Set up pre program mvp matrix
	 * @param mvpMatrix mvp matrix
	 */
	virtual void updateMatrices(const Matrix4x4& mvpMatrix) override;

	/**
	 * Set up pre program texture matrix
	 * @param renderer renderer
	 */
	virtual void updateTextureMatrix(GLRenderer* renderer) override;

	/**
	 * Update material
	 * @param renderer renderer
	 */
	virtual void updateMaterial(GLRenderer* renderer) override;

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param textureId texture id
	 */
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId) override;

	/**
	 * Constructor
	 * @param renderer renderer
	 */
	ShadowMappingShaderPreBaseImplementation(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMappingShaderPreBaseImplementation();
};
