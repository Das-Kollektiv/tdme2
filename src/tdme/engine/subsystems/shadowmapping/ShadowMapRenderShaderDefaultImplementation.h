#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderBaseImplementation.h>

using std::string;

using tdme::engine::subsystems::renderer::Renderer;
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
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(Renderer* renderer);

	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapRenderShaderDefaultImplementation)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	ShadowMapRenderShaderDefaultImplementation(Renderer* renderer);

	/**
	 * Destructor
	 */
	virtual ~ShadowMapRenderShaderDefaultImplementation();

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void updateShaderParameters(Renderer* renderer, int contextIdx) override;

};
