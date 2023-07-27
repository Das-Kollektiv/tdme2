#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderImplementation.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderImplementation;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Shadow mapping base shader to render shadow maps
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderBaseImplementation: public ShadowMapRenderShaderImplementation
{
protected:
	Renderer* renderer { nullptr };
	int32_t vertexShaderId { -1 };
	int32_t renderGeometryShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t renderUniformShadowMapLookUps { -1 };
	int32_t uniformTextureUnit { -1 };
	int32_t renderUniformTexturePixelWidth { -1 };
	int32_t renderUniformTexturePixelHeight { -1 };
	int32_t renderUniformDepthBiasMVPMatrix { -1 };
	int32_t renderUniformProjectionMatrix { -1 };
	int32_t renderUniformCameraMatrix { -1 };
	int32_t renderUniformMVMatrix { -1 };
	int32_t renderUniformMVPMatrix { -1 };
	int32_t renderUniformNormalMatrix { -1 };
	int32_t renderUniformModelTranslation { -1 };
	int32_t uniformTextureMatrix { -1 };
	int32_t uniformTextureAtlasSize { -1 };
	int32_t uniformTextureAtlasPixelDimension { -1 };
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
	int32_t renderUniformTime { -1 };
	bool initialized;
	int lightId { -1 };

public:
	// forbid class copy
	CLASS_FORBID_COPY(ShadowMapRenderShaderBaseImplementation)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	ShadowMapRenderShaderBaseImplementation(Renderer* renderer);

	/**
	 * Destructor
	 */
	virtual ~ShadowMapRenderShaderBaseImplementation();

	// overridden methods
	virtual bool isInitialized() override;
	virtual void initialize() override;
	virtual void useProgram(Engine* engine, int contextIdx) override;
	virtual void unUseProgram(int contextIdx) override;
	virtual void updateMatrices(int contextIdx) override;
	virtual void updateTextureMatrix(Renderer* renderer, int contextIdx) override;
	virtual void updateMaterial(Renderer* renderer, int contextIdx) override;
	virtual void updateLight(Renderer* renderer, int contextIdx, int32_t lightId) override;
	virtual void updateShaderParameters(Renderer* renderer, int contextIdx) override = 0;
	virtual void bindTexture(Renderer* renderer, int contextIdx, int32_t textureId) override;
	virtual void setDepthBiasMVPMatrix(int contextIdx, const Matrix4x4& depthBiasMVPMatrix) override;
	virtual void setRenderLightId(int32_t lightId) override;
	virtual void loadTextures(const string& pathName) override;

};
