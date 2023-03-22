#include <tdme/utilities/PathFinding.h>

#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/PathFindingCustomTest.h>
#include <tdme/utilities/Pool.h>
#include <tdme/utilities/Time.h>

using std::map;
using std::reverse;
using std::stack;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::PathFindingCustomTest;
using tdme::utilities::Pool;
using tdme::utilities::Time;

using tdme::utilities::PathFinding;

PathFinding::PathFinding(
	World* world,
	bool sloping,
	int stepsMax,
	float actorHeight,
	float stepSize,
	float stepSizeLast,
	float actorStepUpMax,
	uint16_t skipOnCollisionTypeIds,
	int maxTries,
	float flowMapStepSize,
	float flowMapScaleActorBoundingVolumes
	) {
	this->world = world;
	this->customTest = nullptr;
	this->sloping = sloping;
	this->actorBoundingVolume = nullptr;
	this->actorBoundingVolumeSlopeTest = nullptr;
	this->stepsMax = stepsMax;
	this->actorHeight = actorHeight;
	this->stepSize = stepSize;
	this->stepSizeLast = stepSizeLast;
	this->actorStepUpMax = actorStepUpMax;
	this->skipOnCollisionTypeIds = skipOnCollisionTypeIds;
	this->maxTries = maxTries;
	this->collisionTypeIds = 0;
	this->flowMapStepSize = flowMapStepSize;
	this->flowMapScaleActorBoundingVolumes = flowMapScaleActorBoundingVolumes;
}

PathFinding::~PathFinding() {
}

bool PathFinding::isWalkableInternal(float x, float y, float z, float& height, float stepSize, float scaleActorBoundingVolumes, bool flowMapRequest, uint16_t collisionTypeIds, bool ignoreStepUpMax) {
	tuple<uint8_t, uint8_t, int, int, int, uint16_t, bool> cacheId;
	if (flowMapRequest == true) {
		cacheId = tuple<uint8_t, uint8_t, int, int, int, uint16_t, bool> {
			static_cast<uint8_t>(stepSize * 10.0f),
			static_cast<uint8_t>(scaleActorBoundingVolumes * 10.0f),
			static_cast<int>(Math::ceil(x / stepSize)),
			static_cast<int>(Math::ceil(y / 0.1f)),
			static_cast<int>(Math::ceil(z / stepSize)),
			collisionTypeIds,
			ignoreStepUpMax
		};
		auto walkableCacheIt = walkableCache.find(cacheId);
		if (walkableCacheIt != walkableCache.end()) {
			height = walkableCacheIt->second;
			return height > -10000.0f;
		}
	}
	auto walkable = isWalkable(x, y, z, height, stepSize, scaleActorBoundingVolumes, flowMapRequest, collisionTypeIds, ignoreStepUpMax);
	if (flowMapRequest == true) walkableCache[cacheId] = walkable == false?-10000.0f:height;
	if (walkable == false) return false;
	return customTest == nullptr || customTest->isWalkable(this, x, height, z) == true;
}

bool PathFinding::isSlopeWalkableInternal(float x, float y, float z, float successorX, float successorY, float successorZ, float stepSize, float scaleActorBoundingVolumes, bool flowMapRequest, uint16_t collisionTypeIds) {
	float slopeAngle = 0.0f;

	// slope angle and center
	auto toVector = Vector3(successorX, y, successorZ);
	auto fromVector = Vector3(x, y, z);
	auto axis = toVector.clone().sub(fromVector);
	auto center = axis.clone().scale(0.5f).add(fromVector).setY(y + 0.1f);
	axis.normalize();
	slopeAngle = Vector3::computeAngle(
		axis,
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 1.0f, 0.0f)
	);

	tuple<uint8_t, uint8_t, int, int, int, uint16_t, int16_t> cacheId;
	if (flowMapRequest == true) {
		cacheId = tuple<uint8_t, uint8_t, int, int, int, uint16_t, int16_t> {
			static_cast<uint8_t>(stepSize * 10.0f),
			static_cast<uint8_t>(scaleActorBoundingVolumes * 10.0f),
			static_cast<int>(Math::ceil(x / stepSize)),
			static_cast<int>(Math::ceil(y / 0.1f)),
			static_cast<int>(Math::ceil(z / stepSize)),
			collisionTypeIds,
			static_cast<int16_t>(slopeAngle),
		};
		auto walkableCacheIt = walkableCache.find(cacheId);
		if (walkableCacheIt != walkableCache.end()) {
			auto height = walkableCacheIt->second;
			return true;
		}
	}

	// set up transform
	Transform slopeTestTransform;
	slopeTestTransform.setTranslation(center);
	slopeTestTransform.addRotation(Vector3(0.0f, 1.0f, 0.0f), slopeAngle);
	slopeTestTransform.update();

	// update rigid body
	auto actorSlopeTestCollisionBody = world->getBody("tdme.pathfinding.actor.slopetest");
	actorSlopeTestCollisionBody->setTransform(slopeTestTransform);

	// check if actor collides with world
	vector<Body*> collidedRigidBodies;
	auto walkable = world->doesCollideWith(collisionTypeIds == 0?this->collisionTypeIds:collisionTypeIds, actorSlopeTestCollisionBody, collidedRigidBodies) == false;
	if (flowMapRequest == true) walkableCache[cacheId] = walkable == false?-10000.0f:0.0f;
	return walkable;
}

