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

class tdme::engine::PartitionOctTreeBoundingBoxPool
	: public Pool<BoundingBox*>
{
public: /* protected */
	BoundingBox* instantiate() override;

public:
	/**
	 * Public constructor
	 */
	PartitionOctTreeBoundingBoxPool();
};
