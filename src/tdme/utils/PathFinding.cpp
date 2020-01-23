#include <tdme/utils/PathFinding.h>

#include <algorithm>
#include <string>
#include <map>
#include <stack>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/PathFindingNode.h>
#include <tdme/utils/PathFindingCustomTest.h>
#include <tdme/utils/Time.h>

using std::map;
using std::reverse;
using std::stack;
using std::string;
using std::to_string;

using tdme::engine::Transformations;
using tdme::engine::physics::World;
using tdme::engine::physics::Body;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utils::Console;
using tdme::utils::Float;
using tdme::utils::PathFindingNode;
using tdme::utils::PathFindingCustomTest;
using tdme::utils::Time;

using tdme::utils::PathFinding;

PathFinding::PathFinding(World* world, bool sloping, int stepsMax, float actorHeight, float stepSize, float stepSizeLast, float actorStepUpMax, uint16_t skipOnCollisionTypeIds, int maxTries) {
	this->world = world;
	this->customTest = nullptr;
	this->sloping = sloping;
	this->end = new PathFindingNode();
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
}

PathFinding::~PathFinding() {
	delete end;
}

void PathFinding::reset() {
	for (auto nodeIt = openNodes.begin(); nodeIt != openNodes.end(); ++nodeIt) {
		delete nodeIt->second;
	}
	openNodes.clear();
	for (auto nodeIt = closedNodes.begin(); nodeIt != closedNodes.end(); ++nodeIt) {
		delete nodeIt->second;
	}
	closedNodes.clear();
}

bool PathFinding::isWalkableInternal(float x, float y, float z, float& height, uint16_t collisionTypeIds, bool ignoreStepUpMax) {
	auto walkable = isWalkable(x, y, z, height, collisionTypeIds, ignoreStepUpMax);
	if (walkable == false) return false;
	return customTest == nullptr || customTest->isWalkable(this, x, height, z) == true;
}

bool PathFinding::isWalkable(float x, float y, float z, float& height, uint16_t collisionTypeIds, bool ignoreStepUpMax) {
	// determine y height of ground plate of actor bounding volume
	float _z = z - stepSize / 2.0f;
	height = -10000.0f;
	Vector3 actorPosition;
	for (auto i = 0; i < 2; i++) {
		float _x = x - stepSize / 2.0f;
		for (auto j = 0; j < 2; j++) {
			Vector3 actorPositionCandidate;
			auto body = world->determineHeight(
				collisionTypeIds == 0?this->collisionTypeIds:collisionTypeIds,
				ignoreStepUpMax == true?10000.0f:actorStepUpMax,
				actorPositionCandidate.set(_x, y, _z),
				actorPosition
			);
			if (body == nullptr || ((body->getCollisionTypeId() & skipOnCollisionTypeIds) != 0)) {
				return false;
			}
			if (actorPosition.getY() > height) height = actorPosition.getY();
			_x+= stepSize;
		}
		_z+= stepSize;
	}

	// set up transformations
	Transformations actorTransformations;
	actorTransformations.setTranslation(Vector3(x, height + 0.1f, z));
	actorTransformations.update();

	// update rigid body
	auto actorCollisionBody = world->getBody("tdme.pathfinding.actor");
	actorCollisionBody->fromTransformations(actorTransformations);

	// check if actor collides with world
	vector<Body*> collidedRigidBodies;
	return world->doesCollideWith(collisionTypeIds == 0?this->collisionTypeIds:collisionTypeIds, actorCollisionBody, collidedRigidBodies) == false;
}

