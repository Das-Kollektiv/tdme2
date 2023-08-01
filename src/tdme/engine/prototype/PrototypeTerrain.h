#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeTerrainBrush.h>
#include <tdme/engine/Transform.h>

using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeTerrainBrush;

using tdme::engine::Transform;

/**
 * Prototype terrain definition
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeTerrain final
{
private:
	float width { -1 };
	float depth { -1 };
	vector<float> terrainHeightVector;
	int waterPositionMapIdx { 0 };
	unordered_map<int, float> waterPositionMapsHeight;
	unordered_map<int, unordered_map<int, unordered_set<int>>> waterPositionMaps;
	int foliagePrototypeMapIdx { 0 };
	unordered_map<int, Prototype*> foliageFoliagePrototypeMap;
	vector<unordered_map<int, vector<Transform>>> foliageMaps;
	vector<PrototypeTerrainBrush*> brushes;

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeTerrain)

	/**
	 * Public constructor
	 */
	inline PrototypeTerrain() {
	}

	/**
	 * Destructor
	 */
	~PrototypeTerrain() {
		for (auto& [foliageFoliagePrototypeIdx, foliageFoliagePrototype]: foliageFoliagePrototypeMap) {
			delete foliageFoliagePrototype;
		}
		for (auto brush: brushes) delete brush;
	}

	/**
	 * @return width
	 */
	inline float getWidth() const {
		return width;
	}

	/**
	 * Set width
	 * @param width width
	 */
	inline void setWidth(float width) {
		this->width = width;
	}

	/**
	 * @return depth
	 */
	inline float getDepth() const {
		return depth;
	}

	/**
	 * Set depth
	 * @param depth depth
	 */
	inline void setDepth(float depth) {
		this->depth = depth;
	}

	/**
	 * @return terrain height vector
	 */
	inline vector<float>& getHeightVector() {
		return terrainHeightVector;
	}

	/**
	 * @return water position maps height
	 */
	inline unordered_map<int, float>& getWaterPositionMapsHeight() {
		return waterPositionMapsHeight;
	}

	/**
	 * @return water position maps
	 */
	inline unordered_map<int, unordered_map<int, unordered_set<int>>>& getWaterPositionMaps() {
		return waterPositionMaps;
	}

	/**
	 * Get water position maps indices
	 * @return water position maps indices
	 */
	inline vector<int> getWaterPositionMapsIndices() {
		vector<int> waterPositionMapsIndices;
		for (const auto& [waterPositionMapId, waterPositionMap]: waterPositionMaps) waterPositionMapsIndices.push_back(waterPositionMapId);
		return waterPositionMapsIndices;
	}

	/**
	 * @return allocated water position map idx
	 */
	inline int allocateWaterPositionMapIdx() {
		return waterPositionMapIdx++;
	}

	/**
	 * Get water position map height at given water position map index
	 * @param idx water position map index
	 * @return water position map height at given water position map index
	 */
	inline float getWaterPositionMapHeight(int idx) {
		return waterPositionMapsHeight[idx];
	}

	/**
	 * Set water position map height at given water position map index
	 * @param idx water position map index
	 * @param waterHeight waterHeight water height
	 */
	inline void setWaterPositionMapHeight(int idx, float waterHeight) {
		waterPositionMapsHeight[idx] = waterHeight;
	}

	/**
	 * Get water position map at given index
	 * @param idx index
	 * @return water position map
	 */
	inline unordered_map<int, unordered_set<int>>& getWaterPositionMap(int idx) {
		return waterPositionMaps[idx];
	}

	/**
	 * Remove water position map at given water position map index
	 * @param idx water position map index
	 */
	inline void removeWaterPositionMap(int idx) {
		waterPositionMapsHeight.erase(idx);
		waterPositionMaps.erase(idx);
	}

	/**
	 * Get or allocate a foliage prototype index
	 * @param prototype prototype
	 * @return prototype index
	 */
	inline int getFoliagePrototypeIndex(Prototype* prototype) {
		auto maxFoliagePrototypeMapIdx = 0;
		for (const auto& [foliageFoliagePrototypeIdx, foliageFoliagePrototype]: foliageFoliagePrototypeMap) {
			if (foliageFoliagePrototypeIdx > maxFoliagePrototypeMapIdx) maxFoliagePrototypeMapIdx = foliageFoliagePrototypeIdx;
			if (prototype->getFileName() == foliageFoliagePrototype->getFileName()) return foliageFoliagePrototypeIdx;
		}
		maxFoliagePrototypeMapIdx++;
		foliageFoliagePrototypeMap[maxFoliagePrototypeMapIdx] = prototype;
		return maxFoliagePrototypeMapIdx;
	}

	/**
	 * Get foliage prototype indices
	 * @return foliage prototype indices
	 */
	inline vector<int> getFoliagePrototypeIndices() {
		vector<int> foliagePrototypeIndices;
		for (const auto& [foliageFoliagePrototypeMapIdx, foliageFoliagePrototypeMap]: foliageFoliagePrototypeMap) {
			foliagePrototypeIndices.push_back(foliageFoliagePrototypeMapIdx);
		}
		return foliagePrototypeIndices;
	}

	/**
	 * Get foliage prototype by given index
	 * @param idx protoype index
	 * @return prototype or nullptr
	 */
	inline Prototype* getFoliagePrototype(int prototypeIdx) {
		auto foliageFoliagePrototypeIt = foliageFoliagePrototypeMap.find(prototypeIdx);
		if (foliageFoliagePrototypeIt == foliageFoliagePrototypeMap.end()) {
			return nullptr;
		}
		return foliageFoliagePrototypeIt->second;
	}

	/**
	 * @return foliage maps
	 */
	inline vector<unordered_map<int, vector<Transform>>>& getFoliageMaps() {
		return foliageMaps;
	}

	/**
	 * Get foliage prototype entity ids
	 * @param prototypeIdx prototype index
	 * @return entity ids
	 */
	inline const vector<string> getFoliagePrototypeEntityIds(int prototypeIdx) {
		vector<string> foliagePrototypeEntityIds;
		auto prototypeEntityIdx = 0;
		for (auto& foliageMapPartition: foliageMaps) {
			for (auto& foliageMapPartitionIt: foliageMapPartition) {
				const auto& transformVector = foliageMapPartition[prototypeIdx];
				if (transformVector.empty() == true) continue;
				auto foliagePrototype = getFoliagePrototype(prototypeIdx);
				if (foliagePrototype->isRenderGroups() == false) {
					for (auto& transform: transformVector) {
						foliagePrototypeEntityIds.push_back("tdme.foliage." + to_string(prototypeIdx) + "." + to_string(prototypeEntityIdx++));
					}
				}
			}
		}
		return foliagePrototypeEntityIds;
	}

	/**
	 * Get foliage prototype entity transform indexed by entity id
	 * @param prototypeIdx prototype index
	 * @return transform indexed by entity id
	 */
	inline const map<string, Transform> getFoliagePrototypeEntityTransform(int prototypeIdx) {
		map<string, Transform> foliagePrototypeEntityTransform;
		auto prototypeEntityIdx = 0;
		for (auto& foliageMapPartition: foliageMaps) {
			const auto& transformVector = foliageMapPartition[prototypeIdx];
			if (transformVector.empty() == true) continue;
			auto foliagePrototype = getFoliagePrototype(prototypeIdx);
			if (foliagePrototype->isRenderGroups() == false) {
				for (auto& transform: transformVector) {
					foliagePrototypeEntityTransform["tdme.foliage." + to_string(prototypeIdx) + "." + to_string(prototypeEntityIdx++)] = transform;
				}
			}
		}
		return foliagePrototypeEntityTransform;
	}

	/**
	 * @return prototype terrain brushes
	 */
	inline const vector<PrototypeTerrainBrush*>& getBrushes() const {
		return brushes;
	}

	/**
	 * Get prototype terrain brush
	 * @param idx index
	 * @return prototype terrain brush prototype
	 */
	inline PrototypeTerrainBrush* getBrush(int idx) {
		if (idx < 0 || idx >= brushes.size()) return nullptr;
		return brushes[idx];
	}

	/**
	 * Add prototype terrain brush
	 * @param idx index
	 */
	PrototypeTerrainBrush* addBrush() {
		auto brush = new PrototypeTerrainBrush();
		brushes.push_back(brush);
		return brush;
	}

	/**
	 * Remove prototype terrain brush
	 * @param idx index
	 */
	bool removeBrush(int idx) {
		if (idx < 0 || idx >= brushes.size()) return false;
		auto brush = brushes[idx];
		brushes.erase(brushes.begin() + idx);
		delete brush;
		return true;
	}

};
