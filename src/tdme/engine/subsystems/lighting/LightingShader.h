#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

/** 
 * Interface to gl3 lighting shader program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::LightingShader final
{
public:
	static constexpr int32_t MAX_LIGHTS { 8 };
	static constexpr int32_t TEXTUREUNIT_DIFFUSE { 0 };
	static constexpr int32_t TEXTUREUNIT_SPECULAR { 1 };
	static constexpr int32_t TEXTUREUNIT_DISPLACEMENT { 2 };
	static constexpr int32_t TEXTUREUNIT_NORMAL { 3 };

private:
	int32_t renderLightingProgramId {  };
	int32_t renderLightingFragmentShaderId {  };
	int32_t renderLightingVertexShaderId {  };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformDiffuseTextureAvailable { -1 };
	int32_t uniformDiffuseTextureMaskedTransparency { -1 };
	int32_t uniformDiffuseTextureMaskedTransparencyThreshold { -1 };
	int32_t uniformSpecularTextureUnit { -1 };
	int32_t uniformSpecularTextureAvailable { -1 };
	int32_t uniformNormalTextureUnit { -1 };
	int32_t uniformNormalTextureAvailable { -1 };
	int32_t uniformDisplacementTextureUnit { -1 };
	int32_t uniformDisplacementTextureAvailable { -1 };
	int32_t uniformProjectionMatrix { -1 };
	int32_t uniformCameraMatrix { -1 };
	int32_t uniformMVPMatrix { -1 };
	int32_t uniformMVMatrix { -1 };
	int32_t uniformNormalMatrix { -1 };
	int32_t uniformTextureMatrix { -1 };
	int32_t uniformSceneColor { -1 };
	int32_t uniformEffectColorMul { -1 };
	int32_t uniformEffectColorAdd { -1 };
	int32_t uniformMaterialAmbient { -1 };
	int32_t uniformMaterialDiffuse { -1 };
	int32_t uniformMaterialSpecular { -1 };
	int32_t uniformMaterialEmission { -1 };
	int32_t uniformMaterialShininess { -1 };
	array<int32_t, MAX_LIGHTS> uniformLightEnabled {  };
	array<int32_t, MAX_LIGHTS> uniformLightAmbient {  };
	array<int32_t, MAX_LIGHTS> uniformLightDiffuse {  };
	array<int32_t, MAX_LIGHTS> uniformLightSpecular {  };
	array<int32_t, MAX_LIGHTS> uniformLightPosition {  };
	array<int32_t, MAX_LIGHTS> uniformLightSpotDirection {  };
	array<int32_t, MAX_LIGHTS> uniformLightSpotExponent {  };
	array<int32_t, MAX_LIGHTS> uniformLightSpotCosCutoff {  };
	array<int32_t, MAX_LIGHTS> uniformLightConstantAttenuation {  };
	array<int32_t, MAX_LIGHTS> uniformLightLinearAttenuation {  };
	array<int32_t, MAX_LIGHTS> uniformLightQuadraticAttenuation {  };
	Matrix4x4 mvMatrix {  };
	Matrix4x4 mvpMatrix {  };
	Matrix4x4 normalMatrix {  };
	array<float, 4> defaultSceneColor {{ 0.0f, 0.0f, 0.0f, 0.0f }};
	bool isRunning {  };
	bool initialized {  };
	GLRenderer* renderer {  };
public:

	/** 
	 * @return initialized and ready to be used
	 */
	bool isInitialized();

	/** 
	 * Initialize renderer
	 */
	void initialize();

	/** 
	 * Use lighting program
	 */
	void useProgram();

	/** 
	 * Unuse lighting program
	 */
	void unUseProgram();

	/** 
	 * Update effect to program
	 * @param renderer
	 */
	void updateEffect(GLRenderer* renderer);

	/** 
	 * Update material to program
	 * @param gl3 renderer
	 */
	void updateMaterial(GLRenderer* renderer);

	/** 
	 * Update light to program
	 * @param renderer
	 * @param light id
	 */
	void updateLight(GLRenderer* renderer, int32_t lightId);

	/** 
	 * Update matrices to program
	 * @param renderer
	 */
	void updateMatrices(GLRenderer* renderer);

	/** 
	 * Update texture matrix to program
	 * @param renderer
	 */
	void updateTextureMatrix(GLRenderer* renderer);

	/**
	 * Bind texture
	 * @param renderer
	 * @param texture id
	 */
	void bindTexture(GLRenderer* renderer, int32_t textureId);

	/**
	 * Public constructor
	 * @param renderer
	 */
	LightingShader(GLRenderer* renderer);
};
