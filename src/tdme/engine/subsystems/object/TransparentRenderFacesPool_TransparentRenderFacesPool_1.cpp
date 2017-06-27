// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFacesPool.java
#include <tdme/engine/subsystems/object/TransparentRenderFacesPool_TransparentRenderFacesPool_1.h>

#include <tdme/engine/subsystems/object/TransparentRenderFace.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesPool.h>

using tdme::engine::subsystems::object::TransparentRenderFacesPool_TransparentRenderFacesPool_1;
using tdme::engine::subsystems::object::TransparentRenderFace;
using tdme::engine::subsystems::object::TransparentRenderFacesPool;

TransparentRenderFacesPool_TransparentRenderFacesPool_1::TransparentRenderFacesPool_TransparentRenderFacesPool_1(TransparentRenderFacesPool *TransparentRenderFacesPool_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, TransparentRenderFacesPool_this(TransparentRenderFacesPool_this)
{
	clinit();
	ctor();
}

TransparentRenderFace* TransparentRenderFacesPool_TransparentRenderFacesPool_1::instantiate()
{
	return new TransparentRenderFace();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TransparentRenderFacesPool_TransparentRenderFacesPool_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* TransparentRenderFacesPool_TransparentRenderFacesPool_1::getClass0()
{
	return class_();
}

