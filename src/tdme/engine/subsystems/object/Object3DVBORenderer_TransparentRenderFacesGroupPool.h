// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DVBORenderer.java

#pragma once

#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesGroup.h>

using tdme::utils::Pool;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::object::TransparentRenderFacesGroup;

class tdme::engine::subsystems::object::Object3DVBORenderer_TransparentRenderFacesGroupPool
	: public Pool<TransparentRenderFacesGroup*>
{
public: /* protected */
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
