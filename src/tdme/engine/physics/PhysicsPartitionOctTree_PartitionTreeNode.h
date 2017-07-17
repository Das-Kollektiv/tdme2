// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <java/lang/Object.h>
#include <tdme/engine/physics/RigidBody.h>

using std::vector;

using java::lang::Object;
using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingBox;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Partition oct tree node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode final
	: public Object
{

public:
	typedef Object super;

private:
	float partitionSize {  };
	int32_t x {  };
	int32_t y {  };
	int32_t z {  };
	PhysicsPartitionOctTree_PartitionTreeNode* parent {  };
	BoundingBox* bv {  };
	vector<PhysicsPartitionOctTree_PartitionTreeNode*> subNodes {  };
	_HashMap* subNodesByCoordinate {  };
	vector<RigidBody*> partitionRidigBodies {  };

	// Generated

public:
	PhysicsPartitionOctTree_PartitionTreeNode();
protected:
	PhysicsPartitionOctTree_PartitionTreeNode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class PhysicsPartitionOctTree;
	friend class PhysicsPartitionOctTree_reset_1;
	friend class PhysicsPartitionOctTree_reset_2;
	friend class PhysicsPartitionOctTree_reset_3;
	friend class PhysicsPartitionOctTree_reset_4;
	friend class PhysicsPartitionOctTree_reset_5;
	friend class PhysicsPartitionOctTree_reset_6;
};
