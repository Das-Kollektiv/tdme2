// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include <tdme/engine/PartitionOctTree_reset_3.h>

#include <tdme/engine/PartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/PartitionOctTree.h>

using tdme::engine::PartitionOctTree_reset_3;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::PartitionOctTree;

PartitionOctTree_reset_3::PartitionOctTree_reset_3(PartitionOctTree *PartitionOctTree_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, PartitionOctTree_this(PartitionOctTree_this)
{
	clinit();
	ctor();
}

PartitionOctTree_PartitionTreeNode* PartitionOctTree_reset_3::instantiate()
{
	return new PartitionOctTree_PartitionTreeNode();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PartitionOctTree_reset_3::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PartitionOctTree_reset_3::getClass0()
{
	return class_();
}

