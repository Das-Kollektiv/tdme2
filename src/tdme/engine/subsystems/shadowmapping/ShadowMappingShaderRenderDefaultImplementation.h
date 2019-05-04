#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderBaseImplementation.h>

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderBaseImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderDefaultImplementation;

/** 
 * Shadow mapping default shader to render shadows
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderDefaultImplementation: public ShadowMappingShaderRenderBaseImplementation
{
public:
	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(Renderer* renderer);

	// overriden methods
	virtual void initialize() override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	ShadowMappingShaderRenderDefaultImplementation(Renderer* renderer);

	/**
	 * Destructor
	 */
	virtual ~ShadowMappingShaderRenderDefaultImplementation();
};
