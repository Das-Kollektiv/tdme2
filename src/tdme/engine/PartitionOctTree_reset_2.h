// Generated from /tdme/src/tdme/engine/PartitionOctTree.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/primitives/BoundingBox.h>

using tdme::utils::Pool;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::PartitionOctTree;
using tdme::engine::primitives::BoundingBox;

class tdme::engine::PartitionOctTree_reset_2
	: public Pool<BoundingBox*>
{
public: /* protected */
	BoundingBox* instantiate() override;

	// Generated

public:
	/**
	 * Public constructor
	 */
	PartitionOctTree_reset_2(PartitionOctTree* partitionOctTree);
	PartitionOctTree* partitionOctTree;

private:
	friend class PartitionOctTree;
	friend class PartitionOctTree_PartitionTreeNode;
	friend class PartitionOctTree_reset_3;
};
