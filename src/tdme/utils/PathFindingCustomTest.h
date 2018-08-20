#pragma once

#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

/**
 * Path finding custom test interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::utils::PathFindingCustomTest
{

	/**
	 * Is walkable user test
	 * @param actorObv actor cbv
	 * @param x x
	 * @param y y
	 * @param z z
	 * @return is walkable
	 */
	virtual bool isWalkable(BoundingVolume* actorObv, float x, float y, float z) = 0;

	/**
	 * Destructor
	 */
	virtual ~PathFindingCustomTest() {}

};
