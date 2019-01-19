#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Lighting shader implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::LightingShaderFrontImplementation: public LightingShaderBaseImplementation
{
public:

	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(GLRenderer* renderer);

	// overriden methods
	virtual void initialize() override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	LightingShaderFrontImplementation(GLRenderer* renderer);
};
