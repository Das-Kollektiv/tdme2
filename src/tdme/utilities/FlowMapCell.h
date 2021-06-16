#pragma once

#include <tdme/math/Vector3.h>

using tdme::math::Vector3;

/**
 * Flow map cell
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utilities::FlowMapCell final {
	friend class PathFinding;
	friend class FlowMap;
public:
	/**
	 * Default constructor
	 */
	FlowMapCell(): walkable(false), pathNodeIdx(-1) {
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
		pathNodeIdx(pathNodeIdx) {
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
	 * Returns if has missing neighbor cells like it happens with border cells or cells that have direct obstacles neighbors
	 * @return missing neighbor cells
	 */
	inline bool isMissingNeighborCells() const {
		return missingNeighborCells;
	}

	/**
	 * @return is border cell
	 */
	inline bool isBorderCell() const {
		return borderCell;
	}

private:
	Vector3 position;
	bool walkable;
	Vector3 direction;
	int pathNodeIdx;
	bool missingNeighborCells { false };
	bool borderCell { false };

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
	 * Set has missing neighbor cells like it happens with border cells or cells that have direct obstacles neighbors
	 * @param missingNeighborCell missing neighbor cells
	 */
	inline void setMissingNeighborCells(bool missingNeighborCell) {
		this->missingNeighborCells = missingNeighborCell;
	}

	/**
	 * Set if border cell
	 * @param borderCell border cell
	 */
	inline void setBorderCell(bool borderCell) {
		this->borderCell = borderCell;
	}

};
