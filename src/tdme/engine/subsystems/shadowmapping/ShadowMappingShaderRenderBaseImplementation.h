#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderImplementation.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderImplementation;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Shadow mapping shader for render shadows pass
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderBaseImplementation: public ShadowMappingShaderRenderImplementation
{
protected:
	GLRenderer* renderer {  };
	int32_t renderVertexShaderGlId {  };
	int32_t renderGeometryShaderGlId {  };
	int32_t renderFragmentShaderGlId {  };
	int32_t renderProgramGlId {  };
	int32_t renderUniformTextureUnit { -1 };
	int32_t renderUniformTexturePixelWidth { -1 };
	int32_t renderUniformTexturePixelHeight { -1 };
	int32_t renderUniformDepthBiasMVPMatrix { -1 };
	int32_t renderUniformProjectionMatrix { -1 };
	int32_t renderUniformCameraMatrix { -1 };
	int32_t renderUniformMVMatrix { -1 };
	int32_t renderUniformMVPMatrix { -1 };
	int32_t renderUniformNormalMatrix { -1 };
	int32_t uniformTextureMatrix { -1 };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformDiffuseTextureAvailable { -1 };
	int32_t uniformDiffuseTextureMaskedTransparency { -1 };
	int32_t uniformDiffuseTextureMaskedTransparencyThreshold { -1 };
	int32_t renderUniformLightPosition { -1 };
	int32_t renderUniformLightDirection { -1 };
	int32_t renderUniformLightSpotExponent { -1 };
	int32_t renderUniformLightSpotCosCutoff { -1 };
	int32_t renderUniformLightConstantAttenuation { -1 };
	int32_t renderUniformLightLinearAttenuation { -1 };
	int32_t renderUniformLightQuadraticAttenuation { -1 };
	int32_t uniformFrame { -1 };
	bool initialized {  };
	int lightId { -1 };

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
	 * Use render shadow mapping program
	 */
	virtual void useProgram() override;

	/** 
	 * Un use render shadow mapping program
	 */
	virtual void unUseProgram() override;

	/** 
	 * Set up program projection and camera matrix
	 */
	virtual void setProgramViewMatrices() override;

	/**
	 * Set up program model view matrix
	 * @param mvMatrix model view matrix
	 */
	virtual void setProgramMVMatrix(const Matrix4x4& mvMatrix) override;

	/** 
	 * Set up program mvp matrix
	 * @param mvpMatrix mvp matrix
	 */
	virtual void setProgramMVPMatrix(const Matrix4x4& mvpMatrix) override;

	/** 
	 * Set up program normal matrix
	 * @param normalMatrix normal matrix
	 */
	virtual void setProgramNormalMatrix(const Matrix4x4& normalMatrix) override;

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
	 * Update light
	 * @param renderer renderer
	 * @param lightId light id
	 */
	virtual void updateLight(GLRenderer* renderer, int32_t lightId) override;

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param textureId texture id
	 */
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId) override;

	/** 
	 * Set up program depth bias mvp matrix
	 * @param depthBiasMVPMatrix depth bias mvp matrix
	 */
	virtual void setProgramDepthBiasMVPMatrix(const Matrix4x4& depthBiasMVPMatrix) override;

	/**
	 * Set light id
	 * @param lightId light id to render
	 */
	virtual void setRenderLightId(int32_t lightId) override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	ShadowMappingShaderRenderBaseImplementation(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	virtual ~ShadowMappingShaderRenderBaseImplementation();
};
