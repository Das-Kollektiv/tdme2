
#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/utils/fwd-tdme.h>

using tdme::engine::PartitionOctTree;
using tdme::engine::primitives::BoundingBox;

using std::list;
using std::map;
using std::wstring;
using std::vector;

/** 
 * Partition oct tree node
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::PartitionOctTree_PartitionTreeNode
{
	float partitionSize {  };
	int32_t x {  };
	int32_t y {  };
	int32_t z {  };
	PartitionOctTree_PartitionTreeNode* parent {  };
	BoundingBox bv {  };
	list<PartitionOctTree_PartitionTreeNode> subNodes {  };
	map<wstring, PartitionOctTree_PartitionTreeNode*> subNodesByCoordinate {  };
	vector<Entity*> partitionEntities {  };
};
