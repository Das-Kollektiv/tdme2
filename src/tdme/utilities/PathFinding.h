#pragma once

#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/Transform.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FlowMap.h>
#include <tdme/utilities/FlowMapCell.h>
#include <tdme/utilities/PathFindingCustomTest.h>
#include <tdme/utilities/Pool.h>

using std::get;
using std::map;
using std::stack;
using std::string;
using std::to_string;
using std::tuple;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transform;
using tdme::engine::Texture;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::FlowMap;
using tdme::utilities::FlowMapCell;
using tdme::utilities::PathFindingCustomTest;
using tdme::utilities::Pool;

/**
 * Path finding class
 * @author Andreas Drewke
 */
class tdme::utilities::PathFinding final
{
public:
	static constexpr bool VERBOSE { true };

	// forbid class copy
	FORBID_CLASS_COPY(PathFinding)

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
	 * @param flowMapStepSize flow map step size
	 * @param flowMapScaleActorBoundingVolumes flow map scale actor bounding volumes
	 */
	PathFinding(
		World* world,
		bool sloping = false,
		int stepsMax = 1000,
		float actorHeight = 2.0f,
		float stepSize = 0.5f,
		float stepSizeLast = 0.75f,
		float actorStepUpMax = 0.25f,
		uint16_t skipOnCollisionTypeIds = 0,
		int maxTries = 5,
		float flowMapStepSize = 0.5f,
		float flowMapScaleActorBoundingVolumes = 1.0f
	);

	/**
	 * Destructor
	 */
	~PathFinding();

