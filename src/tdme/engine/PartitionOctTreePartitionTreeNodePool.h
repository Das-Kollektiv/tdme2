// Generated from /tdme/src/tdme/engine/PartitionOctTree.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/PartitionOctTree_PartitionTreeNode.h>

using tdme::utils::Pool;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::PartitionOctTree;

class tdme::engine::PartitionOctTreePartitionTreeNodePool
	: public Pool<PartitionOctTree_PartitionTreeNode*>
{
public: /* protected */
	PartitionOctTree_PartitionTreeNode* instantiate() override;

public:
	/**
	 * Public constructor
	 */
	PartitionOctTreePartitionTreeNodePool();

private:
	friend class PartitionOctTree;
	friend class PartitionOctTree_PartitionTreeNode;
	friend class PartitionOctTreeBoundingBoxPool;
};
