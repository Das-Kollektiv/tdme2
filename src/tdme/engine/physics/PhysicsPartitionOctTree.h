#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/physics/PhysicsPartition.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/utils/VectorIteratorMultiple.h>
#include <tdme/utils/Pool.h>

using std::map;
using std::vector;
using std::string;
using std::to_string;

using tdme::engine::physics::CollisionDetection;
using tdme::engine::physics::PhysicsPartition;
using tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;
using tdme::utils::Pool;

/** 
 * Partition oct tree implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::PhysicsPartitionOctTree final
	: public PhysicsPartition
{
	friend class PhysicsPartitionOctTree_PartitionTreeNode;

private:
	static constexpr float PARTITION_SIZE_MIN { 64.0f };
	static constexpr float PARTITION_SIZE_MAX { 512.0f };

	VectorIteratorMultiple<RigidBody*> rigidBodyIterator {  };
	map<string, vector<PhysicsPartitionOctTree_PartitionTreeNode*>> rigidBodyPartitionNodes {  };
	PhysicsPartitionOctTree_PartitionTreeNode treeRoot {  };

	/** 
	 * Reset
	 */
	void reset() override;

	/** 
	 * Is partition empty
	 * @param node
	 * @return partition empty
	 */
	inline bool isPartitionNodeEmpty(PhysicsPartitionOctTree_PartitionTreeNode* node) {
		// lowest level node has objects attached?
		if (node->partitionRidigBodies.size() > 0) {
			return false;
		} else {
			// otherwise check top level node sub nodes
			for (auto& subNode: node->subNodes) {
				if (isPartitionNodeEmpty(&subNode) == false)
					return false;
			}
			return true;
		}
	}

	/** 
	 * Remove partition node, should be empty
	 * @param node
	 */
	inline void removePartitionNode(PhysicsPartitionOctTree_PartitionTreeNode* node) {
		// lowest level node has objects attached?
		if (node->partitionRidigBodies.size() > 0) {
			Console::println(string("PartitionOctTree::removePartitionNode(): partition has objects attached!!!"));
			node->partitionRidigBodies.clear();
		} else {
			// otherwise check top level node sub nodes
			for (auto& subNode: node->subNodes) {
				removePartitionNode(&subNode);
			}
			// clear sub nodes
			node->subNodes.clear();
		}
	}

	/** 
	 * Do partition tree lookup
	 * @param node
	 * @param rigid body
	 */
	inline void addToPartitionTree(PhysicsPartitionOctTree_PartitionTreeNode* node, RigidBody* rigidBody) {
		// check if given cbv collides with partition node bv
		if (CollisionDetection::doCollideAABBvsAABBFast(&node->bv, rigidBody->cbv->getBoundingBox()) == false) {
			return;
		}
		// if this node already has the partition cbvs add it to the iterator
		if (node->partitionSize == PARTITION_SIZE_MIN) {
			node->partitionRidigBodies.push_back(rigidBody);
			rigidBodyPartitionNodes[rigidBody->getId()].push_back(node);
		} else {
			// otherwise check sub nodes
			for (auto& subNode: node->subNodes) {
				addToPartitionTree(&subNode, rigidBody);
			}
		}
	}

	/** 
	 * Add rigidBody to tree
	 */
	inline void addToPartitionTree(RigidBody* rigidBody) {
		for (auto& subNode: treeRoot.subNodes) {
			addToPartitionTree(&subNode,rigidBody);
		}
	}

	/** 
	 * Do partition tree lookup for near entities to cbv
	 * @param node
	 * @param cbv
	 * @param rigidBody iterator
	 */
	inline int32_t doPartitionTreeLookUpNearEntities(PhysicsPartitionOctTree_PartitionTreeNode* node, BoundingBox* cbv) {
		// check if given cbv collides with partition node bv
		if (CollisionDetection::doCollideAABBvsAABBFast(cbv, &node->bv) == false) {
			return 1;
		}
		// if this node already has the partition cbvs add it to the iterator
		if (node->partitionRidigBodies.size() > 0) {
			rigidBodyIterator.addVector(&node->partitionRidigBodies);
			return 1;
		} else {
			// otherwise check sub nodes
			auto lookUps = 1;
			for (auto& subNode: node->subNodes) {
				lookUps += doPartitionTreeLookUpNearEntities(&subNode, cbv);
			}
			return lookUps;
		}
	}

	/**
	 * Adds a object
	 * @param rigidBody
	 */
	void addRigidBody(RigidBody* rigidBody) override;

	/**
	 * Updates a object
	 * @param rigidBody
	 */
	inline void updateRigidBody(RigidBody* rigidBody) override {
		addRigidBody(rigidBody);
	}

	/**
	 * Removes a rigid body
	 * @param rigid body
	 */
	void removeRigidBody(RigidBody* rigidBody) override;

public:

	/**
	 * Creates a partition
	 * @param parent
	 * @param x
	 * @param z
	 * @param partition size
	 * @return partition tree node
	 */
	void createPartition(PhysicsPartitionOctTree_PartitionTreeNode* parent, int32_t x, int32_t y, int32_t z, float partitionSize) {
		PhysicsPartitionOctTree_PartitionTreeNode node;
		node.partitionSize = partitionSize;
		node.x = x;
		node.y = y;
		node.z = z;
		node.parent = parent;
		node.bv.getMin().set(x * partitionSize, y * partitionSize, z * partitionSize);
		node.bv.getMax().set(x * partitionSize + partitionSize, y * partitionSize + partitionSize, z * partitionSize + partitionSize);
		node.bv.update();
		// register in parent sub nodes
		parent->subNodes.push_back(node);
		PhysicsPartitionOctTree_PartitionTreeNode* storedNode = &parent->subNodes.back();
		// register in parent sub nodes by coordinate, if root node
		parent->subNodesByCoordinate[to_string(node.x) + "," + to_string(node.y) + "," + to_string(node.z)] = storedNode;
		// create sub nodes
		if (partitionSize > PARTITION_SIZE_MIN) {
			for (auto _y = 0; _y < 2; _y++)
			for (auto _x = 0; _x < 2; _x++)
			for (auto _z = 0; _z < 2; _z++) {
				createPartition(
					storedNode,
					static_cast< int32_t >(((x * partitionSize) / (partitionSize / 2.0f))) + _x,
					static_cast< int32_t >(((y * partitionSize) / (partitionSize / 2.0f))) + _y,
					static_cast< int32_t >(((z * partitionSize) / (partitionSize / 2.0f))) + _z,
					partitionSize / 2.0f
				);
			}
		}
	}

	/**
	 * Get objects near to rigid body
	 * @param cbv
	 * @return objects near to cbv
	 */
	VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(RigidBody* rigidBody) override;

	/**
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(BoundingVolume* cbv) override;

	/** 
	 * Get objects near to
	 * @param center
	 * @param half extension
	 * @return objects near to cbv
	 */
	VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(const Vector3& center, const Vector3& halfExtension = Vector3(0.1f, 0.1f, 0.01f)) override;

	/**
	 * Public constructor
	 */
	PhysicsPartitionOctTree();
};
