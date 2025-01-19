#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;

/**
 * Lighting shader implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::lighting::LightingShaderWaterImplementation: public LightingShaderBaseImplementation
{
public:
	static constexpr int WAVES_MAX { 4 };

	// forbid class copy
	FORBID_CLASS_COPY(LightingShaderWaterImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	LightingShaderWaterImplementation(RendererBackend* rendererBackend);

	/**
	 * @returns if supported by renderer backend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void registerShader() override;
	virtual void useProgram(Engine* engine, int contextIdx) override;
	virtual void updateMatrices(RendererBackend* rendererBackend, int contextIdx) override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;

protected:
	int32_t uniformWaterHeight { -1 };
	int32_t uniformTime { -1 };
	int32_t uniformWaterWaves { -1 };
	array<int32_t, WAVES_MAX> uniformWaterAmplitude;
	array<int32_t, WAVES_MAX> uniformWaterWaveLength;
	array<int32_t, WAVES_MAX> uniformWaterSpeed;
	array<int32_t, WAVES_MAX> uniformWaterDirection;
	int32_t uniformModelMatrix { -1 };
	float time { 0.0f };
	array<float, WAVES_MAX> angle;
};
