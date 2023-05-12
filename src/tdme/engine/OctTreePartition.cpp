#include <tdme/engine/OctTreePartition.h>

#include <algorithm>
#include <bitset>
#include <list>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Frustum.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/VectorIteratorMultiple.h>

using std::bitset;
using std::list;
using std::remove;
using std::string;
using std::to_string;
using std::tuple;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::OctTreePartition;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::VectorIteratorMultiple;

OctTreePartition::OctTreePartition()
{
	reset();
}

void OctTreePartition::reset()
{
	this->entityPartitionNodes.clear();
	this->visibleEntities.clear();
	this->treeRoot.partitionSize = -1;
	this->treeRoot.x = -1;
	this->treeRoot.y = -1;
	this->treeRoot.z = -1;
	this->treeRoot.parent = nullptr;
	this->entityUniquePartitionIdMapping.clear();
	this->freeEntityUniquePartitionIds.clear();
}

void OctTreePartition::addEntity(Entity* entity)
{
	// update if already exists
	vector<PartitionTreeNode*>* thisEntityPartitions = nullptr;
	auto thisEntityPartitionsIt = entityPartitionNodes.find(entity);
	if (thisEntityPartitionsIt != entityPartitionNodes.end()) {
		thisEntityPartitions = &thisEntityPartitionsIt->second;
	}
	if (thisEntityPartitions != nullptr && thisEntityPartitions->empty() == false) {
		removeEntity(entity);
	}
	// do we have a entity -> unique partition id mapping
	auto entityUniquePartitionIdMappingIt = entityUniquePartitionIdMapping.find(entity);
	// nope
	if (entityUniquePartitionIdMappingIt == entityUniquePartitionIdMapping.end()) {
		// reset
		auto uniquePartitionId = Entity::UNIQUEPARTITIONID_NONE;
		// reuse a unique partition id from freeEntityUniquePartitionIds
		if (freeEntityUniquePartitionIds.empty() == false) {
			// yet
			uniquePartitionId = freeEntityUniquePartitionIds[freeEntityUniquePartitionIds.size() - 1];
			freeEntityUniquePartitionIds.erase(freeEntityUniquePartitionIds.begin() + freeEntityUniquePartitionIds.size() - 1);
		} else {
			// otherwise create a id
			uniquePartitionId = entityUniquePartitionIdMapping.size() + 1;
			if (uniquePartitionId >= visibleEntitiesBitSet.size()) {
				Console::println("OctTreePartition::addEntity(): too many entities: " + to_string(uniquePartitionId) + " >= " + to_string(visibleEntitiesBitSet.size()));
				return;
			}
		}
		entity->setUniquePartitionId(uniquePartitionId);
		entityUniquePartitionIdMapping[entity] = uniquePartitionId;
	} else {
		entity->setUniquePartitionId(entityUniquePartitionIdMappingIt->second);
	}
	// frustum bounding box
	auto boundingBox = entity->getWorldBoundingBox();
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

void OctTreePartition::removeEntity(Entity* entity)
{
	// check if we have entity in oct tree
	vector<PartitionTreeNode*>* objectPartitionsVector = nullptr;
	auto objectPartitionsVectorIt = entityPartitionNodes.find(entity);
	if (objectPartitionsVectorIt != entityPartitionNodes.end()) {
		objectPartitionsVector = &objectPartitionsVectorIt->second;
	}
	if (objectPartitionsVector == nullptr || objectPartitionsVector->empty() == true) {
		Console::println(
			"OctTreePartition::removeEntity(): '" +
			entity->getId() +
			"' not registered"
		);
		return;
	}
	//
	auto uniquePartitionId = entity->getUniquePartitionId();
	if (uniquePartitionId != Entity::UNIQUEPARTITIONID_NONE) {
		entity->setUniquePartitionId(Entity::UNIQUEPARTITIONID_NONE);
		entityUniquePartitionIdMapping.erase(entity);
		freeEntityUniquePartitionIds.push_back(uniquePartitionId);
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
			auto rootPartitionTreeNode = partitionTreeNode;
			while (rootPartitionTreeNode->parent != nullptr) rootPartitionTreeNode = rootPartitionTreeNode->parent;
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
				tuple<int32_t, int32_t, int32_t> key = {
					rootPartitionTreeNode->x,
					rootPartitionTreeNode->y,
					rootPartitionTreeNode->z
				};
				treeRoot.subNodesByCoordinate.erase(key);
			}
		}
	}
	entityPartitionNodes.erase(objectPartitionsVectorIt);
}

const vector<Entity*>& OctTreePartition::getVisibleEntities(Frustum* frustum)
{
	visibleEntities.clear();
	visibleEntitiesBitSet.reset();
	auto lookUps = 0;
	for (auto& subNode: treeRoot.subNodes) {
		lookUps += doPartitionTreeLookUpVisibleObjects(frustum, &subNode);
	}
	return visibleEntities;
}

void OctTreePartition::dumpNode(PartitionTreeNode* node, int indent) {
	for (auto i = 0; i < indent; i++) Console::print("\t");
	Console::println(to_string(node->x) + "/" + to_string(node->y) + "/" + to_string(node->z) + ": ");
	for (auto entity: node->partitionEntities) {
		for (auto i = 0; i < indent + 1; i++) Console::print("\t");
		Console::println(entity->getId());
	}
	for (auto subNode: node->subNodes) dumpNode(&subNode, indent + 1);
}

void OctTreePartition::findEntity(PartitionTreeNode* node, Entity* entity) {
	for (auto nodeEntity: node->partitionEntities) {
		if (nodeEntity == entity) Console::println("OctTreePartition::findEntity(): found entity: " + entity->getId());
	}
	for (auto subNode: node->subNodes) findEntity(&subNode, entity);
}

void OctTreePartition::dump() {
	dumpNode(&treeRoot, 0);
}
