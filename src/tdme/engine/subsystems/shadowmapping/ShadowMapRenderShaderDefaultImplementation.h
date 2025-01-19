#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderBaseImplementation.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderBaseImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderDefaultImplementation;

/**
 * Shadow mapping default shader to render shadow map
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderDefaultImplementation: public ShadowMapRenderShaderBaseImplementation
{
public:
	/**
	 * @returns if supported by renderer backend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapRenderShaderDefaultImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	ShadowMapRenderShaderDefaultImplementation(RendererBackend* rendererBackend);

	/**
	 * Destructor
	 */
	virtual ~ShadowMapRenderShaderDefaultImplementation();

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;

};
