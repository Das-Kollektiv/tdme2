// Generated from /tdme/src/tdme/engine/PartitionOctTree.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/_ArrayList.h>

using tdme::utils::Pool;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::PartitionOctTree;
using tdme::utils::_ArrayList;


struct default_init_tag;
class tdme::engine::PartitionOctTree_reset_1
	: public Pool
{

public:
	typedef Pool super;

public: /* protected */
	_ArrayList* instantiate() override;

	// Generated

public:
	PartitionOctTree_reset_1(PartitionOctTree *PartitionOctTree_this);
	static ::java::lang::Class *class_();
	PartitionOctTree *PartitionOctTree_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class PartitionOctTree;
	friend class PartitionOctTree_PartitionTreeNode;
	friend class PartitionOctTree_reset_2;
	friend class PartitionOctTree_reset_3;
	friend class PartitionOctTree_reset_4;
	friend class PartitionOctTree_reset_5;
	friend class PartitionOctTree_reset_6;
};
