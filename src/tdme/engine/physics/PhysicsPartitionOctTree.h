// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/physics/PhysicsPartition.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>

using tdme::engine::physics::PhysicsPartition;
using java::lang::String;
using tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ArrayListIteratorMultiple;
using tdme::utils::Key;
using tdme::utils::Pool;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Partition oct tree implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::PhysicsPartitionOctTree final
	: public PhysicsPartition
{

public:
	typedef PhysicsPartition super;

private:
	Key* key {  };
	ArrayListIteratorMultiple<RigidBody*> rigidBodyIterator {  };
	BoundingBox* boundingBox {  };
	Vector3* halfExtension {  };
	Vector3* sideVector {  };
	Vector3* forwardVector {  };
	Vector3* upVector {  };
	Pool* boundingBoxPool {  };
	Pool* partitionTreeNodePool {  };
	Pool* rigidBodyPartitionNodesPool {  };
	Pool* keyPool {  };
	_HashMap* rigidBodyPartitionNodes {  };
	PhysicsPartitionOctTree_PartitionTreeNode* treeRoot {  };

public:
	static constexpr float PARTITION_SIZE_MIN { 4.0f };
	static constexpr float PARTITION_SIZE_MAX { 16.0f };
protected:

	/** 
	 * Constructor
	 */
	void ctor();

public: /* protected */

	/** 
	 * Reset
	 */
	void reset() override;

public:

	/** 
	 * Creates a partition
	 * @param parent
	 * @param x
	 * @param z
	 * @param partition size
	 * @return partition tree node
	 */
	PhysicsPartitionOctTree_PartitionTreeNode* createPartition(PhysicsPartitionOctTree_PartitionTreeNode* parent, int32_t x, int32_t y, int32_t z, float partitionSize);

public: /* protected */

	/** 
	 * Adds a object
	 * @param rigidBody
	 */
	void addRigidBody(RigidBody* rigidBody) override;

	/** 
	 * Updates a object
	 * @param rigidBody
	 */
	void updateRigidBody(RigidBody* rigidBody) override;

	/** 
	 * Removes a rigid body
	 * @param rigid body
	 */
	void removeRigidBody(RigidBody* rigidBody) override;

private:

	/** 
	 * Is partition empty
	 * @param node
	 * @return partition empty
	 */
	bool isPartitionNodeEmpty(PhysicsPartitionOctTree_PartitionTreeNode* node);

	/** 
	 * Remove partition node, should be empty
	 * @param node
	 */
	void removePartitionNode(PhysicsPartitionOctTree_PartitionTreeNode* node);

	/** 
	 * Do partition tree lookup
	 * @param node
	 * @param cbv
	 * @param cbvsIterator
	 */
	void addToPartitionTree(PhysicsPartitionOctTree_PartitionTreeNode* node, RigidBody* rigidBody, BoundingBox* cbv);

	/** 
	 * Add rigidBody to tree
	 */
	void addToPartitionTree(RigidBody* rigidBody, BoundingBox* cbv);

	/** 
	 * Do partition tree lookup for near entities to cbv
	 * @param node
	 * @param cbv
	 * @param rigidBody iterator
	 */
	int32_t doPartitionTreeLookUpNearEntities(PhysicsPartitionOctTree_PartitionTreeNode* node, BoundingBox* cbv, ArrayListIteratorMultiple<RigidBody*>& rigidBodyIterator);

public:

	/** 
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	ArrayListIteratorMultiple<RigidBody*>* getObjectsNearTo(BoundingVolume* cbv) override;

	/** 
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	ArrayListIteratorMultiple<RigidBody*>* getObjectsNearTo(Vector3* center) override;

	/** 
	 * To string
	 * @param indent
	 * @param node
	 * @return string representation of node
	 */
	String* toString(String* indent, PhysicsPartitionOctTree_PartitionTreeNode* node);
	String* toString() override;

	// Generated

public: /* protected */
	PhysicsPartitionOctTree();
protected:
	PhysicsPartitionOctTree(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class PhysicsPartitionOctTree_PartitionTreeNode;
	friend class PhysicsPartitionOctTree_reset_1;
	friend class PhysicsPartitionOctTree_reset_2;
	friend class PhysicsPartitionOctTree_reset_3;
	friend class PhysicsPartitionOctTree_reset_4;
	friend class PhysicsPartitionOctTree_reset_5;
	friend class PhysicsPartitionOctTree_reset_6;
};
