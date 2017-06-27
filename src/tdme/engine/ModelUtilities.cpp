// Generated from /tdme/src/tdme/engine/ModelUtilities.java
#include <tdme/engine/ModelUtilities.h>

using tdme::engine::ModelUtilities;
ModelUtilities::ModelUtilities(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelUtilities::ModelUtilities()
	: ModelUtilities(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelUtilities::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.ModelUtilities", 26);
    return c;
}

java::lang::Class* ModelUtilities::getClass0()
{
	return class_();
}

