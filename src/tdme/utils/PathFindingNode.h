#pragma once

#include <string>

#include <tdme/utils/fwd-tdme.h>

using std::string;

/**
 * Path Finding Node
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::utils::PathFindingNode final
{
	/**
	 * Node key
	 */
	string key;

	/**
	 * position X position
	 */
	float x;

	/**
	 * position Y position
	 */
	float y;

	/**
	 * position Y position
	 */
	float z;

	/**
	 * Estimated costs to the end plus calculated costs from start to this node
	 */
	float costsAll;

	/**
	 * Calculated costs up to this point (from all previous nodes up to this node) to get to this coordinates from start
	 */
	float costsReachPoint;

	/**
	 * Estimated costs to get to the end
	 */
	float costsEstimated;

	/**
	 * Previous node
	 */
	PathFindingNode* previousNode;

};
