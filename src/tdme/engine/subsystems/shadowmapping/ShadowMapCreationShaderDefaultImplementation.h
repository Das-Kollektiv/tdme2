#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderBaseImplementation.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderBaseImplementation;

/**
 * Shadow mapping default shader class to create shadow map
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderDefaultImplementation: public ShadowMapCreationShaderBaseImplementation
{
public:
	/**
	 * @return if supported by rendererBackend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapCreationShaderDefaultImplementation)

	/**
	 * Constructor
	 * @param rendererBackend renderer backend
	 */
	ShadowMapCreationShaderDefaultImplementation(RendererBackend* rendererBackend);

	/**
	 * Destructor
	 */
	~ShadowMapCreationShaderDefaultImplementation();

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;

};
