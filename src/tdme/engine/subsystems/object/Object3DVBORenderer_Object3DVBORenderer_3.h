// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DVBORenderer.java

#pragma once

#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesGroup.h>

using tdme::utils::Pool;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::object::TransparentRenderFacesGroup;


struct default_init_tag;
class tdme::engine::subsystems::object::Object3DVBORenderer_Object3DVBORenderer_3
	: public Pool
{

public:
	typedef Pool super;

public: /* protected */
	TransparentRenderFacesGroup* instantiate() override;

	// Generated

public:
	Object3DVBORenderer_Object3DVBORenderer_3(Object3DVBORenderer *Object3DVBORenderer_this);
	static ::java::lang::Class *class_();
	Object3DVBORenderer *Object3DVBORenderer_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class Object3DVBORenderer;
	friend class Object3DVBORenderer_1;
	friend class Object3DVBORenderer_Object3DVBORenderer_2;
};
