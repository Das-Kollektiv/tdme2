#pragma once

#include <list>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/physics/RigidBody.h>

using std::list;
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
	// node bounding volume
	BoundingBox bv {  };
	// parent node
	PhysicsPartitionOctTree_PartitionTreeNode* parent {  };
	// sub nodes of oct tree node
	list<PhysicsPartitionOctTree_PartitionTreeNode> subNodes {  };
	// partition rigid bodies
	vector<RigidBody*> partitionRidigBodies {  };
};
