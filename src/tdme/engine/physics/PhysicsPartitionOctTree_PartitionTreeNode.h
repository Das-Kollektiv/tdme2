
#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/physics/RigidBody.h>

using std::list;
using std::map;
using std::wstring;
using std::vector;

using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingBox;

/** 
 * Partition oct tree node
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode final
{
	float partitionSize {  };
	int32_t x {  };
	int32_t y {  };
	int32_t z {  };
	PhysicsPartitionOctTree_PartitionTreeNode* parent {  };
	BoundingBox bv {  };
	list<PhysicsPartitionOctTree_PartitionTreeNode> subNodes {  };
	map<wstring, PhysicsPartitionOctTree_PartitionTreeNode*> subNodesByCoordinate {  };
	vector<RigidBody*> partitionRidigBodies {  };
};
