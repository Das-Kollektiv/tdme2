// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include <tdme/engine/PartitionOctTree_reset_2.h>

#include <tdme/engine/PartitionOctTree.h>
#include <tdme/engine/primitives/BoundingBox.h>

using tdme::engine::PartitionOctTree_reset_2;
using tdme::engine::PartitionOctTree;
using tdme::engine::primitives::BoundingBox;

PartitionOctTree_reset_2::PartitionOctTree_reset_2(PartitionOctTree *partitionOctTree)
	: Pool()
	, partitionOctTree(partitionOctTree)
{
}

BoundingBox* PartitionOctTree_reset_2::instantiate()
{
	return new BoundingBox();
}
