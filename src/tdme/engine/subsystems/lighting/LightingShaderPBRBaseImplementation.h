#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/lighting/LightingShaderImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::Texture;
using tdme::math::Matrix4x4;

/**
 * Lighting shader implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation: public LightingShaderImplementation
{
protected:
	int32_t programId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t vertexShaderId { -1 };
	int32_t uniformBaseColorFactor { -1 };
	int32_t uniformBaseColorSampler { -1 };
	int32_t uniformBaseColorSamplerAvailable { -1 };
	int32_t uniformAlphaCutoffEnabled { -1 };
	int32_t uniformAlphaCutoff { -1 };
	int32_t uniformCamera { -1 };
	int32_t uniformExposure { -1 };
	int32_t uniformMetallicFactor { -1 };
	int32_t uniformMetallicRoughnessSampler { -1 };
	int32_t uniformMetallicRoughnessSamplerAvailable { -1 };
	int32_t uniformRoughnessFactor { -1 };
	int32_t uniformNormalSampler { -1 };
	int32_t uniformNormalSamplerAvailable { -1 };
	int32_t uniformNormalScale { -1 };
	int32_t uniformEmissiveSampler { -1 };
	int32_t uniformEmissiveSamplerAvailable { -1 };
	int32_t uniformEmissiveFactor { -1 };
	int32_t uniformViewProjectionMatrix { -1 };
	int32_t uniformDiffuseEnvSampler { -1 };
	int32_t uniformSpecularEnvSampler { -1 };
	int32_t uniformbrdfLUT { -1 };
	int32_t textureDiffuseEnvSampler { -1 };
	int32_t textureSpecularEnvSampler { -1 };
	int32_t texturebrdfLUT { -1 };

	array<int32_t, Engine::LIGHTS_MAX> uniformLightEnabled;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightAmbient;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightDirection;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightRange;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightColor;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightIntensity;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightPosition;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightInnerConeCos;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightOuterConeCos;
	array<int32_t, Engine::LIGHTS_MAX> uniformLightType;

	array<Texture*, 6> envDiffuseTextures;
	array<Texture*, 6> envSpecularTextures;

	bool initialized { false };
	RendererBackend* rendererBackend { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(LightingShaderPBRBaseImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	LightingShaderPBRBaseImplementation(RendererBackend* rendererBackend);

	// overridden methods
	virtual bool isInitialized() override;
	virtual void initialize() override;
	virtual void useProgram(Engine* engine, int contextIdx) override;
	virtual void unUseProgram(int contextIdx) override;
	virtual void updateEffect(RendererBackend* rendererBackend, int contextIdx) override;
	virtual void updateMaterial(RendererBackend* rendererBackend, int contextIdx) override;
	virtual void updateLight(RendererBackend* rendererBackend, int contextIdx, int32_t lightId) override;
	virtual void updateMatrices(RendererBackend* rendererBackend, int contextIdx) override;
	virtual void updateTextureMatrix(RendererBackend* rendererBackend, int contextIdx) override;
	virtual void bindTexture(RendererBackend* rendererBackend, int contextIdx, int32_t textureId) override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override = 0;
	virtual void unloadTextures() override;
	virtual void loadTextures(const string& pathName) override;

};
