// Generated from /tdme/src/tdme/engine/PartitionOctTree.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/PartitionOctTree_PartitionTreeNode.h>

using tdme::utils::Pool;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::PartitionOctTree;

class tdme::engine::PartitionOctTree_reset_3
	: public Pool<PartitionOctTree_PartitionTreeNode*>
{
public: /* protected */
	PartitionOctTree_PartitionTreeNode* instantiate() override;

public:
	/**
	 * Public constructor
	 */
	PartitionOctTree_reset_3(PartitionOctTree* partitionOctTree);
	PartitionOctTree* partitionOctTree;;

private:
	friend class PartitionOctTree;
	friend class PartitionOctTree_PartitionTreeNode;
	friend class PartitionOctTree_reset_2;
};
