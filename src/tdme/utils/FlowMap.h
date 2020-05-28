#pragma once

#include <map>
#include <string>

#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/FlowMapCell.h>

using std::map;
using std::string;
using std::to_string;

using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utils::Console;
using tdme::utils::FlowMapCell;

/**
 * Flow map
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::FlowMap final {
friend class PathFinding;
private:
	float stepSize;
	map<string, FlowMapCell> cells;

	/**
	 * Adds a cell to flow map
	 * @param id id
	 * @param position position
	 * @param walkable walkable
	 * @param direction direction
	 */
	inline void addCell(const string& id, const Vector3& position, bool walkable, const Vector3& direction) {
		cells[id] = FlowMapCell(position, walkable, direction);
	}

	/**
	 * Checks if a cell exists in flow map
	 * @param id id
	 */
	inline bool hasCell(const string& id) {
		auto cellIt = cells.find(id);
		return cellIt != cells.end();
	}

public:
	/**
	 * Align position component
	 * @param value value which is usually a position vector 3 position component
	 * @param stepSize step size
	 */
	inline static float alignPositionComponent(float value, float stepSize) {
		return Math::floor(value / stepSize) * stepSize;
	}

	/**
	 * Align position component
	 * @param value value which is usually a position vector 3 position component
	 */
	inline float alignPositionComponent(float value) const {
		return alignPositionComponent(value, stepSize);
	}

	/**
	 * Return string representation of given x,z for path finding key
	 * @param x x
	 * @param z z
	 * @return string representation
	 */
	inline string toKey(float x, float z) const {
		return toKey(x, z, stepSize);
	}

	/**
	 * Return string representation of given x,z for path finding key
	 * @param x x
	 * @param z z
	 * @param stepSize step size
	 * @return string representation
	 */
	inline static string toKey(float x, float z, float stepSize) {
		/*
		string result;
		int32_t value = 0;
		result.reserve(sizeof(value) * 2);
		value = static_cast<int>(x * 10.0f);
		result.append((char*)&value, sizeof(value));
		value = static_cast<int>(z * 10.0f);
		result.append((char*)&value, sizeof(value));
		return result;
		*/
		string result;
		int32_t value = 0;
		value = static_cast<int>(Math::ceil(x / stepSize));
		result+= to_string(value);
		result+= ",";
		value = static_cast<int>(Math::ceil(z / stepSize));
		result+= to_string(value);
		return result;
	}

	/**
	 * Returns integer position component
	 * @param value value
	 * @return integer position component
	 */
	inline int getIntegerPositionComponent(float value) {
		return static_cast<int>(alignPositionComponent(value, stepSize) / stepSize);
	}

	/**
	 * Returns integer position component
	 * @param value value
	 * @param stepSize step size
	 * @return integer position component
	 */
	inline static int getIntegerPositionComponent(float value, float stepSize) {
		return static_cast<int>(alignPositionComponent(value, stepSize) / stepSize);
	}

	/**
	 * Return string representation of given x,z integer flow map position representation for path finding key
	 * @param x x
	 * @param z z
	 * @return string representation
	 */
	inline static string toKeyInt(int x, int z) {
		string result;
		result+= to_string(x);
		result+= ",";
		result+= to_string(z);
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
	inline float getStepSize() const {
		return stepSize;
	} 

	/**
	 * Get cell by id
	 * @param id id
	 * @return cell
	 */
	inline const FlowMapCell* getCell(const string& id) const {
		auto cellIt = cells.find(id);
		if (cellIt == cells.end()) return nullptr;
		return &cellIt->second;
	}

	/**
	 * Get cell by id
	 * @param id id
	 * @return cell
	 */
	inline FlowMapCell* getCell(const string& id) {
		auto cellIt = cells.find(id);
		if (cellIt == cells.end()) return nullptr;
		return &cellIt->second;
	}

	/**
	 * Get cell by position
	 * @param x x
	 * @param z z
	 * @return cell
	 */
	inline const FlowMapCell* getCell(float x, float z) const {
		auto id = toKey(
			alignPositionComponent(x),
			alignPositionComponent(z)
		);
		auto cellIt = cells.find(id);
		if (cellIt == cells.end()) return nullptr;
		return &cellIt->second;
	}

	/**
	 * Get cell by position
	 * @param x x
	 * @param z z
	 * @return cell
	 */
	inline FlowMapCell* getCell(float x, float z) {
		auto cellId = toKey(
			alignPositionComponent(x),
			alignPositionComponent(z)
		);
		auto cellIt = cells.find(cellId);
		if (cellIt == cells.end()) return nullptr;
		return &cellIt->second;
	}

	/**
	 * Cell map getter
	 * @returns cell map
	 */
	inline const map<string, FlowMapCell>& getCellMap() {
		return cells;
	}

};
