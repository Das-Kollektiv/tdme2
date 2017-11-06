
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Shadow mapping shader for render shadows pass
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender final
{
private:
	GLRenderer* renderer {  };
	int32_t renderVertexShaderGlId {  };
	int32_t renderFragmentShaderGlId {  };
	int32_t renderProgramGlId {  };
	int32_t renderUniformTextureUnit {  };
	int32_t renderUniformTexturePixelWidth {  };
	int32_t renderUniformTexturePixelHeight {  };
	int32_t renderUniformDepthBiasMVPMatrix {  };
	int32_t renderUniformMVMatrix {  };
	int32_t renderUniformMVPMatrix {  };
	int32_t renderUniformNormalMatrix {  };
	int32_t uniformDiffuseTextureUnit {  };
	int32_t uniformDiffuseTextureAvailable {  };
	int32_t uniformDiffuseTextureMaskedTransparency {  };
	int32_t renderUniformLightPosition {  };
	int32_t renderUniformLightDirection {  };
	int32_t renderUniformLightSpotExponent {  };
	int32_t renderUniformLightSpotCosCutoff {  };
	int32_t renderUniformLightConstantAttenuation {  };
	int32_t renderUniformLightLinearAttenuation {  };
	int32_t renderUniformLightQuadraticAttenuation {  };
	bool initialized {  };
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
	 * Set up program texture unit
	 * @param texture unit
	 */
	void setProgramTextureUnit(int32_t textureUnit);

	/** 
	 * Set up program texture unit
	 * @param texture unit
	 */
	void setProgramTexturePixelDimensions(float width, float height);

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
	 * Update material
	 * @param renderer
	 */
	void updateMaterial(GLRenderer* renderer);

	/**
	 * Bind texture
	 * @param renderer
	 * @param texture id
	 */
	void bindTexture(GLRenderer* renderer, int32_t textureId);

	/** 
	 * Set up program light position
	 * @param light position
	 */
	void setProgramLightPosition(const Vector3& lightPosition);

	/** 
	 * Set up program light position
	 * @param light position
	 */
	void setProgramLightDirection(const Vector3& lightDirection);

	/** 
	 * Set up program depth bias mvp matrix
	 * @param depth bias mvp matrix
	 */
	void setProgramDepthBiasMVPMatrix(const Matrix4x4& depthBiasMVPMatrix);

	/** 
	 * Set up light spot exponent
	 * @param spot exponent
	 */
	void setProgramLightSpotExponent(float spotExponent);

	/** 
	 * Set up light spot cos cut off
	 * @param spot cos cut off
	 */
	void setProgramLightSpotCosCutOff(float spotCosCutOff);

	/** 
	 * Set up light constant attenuation
	 * @param constant attenuation
	 */
	void setProgramLightConstantAttenuation(float constantAttenuation);

	/** 
	 * Set up light linear attenuation
	 * @param linear attenuation
	 */
	void setProgramLightLinearAttenuation(float linearAttenuation);

	/** 
	 * Set up light quadratic attenuation
	 * @param quadratic attenuation
	 */
	void setProgramLightQuadraticAttenuation(float quadraticAttenuation);

	/**
	 * Public constructor
	 * @param renderer
	 */
	ShadowMappingShaderRender(GLRenderer* renderer);
};
