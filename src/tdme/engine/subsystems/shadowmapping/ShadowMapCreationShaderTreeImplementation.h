#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderBaseImplementation.h>

using std::string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderBaseImplementation;

/**
 * Shadow mapping tree shader class to create shadow map
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderTreeImplementation: public ShadowMapCreationShaderBaseImplementation
{
private:
	int32_t uniformSpeed { -1 };

public:
	/**
	 * @return if supported by renderer
	 * @param renderer renderer
	 */
	static bool isSupported(Renderer* renderer);

	// forbid class copy
	CLASS_FORBID_COPY(ShadowMapCreationShaderTreeImplementation)

	/**
	 * Constructor
	 * @param renderer renderer
	 */
	ShadowMapCreationShaderTreeImplementation(Renderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMapCreationShaderTreeImplementation();

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void updateShaderParameters(Renderer* renderer, int contextIdx) override;

};
