#include <tdme/engine/physics/PhysicsPartitionOctTree.h>

#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <vector>

#include <tdme/math/Math.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/VectorIteratorMultiple.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/Console.h>

using std::find;
using std::list;
using std::map;
using std::remove;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::math::Math;
using tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;
using tdme::utils::Pool;
using tdme::utils::Console;

constexpr float PhysicsPartitionOctTree::PARTITION_SIZE_MIN;

constexpr float PhysicsPartitionOctTree::PARTITION_SIZE_MAX;

PhysicsPartitionOctTree::PhysicsPartitionOctTree()
{
	reset();
}

void PhysicsPartitionOctTree::reset()
{
	rigidBodyPartitionNodes.clear();
	treeRootSubNodesByCoordinate.clear();
	this->treeRoot.partitionSize = -1;
	this->treeRoot.x = -1;
	this->treeRoot.y = -1;
	this->treeRoot.z = -1;
	this->treeRoot.parent = nullptr;
}

void PhysicsPartitionOctTree::addRigidBody(RigidBody* rigidBody)
{
	// update if already exists
	vector<PhysicsPartitionOctTree_PartitionTreeNode*>* thisRigidBodyPartitions = nullptr;
	auto rigidBodyPartitionNodesIt = rigidBodyPartitionNodes.find(rigidBody->getId());
	if (rigidBodyPartitionNodesIt != rigidBodyPartitionNodes.end()) {
		thisRigidBodyPartitions = &rigidBodyPartitionNodesIt->second;
	}
	if (thisRigidBodyPartitions != nullptr && thisRigidBodyPartitions->empty() == false) {
		removeRigidBody(rigidBody);
	}
	// determine max first level partition dimension / find, create root nodes if not exists
	auto boundingBox = rigidBody->cbv->getBoundingBox();
	auto minXPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin().getX() / PARTITION_SIZE_MAX));
	auto minYPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin().getY() / PARTITION_SIZE_MAX));
	auto minZPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin().getZ() / PARTITION_SIZE_MAX));
	auto maxXPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax().getX() / PARTITION_SIZE_MAX));
	auto maxYPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax().getY() / PARTITION_SIZE_MAX));
	auto maxZPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax().getZ() / PARTITION_SIZE_MAX));
	for (auto yPartition = minYPartition; yPartition <= maxYPartition; yPartition++) 
	for (auto xPartition = minXPartition; xPartition <= maxXPartition; xPartition++)
	for (auto zPartition = minZPartition; zPartition <= maxZPartition; zPartition++) {
		// check if first level node has been created already
		auto nodeIt = treeRootSubNodesByCoordinate.find(to_string(xPartition) + "," + to_string(yPartition) + "," + to_string(zPartition));
		if (nodeIt == treeRootSubNodesByCoordinate.end()) {
			auto treeRootNodeSubNode = createPartition(&treeRoot, xPartition, yPartition, zPartition, PARTITION_SIZE_MAX);
			// sub node of oct tree root sub nodes by partition coordinate
			treeRootSubNodesByCoordinate[to_string(treeRootNodeSubNode->x) + "," + to_string(treeRootNodeSubNode->y) + "," + to_string(treeRootNodeSubNode->z)] = treeRootNodeSubNode;
		}
	}
	// add rigid body to tree
	addToPartitionTree(rigidBody);
}

void PhysicsPartitionOctTree::removeRigidBody(RigidBody* rigidBody)
{
	auto rigidBodyPartitionsVectorIt = rigidBodyPartitionNodes.find(rigidBody->getId());
	vector<PhysicsPartitionOctTree_PartitionTreeNode*>* rigidBodyPartitionsVector = nullptr;
	if (rigidBodyPartitionsVectorIt != rigidBodyPartitionNodes.end()) {
		rigidBodyPartitionsVector = &rigidBodyPartitionsVectorIt->second;
	}
	if (rigidBodyPartitionsVector == nullptr || rigidBodyPartitionsVector->empty() == true) {
		Console::println(
			string("PartitionOctTree::removeRigidBody(): '") +
			rigidBody->getId() +
			string("' not registered")
		);
		return;
	}
	while (rigidBodyPartitionsVector->size() > 0) {
		// remove object from assigned partitions
		auto lastIdx = rigidBodyPartitionsVector->size() - 1;
		auto partitionTreeNode = rigidBodyPartitionsVector->at(lastIdx);
		auto& partitionRigidBody = partitionTreeNode->partitionRidigBodies;
		partitionRigidBody.erase(remove(partitionRigidBody.begin(), partitionRigidBody.end(), rigidBody), partitionRigidBody.end());
		rigidBodyPartitionsVector->erase(rigidBodyPartitionsVector->begin() + lastIdx);
		// check if whole top level partition is empty
		if (partitionRigidBody.empty() == true) {
			auto rootPartitionTreeNode = partitionTreeNode->parent->parent;
			if (isPartitionNodeEmpty(rootPartitionTreeNode) == true) {
				removePartitionNode(rootPartitionTreeNode);
				for (auto treeRootSubNodeIt = treeRoot.subNodes.begin(); treeRootSubNodeIt != treeRoot.subNodes.end(); ++treeRootSubNodeIt) {
					if ((void*)&treeRootSubNodeIt == (void*)rootPartitionTreeNode) {
						treeRoot.subNodes.erase(treeRootSubNodeIt);
						break;
					}
				}
				treeRootSubNodesByCoordinate.erase(
					to_string(rootPartitionTreeNode->x) + "," + to_string(rootPartitionTreeNode->y) + "," + to_string(rootPartitionTreeNode->z)
				);
			}
		}
	}
	rigidBodyPartitionNodes.erase(rigidBodyPartitionsVectorIt);
}

VectorIteratorMultiple<RigidBody*>* PhysicsPartitionOctTree::getObjectsNearTo(RigidBody* rigidBody) {
	rigidBodyIterator.clear();
	auto rigidBodyPartitionNodesIt = rigidBodyPartitionNodes.find(rigidBody->getId());
	if (rigidBodyPartitionNodesIt != rigidBodyPartitionNodes.end()) {
		for (auto& partitionTreeNode: rigidBodyPartitionNodesIt->second) {
			rigidBodyIterator.addVector(&partitionTreeNode->partitionRidigBodies);
		}
	}
	return &rigidBodyIterator;
}

VectorIteratorMultiple<RigidBody*>* PhysicsPartitionOctTree::getObjectsNearTo(BoundingVolume* cbv)
{
	rigidBodyIterator.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpNearEntities(&subNode, cbv->getBoundingBox());
	}
	return &rigidBodyIterator;
}

VectorIteratorMultiple<RigidBody*>* PhysicsPartitionOctTree::getObjectsNearTo(const Vector3& center, const Vector3& halfExtension)
{
	BoundingBox boundingBox;
	boundingBox.getMin().set(center);
	boundingBox.getMin().sub(halfExtension);
	boundingBox.getMax().set(center);
	boundingBox.getMax().add(halfExtension);
	boundingBox.update();
	rigidBodyIterator.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpNearEntities(&subNode, &boundingBox);
	}
	return &rigidBodyIterator;
}

