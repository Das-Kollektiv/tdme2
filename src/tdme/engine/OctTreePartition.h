#pragma once

#include <bitset>
#include <list>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Frustum.h>
#include <tdme/engine/Partition.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/VectorIteratorMultiple.h>

using std::bitset;
using std::get;
using std::list;
using std::string;
using std::to_string;
using std::tuple;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::Partition;
using tdme::utilities::Console;
using tdme::utilities::VectorIteratorMultiple;

/**
 * Oct tree partition implementation
 * @author Andreas Drewke
 */
class tdme::engine::OctTreePartition final: public Partition
{
private:
	struct PartitionTreeNodeId_Hash {
		std::size_t operator()(const tuple<int32_t, int32_t, int32_t>& k) const {
			std::hash<uint64_t> hashVal;
			return hashVal(get<0>(k) ^ get<1>(k) ^ get<2>(k));
		}
	};

	struct PartitionTreeNode
	{
		// partition size
		float partitionSize;

		// x, y, z position
		int32_t x;
		int32_t y;
		int32_t z;

		// parent node
		PartitionTreeNode* parent { nullptr };

		// node bounding volume
		BoundingBox bv;

		// sub nodes of oct tree nodes
		list<PartitionTreeNode> subNodes;

		// sub nodes of oct tree nodes by partition coordinate, only used in root node
		unordered_map<tuple<int32_t, int32_t, int32_t>, PartitionTreeNode*, PartitionTreeNodeId_Hash> subNodesByCoordinate;

		// or finally our partition entities
		vector<Entity*> partitionEntities;
	};

	static constexpr float PARTITION_SIZE_MIN { 64.0f };
	static constexpr float PARTITION_SIZE_MAX { 512.0f };

	VectorIteratorMultiple<Entity*> entityIterator;
	unordered_map<string, vector<PartitionTreeNode*>> entityPartitionNodes;
	vector<Entity*> visibleEntities;
	PartitionTreeNode treeRoot;

	// TODO: put those limits into tdme.h or use dynamic bitset here
	bitset<1024 * 512> visibleEntitiesBitSet;
	unordered_map<Entity*, int> entityUniquePartitionIdMapping;
	vector<int> freeEntityUniquePartitionIds;

	// overridden methods
	void reset() override;
	void addEntity(Entity* entity) override;
	inline void updateEntity(Entity* entity) override {
		addEntity(entity);
	}
	void removeEntity(Entity* entity) override;

	/**
	 * Update partition tree
	 * @param parent parent
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param partitionSize partition size
	 * @param entity entity
	 */
	inline void updatePartitionTree(PartitionTreeNode* parent, int32_t x, int32_t y, int32_t z, float partitionSize, Entity* entity) {
		// key
		tuple<int32_t, int32_t, int32_t> key = { x, y, z };
		auto storedNodeIt = parent->subNodesByCoordinate.find(key);
		auto storedNode = storedNodeIt != parent->subNodesByCoordinate.end()?storedNodeIt->second:nullptr;

		// check if exists
		if (storedNode == nullptr) {
			// if not add
			PartitionTreeNode node;
			node.partitionSize = partitionSize;
			node.x = x;
			node.y = y;
			node.z = z;
			node.parent = parent;
			node.bv.getMin().set(
				x * partitionSize,
				y * partitionSize,
				z * partitionSize
			);
			node.bv.getMax().set(
				x * partitionSize + partitionSize,
				y * partitionSize + partitionSize,
				z * partitionSize + partitionSize
			);
			node.bv.update();
			// register in parent sub nodes
			parent->subNodes.push_back(node);
			storedNode = &parent->subNodes.back();
			// register in parent sub nodes by coordinate, if root node
			parent->subNodesByCoordinate[key] = storedNode;
		}

		// create sub nodes
		if (partitionSize > PARTITION_SIZE_MIN) {
			// frustum bounding box
			auto boundingBox = entity->getBoundingBoxTransformed();
			// create partitions if not yet done
			auto minXPartition = static_cast<int32_t>((Math::floor(boundingBox->getMin().getX() - x * partitionSize) / (partitionSize / 2.0f)));
			auto minYPartition = static_cast<int32_t>((Math::floor(boundingBox->getMin().getY() - y * partitionSize) / (partitionSize / 2.0f)));
			auto minZPartition = static_cast<int32_t>((Math::floor(boundingBox->getMin().getZ() - z * partitionSize) / (partitionSize / 2.0f)));
			auto maxXPartition = static_cast<int32_t>((Math::floor(boundingBox->getMax().getX() - x * partitionSize) / (partitionSize / 2.0f)));
			auto maxYPartition = static_cast<int32_t>((Math::floor(boundingBox->getMax().getY() - y * partitionSize) / (partitionSize / 2.0f)));
			auto maxZPartition = static_cast<int32_t>((Math::floor(boundingBox->getMax().getZ() - z * partitionSize) / (partitionSize / 2.0f)));
			minXPartition = Math::clamp(minXPartition, 0, 1);
			minYPartition = Math::clamp(minYPartition, 0, 1);
			minZPartition = Math::clamp(minZPartition, 0, 1);
			maxXPartition = Math::clamp(maxXPartition, 0, 1);
			maxYPartition = Math::clamp(maxYPartition, 0, 1);
			maxZPartition = Math::clamp(maxZPartition, 0, 1);
			for (auto yPartition = minYPartition; yPartition <= maxYPartition; yPartition++)
			for (auto xPartition = minXPartition; xPartition <= maxXPartition; xPartition++)
			for (auto zPartition = minZPartition; zPartition <= maxZPartition; zPartition++) {
				updatePartitionTree(
					storedNode,
					static_cast<int32_t>((x * partitionSize) / (partitionSize / 2.0f) + xPartition),
					static_cast<int32_t>((y * partitionSize) / (partitionSize / 2.0f) + yPartition),
					static_cast<int32_t>((z * partitionSize) / (partitionSize / 2.0f) + zPartition),
					partitionSize / 2.0f, entity
				);
			}
		} else {
			storedNode->partitionEntities.push_back(entity);
			entityPartitionNodes[entity->getId()].push_back(storedNode);
		}
	}

