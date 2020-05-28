#pragma once

#include <map>
#include <stack>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/FlowMap.h>
#include <tdme/utils/FlowMapCell.h>
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
using tdme::utils::Console;
using tdme::utils::FlowMap;
using tdme::utils::FlowMapCell;
using tdme::utils::PathFindingCustomTest;

/**
 * Path finding class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::PathFinding final
{
public:
	static constexpr bool VERBOSE { false };

	/**
	 * Public constructor
	 * @param world world
	 * @param sloping sloping
	 * @param stepsMax steps max
	 * @param actorHeight actor height
	 * @param stepSize step size
	 * @param stepSizeLast step size last
	 * @param actorStepUpMax actor step up max
	 * @param skipOnCollisionTypeIds skip cells with given collision type ids
	 * @param maxTries max tries
	 */
	PathFinding(World* world, bool sloping = false, int stepsMax = 1000, float actorHeight = 2.0f, float stepSize = 0.5f, float stepSizeLast = 0.75f, float actorStepUpMax = 0.25f, uint16_t skipOnCollisionTypeIds = 0, int maxTries = 5);

	/**
	 * Destructor
	 */
	~PathFinding();

	/**
	 * @return step size
	 */
	inline float getStepSize() {
		return stepSize;
	}

	/**
	 * Clear caches
	 */
	inline void reset() {
		walkableCache.clear();
	}

	/**
	 * Return string representation of given x,y,z for path finding key
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param stepSize step size  
	 * @return string representation
	 */
	inline string toKey(float x, float y, float z) {
		return toKey(x, y, z, stepSize);
	}

	/**
	 * Return string representation of given x,y,z for path finding key
	 * @param x x
	 * @param y y
	 * @param z z
	 * @return string representation
	 */
	inline static string toKey(float x, float y, float z, float stepSize) {
		/*
		string result;
		int32_t value = 0;
		result.reserve(sizeof(value) * 3);
		value = static_cast<int>(x * 10.0f);
		result.append((char*)&value, sizeof(value));
		value = static_cast<int>(y * 10.0f);
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
		value = static_cast<int>(Math::ceil(y / stepSize));
		result+= to_string(value);
		result+= ",";
		value = static_cast<int>(Math::ceil(z / stepSize));
		result+= to_string(value);
		return result;
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
	 * @param y y
	 * @param z z
	 * @return string representation
	 */
	inline static string toKeyInt(int x, int y, int z) {
		string result;
		result+= to_string(x);
		result+= ",";
		result+= to_string(y);
		result+= ",";
		result+= to_string(z);
		return result;
	}

	/**
	 * Finds path to given end position
	 * @param startPosition start position
	 * @param endPosition end position
	 * @param collisionTypeIds collision type ids
	 * @param path path from actor to target
	 * @param alternativeEndSteps alternative end steps
	 * @param customTest custom test
	 * @return success
	 */
	bool findPath(const Vector3& startPosition, const Vector3& endPosition, const uint16_t collisionTypeIds, vector<Vector3>& path, int alternativeEndSteps = 0, PathFindingCustomTest* customTest = nullptr);

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

	/**
	 * Create flow map
	 * @param endPosition end position
	 * @param center flow map center
	 * @param depth flow map depth
	 * @param width flow map width
	 * @param collisionTypeIds collision type ids
	 * @param customTest custom test
	 * @param path path to test along
	 * @return flow map
	 */
	FlowMap* createFlowMap(const vector<Vector3>& endPositions, const Vector3& center, float depth, float width, const uint16_t collisionTypeIds, const vector<Vector3>& path = vector<Vector3>(), PathFindingCustomTest* customTest = nullptr);

private:
	/**
	 * Path finding node
	 */
	struct PathFindingNode final
	{
		/**
		 * Node key
		 */
		string key;

		/**
		 * Position
		 */
		Vector3 position;

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
		string previousNodeKey;

	};

	/**
	 * Computes non square rooted distance between a and b
	 * @param a node a
	 * @param b node b
	 * @return non square rooted distance
	 */
	inline float computeDistance(const PathFindingNode& a, const PathFindingNode& b) {
		return a.position.clone().sub(b.position).computeLengthSquared();
	}

	/**
	 * Returns if nodes are equals
	 * @param a a
	 * @param bX b x coordinate
	 * @param bY b y coordinate
	 * @param bZ b z coordinate
	 * @return if node a == node b
	 */
	inline bool equals(const PathFindingNode& a, float bX, float bY, float bZ) {
		return a.position.clone().sub(Vector3(bX, bY, bZ)).computeLengthSquared() < Math::square(0.1f);
	}

	/**
	 * Returns if nodes are equals for (last node test)
	 * @param a a
	 * @param lastNode b
	 * @return if node a == node b
	 */
	inline bool equalsLastNode(const PathFindingNode& a, const PathFindingNode& b) {
		return a.position.clone().sub(b.position).computeLengthSquared() < Math::square(stepSizeLast);
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
	 * Checks if a cell is slope walkable
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param successorX x
	 * @param successorY y
	 * @param successorZ z
	 * @param collisionTypeIds collision type ids or 0 for default
	 * @return if cell is walkable
	 */
	bool isSlopeWalkableInternal(float x, float y, float z, float successorX, float successorY, float successorZ, uint16_t collisionTypeIds = 0);

	/**
	 * Sets up the PathFinding, it needs to be called after constructing the object
	 * @param startPosition start position
	 * @param endPosition end position
	 */
	void start(const Vector3& startPosition, const Vector3& endPosition);

	/**
	 * Processes one step in AStar path finding
	 * @return step status
	 */
	void step(const PathFindingNode& node);

	// properties
	World* world { nullptr };
	PathFindingCustomTest* customTest { nullptr };
	bool sloping;
	int stepsMax;
	float actorHeight;
	float stepSize;
	float stepSizeLast;
	float actorStepUpMax;
	uint16_t skipOnCollisionTypeIds;
	uint16_t collisionTypeIds;
	int maxTries;
	PathFindingNode end;
	stack<PathFindingNode> successorNodes;
	map<string, PathFindingNode> openNodes;
	map<string, PathFindingNode> closedNodes;
	BoundingVolume* actorBoundingVolume { nullptr };
	BoundingVolume* actorBoundingVolumeSlopeTest { nullptr };
	map<string, float> walkableCache;
};
