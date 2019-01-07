#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/lighting/LightingShaderImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::engine::Engine;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

/** 
 * Lighting shader implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::LightingShaderBaseImplementation: public LightingShaderImplementation
{
protected:
	int32_t renderLightingProgramId {  };
	int32_t renderLightingFragmentShaderId {  };
	int32_t renderLightingGeometryShaderId {  };
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
	int32_t uniformEffectColorMul { -1 };
	int32_t uniformEffectColorAdd { -1 };
	int32_t uniformMaterialAmbient { -1 };
	int32_t uniformMaterialDiffuse { -1 };
	int32_t uniformMaterialSpecular { -1 };
	int32_t uniformMaterialEmission { -1 };
	int32_t uniformMaterialShininess { -1 };
	int32_t uniformFrame { -1 };
	int32_t uniformApplyFoliageAnimation { -1 };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightEnabled {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightAmbient {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightDiffuse {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightSpecular {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightPosition {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightSpotDirection {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightSpotExponent {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightSpotCosCutoff {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightConstantAttenuation {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightLinearAttenuation {  };
	array<int32_t, LightingShaderConstants::MAX_LIGHTS> uniformLightQuadraticAttenuation {  };
	Matrix4x4 mvMatrix {  };
	Matrix4x4 mvpMatrix {  };
	Matrix4x4 normalMatrix {  };
	array<float, 4> defaultSceneColor {{ 0.0f, 0.0f, 0.0f, 0.0f }};
	bool isRunning {  };
	bool initialized {  };
	GLRenderer* renderer {  };
public:

	// overriden methods
	virtual bool isInitialized() override;
	virtual void initialize() override;
	virtual void useProgram(Engine* engine) override;
	virtual void unUseProgram() override;
	virtual void updateEffect(GLRenderer* renderer) override;
	virtual void updateMaterial(GLRenderer* renderer) override;
	virtual void updateLight(GLRenderer* renderer, int32_t lightId) override;
	virtual void updateMatrices(GLRenderer* renderer) override;
	virtual void updateTextureMatrix(GLRenderer* renderer) override;
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId) override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	LightingShaderBaseImplementation(GLRenderer* renderer);
};