void PathFinding::start(const Vector3& startPosition, const Vector3& endPosition) {
	// start node
	auto& startXYZ = startPosition.getArray();
	PathFindingNode* start = new PathFindingNode();
	start->x = startXYZ[0];
	start->y = startXYZ[1];
	start->z = startXYZ[2];
	start->costsAll = 0.0f;
	start->costsReachPoint = 0.0f;
	start->costsEstimated = 0.0f;
	start->previousNode = nullptr;
	start->key = toKey(start->x, start->y, start->z);

	// end node
	auto& endXYZ = endPosition.getArray();
	end->x = endXYZ[0];
	end->y = endXYZ[1];
	end->z = endXYZ[2];
	end->costsAll = 0.0f;
	end->costsReachPoint = 0.0f;
	end->costsEstimated = 0.0f;
	end->previousNode = nullptr;
	end->key = toKey(end->x, end->y, end->z);

	// set up start node costs
	start->costsEstimated = computeDistance(start, end);
	start->costsAll = start->costsEstimated;

	// put to open nodes
	openNodes[start->key] = start;
}

PathFinding::PathFindingStatus PathFinding::step() {
	// check if there are still open nodes available
	if (openNodes.size() == 0) {
		return PathFindingStatus::PATH_NOWAY;
	}

	// Choose node from open nodes thats least expensive to check its successors
	PathFindingNode* node = nullptr;
	for (auto nodeIt = openNodes.begin(); nodeIt != openNodes.end(); ++nodeIt) {
		if (node == nullptr || nodeIt->second->costsAll < node->costsAll) node = nodeIt->second;
	}

	//
	if (equalsLastNode(node, end)) {
		end->previousNode = node->previousNode;
		return PathFindingStatus::PATH_FOUND;
	} else {
		// Find valid successors
		for (auto z = -1; z <= 1; z++)
		for (auto x = -1; x <= 1; x++)
		if ((z != 0 || x != 0) &&
			(sloping == true ||
			(Math::abs(x) == 1 && Math::abs(z) == 1) == false)) {
			auto slopeWalkable = true;
			float successorX = x * stepSize + node->x;
			float successorZ = z * stepSize + node->z;
			if (Math::abs(x) == 1 && Math::abs(z) == 1) {
				float slopeAngle = 0.0f;

				//
				if (x == -1 && z == -1) slopeAngle = 0.0f - 45.0f; else
				if (x == +1 && z == -1) slopeAngle = 0.0f + 45.0f; else
				if (x == +1 && z == +1) slopeAngle = 180.0f - 45.0f; else
				if (x == -1 && z == +1) slopeAngle = 180.0f + 45.0f;

				// set up transformations
				Transformations slopeTestTransformations;
				slopeTestTransformations.setTranslation(Vector3(successorX, node->y + 0.1f, successorZ));
				slopeTestTransformations.addRotation(Vector3(0.0f, 1.0f, 0.0f), slopeAngle);
				slopeTestTransformations.update();

				// update rigid body
				auto actorSlopeTestCollisionBody = world->getBody("tdme.pathfinding.actor.slopetest");
				actorSlopeTestCollisionBody->fromTransformations(slopeTestTransformations);

				// check if actor collides with world
				vector<Body*> collidedRigidBodies;
				slopeWalkable = world->doesCollideWith(collisionTypeIds == 0?this->collisionTypeIds:collisionTypeIds, actorSlopeTestCollisionBody, collidedRigidBodies) == false;
			}
			//
			float yHeight;
			// first node or walkable?
			if (slopeWalkable == true && isWalkableInternal(successorX, node->y, successorZ, yHeight)) {
				// check if successor node equals previous node / node
				if (equals(node, successorX, yHeight, successorZ)) {
					continue;
				}
				// Add the node to the available sucessorNodes
				PathFindingNode* successorNode = new PathFindingNode();
				successorNode->x = successorX;
				successorNode->z = successorZ;
				successorNode->y = yHeight;
				successorNode->costsAll = 0.0f;
				successorNode->costsReachPoint = 0.0f;
				successorNode->costsEstimated = 0.0f;
				successorNode->previousNode = nullptr;
				successorNode->key = toKey(successorNode->x, successorNode->y, successorNode->z);
				successorNodes.push(successorNode);
			}
		}
	}

	// Check successor nodes
	while (successorNodes.empty() == false) {
		PathFindingNode* successorNode = successorNodes.top();
		successorNodes.pop();
		auto successorNodeKey = successorNode->key;

		// Compute successor node's costs by costs to reach nodes point and the computed distance from node to successor node
		float successorCostsReachPoint = node->costsReachPoint + computeDistance(successorNode, node);

		// Find sucessor node in open nodes list
		PathFindingNode* openListNode = nullptr;
		auto openListNodeIt = openNodes.find(successorNodeKey);
		if (openListNodeIt != openNodes.end()) {
			openListNode = openListNodeIt->second;
		}

		// found it in open nodes list
		if (openListNode != nullptr) {
			// is the node from open nodes less expensive, discard successor node
			if (openListNode->costsReachPoint <= successorCostsReachPoint) {
				delete successorNode;
				// discard it
				continue;
			}
		}

		// Find successor node in closed nodes list
		PathFindingNode* closedListNode = nullptr;
		auto closedListNodeIt = closedNodes.find(successorNodeKey);
		if (closedListNodeIt != closedNodes.end()) {
			closedListNode = closedListNodeIt->second;
		}

		// found it in closed nodes list
		if (closedListNode != nullptr) {
			// is the node from closed nodes list less expensive, discard successor node
			if (closedListNode->costsReachPoint <= successorCostsReachPoint) {
				delete successorNode;
				// discard it
				continue;
			}
		}

		// Sucessor node is the node with least cost to this point
		successorNode->previousNode = node;
		successorNode->costsReachPoint = successorCostsReachPoint;
		successorNode->costsEstimated = computeDistance(successorNode, end);
		successorNode->costsAll = successorNode->costsReachPoint + successorNode->costsEstimated;

		// Remove found node from open nodes list, since it was less optimal
		if (openListNode != nullptr) {
			// remove open list node
			openNodes.erase(openListNodeIt);
			delete openListNode;
		}

		// Remove found node from closed nodes list, since it was less optimal
		if (closedListNode != nullptr) {
			closedNodes.erase(closedListNodeIt);
			delete closedListNode;
		}

		// Add successor node to open nodes list, as we might want to check its successors to find a path to the end
		openNodes[successorNodeKey] = successorNode;
	}

	// node key
	auto nodeKey = node->key;

	// Remove node from open nodes, as we checked its successors
	openNodes.erase(nodeKey);

	// add node to closed nodes list, as we checked its successors
	closedNodes[nodeKey] = node;

	//
	return PathFindingStatus::PATH_STEP;
}

