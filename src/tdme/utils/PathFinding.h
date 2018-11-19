#pragma once

#include <map>
#include <stack>
#include <string>
#include <vector>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/PathFindingNode.h>
#include <tdme/utils/PathFindingCustomTest.h>

using std::map;
using std::stack;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Transformations;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utils::PathFindingNode;
using tdme::utils::PathFindingCustomTest;

/**
 * Path Finding
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::PathFinding final
{
public:
	enum PathFindingStatus {PATH_STEP, PATH_FOUND, PATH_NOWAY};

	/**
	 * Public constructor
	 * @param world world
	 * @param sloping sloping
	 * @param stepsMax steps max
	 * @param stepSize step size
	 * @param stepSizeLast step size last
	 * @param actorStepUpMax actor step up max
	 */
	PathFinding(World* world, bool sloping = false, int stepsMax = 1000, float stepSize = 0.5f, float stepSizeLast = 0.75f, float actorStepUpMax = 0.25f);

	/**
	 * Destructor
	 */
	~PathFinding();

	/**
	 * Return string representation of given x,y,z for path finding key
	 * @param x x
	 * @param y y
	 * @param z z
	 * @return string representation
	 */
	inline static string toKey(float x, float y, float z) {
		return
			floatToStringKey(x) + "," +
			floatToStringKey(y) + "," +
			floatToStringKey(z);
	}

	/**
	 * Finds path to given end position
	 * @param actorBoundingVolume actor original bounding volume
	 * @param actorTransformations current actor transformations
	 * @param endPosition end position
	 * @param collisionTypeIds collision type ids
	 * @param path path from actor to target
	 * @param customTest custom test
	 * @return success
	 */
	bool findPath(BoundingVolume* actorBoundingVolume, const Transformations& actorTransformations, const Vector3& endPosition, const uint16_t collisionTypeIds, vector<Vector3>& path, PathFindingCustomTest* customTest = nullptr);

	/**
	 * Checks if a cell is walkable
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param height y stepped up
	 * @param collisionTypeIds collision type ids or 0 for default
	 * @param ignoreStepUpMax ignore step up max
	 * @return if cell is walkable
	 */
	bool isWalkable(float x, float y, float z, float& height, uint16_t collisionTypeIds = 0, bool ignoreStepUpMax = false);

private:
	/**
	 * Reset path finding
	 */
	void reset();

	/**
	 * Return string representation of float for key usage
	 * @param value value
	 * @return string representation
	 */
	inline static string floatToStringKey(float value) {
		string floatString = to_string(value);
		return floatString.substr(0, floatString.length() - 5);
	}

	/**
	 * Computes non square rooted distance between a and b
	 * @param a a
	 * @param b b
	 * @return non square rooted distance
	 */
	inline float computeDistance(PathFindingNode* a, PathFindingNode* b) {
		float dx = a->x - b->x;
		float dy = a->y - b->y;
		float dz = a->z - b->z;
		return (dx * dx) + (dy * dy) + (dz * dz);
	}

	/**
	 * Returns if nodes are equals
	 * @param a a
	 * @param bX b x coordinate
	 * @param bY b y coordinate
	 * @param bZ b z coordinate
	 * @return if node a == node b
	 */
	inline bool equals(PathFindingNode* a, float bX, float bY, float bZ) {
		return
			(
				Math::abs(a->x - bX) < 0.1f &&
				Math::abs(a->y - bY) < 0.1f &&
				Math::abs(a->z - bZ) < 0.1f
			);
	}

	/**
	 * Returns if nodes are equals for (last node test)
	 * @param a a
	 * @param lastNode b
	 * @return if node a == node b
	 */
	inline bool equalsLastNode(PathFindingNode* a, PathFindingNode* lastNode) {
		return
			(a == lastNode) ||
			(
				Math::abs(a->x - lastNode->x) < stepSizeLast &&
				Math::abs(a->y - lastNode->y) < stepSizeLast &&
				Math::abs(a->z - lastNode->z) < stepSizeLast
			);
	}

	/**
	 * Checks if a cell is walkable
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param height y stepped up
	 * @param collisionTypeIds collision type ids or 0 for default
	 * @param ignoreStepUpMax ignore step up max
	 * @return if cell is walkable
	 */
	bool isWalkableInternal(float x, float y, float z, float& height, uint16_t collisionTypeIds = 0, bool ignoreStepUpMax = false);

	/**
	 * Sets up the PathFinding, it needs to be called after constructing the object
	 * @param startPosition start position
	 * @param endPosition end position
	 */
	void start(Vector3 startPosition, Vector3 endPosition);

	/**
	 * Processes one step in AStar path finding
	 * @return step status
	 */
	PathFindingStatus step();

	// properties
	World* world;
	PathFindingCustomTest* customTest;
	bool sloping;
	int stepsMax;
	float stepSize;
	float stepSizeLast;
	float actorStepUpMax;
	uint16_t collisionTypeIds;
	PathFindingNode* end;
	stack<PathFindingNode*> successorNodes;
	map<string, PathFindingNode*> openNodes;
	map<string, PathFindingNode*> closedNodes;
	Vector3 sideVector { 1.0f, 0.0f, 0.0f };
	Vector3 forwardVector { 0.0f, 0.0f, 1.0f };
	Transformations actorTransformations;
	BoundingVolume* actorBoundingVolume;
	float actorXHalfExtension;
	float actorZHalfExtension;
};
