// Generated from /tdme/src/tdme/engine/PartitionOctTree.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::PartitionOctTree;
using tdme::engine::primitives::BoundingBox;
using tdme::utils::_HashMap;

using std::map;
using std::wstring;
using std::vector;

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
	vector<PartitionOctTree_PartitionTreeNode*> subNodes {  };
	map<wstring, PartitionOctTree_PartitionTreeNode*> subNodesByCoordinate {  };
	vector<Entity*> partitionEntities {  };

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
	friend class PartitionOctTree_reset_2;
	friend class PartitionOctTree_reset_3;
};
