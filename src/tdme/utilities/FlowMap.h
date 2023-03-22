#pragma once

#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FlowMapCell.h>
#include <tdme/utilities/Reference.h>

using std::get;
using std::string;
using std::to_string;
using std::tuple;
using std::unordered_map;
using std::vector;

using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::FlowMapCell;
using tdme::utilities::Reference;

/**
 * Flow map
 * @author Andreas Drewke
 */
class tdme::utilities::FlowMap final: public Reference {
friend class PathFinding;
private:
	struct FlowMapCellId_Hash {
		std::size_t operator()(tuple<int, int> k) const {
			std::hash<uint64_t> hashVal;
			return hashVal(get<0>(k) ^ get<1>(k));
		}
	};

	bool complete;
	float stepSize;
	unordered_map<tuple<int, int>, FlowMapCell*, FlowMapCellId_Hash> cells;
	vector<Vector3> endPositions;
	vector<Vector3> path;

	/**
	 * Private destructor
	 */
	inline ~FlowMap() {
		for (auto& cellIt: cells) delete cellIt.second;
	}

	/**
	 * Set flow map complete flag
	 * @param complete complete
	 */
	inline void setComplete(bool complete) {
		this->complete = complete;
	}

	/**
	 * Adds a cell to flow map
	 * @param id id
	 * @param position position
	 * @param walkable walkable
	 * @param direction direction
	 * @param pathIdx path index
	 */
	inline void addCell(const tuple<int, int>& id, const Vector3& position, bool walkable, const Vector3& direction, int pathIdx) {
		cells[id] = new FlowMapCell(position, walkable, direction, pathIdx);
	}

	/**
	 * Checks if a cell exists in flow map
	 * @param id id
	 */
	inline bool hasCell(const tuple<int, int>& id) const {
		auto cellIt = cells.find(id);
		return cellIt != cells.end();
	}

public:
	/**
	 * Return string representation of given x,z for flow map cell id
	 * @param x x
	 * @param z z
	 * @return string representation
	 */
	inline const tuple<int, int> toId(float x, float z) const {
		return toId(x, z, stepSize);
	}

