// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java
#include <tdme/engine/physics/PhysicsPartitionOctTree.h>

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/util/Iterator.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree_reset_2.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree_reset_3.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/_Console.h>

using std::find;
using std::map;
using std::remove;
using std::wstring;
using std::to_wstring;
using std::vector;

using tdme::engine::physics::PhysicsPartitionOctTree;
using java::lang::Math;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::physics::PhysicsPartitionOctTree_reset_2;
using tdme::engine::physics::PhysicsPartitionOctTree_reset_3;
using tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ArrayListIteratorMultiple;
using tdme::utils::Pool;
using tdme::utils::_Console;

constexpr float PhysicsPartitionOctTree::PARTITION_SIZE_MIN;

constexpr float PhysicsPartitionOctTree::PARTITION_SIZE_MAX;

PhysicsPartitionOctTree::PhysicsPartitionOctTree()
{
	treeRoot = nullptr;
	this->boundingBox = new BoundingBox();
	this->halfExtension = new Vector3();
	this->sideVector = new Vector3(1.0f, 0.0f, 0.0f);
	this->upVector = new Vector3(0.0f, 1.0f, 0.0f);
	this->forwardVector = new Vector3(0.0f, 0.0f, 1.0f);
	reset();
}

void PhysicsPartitionOctTree::reset()
{
	this->boundingBoxPool = new PhysicsPartitionOctTree_reset_2();
	this->partitionTreeNodePool = new PhysicsPartitionOctTree_reset_3(this);
	this->treeRoot = new PhysicsPartitionOctTree_PartitionTreeNode();
	this->treeRoot->partitionSize = -1;
	this->treeRoot->x = -1;
	this->treeRoot->y = -1;
	this->treeRoot->z = -1;
	this->treeRoot->parent = nullptr;
	this->treeRoot->bv = nullptr;
	this->treeRoot->subNodes.clear();
	this->treeRoot->partitionRidigBodies.clear();
	this->rigidBodyIterator.clear();
}

PhysicsPartitionOctTree_PartitionTreeNode* PhysicsPartitionOctTree::createPartition(PhysicsPartitionOctTree_PartitionTreeNode* parent, int32_t x, int32_t y, int32_t z, float partitionSize)
{
	auto node = dynamic_cast< PhysicsPartitionOctTree_PartitionTreeNode* >(partitionTreeNodePool->allocate());
	node->partitionSize = partitionSize;
	node->x = x;
	node->y = y;
	node->z = z;
	node->parent = parent;
	node->bv = dynamic_cast< BoundingBox* >(boundingBoxPool->allocate());
	node->bv->getMin()->set(x * partitionSize, y * partitionSize, z * partitionSize);
	node->bv->getMax()->set(x * partitionSize + partitionSize, y * partitionSize + partitionSize, z * partitionSize + partitionSize);
	node->bv->update();
	node->subNodes.clear();
	node->subNodesByCoordinate.clear();
	node->partitionRidigBodies.clear();
	parent->subNodes.push_back(node);
	if (parent == treeRoot) {
		wstring key = to_wstring(node->x) + L"," + to_wstring(node->y) + L"," + to_wstring(node->z);
		parent->subNodesByCoordinate[key] = node;
	}
	if (partitionSize > PARTITION_SIZE_MIN) {
		for (auto _y = 0; _y < 2; _y++) 
		for (auto _x = 0; _x < 2; _x++)
		for (auto _z = 0; _z < 2; _z++) {
			createPartition(node, static_cast< int32_t >(((x * partitionSize) / (partitionSize / 2.0f))) + _x, static_cast< int32_t >(((y * partitionSize) / (partitionSize / 2.0f))) + _y, static_cast< int32_t >(((z * partitionSize) / (partitionSize / 2.0f))) + _z, partitionSize / 2.0f);
		}
	}
	return node;
}

