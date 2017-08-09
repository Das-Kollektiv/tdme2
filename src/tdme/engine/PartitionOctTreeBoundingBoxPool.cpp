// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include "PartitionOctTreeBoundingBoxPool.h"

#include <tdme/engine/PartitionOctTree.h>
#include <tdme/engine/primitives/BoundingBox.h>

using tdme::engine::PartitionOctTreeBoundingBoxPool;
using tdme::engine::PartitionOctTree;
using tdme::engine::primitives::BoundingBox;

PartitionOctTreeBoundingBoxPool::PartitionOctTreeBoundingBoxPool()
	: Pool()
{
}

BoundingBox* PartitionOctTreeBoundingBoxPool::instantiate()
{
	return new BoundingBox();
}
