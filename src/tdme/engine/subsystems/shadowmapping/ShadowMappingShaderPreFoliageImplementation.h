#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreBaseImplementation.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreBaseImplementation;

/** 
 * Pre shadow mapping shader for render shadow map pass 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreFoliageImplementation: public ShadowMappingShaderPreBaseImplementation
{
public:
	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(GLRenderer* renderer);

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize() override;

/**
	 * Constructor
	 * @param renderer renderer
	 */
	ShadowMappingShaderPreFoliageImplementation(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMappingShaderPreFoliageImplementation();
};
