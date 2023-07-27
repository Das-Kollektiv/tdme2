#pragma once

#include <tdme/tdme.h>
#include <tdme/math/Vector3.h>

using tdme::math::Vector3;

/**
 * Flow map cell
 * @author Andreas Drewke
 */
class tdme::utilities::FlowMapCell final {
	friend class PathFinding;
	friend class FlowMap;
public:
	// forbid class copy
	CLASS_FORBID_COPY(FlowMapCell)

	/**
	 * Default constructor
	 */
	FlowMapCell(): walkable(false), pathNodeIdx(-1), missingNeighborCell(false) {
	}

	/**
	 * Private constructor
	 * @param position position
	 * @param walkable walkable
	 * @param direction direction
	 * @param pathNodeIdx path node index
	 */
	FlowMapCell(const Vector3& position, bool walkable, const Vector3& direction, int pathNodeIdx):
		position(position),
		walkable(walkable),
		direction(direction),
		pathNodeIdx(pathNodeIdx),
		missingNeighborCell(false) {
		//
	}

	/**
	 * Private constructor
	 * @param position position
	 * @param walkable walkable
	 * @param direction direction
	 * @param pathNodeIdx path node index
	 * @param missingNeighborCell missing neighbor cell
	 */
	FlowMapCell(const Vector3& position, bool walkable, const Vector3& direction, int pathNodeIdx, bool missingNeighborCell):
		position(position),
		walkable(walkable),
		direction(direction),
		pathNodeIdx(pathNodeIdx),
		missingNeighborCell(missingNeighborCell) {
		//
	}

	/**
	 * @return cell position
	 */
	inline const Vector3& getPosition() const {
		return position;
	}

	/**
	 * @return if cell is walkable
	 */
	inline bool isWalkable() const {
		return walkable;
	}

	/**
	 * @return cell movement direction
	 */
	inline const Vector3& getDirection() const {
		return direction;
	}

	/**
	 * Get path node index
	 * @return path node index
	 */
	inline int getPathNodeIdx() {
		return pathNodeIdx;
	}

	/**
	 * @return has missing neighbor cell
	 */
	inline bool hasMissingNeighborCell() {
		return missingNeighborCell;
	}

	/**
	 * @return cloned flow map cell
	 */
	inline FlowMapCell* clone() {
		return new FlowMapCell(
			position,
			walkable,
			direction,
			pathNodeIdx,
			missingNeighborCell
		);
	}

private:
	Vector3 position;
	bool walkable;
	Vector3 direction;
	int pathNodeIdx;
	bool missingNeighborCell;

	/**
	 * Set path node index
	 * @param pathNodeIdx path node index
	 */
	inline void setPathNodeIdx(int pathNodeIdx) {
		this->pathNodeIdx = pathNodeIdx;
	}

	/**
	 * Set movement direction
	 * @param cell movement direction
	 */
	inline void setDirection(const Vector3& direction) {
		this->direction = direction;
	}

	/**
	 * Set has missing neighbor cell
	 * @param missingNeighborCell missing neighbor cell
	 */
	inline void setMissingNeighborCell(bool missingNeighborCell) {
		this->missingNeighborCell = missingNeighborCell;
	}

};
