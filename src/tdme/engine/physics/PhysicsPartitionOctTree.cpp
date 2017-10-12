#include <tdme/engine/physics/PhysicsPartitionOctTree.h>

#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <vector>

#include <tdme/math/Math.h>
#include <tdme/engine/physics/CollisionDetection.h>
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
using std::wstring;
using std::to_wstring;
using std::vector;

using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::math::Math;
using tdme::engine::physics::CollisionDetection;
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
	this->sideVector.set(1.0f, 0.0f, 0.0f);
	this->upVector.set(0.0f, 1.0f, 0.0f);
	this->forwardVector.set(0.0f, 0.0f, 1.0f);
	reset();
}

void PhysicsPartitionOctTree::reset()
{
	this->treeRoot.partitionSize = -1;
	this->treeRoot.x = -1;
	this->treeRoot.y = -1;
	this->treeRoot.z = -1;
	this->treeRoot.parent = nullptr;
}

PhysicsPartitionOctTree_PartitionTreeNode* PhysicsPartitionOctTree::createPartition(PhysicsPartitionOctTree_PartitionTreeNode* parent, int32_t x, int32_t y, int32_t z, float partitionSize)
{
	PhysicsPartitionOctTree_PartitionTreeNode node;
	node.partitionSize = partitionSize;
	node.x = x;
	node.y = y;
	node.z = z;
	node.parent = parent;
	node.bv.getMin().set(x * partitionSize, y * partitionSize, z * partitionSize);
	node.bv.getMax().set(x * partitionSize + partitionSize, y * partitionSize + partitionSize, z * partitionSize + partitionSize);
	node.bv.update();
	parent->subNodes.push_back(node);
	PhysicsPartitionOctTree_PartitionTreeNode* storedNode = &parent->subNodes.back();
	if (parent == &treeRoot) {
		parent->subNodesByCoordinate[to_wstring(node.x) + L"," + to_wstring(node.y) + L"," + to_wstring(node.z)] = storedNode;
	}
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
	return storedNode;
}

void PhysicsPartitionOctTree::addRigidBody(RigidBody* rigidBody)
{
	vector<PhysicsPartitionOctTree_PartitionTreeNode*>* thisRigidBodyPartitions = nullptr;
	auto rigidBodyPartitionNodesIt = rigidBodyPartitionNodes.find(rigidBody->getId());
	if (rigidBodyPartitionNodesIt != rigidBodyPartitionNodes.end()) {
		thisRigidBodyPartitions = &rigidBodyPartitionNodesIt->second;
	}
	if (thisRigidBodyPartitions != nullptr && thisRigidBodyPartitions->empty() == false) {
		removeRigidBody(rigidBody);
	}
	auto cbv = rigidBody->cbv;
	auto& center = cbv->getCenter();
	halfExtension.set(cbv->computeDimensionOnAxis(sideVector) + 0.2f, cbv->computeDimensionOnAxis(upVector) + 0.2f, cbv->computeDimensionOnAxis(forwardVector) + 0.2f).scale(0.5f);
	boundingBox.getMin().set(center);
	boundingBox.getMin().sub(halfExtension);
	boundingBox.getMax().set(center);
	boundingBox.getMax().add(halfExtension);
	boundingBox.update();
	auto minXPartition = static_cast< int32_t >(Math::floor(boundingBox.getMin().getX() / PARTITION_SIZE_MAX));
	auto minYPartition = static_cast< int32_t >(Math::floor(boundingBox.getMin().getY() / PARTITION_SIZE_MAX));
	auto minZPartition = static_cast< int32_t >(Math::floor(boundingBox.getMin().getZ() / PARTITION_SIZE_MAX));
	auto maxXPartition = static_cast< int32_t >(Math::floor(boundingBox.getMax().getX() / PARTITION_SIZE_MAX));
	auto maxYPartition = static_cast< int32_t >(Math::floor(boundingBox.getMax().getY() / PARTITION_SIZE_MAX));
	auto maxZPartition = static_cast< int32_t >(Math::floor(boundingBox.getMax().getZ() / PARTITION_SIZE_MAX));
	for (auto yPartition = minYPartition; yPartition <= maxYPartition; yPartition++) 
	for (auto xPartition = minXPartition; xPartition <= maxXPartition; xPartition++)
	for (auto zPartition = minZPartition; zPartition <= maxZPartition; zPartition++) {
		auto nodeIt = treeRoot.subNodesByCoordinate.find(to_wstring(xPartition) + L"," + to_wstring(yPartition) + L"," + to_wstring(zPartition));
		if (nodeIt == treeRoot.subNodesByCoordinate.end()) {
			createPartition(&treeRoot, xPartition, yPartition, zPartition, PARTITION_SIZE_MAX);
		}
	}

	addToPartitionTree(rigidBody, &boundingBox);
}

