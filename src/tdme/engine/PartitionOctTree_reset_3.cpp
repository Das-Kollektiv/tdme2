// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include <tdme/engine/PartitionOctTree_reset_3.h>

#include <tdme/engine/PartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/PartitionOctTree.h>

using tdme::engine::PartitionOctTree_reset_3;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::PartitionOctTree;

PartitionOctTree_reset_3::PartitionOctTree_reset_3(PartitionOctTree* partitionOctTree)
	: Pool()
	, partitionOctTree(partitionOctTree)
{
}

PartitionOctTree_PartitionTreeNode* PartitionOctTree_reset_3::instantiate()
{
	return new PartitionOctTree_PartitionTreeNode();
}

