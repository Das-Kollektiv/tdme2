#pragma once

#include <tdme/math/Vector3.h>

using tdme::math::Vector3;

/**
 * Flow map cell
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::FlowMapCell {
public:
	/**
	 * Default constructor
	 */
	FlowMapCell(): walkable(false) {
	} 

	/**
	 * Private constructor
	 * @param position position
	 * @param walkable walkable
	 * @param direction direction
	 */
	FlowMapCell(const Vector3& position, bool walkable, const Vector3& direction): position(position), walkable(walkable), direction(direction) {
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

private:
	Vector3 position;
	bool walkable;
	Vector3 direction;
};
