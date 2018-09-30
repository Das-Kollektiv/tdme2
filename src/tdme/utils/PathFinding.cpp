#include <tdme/utils/PathFinding.h>

#include <algorithm>
#include <string>
#include <map>
#include <stack>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>
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
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utils::Console;
using tdme::utils::PathFindingNode;
using tdme::utils::PathFindingCustomTest;
using tdme::utils::Time;

using tdme::utils::PathFinding;

PathFinding::PathFinding(World* world, PathFindingCustomTest* customtest, bool sloping, int stepsMax, float stepSize, float stepSizeLast, float actorStepUpMax) {
	this->world = world;
	this->customTest = customtest;
	this->sloping = sloping;
	this->end = new PathFindingNode();
	this->actorBoundingVolume = nullptr;
	this->stepsMax = stepsMax;
	this->stepSize = stepSize;
	this->stepSizeLast = stepSizeLast;
	this->actorStepUpMax = actorStepUpMax;
	this->collisionTypeIds = 0;
	this->actorXHalfExtension = 0.0f;
	this->actorZHalfExtension = 0.0f;
}

PathFinding::~PathFinding() {
	delete end;
	if (customTest != nullptr) delete customTest;
}

string PathFinding::toKeyFloat(float value)
{
	string floatString = to_string(value);
	return floatString.substr(0, floatString.length() - 5);
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

bool PathFinding::isWalkable(float x, float y, float z, float stepUpMax, float& height) {
	// determine y height of ground plate of actor bounding volume
	float _z = z - actorZHalfExtension;
	height = -10000.0f;
	Vector3 actorPosition;
	for (int i = 0; i < 2; i++) {
		float _x = x - actorXHalfExtension;
		for (int j = 0; j < 2; j++) {
			Vector3 actorPositionCandidate;
			if (world->determineHeight(
				collisionTypeIds,
				stepUpMax,
				actorPositionCandidate.set(_x, y, _z),
				actorPosition) == nullptr) {
				return false;
			}
			if (actorPosition.getY() > height) height = actorPosition.getY();
			if (customTest != nullptr && customTest->isWalkable(actorBoundingVolume, actorPosition.getX(), actorPosition.getY(), actorPosition.getZ()) == false) {
				return false;
			}
			_x+= actorXHalfExtension * 2.0f;
		}
		_z+= actorZHalfExtension * 2.0f;
	}

	// set up transformations
	actorTransformations.setTranslation(Vector3(x, height + 0.1f, z));
	actorTransformations.update();

	// update rigid body
	auto actorCollisionBody = world->getBody("pathfinding.actor");
	actorCollisionBody->fromTransformations(actorTransformations);

	// check if actor collides with world
	vector<Body*> collidedRigidBodies;
	auto collision = world->doesCollideWith(collisionTypeIds, actorCollisionBody, collidedRigidBodies) == false;
	return collision;
}

void PathFinding::start(Vector3 startPosition, Vector3 endPosition) {
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
	start->key = toKeyFloat(start->x) + "," + toKeyFloat(start->y) + "," + toKeyFloat(start->z);

	// end node
	auto& endXYZ = endPosition.getArray();
	end->x = endXYZ[0];
	end->y = endXYZ[1];
	end->z = endXYZ[2];
	end->costsAll = 0.0f;
	end->costsReachPoint = 0.0f;
	end->costsEstimated = 0.0f;
	end->previousNode = nullptr;
	end->key = toKeyFloat(end->x) + "," + toKeyFloat(end->y) + "," + toKeyFloat(end->z);

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
		for (int z = -1; z <= 1; z++)
		for (int x = -1; x <= 1; x++)
		if ((z != 0 || x != 0) &&
			(sloping == true ||
			(Math::abs(x) == 1 && Math::abs(z) == 1) == false)) {
			//
			float yHeight;
			float successorX = x * stepSize + node->x;
			float successorZ = z * stepSize + node->z;
			// first node or walkable?
			if (isWalkable(successorX, node->y, successorZ, actorStepUpMax, yHeight) == true) {
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
				successorNode->key = toKeyFloat(successorNode->x) + "," + toKeyFloat(successorNode->y) + "," + toKeyFloat(successorNode->z);
				successorNodes.push(successorNode);
			}
		}
	}

	// Check successor nodes
	while (successorNodes.empty() == false) {
		PathFindingNode* successorNode = successorNodes.top();
		successorNodes.pop();
		auto& successorNodeKey = successorNode->key;

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
	auto& nodeKey = node->key;

	// Remove node from open nodes, as we checked its successors
	openNodes.erase(nodeKey);

	// add node to closed nodes list, as we checked its successors
	closedNodes[nodeKey] = node;

	//
	return PathFindingStatus::PATH_STEP;
}

bool PathFinding::findPath(BoundingVolume* actorBoundingVolume, const Transformations& actorTransformations, const Vector3& endPosition, const uint16_t collisionTypeIds, vector<Vector3>& path) {
	//
	auto now = Time::getCurrentMillis();

	// clear path
	path.clear();

	//
	this->collisionTypeIds = collisionTypeIds;

	// TODO: try to avoid cloning actor bv
	auto actorBoundingVolumeTransformed = actorBoundingVolume->clone();
	actorBoundingVolumeTransformed->fromTransformations(actorTransformations);
	this->actorXHalfExtension = actorBoundingVolumeTransformed->getBoundingBoxTransformed().getDimensions().getX() / 2.0f;
	this->actorZHalfExtension = actorBoundingVolumeTransformed->getBoundingBoxTransformed().getDimensions().getZ() / 2.0f;
	delete actorBoundingVolumeTransformed;

	// init bounding volume, transformations, collision body
	this->actorBoundingVolume = actorBoundingVolume;
	this->actorTransformations.fromTransformations(actorTransformations);
	auto actorCollisionBody = world->addCollisionBody("pathfinding.actor", true, collisionTypeIds, actorTransformations, {actorBoundingVolume});

	// positions
	Vector3 startPositionComputed;
	startPositionComputed.set(this->actorTransformations.getTranslation());

	// check if start is reachable
	/*
	{
		float startYHeight = startPositionComputed.getY();
		if (isWalkable(
			startPositionComputed.getX(),
			startPositionComputed.getY(),
			startPositionComputed.getZ(),
			startYHeight
			) == false) {
			//
			Console::println("PathFinding::findPath(): start is not walkable!");
			return false;
		} else {
			startPositionComputed.setY(startYHeight);
		}
	}
	*/

	// check if target is reachable
	Vector3 endPositionComputed;
	endPositionComputed.set(endPosition);
	{
		float endYHeight = endPositionComputed.getY();
		if (isWalkable(
				endPositionComputed.getX(),
				endPositionComputed.getY(),
				endPositionComputed.getZ(),
				10000.0f,
				endYHeight
			) == false) {
			//
			Console::println("PathFinding::findPath(): end is not walkable!");
			return false;
		} else {
			endPositionComputed.setY(endYHeight);
		}
	}

	// otherwise start path finding
	start(startPositionComputed, endPositionComputed);

	// do the steps
	bool done = false;
	bool success = false;
	int stepIdx;
	for (stepIdx = 0; done == false && stepIdx < stepsMax; stepIdx++) {
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
						path.push_back(Vector3(node->x, node->y, node->z));
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
						Console::println("PathFinding::findPath(): path with 0 steps: Fixing!");
						path.push_back(endPositionComputed);
					}
					done = true;
					success = true;
					break;
				}
		}
	}

	//
	/*
	if (stepIdx == stepsMax) {
		Console::println("PathFinding::findPath(): steps == stepsMax: " + to_string(stepIdx));
	}
	*/

	// unset actor bounding volume and remove rigid body
	this->actorBoundingVolume = nullptr;
	world->removeBody("pathfinding.actor");

	// reset
	reset();

	// Console::println("PathFinding::findPath(): time: " + to_string(Time::getCurrentMillis() - now) + "ms");

	// return success
	return success;
}