	/**
	 * Return string representation of given x,z for flow map cell id
	 * @param x x
	 * @param z z
	 * @param stepSize step size
	 * @return string representation
	 */
	inline static const tuple<int, int> toId(float x, float z, float stepSize) {
		return tuple<int, int> { static_cast<int>(Math::ceil(x / stepSize)), static_cast<int>(Math::ceil(z / stepSize)) };
	}

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
	 * Returns integer position component
	 * @param value value
	 * @return integer position component
	 */
	inline int getIntegerPositionComponent(float value) const {
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
	 * Return string representation of given x,z integer flow map position representation for flow map cell id
	 * @param x x
	 * @param z z
	 * @return string representation
	 */
	inline static const tuple<int, int> toIdInt(int x, int z) {
		return tuple<int, int> { x, z };
	}

	/**
	 * Constructor
	 * @param path path
	 * @param endPositions end positions
	 * @param stepSize step size
	 */
	inline FlowMap(const vector<Vector3>& path, const vector<Vector3>& endPositions, float stepSize, bool complete = true): path(path), endPositions(endPositions), stepSize(stepSize), complete(complete) {
	}

	/**
	 * @return if flow map is complete
	 */
	inline bool isComplete() const {
		return complete;
	}

	/**
	 * @return step size
	 */
	inline float getStepSize() const {
		return stepSize;
	}

	/**
	 * Returns end positions
	 * @return end positions
	 */
	inline const vector<Vector3>& getEndPositions() const {
		return endPositions;
	}

	/**
	 * Returns path flow map is generated on
	 * @return path
	 */
	inline const vector<Vector3>& getPath() const {
		return path;
	}

	/**
	 * Get cell by id
	 * @param id id
	 * @return cell
	 */
	inline const FlowMapCell* getCell(const tuple<int, int>& id) const {
		auto cellIt = cells.find(id);
		if (cellIt == cells.end()) return nullptr;
		return cellIt->second;
	}

	/**
	 * Get cell by id
	 * @param id id
	 * @return cell
	 */
	inline FlowMapCell* getCell(const tuple<int, int>& id) {
		auto cellIt = cells.find(id);
		if (cellIt == cells.end()) return nullptr;
		return cellIt->second;
	}

	/**
	 * Get cell by position
	 * @param x x
	 * @param z z
	 * @return cell
	 */
	inline const FlowMapCell* getCell(float x, float z) const {
		auto id = toId(
			alignPositionComponent(x),
			alignPositionComponent(z)
		);
		auto cellIt = cells.find(id);
		if (cellIt == cells.end()) return nullptr;
		return cellIt->second;
	}

	/**
	 * Get cell by position
	 * @param x x
	 * @param z z
	 * @return cell
	 */
	inline FlowMapCell* getCell(float x, float z) {
		auto cellId = toId(
			alignPositionComponent(x),
			alignPositionComponent(z)
		);
		auto cellIt = cells.find(cellId);
		if (cellIt == cells.end()) return nullptr;
		return cellIt->second;
	}

	/**
	 * Compute direction also taking neighbour cells into account
	 * @param x x
	 * @param y y
	 * @param direction direction
	 */
	inline const Vector3 computeDirection(float x, float z) const {
		// https://howtorts.github.io/2014/01/04/basic-flow-fields.html
		auto cellCount = 0;
		auto xInt = getIntegerPositionComponent(x);
		auto zInt = getIntegerPositionComponent(z);
		auto f00 = getCell(toIdInt(xInt, zInt));
		if (f00 == nullptr) return Vector3();
		auto f01 = getCell(toIdInt(xInt, zInt + 1));
		auto f10 = getCell(toIdInt(xInt + 1, zInt));
		auto f11 = getCell(toIdInt(xInt + 1, zInt + 1));
		auto xWeight = x - xInt * stepSize;
		auto top = f10 != nullptr?f00->getDirection().clone().scale(1.0f - xWeight).add(f10->getDirection().clone().scale(xWeight)):f00->getDirection();
		auto bottom = f01 != nullptr && f11 != nullptr?f01->getDirection().clone().scale(1.0f - xWeight).add(f11->getDirection().clone().scale(xWeight)):top;
		auto yWeight = z - zInt * stepSize;
		auto direction = top.clone().scale(1.0f - yWeight).add(bottom.clone().scale(yWeight)).normalize();
		return direction;
	}

	/**
	 * Cell map getter
	 * @returns cell map
	 */
	inline const unordered_map<tuple<int, int>, FlowMapCell*, FlowMapCellId_Hash>& getCellMap() const {
		return cells;
	}

	/**
	 * Remove cell by id
	 * @param id id
	 */
	inline void removeCell(const tuple<int, int>& id) {
		auto cellIt = cells.find(id);
		if (cellIt == cells.end()) return;
		cells.erase(cellIt);
	}

	/**
	 * Merge given flow map into this flow map, please note that given flow map step size needs to match this flow maps step size
	 * This only applies to a series of flow maps created sequentially and in correct order along a path
	 * @param flowMap flow map
	 */
	inline void merge(const FlowMap* flowMap) {
		// complete
		complete = flowMap->complete;
		// add path
		auto pathSize = path.size();
		for (auto& pathNode: flowMap->path) {
			path.push_back(pathNode);
		}
		// add cells
		// TODO: check again cell misssing neighbour cells
		for (auto& cellIt: flowMap->cells) {
			auto clonedCell = cellIt.second->clone();
			clonedCell->pathNodeIdx+= pathSize;
			cells[cellIt.first] = clonedCell;
		}
		// check if we have missing neighbour cells
		for (auto& cellIt: flowMap->cells) {
			auto cell = getCell(cellIt.first);
			cell->setMissingNeighborCell(false);
			auto cellX = getIntegerPositionComponent(cell->position.getX());
			auto cellZ = getIntegerPositionComponent(cell->position.getZ());
			auto hadMissingNeighborCell = false;
			for (auto nZ = -1; nZ < 2 && hadMissingNeighborCell == false; nZ++) {
				for (auto nX = -1; nX < 2 && hadMissingNeighborCell == false; nX++) {
					if (nZ == 0 && nX == 0) continue;
					auto neighbourCellId = FlowMap::toIdInt(
						cellX + nX,
						cellZ + nZ
					);
					auto neighbourCell = getCell(neighbourCellId);
					if (neighbourCell == nullptr) {
						cell->setMissingNeighborCell(true);
						hadMissingNeighborCell = true;
						break;
					}
				}
			}
		}
		// end positions
		endPositions = flowMap->endPositions;
	}

	/**
	 * Find nearest cell, which can be used if outside of flow map to find back in
	 * @param x x
	 * @param z z
	 * @param steps steps
	 */
	inline FlowMapCell* findNearestCell(float x, float z, int steps = 8) {
		Vector3 position = Vector3(x, 0.0f, z);
		auto cellX = getIntegerPositionComponent(x);
		auto cellZ = getIntegerPositionComponent(z);
		auto halfSteps = steps / 2;
		FlowMapCell* cellBestFit = nullptr;
		float cellBestFitDistanceSquared = Float::MAX_VALUE;
		for (auto nZ = -halfSteps; nZ < halfSteps; nZ++) {
			for (auto nX = -halfSteps; nX < halfSteps; nX++) {
				auto cellId = FlowMap::toIdInt(
					cellX + nX,
					cellZ + nZ
				);
				auto cellCandidate = getCell(cellId);
				if (cellCandidate == nullptr) continue;
				auto cellCandidateDistanceSquared = cellCandidate->getPosition().clone().sub(position).computeLengthSquared();
				if (cellBestFit == nullptr || cellCandidateDistanceSquared < cellBestFitDistanceSquared) {
					cellBestFit = cellCandidate;
					cellBestFitDistanceSquared = cellCandidateDistanceSquared;
				}
			}
		}
		return cellBestFit;
	}

};
