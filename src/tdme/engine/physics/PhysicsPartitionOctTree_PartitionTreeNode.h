#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/physics/RigidBody.h>

using std::list;
using std::map;
using std::string;
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
	// partition size
	float partitionSize {  };
	// x, y, z position
	int32_t x {  };
	int32_t y {  };
	int32_t z {  };
	// parent node
	PhysicsPartitionOctTree_PartitionTreeNode* parent {  };
	// node bounding volume
	BoundingBox bv {  };
	// sub nodes of oct tree node
	list<PhysicsPartitionOctTree_PartitionTreeNode> subNodes {  };
	// sub node of oct tree nodes by partition coordinate, only used in root node
	map<string, PhysicsPartitionOctTree_PartitionTreeNode*> subNodesByCoordinate {  };
	// partition rigid bodies
	vector<RigidBody*> partitionRidigBodies {  };
};
