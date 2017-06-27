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


struct default_init_tag;
class tdme::engine::PartitionOctTree_reset_2
	: public Pool
{

public:
	typedef Pool super;

public: /* protected */
	BoundingBox* instantiate() override;

	// Generated

public:
	PartitionOctTree_reset_2(PartitionOctTree *PartitionOctTree_this);
	static ::java::lang::Class *class_();
	PartitionOctTree *PartitionOctTree_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class PartitionOctTree;
	friend class PartitionOctTree_PartitionTreeNode;
	friend class PartitionOctTree_reset_1;
	friend class PartitionOctTree_reset_3;
	friend class PartitionOctTree_reset_4;
	friend class PartitionOctTree_reset_5;
	friend class PartitionOctTree_reset_6;
};
