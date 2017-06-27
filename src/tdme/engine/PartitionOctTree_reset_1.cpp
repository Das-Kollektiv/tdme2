// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include <tdme/engine/PartitionOctTree_reset_1.h>

#include <tdme/engine/PartitionOctTree.h>
#include <tdme/utils/_ArrayList.h>

using tdme::engine::PartitionOctTree_reset_1;
using tdme::engine::PartitionOctTree;
using tdme::utils::_ArrayList;

PartitionOctTree_reset_1::PartitionOctTree_reset_1(PartitionOctTree *PartitionOctTree_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, PartitionOctTree_this(PartitionOctTree_this)
{
	clinit();
	ctor();
}

_ArrayList* PartitionOctTree_reset_1::instantiate()
{
	return new _ArrayList();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PartitionOctTree_reset_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PartitionOctTree_reset_1::getClass0()
{
	return class_();
}

