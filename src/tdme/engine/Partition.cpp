// Generated from /tdme/src/tdme/engine/Partition.java
#include <tdme/engine/Partition.h>

using tdme::engine::Partition;
Partition::Partition(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Partition::Partition()
	: Partition(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Partition::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.Partition", 21);
    return c;
}

java::lang::Class* Partition::getClass0()
{
	return class_();
}

