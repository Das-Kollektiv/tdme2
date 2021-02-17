#pragma once

#include <map>
#include <set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>

using std::map;
using std::set;
using std::vector;

using tdme::engine::prototype::Prototype;

/**
 * Prototype terrain definition
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::prototype::PrototypeTerrain final
{
private:
	float width { -1 };
	float depth { -1 };
	vector<float> terrainHeightVector;
	int waterPositionMapIdx { 0 };
	map<int, float> waterPositionMapsHeight;
	map<int, map<int, set<int>>> waterPositionMaps;

public:

	/**
	 * Public constructor
	 */
	inline PrototypeTerrain() {
	}

	/**
	 * Destructor
	 */
	~PrototypeTerrain() {
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
	 * Get water position maps indices
	 * @return water position maps indices
	 */
	inline vector<int> getWaterPositionMapsIndices() {
		vector<int> waterPositionMapsIndices;
		for (auto waterPositionMapsIt: waterPositionMaps) {
			waterPositionMapsIndices.push_back(waterPositionMapsIt.first);
		}
		return waterPositionMapsIndices;
	}

	/**
	 * @return allocated water position map idx
	 */
	inline int allocateWaterPositionMapIdx() {
		return waterPositionMapIdx++;
	}

	/**
	 * Get water position map height at given index
	 * @param idx index
	 * @return water position map height at given index
	 */
	inline float getWaterPositionMapHeight(int idx) {
		return waterPositionMapsHeight[idx];
	}

	/**
	 * Get water position map height at given index
	 * @param idx index
	 * @param waterHeight water height
	 * @return water position map height at given index
	 */
	inline void setWaterPositionMapHeight(int idx, float waterHeight) {
		waterPositionMapsHeight[idx] = waterHeight;
	}

	/**
	 * Get water position map at given index
	 * @param idx index
	 * @return water position map
	 */
	inline map<int, set<int>>& getWaterPositionMap(int idx) {
		return waterPositionMaps[idx];
	}

	/**
	 * Remove water position map at given index
	 * @param idx index
	 */
	inline void removeWaterPositionMap(int idx) {
		waterPositionMapsHeight.erase(idx);
		waterPositionMaps.erase(idx);
	}

};
