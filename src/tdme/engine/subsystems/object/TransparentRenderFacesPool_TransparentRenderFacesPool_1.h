// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFacesPool.java

#pragma once

#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/subsystems/object/TransparentRenderFace.h>

using tdme::utils::Pool;
using tdme::engine::subsystems::object::TransparentRenderFace;
using tdme::engine::subsystems::object::TransparentRenderFacesPool;


struct default_init_tag;
class tdme::engine::subsystems::object::TransparentRenderFacesPool_TransparentRenderFacesPool_1
	: public Pool
{

public:
	typedef Pool super;

public: /* protected */
	TransparentRenderFace* instantiate() override;

	// Generated

public:
	TransparentRenderFacesPool_TransparentRenderFacesPool_1(TransparentRenderFacesPool *TransparentRenderFacesPool_this);
	static ::java::lang::Class *class_();
	TransparentRenderFacesPool *TransparentRenderFacesPool_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class TransparentRenderFacesPool;
};