	/**
	 * Is partition empty
	 * @param node node
	 * @return partition empty
	 */
	inline bool isPartitionNodeEmpty(PartitionTreeNode* node) {
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

	/**
	 * Remove partition node, should be empty
	 * @param node node
	 */
	inline void removePartitionNode(PartitionTreeNode* node) {
		// lowest level node has objects attached?
		if (node->partitionEntities.size() > 0) {
			Console::println("OctTreePartition::removePartitionNode(): partition has objects attached!!!");
			node->partitionEntities.clear();
		} else {
			// otherwise check top level node sub nodes
			for (auto& subNode: node->subNodes) {
				removePartitionNode(&subNode);
			}
			node->subNodesByCoordinate.clear();
			node->subNodes.clear();
		}
	}

	/**
	 * Do partition tree lookup
	 * @param frustum frustum
	 * @param node node
	 * @return number of look ups
	 */
	inline int32_t doPartitionTreeLookUpVisibleObjects(Frustum* frustum, PartitionTreeNode* node) {
		auto lookUps = 1;
		// check if given cbv collides with partition node bv
		if (frustum->isVisible(&node->bv) == false) {
			return lookUps;
		} else
		// otherwise check sub nodes
		if (node->subNodes.size() > 0) {
			for (auto& subNode: node->subNodes) {
				lookUps += doPartitionTreeLookUpVisibleObjects(frustum, &subNode);
			}
			return lookUps;
		} else
		// last check if this node has partition entities
		if (node->partitionEntities.size() > 0) {
			for (auto i = 0; i < node->partitionEntities.size(); i++) {
				auto entity = node->partitionEntities[i];

				// look up
				lookUps++;
				if (frustum->isVisible(entity->getBoundingBoxTransformed()) == false) continue;

				//
				auto uniquePartitionId = entity->getUniquePartitionId();
				// lets have this only once in result
				if (visibleEntitiesBitSet.test(uniquePartitionId) == true) {
					continue;
				}
				visibleEntitiesBitSet.set(uniquePartitionId);

				// done
				visibleEntities.push_back(entity);
			}
			return lookUps;
		}
		return lookUps;
	}

	/**
	 * Dump node to console
	 * @param node node
	 * @param indent indent
	 */
	void dumpNode(PartitionTreeNode* node, int indent);

	/**
	 * Find entity
	 * @param node node
	 * @param entity entity
	 */
	void findEntity(PartitionTreeNode* node, Entity* entity);

public:
	/**
	 * Public constructor
	 */
	OctTreePartition();

	// overridden methods
	const vector<Entity*>& getVisibleEntities(Frustum* frustum) override;
	inline bool isVisibleEntity(Entity* entity) override {
		auto uniquePartitionId = entity->getUniquePartitionId();
		return uniquePartitionId != Entity::UNIQUEPARTITIONID_NONE && visibleEntitiesBitSet.test(uniquePartitionId) == true;
	}

	/**
	 * Dump oct tree to console
	 */
	void dump();

};
