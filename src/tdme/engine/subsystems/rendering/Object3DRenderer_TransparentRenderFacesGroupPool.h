#pragma once

#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>

using tdme::utils::Pool;
using tdme::engine::subsystems::rendering::Object3DRenderer;
using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;

/**
 * Transparent render faces group pool
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::Object3DRenderer_TransparentRenderFacesGroupPool: public Pool<TransparentRenderFacesGroup*>
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
	Object3DRenderer_TransparentRenderFacesGroupPool();
};
