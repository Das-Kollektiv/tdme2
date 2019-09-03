#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::Renderer;

/** 
 * Lighting shader implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::LightingShaderWaterImplementation: public LightingShaderBaseImplementation
{
public:

	static constexpr int WAVES_MAX { 4 };

	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(Renderer* renderer);

	// overriden methods
	virtual void initialize() override;
	virtual void useProgram(Engine* engine, void* context) override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	LightingShaderWaterImplementation(Renderer* renderer);

protected:
	int32_t uniformWaterHeight;
	int32_t uniformTime;
	int32_t uniformNumWaves;
	array<int32_t, WAVES_MAX> uniformAmplitude;
	array<int32_t, WAVES_MAX> uniformWavelength;
	array<int32_t, WAVES_MAX> uniformSpeed;
	array<int32_t, WAVES_MAX> uniformDirection;
	float time { 0.0f };
	array<float, WAVES_MAX> angle;
};