void PhysicsPartitionOctTree::updateRigidBody(RigidBody* rigidBody)
{
	addRigidBody(rigidBody);
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
			wstring(L"PartitionOctTree::removeRigidBody(): '") +
			rigidBody->getId() +
			wstring(L"' not registered")
		);
		return;
	}
	while (rigidBodyPartitionsVector->size() > 0) {
		auto lastIdx = rigidBodyPartitionsVector->size() - 1;
		auto partitionTreeNode = rigidBodyPartitionsVector->at(lastIdx);
		auto& partitionRigidBody = partitionTreeNode->partitionRidigBodies;
		partitionRigidBody.erase(remove(partitionRigidBody.begin(), partitionRigidBody.end(), rigidBody), partitionRigidBody.end());
		rigidBodyPartitionsVector->erase(rigidBodyPartitionsVector->begin() + lastIdx);
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
				treeRoot.subNodesByCoordinate.erase(
					to_wstring(rootPartitionTreeNode->x) + L"," + to_wstring(rootPartitionTreeNode->y) + L"," + to_wstring(rootPartitionTreeNode->z)
				);
			}
		}
	}
	rigidBodyPartitionNodes.erase(rigidBodyPartitionsVectorIt);
}

bool PhysicsPartitionOctTree::isPartitionNodeEmpty(PhysicsPartitionOctTree_PartitionTreeNode* node)
{
	if (node->partitionRidigBodies.size() > 0) {
		return false;
	} else {
		for (auto& subNode: node->subNodes) {
			if (isPartitionNodeEmpty(&subNode) == false)
				return false;
		}
		return true;
	}
}

void PhysicsPartitionOctTree::removePartitionNode(PhysicsPartitionOctTree_PartitionTreeNode* node)
{
	if (node->partitionRidigBodies.size() > 0) {
		Console::println(wstring(L"PartitionOctTree::removePartitionNode(): partition has objects attached!!!"));
		node->partitionRidigBodies.clear();
	} else {
		for (auto& subNode: node->subNodes) {
			removePartitionNode(&subNode);
		}
		node->subNodes.clear();
	}
}

void PhysicsPartitionOctTree::addToPartitionTree(PhysicsPartitionOctTree_PartitionTreeNode* node, RigidBody* rigidBody, BoundingBox* cbv)
{
	if (CollisionDetection::doCollideAABBvsAABBFast(&node->bv, cbv) == false) {
		return;
	}
	if (node->partitionSize == PARTITION_SIZE_MIN) {
		node->partitionRidigBodies.push_back(rigidBody);
		rigidBodyPartitionNodes[rigidBody->getId()].push_back(node);
	} else {
		for (auto& subNode: node->subNodes) {
			addToPartitionTree(&subNode, rigidBody, cbv);
		}
	}
}

void PhysicsPartitionOctTree::addToPartitionTree(RigidBody* rigidBody, BoundingBox* cbv)
{
	for (auto& subNode: treeRoot.subNodes) {
		addToPartitionTree(&subNode, rigidBody, cbv);
	}
}

int32_t PhysicsPartitionOctTree::doPartitionTreeLookUpNearEntities(PhysicsPartitionOctTree_PartitionTreeNode* node, BoundingBox* cbv, VectorIteratorMultiple<RigidBody*>& rigidBodyIterator)
{
	if (CollisionDetection::doCollideAABBvsAABBFast(cbv, &node->bv) == false) {
		return 1;
	}
	if (node->partitionRidigBodies.size() > 0) {
		rigidBodyIterator.addVector(&node->partitionRidigBodies);
		return 1;
	} else {
		auto lookUps = 1;
		for (auto& subNode: node->subNodes) {
			lookUps += doPartitionTreeLookUpNearEntities(&subNode, cbv, rigidBodyIterator);
		}
		return lookUps;
	}
}

VectorIteratorMultiple<RigidBody*>* PhysicsPartitionOctTree::getObjectsNearTo(BoundingVolume* cbv)
{
	auto& center = cbv->getCenter();
	halfExtension.set(cbv->computeDimensionOnAxis(sideVector), cbv->computeDimensionOnAxis(upVector), cbv->computeDimensionOnAxis(forwardVector)).scale(0.5f);
	boundingBox.getMin().set(center);
	boundingBox.getMin().sub(halfExtension);
	boundingBox.getMax().set(center);
	boundingBox.getMax().add(halfExtension);
	boundingBox.update();
	rigidBodyIterator.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpNearEntities(&subNode, &boundingBox, rigidBodyIterator);
	}
	return &rigidBodyIterator;
}

VectorIteratorMultiple<RigidBody*>* PhysicsPartitionOctTree::getObjectsNearTo(const Vector3& center)
{
	halfExtension.set(0.2f, 0.2f, 0.2f).scale(0.5f);
	boundingBox.getMin().set(center);
	boundingBox.getMin().sub(halfExtension);
	boundingBox.getMax().set(center);
	boundingBox.getMax().add(halfExtension);
	boundingBox.update();
	rigidBodyIterator.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpNearEntities(&subNode, &boundingBox, rigidBodyIterator);
	}
	return &rigidBodyIterator;
}

