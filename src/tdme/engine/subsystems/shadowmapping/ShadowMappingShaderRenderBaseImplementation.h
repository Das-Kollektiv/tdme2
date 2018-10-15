#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderImplementation.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Engine;
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

	// overriden methods
	virtual bool isInitialized() override;
	virtual void initialize() override;
	virtual void useProgram(Engine* engine) override;
	virtual void unUseProgram() override;
	virtual void setProgramViewMatrices() override;
	virtual void setProgramMVMatrix(const Matrix4x4& mvMatrix) override;
	virtual void setProgramMVPMatrix(const Matrix4x4& mvpMatrix) override;
	virtual void setProgramNormalMatrix(const Matrix4x4& normalMatrix) override;
	virtual void updateTextureMatrix(GLRenderer* renderer) override;
	virtual void updateMaterial(GLRenderer* renderer) override;
	virtual void updateLight(GLRenderer* renderer, int32_t lightId) override;
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId) override;
	virtual void setProgramDepthBiasMVPMatrix(const Matrix4x4& depthBiasMVPMatrix) override;
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