bool PathFinding::findPath(const Vector3& startPosition, const Vector3& endPosition, const uint16_t collisionTypeIds, vector<Vector3>& path, int alternativeEndSteps, PathFindingCustomTest* customTest) {
	// clear path
	path.clear();

	// equal start and end position?
	if (startPosition.equals(endPosition, 0.1f) == true) {
		if (VERBOSE == true) Console::println("PathFinding::findPath(): start position == end position! Exiting!");
		path.push_back(endPosition);
		return true;
	}

	//
	auto now = Time::getCurrentMillis();

	// set up custom test
	this->customTest = customTest;

	// initialize custom test
	if (this->customTest != nullptr) this->customTest->initialize();

	//
	this->collisionTypeIds = collisionTypeIds;

	// init bounding volume, transformations, collision body
	actorBoundingVolume = new OrientedBoundingBox(
		Vector3(0.0f, actorHeight / 2.0f, 0.0f),
		OrientedBoundingBox::AABB_AXIS_X,
		OrientedBoundingBox::AABB_AXIS_Y,
		OrientedBoundingBox::AABB_AXIS_Z,
		Vector3(stepSize, actorHeight / 2.0f, stepSize)
	);
	// set up transformations
	Transformations actorTransformations;
	actorTransformations.setTranslation(startPosition);
	actorTransformations.update();
	world->addCollisionBody("tdme.pathfinding.actor", true, 32768, actorTransformations, {actorBoundingVolume});

	// init bounding volume for slope testcollision body
	auto actorBoundingVolumeSlopeTest =	new OrientedBoundingBox(
		Vector3(0.0f, actorHeight / 2.0f, 0.0f),
		OrientedBoundingBox::AABB_AXIS_X,
		OrientedBoundingBox::AABB_AXIS_Y,
		OrientedBoundingBox::AABB_AXIS_Z,
		Vector3(stepSize * 3.0f, actorHeight / 2.0f, stepSize * 3.0f)
	);
	world->addCollisionBody("tdme.pathfinding.actor.slopetest", true, 32768, actorTransformations, {actorBoundingVolumeSlopeTest});

	// positions
	Vector3 startPositionComputed;
	startPositionComputed.set(startPosition);

	// compute possible end positions
	vector<Vector3> endPositionCandidates;
	{
		Vector3 forwardVector;
		Vector3 sideVector;
		forwardVector.set(endPosition).sub(startPositionComputed).setY(0.0f).normalize();
		Vector3::computeCrossProduct(forwardVector, Vector3(0.0f, 1.0f, 0.0f), sideVector).normalize();
		if (Float::isNaN(sideVector.getX()) ||
			Float::isNaN(sideVector.getY()) ||
			Float::isNaN(sideVector.getZ())) {
			endPositionCandidates.push_back(endPosition);
		} else {
			auto sideDistance = stepSize;
			auto forwardDistance = 0.0f;
			auto endYHeight = 0.0;
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
		}
	}

	auto tries = 0;
	bool success = false;
	for (auto& endPositionCandidate: endPositionCandidates) {
		Vector3 endPositionComputed = endPositionCandidate;
		float endYHeight = endPositionComputed.getY();
		if (isWalkableInternal(
				endPositionComputed.getX(),
				endPositionComputed.getY(),
				endPositionComputed.getZ(),
				endYHeight,
				0,
				true
			) == false) {
			if (VERBOSE == true) {
				Console::println(
					"Not walkable: " +
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

		// otherwise start path finding
		start(startPositionComputed, endPositionComputed);

		// do the steps
		bool done = false;
		for (auto stepIdx = 0; done == false && stepIdx < stepsMax; stepIdx++) {
			PathFindingStatus status = step();
			switch(status) {
				case PATH_STEP:
					{
						break;
					}
				case PATH_NOWAY:
					{
						// Console::println("PathFinding::findPath(): path no way with steps: " + to_string(stepIdx));
						done = true;
						break;
					}
				case PATH_FOUND:
					{
						// Console::println("PathFinding::findPath(): path found with steps: " + to_string(stepIdx));
						int nodesCount = 0;
						for (PathFindingNode* node = end; node != nullptr; node = node->previousNode) {
							path.
								push_back(
									Vector3(
										node->x,
										node->y,
										node->z
									)
								);
							/*
							if (nodesCount > 0 && nodesCount % 100 == 0) {
								Console::println("PathFinding::findPath(): compute path: steps: " + to_string(nodesCount));
							}
							*/
							nodesCount++;
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
					}
			}
		}

		// reset
		reset();
		tries++;

		//
		if (success == true || tries == maxTries) break;
	}

	//
	if (tries == 0) {
		if (VERBOSE == true) Console::println("PathFinding::findPath(): end position were not walkable!");
	}

	//
	/*
	if (stepIdx == stepsMax) {
		Console::println("PathFinding::findPath(): steps == stepsMax: " + to_string(stepIdx));
	}
	*/

	// unset actor bounding volume and remove rigid body
	this->actorBoundingVolume = nullptr;
	this->actorBoundingVolumeSlopeTest = nullptr;
	world->removeBody("tdme.pathfinding.actor");
	world->removeBody("tdme.pathfinding.actor.slopetest");

	//
	if (VERBOSE == true && tries > 1) Console::println("PathFinding::findPath(): time: " + to_string(Time::getCurrentMillis() - now) + "ms / " + to_string(tries) + " tries");

	// dispose custom test
	if (this->customTest != nullptr) {
		this->customTest->dispose();
		this->customTest = nullptr;
	}

	// return success
	return success;
}
