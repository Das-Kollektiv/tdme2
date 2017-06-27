// Generated from /tdme/src/tdme/engine/PartitionOctTree.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::PartitionOctTree;
using tdme::engine::primitives::BoundingBox;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Partition oct tree node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::PartitionOctTree_PartitionTreeNode
	: public virtual Object
{

public:
	typedef Object super;

private:
	float partitionSize {  };
	int32_t x {  };
	int32_t y {  };
	int32_t z {  };
	PartitionOctTree_PartitionTreeNode* parent {  };
	BoundingBox* bv {  };
	_ArrayList* subNodes {  };
	_HashMap* subNodesByCoordinate {  };
	_ArrayList* partitionEntities {  };

	// Generated

public:
	PartitionOctTree_PartitionTreeNode();
protected:
	PartitionOctTree_PartitionTreeNode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class PartitionOctTree;
	friend class PartitionOctTree_reset_1;
	friend class PartitionOctTree_reset_2;
	friend class PartitionOctTree_reset_3;
	friend class PartitionOctTree_reset_4;
	friend class PartitionOctTree_reset_5;
	friend class PartitionOctTree_reset_6;
};