	/**
	 * Set navigation map which allows fast look ups if Terrain::STEP_SIZE dimensioned cells are walkable
	 * @param navigationMap navigation map
	 */
	inline void setNavigationMap(Texture* navigationMap) {
		this->navigationMap	= navigationMap;
	}

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
		walkableSlopeCache.clear();
	}

	/**
	 * Return path finding node id of given x, y, z position components
	 * @param x x
	 * @param y y
	 * @param z z
	 * @return path finding node id of given x, y, z position components
	 */
	inline const tuple<int, int, int> toId(float x, float y, float z) {
		return toId(x, y, z, stepSize);
	}

	/**
	 * Return path finding node id of given x, y, z position components
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param stepSize step size
	 * @return path finding node id of given x, y, z position components
	 */
	inline static const tuple<int, int, int> toId(float x, float y, float z, float stepSize) {
		return tuple<int, int, int> {
			static_cast<int>(Math::ceil(x / stepSize)),
			static_cast<int>(Math::ceil(y / 0.1f)),
			static_cast<int>(Math::ceil(z / stepSize))
		};
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
	inline float alignPositionComponent(float value) {
		return alignPositionComponent(value, stepSize);
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
	 * Returns integer position component
	 * @param value value
	 * @return integer position component
	 */
	inline int getIntegerPositionComponent(float value) {
		return getIntegerPositionComponent(value, stepSize);
	}

	/**
	 * Return string representation of given x,z integer flow map position representation for path finding id
	 * @param x x
	 * @param y y
	 * @param z z
	 * @return string representation
	 */
	inline static const tuple<int, int, int> toIdInt(int x, int y, int z) {
		return tuple<int, int, int> {
			x,
			y,
			z
		};
	}

	/**
	 * Finds path to given end position
	 * @param startPosition start position
	 * @param endPosition end position
	 * @param collisionTypeIds collision type ids
	 * @param path path from actor to target
	 * @param alternativeEndSteps alternative end steps
	 * @param maxTriesOverride max tries override or -1 for default
	 * @param customTest custom test
	 * @return success
	 */
	inline bool findPath(const Vector3& startPosition, const Vector3& endPosition, const uint16_t collisionTypeIds, vector<Vector3>& path, int alternativeEndSteps = 0, int maxTriesOverride = -1, PathFindingCustomTest* customTest = nullptr) {
		return findPathCustom(startPosition, endPosition, stepSize, 1.0f, collisionTypeIds, path, alternativeEndSteps, maxTriesOverride, customTest);
	}


	/**
	 * Finds path to given end position for flow maps
	 * @param startPosition start position
	 * @param endPosition end position
	 * @param collisionTypeIds collision type ids
	 * @param path path from actor to target
	 * @param alternativeEndSteps alternative end steps
	 * @param maxTriesOverride max tries override or -1 for default
	 * @param customTest custom test
	 * @return success
	 */
	inline bool findFlowMapPath(const Vector3& startPosition, const Vector3& endPosition, const uint16_t collisionTypeIds, vector<Vector3>& path, int alternativeEndSteps = 0, int maxTriesOverride = -1, PathFindingCustomTest* customTest = nullptr) {
		return findPathCustom(startPosition, endPosition, flowMapStepSize, flowMapScaleActorBoundingVolumes, collisionTypeIds, path, alternativeEndSteps, maxTriesOverride, customTest);
	}

	/**
	 * Finds path to given end position
	 * @param startPosition start position
	 * @param endPosition end position
	 * @param stepSize step size
	 * @param scaleActorBoundingVolumes scale actor bounding volumes
	 * @param collisionTypeIds collision type ids
	 * @param path path from actor to target
	 * @param alternativeEndSteps alternative end steps
	 * @param maxTriesOverride max tries override or -1 for default
	 * @param customTest custom test
	 * @return success
	 */
	bool findPathCustom(const Vector3& startPosition, const Vector3& endPosition, float stepSize, float scaleActorBoundingVolumes, const uint16_t collisionTypeIds, vector<Vector3>& path, int alternativeEndSteps = 0, int maxTriesOverride = -1, PathFindingCustomTest* customTest = nullptr);

	/**
	 * Checks if a cell is walkable
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param height y stepped up
	 * @param stepSize step size
	 * @param scaleActorBoundingVolumes scale actor bounding volumes
	 * @param flowMapRequest flow map request
	 * @param collisionTypeIds collision type ids or 0 for default
	 * @param ignoreStepUpMax ignore step up max
	 * @return if cell is walkable
	 */
	bool isWalkable(float x, float y, float z, float& height, float stepSize, float scaleActorBoundingVolumes, bool flowMapRequest, uint16_t collisionTypeIds = 0, bool ignoreStepUpMax = false);

	/**
	 * Create flow map
	 * @param endPositions end positions
	 * @param center flow map center
	 * @param depth flow map depth
	 * @param width flow map width
	 * @param collisionTypeIds collision type ids
	 * @param path path to test along
	 * @param complete complete
	 * @param customTest custom test
	 * @return flow map
	 */
	FlowMap* createFlowMap(const vector<Vector3>& endPositions, const Vector3& center, float depth, float width, const uint16_t collisionTypeIds, const vector<Vector3>& path = vector<Vector3>(), bool complete = true, PathFindingCustomTest* customTest = nullptr);

	/**
	 * Generate direct path from start to end
	 * @param start start
	 * @param end end
	 * @return path nodes
	 */
	const vector<Vector3> generateDirectPath(const Vector3& start, const Vector3& end);
private:
	/**
	 * Path finding node
	 */
	struct PathFindingNode final
	{
		/**
		 * Node id
		 */
		tuple<int, int, int> id;

		/**
		 * Has previous node
		 */
		bool hasPreviousNode;

		/**
		 * Previous node
		 */
		tuple<int, int, int> previousNodeId;

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
		 * Integer position along x axis
		 */
		int x;

		/**
		 * Integer position along y axis
		 */
		int y;

		/**
		 * Integer position along z axis
		 */
		int z;
	};

	/**
	 * Path finding node pool
	 */
	class PathFindingNodesPool: public Pool<PathFindingNode> {
	public:
		/**
		 * Public constructor
		 */
		inline PathFindingNodesPool() {
		}

	protected:
		/**
		 * Instantiate a path finding node
		 */
		inline PathFindingNode* instantiate() override {
			return new PathFindingNode();
		}

	};

	struct PathFindingNodeId_Hash {
		std::size_t operator()(const tuple<int, int, int>& k) const {
			std::hash<uint64_t> hashVal;
			return hashVal(get<0>(k) ^ get<1>(k) ^ get<2>(k));
		}
	};

	struct WalkableCache_Hash {
		std::size_t operator()(const tuple<uint8_t, uint8_t, int, int, int, uint16_t, bool>& k) const {
			std::hash<uint64_t> hashVal;
			return hashVal(static_cast<int>(get<0>(k)) ^ static_cast<int>(get<1>(k)) ^ get<2>(k) ^ get<3>(k) ^ get<4>(k) ^ static_cast<int>(get<5>(k)) ^ static_cast<int>(get<6>(k)));
		}
	};

	struct WalkableSlopeCache_Hash {
		std::size_t operator()(const tuple<uint8_t, uint8_t, int, int, int, uint16_t, int16_t>& k) const {
			std::hash<uint64_t> hashVal;
			return hashVal(static_cast<int>(get<0>(k)) ^ static_cast<int>(get<1>(k)) ^ get<2>(k) ^ get<3>(k) ^ get<4>(k) ^ static_cast<int>(get<5>(k)) ^ static_cast<int>(get<6>(k)));
		}
	};

	/**
	 * Computes non square rooted distance between a and b
	 * @param a node a
	 * @param b node b
	 * @return non square rooted distance
	 */
	inline float computeDistance(const PathFindingNode* a, const PathFindingNode* b) {
		return a->position.clone().sub(b->position).computeLengthSquared();
	}

	/**
	 * Computes minimal non square rooted distance between node and end point
	 * @param node node
	 * @return non square rooted distance
	 */
	inline float computeDistanceToEnd(const PathFindingNode* node) {
		return node->position.clone().sub(end.position).computeLengthSquared();
	}

	/**
	 * Returns if nodes are equals
	 * @param a a
	 * @param bX b x coordinate
	 * @param bY b y coordinate
	 * @param bZ b z coordinate
	 * @return if node a == node b
	 */
	inline bool equals(const PathFindingNode* a, float bX, float bY, float bZ) {
		return a->position.clone().sub(Vector3(bX, bY, bZ)).computeLengthSquared() < Math::square(0.1f);
	}

	/**
	 * Returns if nodes are equals for (last node test)
	 * @param a a
	 * @param lastNode b
	 * @return if node a == node b
	 */
	inline bool equalsLastNode(const PathFindingNode* a, const PathFindingNode* b) {
		return a->position.clone().sub(b->position).setY(0.0f).computeLengthSquared() < stepSizeLast * stepSizeLast + stepSizeLast * stepSizeLast + 0.1f;
	}

	/**
	 * Checks if a cell is walkable
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param height y stepped up
	 * @param stepSize step size
	 * @param scaleActorBoundingVolumes scale actor bounding volumes
	 * @param flowMapRequest flow map request
	 * @param customTest custom test
	 * @param collisionTypeIds collision type ids or 0 for default
	 * @param ignoreStepUpMax ignore step up max
	 * @return if cell is walkable
	 */
	bool isWalkableInternal(float x, float y, float z, float& height, float stepSize, float scaleActorBoundingVolumes, bool flowMapRequest, PathFindingCustomTest* customTest = nullptr, uint16_t collisionTypeIds = 0, bool ignoreStepUpMax = false);

	/**
	 * Checks if a cell is slope walkable
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param successorX x
	 * @param successorY y
	 * @param successorZ z
	 * @param stepSize step size
	 * @param scaleActorBoundingVolumes scale actor bounding volumes
	 * @param customTest custom test
	 * @param collisionTypeIds collision type ids or 0 for default
	 * @return if cell is walkable
	 */
	bool isSlopeWalkableInternal(float x, float y, float z, float successorX, float successorY, float successorZ, float stepSize, float scaleActorBoundingVolumes, bool flowMapRequest, PathFindingCustomTest* customTest = nullptr, uint16_t collisionTypeIds = 0);

	/**
	 * Processes one step in AStar path finding
	 * @param node node
	 * @param stepSize step size
	 * @param scaleActorBoundingVolumes scale actor bounding volumes
	 * @param nodesToTest nodes to test or nullptr, applies to flow cost map generation
	 * @param flowMapRequest flow map request
	 * @param customTest custom test
	 * @return step status
	 */
	void step(PathFindingNode* node, float stepSize, float scaleActorBoundingVolumes, const unordered_set<tuple<int, int, int>, PathFindingNodeId_Hash>* nodesToTest, bool flowMapRequest, PathFindingCustomTest* customTest = nullptr);

	// properties
	World* world { nullptr };
	bool sloping;
	int stepsMax;
	float actorHeight;
	float stepSize;
	float stepSizeLast;
	float actorStepUpMax;
	uint16_t skipOnCollisionTypeIds;
	uint16_t collisionTypeIds;
	int maxTries;
	float flowMapStepSize;
	float flowMapScaleActorBoundingVolumes;
	PathFindingNode end;
	unordered_map<tuple<int, int, int>, PathFindingNode*, PathFindingNodeId_Hash> openNodes;
	unordered_map<tuple<int, int, int>, PathFindingNode*, PathFindingNodeId_Hash> closedNodes;
	PathFindingNodesPool pathFindingNodesPool;
	unordered_map<tuple<uint8_t, uint8_t, int, int, int, uint16_t, bool>, float, WalkableCache_Hash> walkableCache;
	unordered_map<tuple<uint8_t, uint8_t, int, int, int, uint16_t, int16_t>, float, WalkableSlopeCache_Hash> walkableSlopeCache;
	Texture* navigationMap { nullptr };
};
