#pragma once

#include <map>
#include <string>

#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/FlowMapCell.h>

using std::map;
using std::string;
using std::to_string;

using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utils::FlowMapCell;

/**
 * Flow map
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::FlowMap {
friend class PathFinding;
private:
	float stepSize;
	map<string, FlowMapCell> cells;

	/**
	 * Adds a cell to flow map
	 * @param position position
	 * @param walkable walkable
	 * @param direction direction
	 */
	inline void addCell(const Vector3& position, bool walkable, const Vector3& direction) {
		auto cellId = toKey(
			Math::floor(position.getX() / stepSize) * stepSize,
			Math::floor(position.getZ() / stepSize) * stepSize
		);
		cells[cellId] = FlowMapCell(position, walkable, direction);
	}

public:

	/**
	 * Return string representation of given x,z for path finding key
	 * @param x x
	 * @param z z
	 * @return string representation
	 */
	inline static string toKey(float x, float z) {
		string result;
		int32_t value = 0;
		result.reserve(sizeof(value) * 2);
		value = static_cast<int>(x * 10.0f);
		result.append((char*)&value, sizeof(value));
		value = static_cast<int>(z * 10.0f);
		result.append((char*)&value, sizeof(value));
		return result;
	}

	/**
	 * Constructor
	 */
	inline FlowMap(float stepSize): stepSize(stepSize) {
	}

	/**
	 * @return step size 
	 */
	inline float getStepSize() {
		return stepSize;
	} 

	/**
	 * Get cell
	 * @param x x
	 * @param z z
	 */
	inline FlowMapCell* getCell(float x, float z) {
		auto cellId = toKey(
			Math::floor(x / stepSize) * stepSize,
			Math::floor(z / stepSize) * stepSize
		);
		auto cellIt = cells.find(cellId);
		if (cellIt == cells.end()) return nullptr;
		return &cellIt->second;
	}

	/**
	 * Get cell
	 * @param x x
	 * @param z z
	 */
	inline const FlowMapCell* getCell(float x, float z) const {
		auto cellId = toKey(
			Math::floor(x / stepSize) * stepSize,
			Math::floor(z / stepSize) * stepSize
		);
		auto cellIt = cells.find(cellId);
		if (cellIt == cells.end()) return nullptr;
		return &cellIt->second;
	}

};
