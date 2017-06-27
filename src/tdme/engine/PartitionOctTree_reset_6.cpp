// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include <tdme/engine/PartitionOctTree_reset_6.h>

#include <tdme/engine/PartitionOctTree.h>
#include <tdme/utils/Key.h>

using tdme::engine::PartitionOctTree_reset_6;
using tdme::engine::PartitionOctTree;
using tdme::utils::Key;

PartitionOctTree_reset_6::PartitionOctTree_reset_6(PartitionOctTree *PartitionOctTree_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, PartitionOctTree_this(PartitionOctTree_this)
{
	clinit();
	ctor();
}

Key* PartitionOctTree_reset_6::instantiate()
{
	return new Key();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PartitionOctTree_reset_6::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PartitionOctTree_reset_6::getClass0()
{
	return class_();
}

