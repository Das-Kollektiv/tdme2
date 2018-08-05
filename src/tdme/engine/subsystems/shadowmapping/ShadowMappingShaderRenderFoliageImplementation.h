#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderBaseImplementation.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderBaseImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderFoliageImplementation;

/** 
 * Shadow mapping shader for render shadows pass
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderFoliageImplementation: public ShadowMappingShaderRenderBaseImplementation
{
public:
	/**
	 * @return if supported by renderer
	 * @param renderer
	 */
	static bool isSupported(GLRenderer* renderer);

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize() override;

	/**
	 * Public constructor
	 * @param renderer
	 */
	ShadowMappingShaderRenderFoliageImplementation(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	virtual ~ShadowMappingShaderRenderFoliageImplementation();
};
