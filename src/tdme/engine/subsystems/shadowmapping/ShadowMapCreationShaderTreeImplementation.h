#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderBaseImplementation.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderBaseImplementation;

/**
 * Shadow mapping tree shader class to create shadow map
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderTreeImplementation: public ShadowMapCreationShaderBaseImplementation
{
private:
	int32_t uniformSpeed { -1 };

public:
	/**
	 * @returns if supported by renderer backend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapCreationShaderTreeImplementation)

	/**
	 * Constructor
	 * @param rendererBackend renderer backend
	 */
	ShadowMapCreationShaderTreeImplementation(RendererBackend* rendererBackend);

	/**
	 * Destructor
	 */
	~ShadowMapCreationShaderTreeImplementation();

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;

};
