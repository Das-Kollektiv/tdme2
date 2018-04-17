#include <tdme/engine/PartitionOctTree.h>

#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <vector>

#include <tdme/math/Math.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Frustum.h>
#include <tdme/engine/PartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/VectorIteratorMultiple.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/Console.h>

using std::list;
using std::map;
using std::remove;
using std::vector;
using std::string;
using std::to_string;

using tdme::engine::PartitionOctTree;
using tdme::math::Math;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;
using tdme::utils::Pool;
using tdme::utils::Console;

constexpr float PartitionOctTree::PARTITION_SIZE_MIN;

constexpr float PartitionOctTree::PARTITION_SIZE_MAX;

PartitionOctTree::PartitionOctTree() 
{
	this->sideVector.set(1.0f, 0.0f, 0.0f);
	this->upVector.set(0.0f, 1.0f, 0.0f);
	this->forwardVector.set(0.0f, 0.0f, 1.0f);
	reset();
}

void PartitionOctTree::reset()
{
	this->entityPartitionNodes.clear();
	this->visibleEntities.clear();
	this->treeRoot.partitionSize = -1;
	this->treeRoot.x = -1;
	this->treeRoot.y = -1;
	this->treeRoot.z = -1;
	this->treeRoot.parent = nullptr;
}

void PartitionOctTree::createPartition(PartitionOctTree_PartitionTreeNode* parent, int32_t x, int32_t y, int32_t z, float partitionSize)
{
	PartitionOctTree_PartitionTreeNode node;
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
	PartitionOctTree_PartitionTreeNode* storedNode = &parent->subNodes.back();
	// register in parent sub nodes by coordinate, if root node
	if (parent == &treeRoot) {
		string key = to_string(node.x) + "," + to_string(node.y) + "," + to_string(node.z);
		parent->subNodesByCoordinate[key] = storedNode;
	}
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

void PartitionOctTree::addEntity(Entity* entity)
{
	// update if already exists
	vector<PartitionOctTree_PartitionTreeNode*>* thisEntityPartitions = nullptr;
	auto thisEntityPartitionsIt = entityPartitionNodes.find(entity->getId());
	if (thisEntityPartitionsIt != entityPartitionNodes.end()) {
		thisEntityPartitions = &thisEntityPartitionsIt->second;
	}
	if (thisEntityPartitions != nullptr && thisEntityPartitions->empty() == false) {
		removeEntity(entity);
	}
	// frustum bounding box
	auto boundingBox = entity->getBoundingBoxTransformed();
	// find, create root nodes if not exists
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
		auto nodeIt = treeRoot.subNodesByCoordinate.find(to_string(xPartition) + "," + to_string(yPartition) + "," + to_string(zPartition));
		if (nodeIt == treeRoot.subNodesByCoordinate.end()) {
			createPartition(&treeRoot, xPartition, yPartition, zPartition, PARTITION_SIZE_MAX);
		}
	}
	// add entity to tree
	addToPartitionTree(entity, boundingBox);
}

void PartitionOctTree::updateEntity(Entity* entity)
{
	addEntity(entity);
}

void PartitionOctTree::removeEntity(Entity* entity)
{
	// check if we have entity in oct tree
	vector<PartitionOctTree_PartitionTreeNode*>* objectPartitionsVector = nullptr;
	auto objectPartitionsVectorIt = entityPartitionNodes.find(entity->getId());
	if (objectPartitionsVectorIt != entityPartitionNodes.end()) {
		objectPartitionsVector = &objectPartitionsVectorIt->second;
	}
	if (objectPartitionsVector == nullptr || objectPartitionsVector->empty() == true) {
		Console::println(
			"PartitionOctTree::removeEntity(): '" +
			entity->getId() +
			"' not registered"
		);
		return;
	}
	// remove object from assigned partitions
	while (objectPartitionsVector->size() > 0) {
		auto lastIdx = objectPartitionsVector->size() - 1;
		auto partitionTreeNode = objectPartitionsVector->at(lastIdx);
		auto& partitionObjects = partitionTreeNode->partitionEntities;
		partitionObjects.erase(remove(partitionObjects.begin(), partitionObjects.end(), entity), partitionObjects.end());
		objectPartitionsVector->erase(objectPartitionsVector->begin() + lastIdx);
		if (partitionObjects.empty() == true) {
			auto rootPartitionTreeNode = partitionTreeNode->parent->parent;
			// check if whole top level partition is empty
			if (isPartitionNodeEmpty(rootPartitionTreeNode) == true) {
				// yep, remove it
				removePartitionNode(rootPartitionTreeNode);
				for (auto treeRootSubNodeIt = treeRoot.subNodes.begin(); treeRootSubNodeIt != treeRoot.subNodes.end(); ++treeRootSubNodeIt) {
					if ((void*)&treeRootSubNodeIt == (void*)rootPartitionTreeNode) {
						treeRoot.subNodes.erase(treeRootSubNodeIt);
						break;
					}
				}
				string key = to_string(rootPartitionTreeNode->x) + "," + to_string(rootPartitionTreeNode->y) + "," + to_string(rootPartitionTreeNode->z);
				treeRoot.subNodesByCoordinate.erase(key);
			}
		}
	}
	entityPartitionNodes.erase(objectPartitionsVectorIt);
}

