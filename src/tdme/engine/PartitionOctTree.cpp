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
		updatePartitionTree(&treeRoot, xPartition, yPartition, zPartition, PARTITION_SIZE_MAX, entity);
	}
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
	// TODO: remove tree root sub nodes as well not only empty root nodes
	while (objectPartitionsVector->size() > 0) {
		auto lastIdx = objectPartitionsVector->size() - 1;
		auto partitionTreeNode = (*objectPartitionsVector)[lastIdx];
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

vector<Entity*>* PartitionOctTree::getVisibleEntities(Frustum* frustum)
{
	visibleEntities.clear();
	visibleEntitiesById.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpVisibleObjects(frustum, &subNode);
	}
	return &visibleEntities;
}

VectorIteratorMultiple<Entity*>* PartitionOctTree::getObjectsNearTo(BoundingVolume* cbv)
{
	entityIterator.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpNearEntities(&subNode, cbv->getBoundingBox());
	}
	return &entityIterator;
}

VectorIteratorMultiple<Entity*>* PartitionOctTree::getObjectsNearTo(const Vector3& center, const Vector3& halfExtension)
{
	BoundingBox boundingBox;
	boundingBox.getMin().set(center);
	boundingBox.getMin().sub(halfExtension);
	boundingBox.getMax().set(center);
	boundingBox.getMax().add(halfExtension);
	boundingBox.update();
	entityIterator.clear();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpNearEntities(&subNode, &boundingBox);
	}
	return &entityIterator;
}
