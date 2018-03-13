
#pragma once

#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>

using tdme::utils::Pool;
using tdme::engine::subsystems::rendering::Object3DVBORenderer;
using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;

class tdme::engine::subsystems::rendering::Object3DVBORenderer_TransparentRenderFacesGroupPool
	: public Pool<TransparentRenderFacesGroup*>
{
protected:
	/**
	 * Instantiate
	 */
	TransparentRenderFacesGroup* instantiate() override;
public:
	/**
	 * Public constructor
	 */
	Object3DVBORenderer_TransparentRenderFacesGroupPool();
};
