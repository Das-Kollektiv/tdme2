#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>
#include <tdme/utilities/Pool.h>

using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;
using tdme::utilities::Pool;

/**
 * Entity renderer transparent render faces node pool
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::EntityRenderer_TransparentRenderFacesGroupPool: public Pool<TransparentRenderFacesGroup*>
{
public:
	// forbid class copy
	CLASS_FORBID_COPY(EntityRenderer_TransparentRenderFacesGroupPool)

	/**
	 * Public constructor
	 */
	inline EntityRenderer_TransparentRenderFacesGroupPool() {}

protected:
	/**
	 * Instantiate
	 */
	inline TransparentRenderFacesGroup* instantiate() override {
		return new TransparentRenderFacesGroup();
	}

};
