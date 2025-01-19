#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderBaseImplementation.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderBaseImplementation;

/**
 * Shadow mapping foliage shader class to create shadow map
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderFoliageImplementation: public ShadowMapCreationShaderBaseImplementation
{
private:
	int32_t uniformSpeed { -1 };
	int32_t uniformAmplitudeDefault	{ -1 };
	int32_t uniformAmplitudeMax { -1 };

public:
	/**
	 * @returns if supported by renderer backend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapCreationShaderFoliageImplementation)

	/**
	 * Constructor
	 * @param rendererBackend renderer backend
	 */
	ShadowMapCreationShaderFoliageImplementation(RendererBackend* rendererBackend);

	/**
	 * Destructor
	 */
	~ShadowMapCreationShaderFoliageImplementation();

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;

};
