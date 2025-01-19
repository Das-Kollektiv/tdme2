#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderBaseImplementation.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderBaseImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderTreeImplementation;

/**
 * Shadow mapping tree shader to render shadow map
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapRenderShaderTreeImplementation: public ShadowMapRenderShaderBaseImplementation
{
private:
	int32_t uniformSpeed { -1 };

public:
	/**
	 * @return if supported by rendererBackend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapRenderShaderTreeImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	ShadowMapRenderShaderTreeImplementation(RendererBackend* rendererBackend);

	/**
	 * Destructor
	 */
	virtual ~ShadowMapRenderShaderTreeImplementation();

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;

};
