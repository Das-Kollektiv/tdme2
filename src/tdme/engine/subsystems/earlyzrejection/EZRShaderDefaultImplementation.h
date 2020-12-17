#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderBaseImplementation.h>

using std::string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::earlyzrejection::EZRShaderBaseImplementation;

/**
 * Early z rejection default shader class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::earlyzrejection::EZRShaderDefaultImplementation: public EZRShaderBaseImplementation
{
public:
	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(Renderer* renderer);

	/**
	 * Constructor
	 * @param renderer renderer
	 */
	EZRShaderDefaultImplementation(Renderer* renderer);

	/**
	 * Destructor
	 */
	~EZRShaderDefaultImplementation();

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;

};