void PhysicsPartitionOctTree::addRigidBody(RigidBody* rigidBody)
{
	vector<PhysicsPartitionOctTree_PartitionTreeNode*>* thisRigidBodyPartitions = nullptr;
	auto rigidBodyPartitionNodesIt = rigidBodyPartitionNodes.find(rigidBody->getId()->getCPPWString());
	if (rigidBodyPartitionNodesIt != rigidBodyPartitionNodes.end()) {
		thisRigidBodyPartitions = &rigidBodyPartitionNodesIt->second;
	}
	if (thisRigidBodyPartitions != nullptr && thisRigidBodyPartitions->empty() == false) {
		removeRigidBody(rigidBody);
	}
	auto cbv = rigidBody->cbv;
	auto center = cbv->getCenter();
	halfExtension->set(cbv->computeDimensionOnAxis(sideVector) + 0.2f, cbv->computeDimensionOnAxis(upVector) + 0.2f, cbv->computeDimensionOnAxis(forwardVector) + 0.2f)->scale(0.5f);
	boundingBox->getMin()->set(center);
	boundingBox->getMin()->sub(halfExtension);
	boundingBox->getMax()->set(center);
	boundingBox->getMax()->add(halfExtension);
	boundingBox->update();
	auto minXPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin()->getX() / PARTITION_SIZE_MAX));
	auto minYPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin()->getY() / PARTITION_SIZE_MAX));
	auto minZPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin()->getZ() / PARTITION_SIZE_MAX));
	auto maxXPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax()->getX() / PARTITION_SIZE_MAX));
	auto maxYPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax()->getY() / PARTITION_SIZE_MAX));
	auto maxZPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax()->getZ() / PARTITION_SIZE_MAX));
	for (auto yPartition = minYPartition; yPartition <= maxYPartition; yPartition++) 
	for (auto xPartition = minXPartition; xPartition <= maxXPartition; xPartition++)
	for (auto zPartition = minZPartition; zPartition <= maxZPartition; zPartition++) {
		wstring key = to_wstring(xPartition) + L"," + to_wstring(yPartition) + L"," + to_wstring(zPartition);
		auto nodeIt = treeRoot->subNodesByCoordinate.find(key);
		if (nodeIt == treeRoot->subNodesByCoordinate.end()) {
			createPartition(treeRoot, xPartition, yPartition, zPartition, PARTITION_SIZE_MAX);
		}
	}

	addToPartitionTree(rigidBody, boundingBox);
}

void PhysicsPartitionOctTree::updateRigidBody(RigidBody* rigidBody)
{
	addRigidBody(rigidBody);
}