bool PathFinding::isWalkable(float x, float y, float z, float& height, float stepSize, float scaleActorBoundingVolumes, bool flowMapRequest, uint16_t collisionTypeIds, bool ignoreStepUpMax) {
	// determine y height of ground plate of actor bounding volume
	float _z = z - stepSize / 2.0f;
	height = -10000.0f;
	Vector3 actorPosition;
	for (auto i = 0; i <= 4; i++) {
		float _x = x - stepSize / 2.0f;
		for (auto j = 0; j <= 4; j++) {
			Vector3 actorPositionCandidate;
			auto body = world->determineHeight(
				collisionTypeIds == 0?this->collisionTypeIds:collisionTypeIds,
				ignoreStepUpMax == true?10000.0f:actorStepUpMax,
				actorPositionCandidate.set(_x, y, _z),
				actorPosition,
				-10000.0f,
				ignoreStepUpMax == true?10000.0f:y + actorStepUpMax + 0.2f
			);
			if (body == nullptr || ((body->getCollisionTypeId() & skipOnCollisionTypeIds) != 0)) {
				return false;
			}
			if (actorPosition.getY() > height) height = actorPosition.getY();
			_x+= stepSize / 4.0f;
		}
		_z+= stepSize / 4.0f;
	}

	// set up transform
	Transform actorTransform;
	actorTransform.setTranslation(Vector3(x, ignoreStepUpMax == true?height + 0.2f:Math::min(y + actorStepUpMax, height + 0.2f), z));
	actorTransform.update();

	// update rigid body
	auto actorCollisionBody = world->getBody("tdme.pathfinding.actor");
	actorCollisionBody->setTransform(actorTransform);

	// check if actor collides with world
	vector<Body*> collidedRigidBodies;
	return world->doesCollideWith(collisionTypeIds == 0?this->collisionTypeIds:collisionTypeIds, actorCollisionBody, collidedRigidBodies) == false;
}

void PathFinding::step(PathFindingNode* node, float stepSize, float scaleActorBoundingVolumes, const unordered_set<tuple<int, int, int>, PathFindingNodeId_Hash>* nodesToTestPtr, bool flowMapRequest) {
	auto nodeId = node->id;

	// Find valid successors
	stack<PathFindingNode*> successorNodes;
	for (auto z = -1; z <= 1; z++)
	for (auto x = -1; x <= 1; x++)
	if ((z != 0 || x != 0) &&
		(sloping == true ||
		(Math::abs(x) == 1 && Math::abs(z) == 1) == false)) {
		auto successorX = static_cast<float>(x) * stepSize + (nodesToTestPtr != nullptr?static_cast<float>(node->x) * stepSize:node->position.getX());
		auto successorZ = static_cast<float>(z) * stepSize + (nodesToTestPtr != nullptr?static_cast<float>(node->z) * stepSize:node->position.getZ());
		if (nodesToTestPtr != nullptr) {
			auto successorNodeId = toIdInt(
				node->x + x,
				0,
				node->z + z
			);
			if (nodesToTestPtr->find(successorNodeId) == nodesToTestPtr->end()) continue;
		}
		auto slopeWalkable = Math::abs(x) == 1 && Math::abs(z) == 1?isSlopeWalkableInternal(node->position.getX(), node->position.getY(), node->position.getZ(), successorX, node->position.getY(), successorZ, stepSize, scaleActorBoundingVolumes, flowMapRequest):true;
		//
		float yHeight;
		// first node or walkable?
		if (slopeWalkable == true && isWalkableInternal(successorX, node->position.getY(), successorZ, yHeight, stepSize, scaleActorBoundingVolumes, flowMapRequest) == true) {
			// check if successor node equals previous node / node
			if (equals(node, successorX, yHeight, successorZ)) {
				continue;
			}
			// Add the node to the available sucessorNodes
			auto successorNode = pathFindingNodesPool.allocate();
			successorNode->hasPreviousNode = false;
			successorNode->position = Vector3(successorX, yHeight, successorZ);
			successorNode->costsAll = 0.0f;
			successorNode->costsReachPoint = 0.0f;
			successorNode->costsEstimated = 0.0f;
			successorNode->x = node->x + x;
			successorNode->y = flowMapRequest == true?0:getIntegerPositionComponent(successorNode->position.getY(), 0.1f);
			successorNode->z = node->z + z;
			successorNode->id = toIdInt(
				successorNode->x,
				successorNode->y,
				successorNode->z
			);
			successorNodes.push(successorNode);
		}
	}

	// Check successor nodes
	while (successorNodes.empty() == false) {
		auto successorNode = successorNodes.top();

		// Compute successor node's costs by costs to reach nodes point and the computed distance from node to successor node
		float successorCostsReachPoint = node->costsReachPoint + computeDistance(successorNode, node);

		// Find sucessor node in open nodes list
		PathFindingNode* openListNode = nullptr;
		auto openListNodeIt = openNodes.find(successorNode->id);
		if (openListNodeIt != openNodes.end()) {
			openListNode = openListNodeIt->second;
		}

		// found it in open nodes list
		if (openListNode != nullptr) {
			// is the node from open nodes less expensive, discard successor node
			if (openListNode->costsReachPoint <= successorCostsReachPoint) {
				// remove it from stack
				pathFindingNodesPool.release(successorNode);
				successorNodes.pop();
				// discard it
				continue;
			}
		}

		// Find successor node in closed nodes list
		PathFindingNode* closedListNode = nullptr;
		auto closedListNodeIt = closedNodes.find(successorNode->id);
		if (closedListNodeIt != closedNodes.end()) {
			closedListNode = closedListNodeIt->second;
		}

		// found it in closed nodes list
		if (closedListNode != nullptr) {
			// is the node from closed nodes list less expensive, discard successor node
			if (closedListNode->costsReachPoint <= successorCostsReachPoint) {
				// remove it from stack
				pathFindingNodesPool.release(successorNode);
				successorNodes.pop();
				// discard it
				continue;
			}
		}

		// successor node is the node with least cost to this point
		successorNode->hasPreviousNode = true;
		successorNode->previousNodeId = nodeId;
		successorNode->costsReachPoint = successorCostsReachPoint;
		successorNode->costsEstimated = computeDistanceToEnd(successorNode);
		successorNode->costsAll = successorNode->costsReachPoint + successorNode->costsEstimated;

		// remove found node from open nodes list, since it was less optimal
		if (openListNode != nullptr) {
			// remove open list node
			pathFindingNodesPool.release(openListNode);
			openNodes.erase(openListNodeIt);
		}

		// remove found node from closed nodes list, since it was less optimal
		if (closedListNode != nullptr) {
			pathFindingNodesPool.release(closedListNode);
			closedNodes.erase(closedListNodeIt);
		}

		// add successor node to open nodes list, as we might want to check its successors to find a path to the end
		openNodes[successorNode->id] = successorNode;

		// remove it from stack
		successorNodes.pop();
	}

	// add node to closed nodes list, as we checked its successors
	closedNodes[nodeId] = node;

	// remove node from open nodes, as we checked its successors
	openNodes.erase(nodeId);
}

