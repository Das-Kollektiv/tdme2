// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include <tdme/engine/PartitionOctTree_reset_2.h>

#include <tdme/engine/PartitionOctTree.h>
#include <tdme/engine/primitives/BoundingBox.h>

using tdme::engine::PartitionOctTree_reset_2;
using tdme::engine::PartitionOctTree;
using tdme::engine::primitives::BoundingBox;

PartitionOctTree_reset_2::PartitionOctTree_reset_2(PartitionOctTree *PartitionOctTree_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, PartitionOctTree_this(PartitionOctTree_this)
{
	clinit();
	ctor();
}

BoundingBox* PartitionOctTree_reset_2::instantiate()
{
	return new BoundingBox();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PartitionOctTree_reset_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PartitionOctTree_reset_2::getClass0()
{
	return class_();
}