void PhysicsPartitionOctTree::removeRigidBody(RigidBody* rigidBody)
{
	auto rigidBodyPartitionsVectorIt = rigidBodyPartitionNodes.find(rigidBody->getId()->getCPPWString());
	vector<PhysicsPartitionOctTree_PartitionTreeNode*>* rigidBodyPartitionsVector = nullptr;
	if (rigidBodyPartitionsVectorIt != rigidBodyPartitionNodes.end()) {
		rigidBodyPartitionsVector = &rigidBodyPartitionsVectorIt->second;
	}
	if (rigidBodyPartitionsVector == nullptr || rigidBodyPartitionsVector->empty() == true) {
		_Console::println(
			wstring(L"PartitionOctTree::removeRigidBody(): '") +
			rigidBody->getId()->getCPPWString() +
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
				treeRoot->subNodes.erase(remove(treeRoot->subNodes.begin(), treeRoot->subNodes.end(), rootPartitionTreeNode), treeRoot->subNodes.end());
				wstring key = to_wstring(rootPartitionTreeNode->x) + L"," + to_wstring(rootPartitionTreeNode->y) + L"," + to_wstring(rootPartitionTreeNode->z);
				treeRoot->subNodesByCoordinate.erase(key);
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
		for (auto i = 0; i < node->subNodes.size(); i++) {
			if (isPartitionNodeEmpty(dynamic_cast< PhysicsPartitionOctTree_PartitionTreeNode* >(node->subNodes.at(i))) == false)
				return false;
		}
		return true;
	}
}

void PhysicsPartitionOctTree::removePartitionNode(PhysicsPartitionOctTree_PartitionTreeNode* node)
{
	if (node->partitionRidigBodies.size() > 0) {
		_Console::println(static_cast< Object* >(u"PartitionOctTree::removePartitionNode(): partition has objects attached!!!"_j));
		node->partitionRidigBodies.clear();
	} else {
		for (auto i = 0; i < node->subNodes.size(); i++) {
			auto subNode = node->subNodes.at(i);
			removePartitionNode(subNode);
		}
		node->subNodes.clear();
	}
	boundingBoxPool->release(node->bv);
	node->bv = nullptr;
	partitionTreeNodePool->release(node);
}

void PhysicsPartitionOctTree::addToPartitionTree(PhysicsPartitionOctTree_PartitionTreeNode* node, RigidBody* rigidBody, BoundingBox* cbv)
{
	if (CollisionDetection::doCollideAABBvsAABBFast(node->bv, cbv) == false) {
		return;
	}
	if (node->partitionSize == PARTITION_SIZE_MIN) {
		node->partitionRidigBodies.push_back(rigidBody);
		rigidBodyPartitionNodes[rigidBody->getId()->getCPPWString()].push_back(node);
	} else {
		for (auto i = 0; i < node->subNodes.size(); i++) {
			addToPartitionTree(node->subNodes.at(i), rigidBody, cbv);
		}
	}
}

void PhysicsPartitionOctTree::addToPartitionTree(RigidBody* rigidBody, BoundingBox* cbv)
{
	for (auto i = 0; i < treeRoot->subNodes.size(); i++) {
		addToPartitionTree(treeRoot->subNodes.at(i), rigidBody, cbv);
	}
}

int32_t PhysicsPartitionOctTree::doPartitionTreeLookUpNearEntities(PhysicsPartitionOctTree_PartitionTreeNode* node, BoundingBox* cbv, ArrayListIteratorMultiple<RigidBody*>& rigidBodyIterator)
{
	if (CollisionDetection::doCollideAABBvsAABBFast(cbv, node->bv) == false) {
		return 1;
	}
	if (node->partitionRidigBodies.size() > 0) {
		rigidBodyIterator.addArrayList(&node->partitionRidigBodies);
		return 1;
	} else {
		auto lookUps = 1;
		for (auto i = 0; i < node->subNodes.size(); i++) {
			lookUps += doPartitionTreeLookUpNearEntities(node->subNodes.at(i), cbv, rigidBodyIterator);
		}
		return lookUps;
	}
}

ArrayListIteratorMultiple<RigidBody*>* PhysicsPartitionOctTree::getObjectsNearTo(BoundingVolume* cbv)
{
	auto center = cbv->getCenter();
	halfExtension->set(cbv->computeDimensionOnAxis(sideVector) + 0.2f, cbv->computeDimensionOnAxis(upVector) + 0.2f, cbv->computeDimensionOnAxis(forwardVector) + 0.2f)->scale(0.5f);
	boundingBox->getMin()->set(center);
	boundingBox->getMin()->sub(halfExtension);
	boundingBox->getMax()->set(center);
	boundingBox->getMax()->add(halfExtension);
	boundingBox->update();
	rigidBodyIterator.clear();
	auto lookUps = 0;
	for (auto i = 0; i < treeRoot->subNodes.size(); i++) {
		lookUps += doPartitionTreeLookUpNearEntities(treeRoot->subNodes.at(i), boundingBox, rigidBodyIterator);
	}
	return &rigidBodyIterator;
}

ArrayListIteratorMultiple<RigidBody*>* PhysicsPartitionOctTree::getObjectsNearTo(Vector3* center)
{
	halfExtension->set(0.2f, 0.2f, 0.2f)->scale(0.5f);
	boundingBox->getMin()->set(center);
	boundingBox->getMin()->sub(halfExtension);
	boundingBox->getMax()->set(center);
	boundingBox->getMax()->add(halfExtension);
	boundingBox->update();
	rigidBodyIterator.clear();
	auto lookUps = 0;
	for (auto i = 0; i < treeRoot->subNodes.size(); i++) {
		lookUps += doPartitionTreeLookUpNearEntities(treeRoot->subNodes.at(i), boundingBox, rigidBodyIterator);
	}
	return &rigidBodyIterator;
}