bool PathFinding::findPathCustom(
	const Vector3& startPosition,
	const Vector3& endPosition,
	float stepSize,
	float scaleActorBoundingVolumes,
	const uint16_t collisionTypeIds,
	vector<Vector3>& path,
	int alternativeEndSteps,
	int maxTriesOverride,
	PathFindingCustomTest* customTest) {
	// clear path
	path.clear();

	//
	auto now = Time::getCurrentMillis();

	//
	auto currentMaxTries = maxTriesOverride == -1?this->maxTries:maxTriesOverride;

	// set up custom test
	this->customTest = customTest;

	// initialize custom test
	if (this->customTest != nullptr) this->customTest->initialize();

	//
	this->collisionTypeIds = collisionTypeIds;

	// init bounding volume, transform, collision body
	actorBoundingVolume = new OrientedBoundingBox(
		Vector3(0.0f, actorHeight / 2.0f, 0.0f),
		OrientedBoundingBox::AABB_AXIS_X,
		OrientedBoundingBox::AABB_AXIS_Y,
		OrientedBoundingBox::AABB_AXIS_Z,
		Vector3(stepSize * scaleActorBoundingVolumes, actorHeight / 2.0f, stepSize * scaleActorBoundingVolumes)
	);
	// set up transform
	Transform actorTransform;
	actorTransform.setTranslation(startPosition);
	actorTransform.update();
	world->addCollisionBody("tdme.pathfinding.actor", true, 32768, actorTransform, {actorBoundingVolume});

	// init bounding volume for slope testcollision body
	actorBoundingVolumeSlopeTest = new OrientedBoundingBox(
		Vector3(0.0f, actorHeight / 2.0f, 0.0f),
		OrientedBoundingBox::AABB_AXIS_X,
		OrientedBoundingBox::AABB_AXIS_Y,
		OrientedBoundingBox::AABB_AXIS_Z,
		Vector3(stepSize * scaleActorBoundingVolumes * 2.5f, actorHeight / 2.0f, stepSize * scaleActorBoundingVolumes * 2.5f)
	);
	world->addCollisionBody("tdme.pathfinding.actor.slopetest", true, 32768, actorTransform, {actorBoundingVolumeSlopeTest});

	//
	bool success = false;

	// equal start and end position?
	if (endPosition.clone().sub(startPosition).computeLengthSquared() < Math::square(0.1f)) {
		if (VERBOSE == true) Console::println("PathFinding::findPath(): start position == end position! Exiting!");
		path.push_back(startPosition);
		float endYHeight = endPosition.getY();
		if (isWalkableInternal(
			endPosition.getX(),
			endPosition.getY(),
			endPosition.getZ(),
			endYHeight,
			stepSize,
			scaleActorBoundingVolumes,
			false
		) == false) {
			path.push_back(endPosition);
			success = true;
		}
	} else
	// equal start and end position?
	if (startPosition.clone().sub(endPosition).computeLengthSquared() < stepSizeLast * stepSizeLast + stepSizeLast * stepSizeLast + 0.1f) {
		if (VERBOSE == true) Console::println("PathFinding::findPath(): end - start position < stepSizeLast! Exiting!");
		path.push_back(startPosition);
		float endYHeight = endPosition.getY();
		if (isWalkableInternal(
			endPosition.getX(),
			endPosition.getY(),
			endPosition.getZ(),
			endYHeight,
			stepSize,
			scaleActorBoundingVolumes,
			false
		) == false) {
			path.push_back(endPosition);
			success = true;
		}
	}

	//
	auto tries = 0;
	auto endPositionIdx = 0;

	//
	if (success == false) {
		//
		auto forcedAlternativeEndSteps = 0;

		// compute possible end positions
		vector<Vector3> startPositionCandidates;
		vector<Vector3> endPositionCandidates;
		{
			auto forwardVector = endPosition.clone().sub(startPosition).setY(0.0f).normalize();
			auto sideVector = Vector3::computeCrossProduct(forwardVector, Vector3(0.0f, 1.0f, 0.0f)).setY(0.0f).normalize();
			if (Float::isNaN(sideVector.getX()) ||
				Float::isNaN(sideVector.getY()) ||
				Float::isNaN(sideVector.getZ())) {
				if (VERBOSE == true) Console::println("PathFinding::findPath(): side vector = NaN!");
				endPositionCandidates.push_back(endPosition);
				startPositionCandidates.push_back(startPosition);
			} else {
				{
					auto sideDistance = stepSize;
					auto forwardDistance = 0.0f;
					auto i = 0;
					while (true == true) {
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= alternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(-sideDistance).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= alternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(+sideDistance).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= alternativeEndSteps) break;
						forwardDistance+= stepSize;
					}
					forwardDistance = 0.0f;
					forwardVector.scale(-1.0f);
					sideVector.scale(-1.0f);
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(-sideDistance).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(+sideDistance).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(-sideDistance).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(+sideDistance).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
					forwardDistance+= stepSize;
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(-sideDistance).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(+sideDistance).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(-sideDistance).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(+sideDistance).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
					forwardDistance+= stepSize;
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(-sideDistance).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(+sideDistance).add(forwardVector.clone().scale(-forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(-sideDistance).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
					startPositionCandidates.push_back(Vector3().set(sideVector).scale(+sideDistance).add(forwardVector.clone().scale(forwardDistance)).add(startPosition));
				}
				if (currentMaxTries == 0) {
					forcedAlternativeEndSteps = 27 * 2;
					auto forwardDistance = 0.0f;
					auto i = 0;
					while (true == true) {
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(-0.3f).add(forwardVector.clone().scale(forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(-0.2f).add(forwardVector.clone().scale(forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(-0.1f).add(forwardVector.clone().scale(forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(+0.1f).add(forwardVector.clone().scale(forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(+0.2f).add(forwardVector.clone().scale(forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(+0.3f).add(forwardVector.clone().scale(forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(0.0f).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(-0.3f).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(-0.2f).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(-0.1f).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(+0.1f).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(+0.2f).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						endPositionCandidates.push_back(Vector3().set(sideVector).scale(+0.3f).add(forwardVector.clone().scale(-forwardDistance)).add(endPosition));
						i++; if (i >= forcedAlternativeEndSteps) break;
						forwardDistance+= 0.1f;
					}
				}
			}
		}

		Vector3 startPositionComputed = startPosition;
		for (auto& startPositionCandidate: startPositionCandidates) {
			float startYHeight = startPositionCandidate.getY();
			if (isWalkableInternal(
				startPositionCandidate.getX(),
				startPositionCandidate.getY(),
				startPositionCandidate.getZ(),
				startYHeight,
				stepSize,
				scaleActorBoundingVolumes,
				false
			) == false) {
				if (VERBOSE == true) {
					Console::println(
						"PathFinding::findPath(): Start position not walkable: " +
						to_string(startPositionCandidate.getX()) + ", " +
						to_string(startPositionCandidate.getY()) + ", " +
						to_string(startPositionCandidate.getZ()) + " / " +
						to_string(startYHeight)
					);
				}
				//
				continue;
			} else {
				startPositionComputed = startPositionCandidate;
				startPositionComputed.setY(startYHeight);
				break;
			}
		}

		for (auto& endPositionCandidate: endPositionCandidates) {
			Vector3 endPositionComputed = endPositionCandidate;
			float endYHeight = endPositionComputed.getY();
			if (alternativeEndSteps > 0 &&
				isWalkableInternal(
					endPositionComputed.getX(),
					endPositionComputed.getY(),
					endPositionComputed.getZ(),
					endYHeight,
					stepSize,
					scaleActorBoundingVolumes,
					false
				) == false) {
				if (VERBOSE == true) {
					Console::println(
						"PathFinding::findPath(): End position not walkable: " +
						to_string(endPositionComputed.getX()) + ", " +
						to_string(endPositionComputed.getY()) + ", " +
						to_string(endPositionComputed.getZ()) + " / " +
						to_string(endYHeight)
					);
				}
				//
				continue;
			} else {
				endPositionComputed.setY(endYHeight);
			}

			if (VERBOSE == true) {
				Console::println(
					"Finding path: " +
					to_string(startPositionComputed.getX()) + ", " +
					to_string(startPositionComputed.getY()) + ", " +
					to_string(startPositionComputed.getZ()) + " --> " +
					to_string(endPositionComputed.getX()) + ", " +
					to_string(endPositionComputed.getY()) + ", " +
					to_string(endPositionComputed.getZ())
				);
			}

			// end node + start node
			{
				// start node
				auto start = pathFindingNodesPool.allocate();
				start->hasPreviousNode = false;
				start->position = startPositionComputed;
				start->costsAll = 0.0f;
				start->costsReachPoint = 0.0f;
				start->costsEstimated = 0.0f;
				start->x = getIntegerPositionComponent(start->position.getX(), stepSize);
				start->y = 0;
				start->z = getIntegerPositionComponent(start->position.getZ(), stepSize);
				start->id = toId(
					start->position.getX(),
					start->position.getY(),
					start->position.getZ(),
					stepSize
				);

				// end node
				end.hasPreviousNode = false;
				end.position = endPositionComputed;
				end.costsAll = 0.0f;
				end.costsReachPoint = 0.0f;
				end.costsEstimated = 0.0f;
				end.x = getIntegerPositionComponent(end.position.getX(), stepSize);
				end.y = 0;
				end.z = getIntegerPositionComponent(end.position.getZ(), stepSize);
				end.id = toId(
					end.position.getX(),
					end.position.getY(),
					end.position.getZ(),
					stepSize
				);

				// set up start node costs
				start->costsEstimated = computeDistanceToEnd(start);
				start->costsAll = start->costsEstimated;

				// put to open nodes
				openNodes[start->id] = start;
			}

			// do the steps
			bool done = false;
			for (auto stepIdx = 0; done == false && stepIdx < stepsMax; stepIdx++) {
				// check if there are still open nodes available
				if (openNodes.size() == 0) {
					done = true;
					break;
				}

				// choose node from open nodes thats least expensive to check its successors
				PathFindingNode* endNode = nullptr;
				PathFindingNode* endNodeCandidate = nullptr;
				for (auto nodeIt = openNodes.begin(); nodeIt != openNodes.end(); ++nodeIt) {
					if (equalsLastNode(nodeIt->second, &end) == true && (endNode == nullptr || nodeIt->second->costsAll < endNode->costsAll)) endNode = nodeIt->second;
					if (endNodeCandidate == nullptr || nodeIt->second->costsAll < endNodeCandidate->costsAll) endNodeCandidate = nodeIt->second;
				}

				//
				if (endNodeCandidate == nullptr) {
					done = true;
					break;
				}

				//
				if (endNode != nullptr) {
					end.hasPreviousNode = true;
					end.previousNodeId = endNode->previousNodeId;
					// Console::println("PathFinding::findPath(): path found with steps: " + to_string(stepIdx));
					int nodesCount = 0;
					unordered_map<tuple<int, int, int>, PathFindingNode*, PathFindingNodeId_Hash>::iterator nodeIt;
					for (auto pathNode = &end; pathNode != nullptr; pathNode = (nodeIt = (pathNode->hasPreviousNode == false?closedNodes.end():closedNodes.find(pathNode->previousNodeId))) != closedNodes.end()?nodeIt->second:nullptr) {
						nodesCount++;
						// if (nodesCount > 0 && nodesCount % 100 == 0) {
						//	 Console::println("PathFinding::findPath(): compute path: steps: " + to_string(nodesCount) + " / " + to_string(path.size()) + ": " + to_string((uint64_t)node));
						// }
						if (Float::isNaN(pathNode->position.getX()) ||
							Float::isNaN(pathNode->position.getY()) ||
							Float::isNaN(pathNode->position.getZ())) {
							Console::println("PathFinding::findPath(): compute path: step: NaN");
							done = true;
							break;
						}
						path.push_back(pathNode->position);
					}
					reverse(path.begin(), path.end());
					if (path.size() > 1) path.erase(path.begin());
					if (path.size() == 0) {
						// Console::println("PathFinding::findPath(): path with 0 steps: Fixing!");
						path.push_back(endPositionComputed);
					}
					done = true;
					success = true;
					break;
				} else {
					const auto node = endNodeCandidate;
					// do a step
					step(node, stepSize, scaleActorBoundingVolumes, nullptr, false);
				}
			}

			// reset
			openNodes.clear();
			closedNodes.clear();
			pathFindingNodesPool.reset();

			//
			tries++;

			//
			if (success == true || tries >= currentMaxTries + forcedAlternativeEndSteps) break;
		}

		//
		if (tries == 0) {
			Console::println("PathFinding::findPath(): end position were not walkable!");
		}
	}

	//
	/*
	if (stepIdx == stepsMax) {
		Console::println("PathFinding::findPath(): steps == stepsMax: " + to_string(stepIdx));
	}
	*/

	// unset actor bounding volume and remove rigid body
	world->removeBody("tdme.pathfinding.actor");
	world->removeBody("tdme.pathfinding.actor.slopetest");
	delete actorBoundingVolume;
	actorBoundingVolume = nullptr;
	delete actorBoundingVolumeSlopeTest;
	actorBoundingVolumeSlopeTest = nullptr;

	//
	if (VERBOSE == true && tries > 1) Console::println("PathFinding::findPath(): time: " + to_string(Time::getCurrentMillis() - now) + "ms / " + to_string(tries) + " tries, success = " + to_string(success) + ", path steps: " + to_string(path.size()));

	// dispose custom test
	if (this->customTest != nullptr) {
		this->customTest->dispose();
		this->customTest = nullptr;
	}

	// return success
	return success;
}

FlowMap* PathFinding::createFlowMap(const vector<Vector3>& endPositions, const Vector3& center, float depth, float width, const uint16_t collisionTypeIds, const vector<Vector3>& path, bool complete, PathFindingCustomTest* customTest) {
	// set up end position in costs map
	if (path.empty() == true) {
		Console::println("PathFinding::createFlowMap(): no path given");
		return nullptr;
	}

	// set up custom test
	this->customTest = customTest;

	// initialize custom test
	if (this->customTest != nullptr) this->customTest->initialize();

	//
	this->collisionTypeIds = collisionTypeIds;

	// init bounding volume, transform, collision body
	actorBoundingVolume = new OrientedBoundingBox(
		Vector3(0.0f, actorHeight / 2.0f, 0.0f),
		OrientedBoundingBox::AABB_AXIS_X,
		OrientedBoundingBox::AABB_AXIS_Y,
		OrientedBoundingBox::AABB_AXIS_Z,
		Vector3(flowMapStepSize * flowMapScaleActorBoundingVolumes, actorHeight / 2.0f, flowMapStepSize * flowMapScaleActorBoundingVolumes)
	);
	// set up transform
	Transform actorTransform;
	actorTransform.setTranslation(endPositions[0]);
	actorTransform.update();
	world->addCollisionBody("tdme.pathfinding.actor", true, 32768, actorTransform, {actorBoundingVolume});

	// init bounding volume for slope testcollision body
	actorBoundingVolumeSlopeTest =	new OrientedBoundingBox(
		Vector3(0.0f, actorHeight / 2.0f, 0.0f),
		OrientedBoundingBox::AABB_AXIS_X,
		OrientedBoundingBox::AABB_AXIS_Y,
		OrientedBoundingBox::AABB_AXIS_Z,
		Vector3(flowMapStepSize * flowMapScaleActorBoundingVolumes * 2.5f, actorHeight / 2.0f, flowMapStepSize * flowMapScaleActorBoundingVolumes * 2.5f)
	);
	world->addCollisionBody("tdme.pathfinding.actor.slopetest", true, 32768, actorTransform, {actorBoundingVolumeSlopeTest});

	//
	auto zMin = static_cast<int>(Math::ceil(-depth / 2.0f / flowMapStepSize));
	auto zMax = static_cast<int>(Math::ceil(depth / 2.0f / flowMapStepSize));
	auto xMin = static_cast<int>(Math::ceil(-width / 2.0f / flowMapStepSize));
	auto xMax = static_cast<int>(Math::ceil(width / 2.0f / flowMapStepSize));
	const vector<Vector3> emptyPath = { center };
	const vector<Vector3>& pathToUse = path.empty() == false?path:emptyPath;

	// set up end position in costs map
	if (endPositions.size() == 0) {
		Console::println("PathFinding::createFlowMap(): no end positions given");
	}

	// end node
	end.hasPreviousNode = false;
	end.position = path[0];
	end.costsAll = 0.0f;
	end.costsReachPoint = 0.0f;
	end.costsEstimated = 0.0f;
	end.x = getIntegerPositionComponent(end.position.getX());
	end.y = 0;
	end.z = getIntegerPositionComponent(end.position.getZ());
	end.id = toId(
		end.position.getX(),
		end.position.getY(),
		end.position.getZ()
	);

	// add end position to open nodes/start nodes
	for (auto& endPosition: endPositions) {
		auto nodePosition = Vector3(
			FlowMap::alignPositionComponent(endPosition.getX(), flowMapStepSize),
			endPosition.getY(),
			FlowMap::alignPositionComponent(endPosition.getZ(), flowMapStepSize)
		);
		float nodeYHeight;
		isWalkableInternal(nodePosition.getX(), nodePosition.getY(), nodePosition.getZ(), nodeYHeight, flowMapStepSize, flowMapScaleActorBoundingVolumes, true);
		auto node = pathFindingNodesPool.allocate();
		node->hasPreviousNode = false;
		node->position.set(nodePosition).setY(nodeYHeight);
		node->costsReachPoint = 0.0f;
		node->x = FlowMap::getIntegerPositionComponent(nodePosition.getX(), flowMapStepSize);
		node->y = 0;
		node->z = FlowMap::getIntegerPositionComponent(nodePosition.getZ(), flowMapStepSize);
		node->id = toIdInt(node->x, node->y, node->z);
		// set up start node costs
		node->costsEstimated = computeDistanceToEnd(node);
		node->costsAll = node->costsEstimated;
		// put to open nodes
		openNodes[node->id] = node;
	}

	// nodes to test
	unordered_set<tuple<int, int, int>, PathFindingNodeId_Hash> nodesToTest;
	for (auto& _centerPathNode: pathToUse) {
		auto centerPathNode = Vector3(
			FlowMap::alignPositionComponent(_centerPathNode.getX(), flowMapStepSize),
			_centerPathNode.getY(),
			FlowMap::alignPositionComponent(_centerPathNode.getZ(), flowMapStepSize)
		);
		auto centerPathNodeX = FlowMap::getIntegerPositionComponent(centerPathNode.getX(), flowMapStepSize);
		auto centerPathNodeZ = FlowMap::getIntegerPositionComponent(centerPathNode.getZ(), flowMapStepSize);
		for (auto z = zMin; z <= zMax; z++) {
			for (auto x = xMin; x <= xMax; x++) {
				auto nodeId = toIdInt(
					centerPathNodeX + x,
					0,
					centerPathNodeZ + z
				);
				nodesToTest.insert(nodeId);
			}
		}
	}

	// do A* on open nodes
	while (openNodes.size() > 0) {
		// choose node from open nodes thats least expensive to check its successors
		PathFindingNode* openNode = nullptr;
		for (auto nodeIt = openNodes.begin(); nodeIt != openNodes.end(); ++nodeIt) {
			if (openNode == nullptr || nodeIt->second->costsAll < openNode->costsAll) openNode = nodeIt->second;
		}
		if (openNode == nullptr) break;

		// do a step
		step(openNode, flowMapStepSize, flowMapScaleActorBoundingVolumes, &nodesToTest, true);
	}

	// clear nodes to test
	nodesToTest.clear();

	// generate flow map, which is based on
	//	see: https://howtorts.github.io/2014/01/04/basic-flow-fields.html
	auto flowMap = new FlowMap(pathToUse, endPositions, flowMapStepSize, complete);
	flowMap->acquireReference();
	for (auto& _centerPathNode: pathToUse) {
		auto centerPathNode = Vector3(
			FlowMap::alignPositionComponent(_centerPathNode.getX(), flowMapStepSize),
			_centerPathNode.getY(),
			FlowMap::alignPositionComponent(_centerPathNode.getZ(), flowMapStepSize)
		);
		auto centerPathNodeX = FlowMap::getIntegerPositionComponent(centerPathNode.getX(), flowMapStepSize);
		auto centerPathNodeZ = FlowMap::getIntegerPositionComponent(centerPathNode.getZ(), flowMapStepSize);
		for (auto z = zMin; z <= zMax; z++) {
			for (auto x = xMin; x <= xMax; x++) {
				auto cellPosition = Vector3(
					static_cast<float>(centerPathNodeX) * flowMapStepSize + static_cast<float>(x) * flowMapStepSize,
					0.0f,
					static_cast<float>(centerPathNodeZ) * flowMapStepSize + static_cast<float>(z) * flowMapStepSize
				);
				auto cellId = FlowMap::toIdInt(
					centerPathNodeX + x,
					centerPathNodeZ + z
				);
				auto nodeId = toIdInt(
					centerPathNodeX + x,
					0,
					centerPathNodeZ + z
				);

				// do we already have this cell?
				if (flowMap->hasCell(cellId) == true) continue;

				// walkable?
				auto nodeIt = closedNodes.find(nodeId);
				if (nodeIt == closedNodes.end()) {
					continue;
				}
				auto node = nodeIt->second;
				// set y
				cellPosition.setY(node->position.getY());

				// check neighbours around our current cell
				PathFindingNode* minCostsNode = nullptr;
				auto minCosts = Float::MAX_VALUE;
				for (auto _z = -1; _z <= 1; _z++)
				for (auto _x = -1; _x <= 1; _x++)
				if (_z != 0 || _x != 0) {
					//
					auto neighbourNodeId = toIdInt(
						centerPathNodeX + x + _x,
						0,
						centerPathNodeZ + z + _z
					);
					// same node?
					if (neighbourNodeId == nodeId) continue;
					// do we have this cell?
					auto neighbourNodeIt = closedNodes.find(neighbourNodeId);
					if (neighbourNodeIt == closedNodes.end()) {
						// nope
						continue;
					} else {
						// yes && walkable
						auto& neighbourNode = neighbourNodeIt->second;
						if (minCostsNode == nullptr || neighbourNode->costsReachPoint < minCosts) {
							minCostsNode = neighbourNode;
							minCosts = neighbourNode->costsReachPoint;
						}
					}
				}
				if (minCostsNode != nullptr) {
					auto direction = minCostsNode->position.clone().sub(node->position).setY(0.0f).normalize();
					if (Float::isNaN(direction.getX()) || Float::isNaN(direction.getY()) || Float::isNaN(direction.getZ())) {
						Console::println(
							to_string(minCostsNode->position.getX()) + ", " +
							to_string(minCostsNode->position.getY()) + ", " +
							to_string(minCostsNode->position.getZ()) + " -> " +
							to_string(node->position.getX()) + ", " +
							to_string(node->position.getY()) + ", " +
							to_string(node->position.getZ()) + ": " +
							to_string(minCostsNode == node) + "; " +
							to_string(cellPosition.getX()) + ", " +
							to_string(cellPosition.getY()) + ", " +
							to_string(cellPosition.getZ()) + "; " +
							cellId
						);
					}
					flowMap->addCell(
						cellId,
						cellPosition,
						true,
						direction,
						-1
					);
				}
			}
		}
	}

	// reset
	openNodes.clear();
	closedNodes.clear();
	pathFindingNodesPool.reset();

	// do some post adjustments
	for (auto& _centerPathNode: pathToUse) {
		auto centerPathNode = Vector3(
			FlowMap::alignPositionComponent(_centerPathNode.getX(), flowMapStepSize),
			_centerPathNode.getY(),
			FlowMap::alignPositionComponent(_centerPathNode.getZ(), flowMapStepSize)
		);
		auto centerPathNodeX = FlowMap::getIntegerPositionComponent(centerPathNode.getX(), flowMapStepSize);
		auto centerPathNodeZ = FlowMap::getIntegerPositionComponent(centerPathNode.getZ(), flowMapStepSize);
		for (auto z = zMin; z <= zMax; z++) {
			for (auto x = xMin; x <= xMax; x++) {
				auto cellPosition = Vector3(
					static_cast<float>(centerPathNodeX) * flowMapStepSize + static_cast<float>(x) * flowMapStepSize,
					0.0f,
					static_cast<float>(centerPathNodeZ) * flowMapStepSize + static_cast<float>(z) * flowMapStepSize
				);
				auto cellId = FlowMap::toIdInt(
					centerPathNodeX + x,
					centerPathNodeZ + z
				);
				auto cell = flowMap->getCell(cellId);
				if (cell == nullptr) continue;
				auto topCell = flowMap->getCell(FlowMap::toIdInt(centerPathNodeX + x, centerPathNodeZ + z - 1));
				if (topCell == nullptr && Math::abs(cell->getDirection().getX()) > 0.0f && cell->getDirection().getZ() < 0.0f){
					cell->setDirection(cell->getDirection().clone().setZ(0.0f).normalize());
				}
				auto bottomCell = flowMap->getCell(FlowMap::toIdInt(centerPathNodeX + x, centerPathNodeZ + z + 1));
				if (bottomCell == nullptr && Math::abs(cell->getDirection().getX()) > 0.0f && cell->getDirection().getZ() > 0.0f){
					cell->setDirection(cell->getDirection().clone().setZ(0.0f).normalize());
				}
				auto leftCell = flowMap->getCell(FlowMap::toIdInt(centerPathNodeX + x - 1, centerPathNodeZ + z));
				if (leftCell == nullptr && cell->getDirection().getX() < 0.0f && Math::abs(cell->getDirection().getZ()) > 0.0f){
					cell->setDirection(cell->getDirection().clone().setX(0.0f).normalize());
				}
				auto rightCell = flowMap->getCell(FlowMap::toIdInt(centerPathNodeX + x + 1, centerPathNodeZ + z));
				if (rightCell == nullptr && cell->getDirection().getX() > 0.0f && Math::abs(cell->getDirection().getZ()) > 0.0f){
					cell->setDirection(cell->getDirection().clone().setX(0.0f).normalize());
				}
			}
		}
	}

	// do some more post adjustments
	Vector3 lastCenterPathNode = pathToUse.size() < 2?Vector3():pathToUse[0] - (pathToUse[1] - pathToUse[0]);
	unordered_set<string> cellsProcessed;
	for (int i = pathToUse.size() - 1; i >= 0; i--) {
		auto _centerPathNode = pathToUse[i];
		auto centerPathNode = Vector3(
			FlowMap::alignPositionComponent(_centerPathNode.getX(), flowMapStepSize),
			_centerPathNode.getY(),
			FlowMap::alignPositionComponent(_centerPathNode.getZ(), flowMapStepSize)
		);
		auto pathDirection = (lastCenterPathNode - centerPathNode).setY(0.0f).normalize();
		auto centerPathNodeX = FlowMap::getIntegerPositionComponent(centerPathNode.getX(), flowMapStepSize);
		auto centerPathNodeZ = FlowMap::getIntegerPositionComponent(centerPathNode.getZ(), flowMapStepSize);
		for (auto z = zMin; z <= zMax; z++) {
			for (auto x = xMin; x <= xMax; x++) {
				auto cellId = FlowMap::toIdInt(
					centerPathNodeX + x,
					centerPathNodeZ + z
				);
				auto cell = flowMap->getCell(cellId);
				if (cell == nullptr) continue;

				// check if we have missing neighbour cells
				auto hadMissingNeighborCell = false;
				for (auto nZ = -1; nZ < 2 && hadMissingNeighborCell == false; nZ++) {
					for (auto nX = -1; nX < 2 && hadMissingNeighborCell == false; nX++) {
						if (nZ == 0 && nX == 0) continue;
						auto neighbourCellId = FlowMap::toIdInt(
							centerPathNodeX + x + nX,
							centerPathNodeZ + z + nZ
						);
						auto neighbourCell = flowMap->getCell(neighbourCellId);
						if (neighbourCell == nullptr) {
							cell->setMissingNeighborCell(true);
							hadMissingNeighborCell = true;
							break;
						}
					}
				}

				// determine path node index
				{
					auto i = 0;
					auto pathNodeIdx = -1;
					auto pathNodeNodeDistanceSquared = Float::MAX_VALUE;
					for (auto& pathNode: pathToUse) {
						auto pathNodeCellAxis = pathNode - cell->getPosition();
						auto pathNodeCandidateDistanceSquared = pathNodeCellAxis.computeLengthSquared();
						if (pathNodeIdx == -1 || pathNodeCandidateDistanceSquared < pathNodeNodeDistanceSquared) {
							pathNodeIdx = i;
							pathNodeNodeDistanceSquared = pathNodeCandidateDistanceSquared;
						}
						i++;
					}
					cell->setPathNodeIdx(pathNodeIdx < pathToUse.size() - 1?pathNodeIdx + 1:pathNodeIdx);
				}
			}
		}
		lastCenterPathNode = centerPathNode;
	}

	// unset actor bounding volume and remove rigid body
	world->removeBody("tdme.pathfinding.actor");
	world->removeBody("tdme.pathfinding.actor.slopetest");
	delete actorBoundingVolume;
	actorBoundingVolume = nullptr;
	delete actorBoundingVolumeSlopeTest;
	actorBoundingVolumeSlopeTest = nullptr;

	// dispose custom test
	if (this->customTest != nullptr) {
		this->customTest->dispose();
		this->customTest = nullptr;
	}

	//
	return flowMap;
}

const vector<Vector3> PathFinding::generateDirectPath(const Vector3& start, const Vector3& end) {
	vector<Vector3> path;
	Vector3 axis;
	axis.set(end).sub(start);
	auto length = axis.computeLength();
	auto step = axis.clone().normalize() * stepSize;
	Vector3 current = start;
	for (auto i = stepSize; i < length; i+= stepSize) {
		path.push_back(current.add(step));
	}
	path.push_back(end);
	return path;
}