bool PartitionOctTree::isPartitionNodeEmpty(PartitionOctTree_PartitionTreeNode* node)
{
	// lowest level node has objects attached?
	if (node->partitionEntities.size() > 0) {
		return false;
	} else {
		for (auto& subNode: node->subNodes) {
			if (isPartitionNodeEmpty(&subNode) == false)
				return false;

		}
		return true;
	}
}

void PartitionOctTree::removePartitionNode(PartitionOctTree_PartitionTreeNode* node)
{
	// lowest level node has objects attached?
	if (node->partitionEntities.size() > 0) {
		Console::println("PartitionOctTree::removePartitionNode(): partition has objects attached!!!");
		node->partitionEntities.clear();
	} else {
		// otherwise check top level node sub nodes
		for (auto& subNode: node->subNodes) {
			removePartitionNode(&subNode);
		}
		node->subNodes.clear();
	}
}

vector<Entity*>* PartitionOctTree::getVisibleEntities(Frustum* frustum)
{
	visibleEntities.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpVisibleObjects(frustum, &subNode, visibleEntities);
	}
	return &visibleEntities;
}

void PartitionOctTree::addToPartitionTree(PartitionOctTree_PartitionTreeNode* node, Entity* entity, BoundingBox* cbv)
{
	if (CollisionDetection::doCollideAABBvsAABBFast(&node->bv, cbv) == false) {
		return;
	}
	// if this node already has the partition cbvs add it to the iterator
	if (node->partitionSize == PARTITION_SIZE_MIN) {
		node->partitionEntities.push_back(entity);
		entityPartitionNodes[entity->getId()].push_back(node);
	} else
		// otherwise check sub nodes
	if (node->subNodes.size() > 0) {
		for (auto& subNode: node->subNodes) {
			addToPartitionTree(&subNode, entity, cbv);
		}
	}
}

void PartitionOctTree::addToPartitionTree(Entity* entity, BoundingBox* cbv)
{
	for (auto& subNode: treeRoot.subNodes) {
		addToPartitionTree(&subNode, entity, cbv);
	}
}

int32_t PartitionOctTree::doPartitionTreeLookUpNearEntities(PartitionOctTree_PartitionTreeNode* node, BoundingBox* cbv, VectorIteratorMultiple<Entity*>& entityIterator)
{
	// check if given cbv collides with partition node bv
	if (CollisionDetection::doCollideAABBvsAABBFast(cbv, &node->bv) == false) {
		return 1;
	}
	// if this node already has the partition cbvs add it to the iterator
	if (node->partitionEntities.size() > 0) {
		entityIterator.addVector(&node->partitionEntities);
		return 1;
	} else
	// otherwise check sub nodes
	if (node->subNodes.size() > 0) {
		auto lookUps = 1;
		for (auto& subNode: node->subNodes) {
			lookUps += doPartitionTreeLookUpNearEntities(&subNode, cbv, entityIterator);
		}
		return lookUps;
	}
	return 0;
}

VectorIteratorMultiple<Entity*>* PartitionOctTree::getObjectsNearTo(BoundingVolume* cbv)
{
	auto& center = cbv->getCenter();
	halfExtension.set(cbv->computeDimensionOnAxis(sideVector), cbv->computeDimensionOnAxis(upVector), cbv->computeDimensionOnAxis(forwardVector)).scale(0.5f);
	boundingBox.getMin().set(center);
	boundingBox.getMin().sub(halfExtension);
	boundingBox.getMax().set(center);
	boundingBox.getMax().add(halfExtension);
	boundingBox.update();
	entityIterator.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpNearEntities(&subNode, &boundingBox, entityIterator);
	}
	return &entityIterator;
}

VectorIteratorMultiple<Entity*>* PartitionOctTree::getObjectsNearTo(const Vector3& center)
{
	halfExtension.set(0.2f, 0.2f, 0.2f).scale(0.5f);
	boundingBox.getMin().set(center);
	boundingBox.getMin().sub(halfExtension);
	boundingBox.getMax().set(center);
	boundingBox.getMax().add(halfExtension);
	boundingBox.update();
	entityIterator.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpNearEntities(&subNode, &boundingBox, entityIterator);
	}
	return &entityIterator;
}
