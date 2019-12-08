#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPreBaseImplementation.h>

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::earlyzrejection::EZRShaderPreBaseImplementation;

/** 
 * Early z rejection tre shader class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::earlyzrejection::EZRShaderPreTreeImplementation: public EZRShaderPreBaseImplementation
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
	 * Constructor
	 * @param renderer renderer
	 */
	EZRShaderPreTreeImplementation(Renderer* renderer);

	/**
	 * Destructor
	 */
	~EZRShaderPreTreeImplementation();
};
