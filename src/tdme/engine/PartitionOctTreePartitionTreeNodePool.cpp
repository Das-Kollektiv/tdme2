// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include <tdme/engine/PartitionOctTreePartitionTreeNodePool.h>

#include <tdme/engine/PartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/PartitionOctTree.h>

using tdme::engine::PartitionOctTreePartitionTreeNodePool;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::PartitionOctTree;

PartitionOctTreePartitionTreeNodePool::PartitionOctTreePartitionTreeNodePool()
	: Pool()
{
}

PartitionOctTree_PartitionTreeNode* PartitionOctTreePartitionTreeNodePool::instantiate()
{
	return new PartitionOctTree_PartitionTreeNode();
}

