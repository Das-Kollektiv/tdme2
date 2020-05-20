#include <tdme/utils/PathFinding.h>

#include <algorithm>
#include <string>
#include <map>
#include <stack>
#include <vector>

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
using std::vector;

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
	Console::print(
		"PathFinding::isWalkableInternal(): " +
		to_string(x) + ", " +
		to_string(y) + ", " +
		to_string(z)
	);
	auto walkable = isWalkable(x, y, z, height, collisionTypeIds, ignoreStepUpMax);
	Console::println(", success: " + to_string(walkable));
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
	auto start = new PathFindingNode();
	start->x = startXYZ[0];
	start->y = startXYZ[1];
	start->z = startXYZ[2];
	start->costsAll = 0.0f;
	start->costsReachPoint = 0.0f;
	start->costsEstimated = 0.0f;
	start->key = toKey(start->x, start->y, start->z);

	// end node
	auto& endXYZ = endPosition.getArray();
	end.x = endXYZ[0];
	end.y = endXYZ[1];
	end.z = endXYZ[2];
	end.costsAll = 0.0f;
	end.costsReachPoint = 0.0f;
	end.costsEstimated = 0.0f;
	end.key = toKey(end.x, end.y, end.z);

	// set up start node costs
	start->costsEstimated = computeDistance(start, &end);
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
	if (equalsLastNode(node, &end)) {
		end.previousNodeKey = node->previousNodeKey;
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

				// slope angle and center
				auto toVector = Vector3(successorX, node->y, successorZ);
				auto fromVector = Vector3(node->x, node->y, node->z);
				auto axis = toVector.clone().sub(fromVector);
				auto center = axis.clone().scale(0.5f).add(fromVector).setY(node->y + 0.1f);
				axis.normalize();
				slopeAngle = Vector3::computeAngle(
					Vector3(0.0f, 0.0f, 1.0f),
					axis,
					Vector3(0.0f, 1.0f, 0.0f)
				);

				// set up transformations
				Transformations slopeTestTransformations;
				slopeTestTransformations.setTranslation(center);
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
				auto successorNode = new PathFindingNode();
				successorNode->x = successorX;
				successorNode->z = successorZ;
				successorNode->y = yHeight;
				successorNode->costsAll = 0.0f;
				successorNode->costsReachPoint = 0.0f;
				successorNode->costsEstimated = 0.0f;
				successorNode->key = toKey(successorNode->x, successorNode->y, successorNode->z);
				// this should never happen, but still I like to check for it
				if (successorNode->key == node->key) {
					delete successorNode;
					continue;
				}
				successorNodes.push(successorNode);
			}
		}
	}

	// Check successor nodes
	while (successorNodes.empty() == false) {
		PathFindingNode* successorNode = successorNodes.top();
		successorNodes.pop();

		// Compute successor node's costs by costs to reach nodes point and the computed distance from node to successor node
		float successorCostsReachPoint = node->costsReachPoint + computeDistance(successorNode, node);

		// Find sucessor node in open nodes list
		PathFindingNode* openListNode = nullptr;
		auto openListNodeIt = openNodes.find(successorNode->key);
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
		auto closedListNodeIt = closedNodes.find(successorNode->key);
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
		successorNode->previousNodeKey = node->key;
		successorNode->costsReachPoint = successorCostsReachPoint;
		successorNode->costsEstimated = computeDistance(successorNode, &end);
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
		openNodes[successorNode->key] = successorNode;
	}

	// Remove node from open nodes, as we checked its successors
	openNodes.erase(node->key);

	// add node to closed nodes list, as we checked its successors
	closedNodes[node->key] = node;

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
		Vector3(stepSize * 2.0f, actorHeight / 2.0f, stepSize * 2.5f)
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
						map<string, PathFindingNode*>::iterator nodeIt;
						for (auto node = &end; node != nullptr; node = (nodeIt = closedNodes.find(node->previousNodeKey)) != closedNodes.end()?nodeIt->second:nullptr) {
							nodesCount++;
							// if (nodesCount > 0 && nodesCount % 100 == 0) {
							//	 Console::println("PathFinding::findPath(): compute path: steps: " + to_string(nodesCount) + " / " + to_string(path.size()) + ": " + to_string((uint64_t)node));
							// }
							Vector3 pathPosition(
								node->x,
								node->y,
								node->z
							);
							if (Float::isNaN(pathPosition.getX()) ||
								Float::isNaN(pathPosition.getY()) ||
								Float::isNaN(pathPosition.getZ())) {
								Console::println("PathFinding::findPath(): compute path: step: NAN");
								done = true;
								break;
							}
							path.
								push_back(
									pathPosition
								);
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

PathFinding::FlowMap* PathFinding::createFlowMap(map<string, DijkstraCellStruct>& dijkstraCellMap, const Vector3& endPosition, const Vector3& center, float depth, float width, const uint16_t collisionTypeIds, PathFindingCustomTest* customTest) {
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
	actorTransformations.setTranslation(endPosition);
	actorTransformations.update();
	world->addCollisionBody("tdme.pathfinding.actor", true, 32768, actorTransformations, {actorBoundingVolume});

	// see: https://howtorts.github.io/2014/01/04/basic-flow-fields.html
	// generate cost map via dijkstra
	vector<DijkstraCellStruct*> dijkstraCellsToProcess;
	for (auto z = -depth / 2; z < depth / 2; z+= stepSize) {
		for (auto x = -width / 2; x < width / 2; x+= stepSize) {
			auto cellPosition = Vector3(
				Math::floor((x + center.getX()) / stepSize) * stepSize,
				-10000.0f,
				Math::floor((z + center.getZ()) / stepSize) * stepSize
			);
			auto cellKey = toKey(
				cellPosition.getX(),
				cellPosition.getZ()
			);
			dijkstraCellMap[cellKey] =
				{
					.id = cellKey,
					.tested = false,
					.position = cellPosition,
					.walkable = false,
					.costs = 0.0f
				};
		}
	}

	// set up end position in costs map
	{
		auto endPositionGrid = Vector3(
			Math::floor(endPosition.getX() / stepSize) * stepSize,
			endPosition.getY(),
			Math::floor(endPosition.getZ() / stepSize) * stepSize
		);
		auto endPositionCellKey = toKey(
			endPositionGrid.getX(),
			endPositionGrid.getZ()
		);
		auto dijkstraCellEndPositionIt = dijkstraCellMap.find(endPositionCellKey);
		if (dijkstraCellEndPositionIt == dijkstraCellMap.end()) {
			Console::println("PathFinding::createFlowMap(): end position not in dijkstra cell map");
			return nullptr;
		} else {
			auto& dijkstraCellEndPosition = dijkstraCellEndPositionIt->second;
			dijkstraCellEndPosition.tested = true;
			dijkstraCellEndPosition.position = endPositionGrid;
			dijkstraCellEndPosition.walkable = true;
			dijkstraCellEndPosition.costs = 0.0f;
			dijkstraCellsToProcess.push_back(&dijkstraCellEndPosition);
		}
	}

	// compute costs and put it into map
	for (auto i = 0; i < dijkstraCellsToProcess.size(); i++) {
		auto& dijkstraCell = *dijkstraCellsToProcess[i];
		for (auto z = -1; z <= 1; z++)
		for (auto x = -1; x <= 1; x++)
		if ((z != 0 || x != 0)/* &&
			(Math::abs(x) == 1 && Math::abs(z) == 1) == false*/) {
			float neighbourX = x * stepSize + dijkstraCell.position.getX();
			float neighbourZ = z * stepSize + dijkstraCell.position.getZ();
			auto neighbourCellKey = toKey(
				Math::floor(neighbourX / stepSize) * stepSize,
				Math::floor(neighbourZ / stepSize) * stepSize
			);
			auto dijkstraNeighbourCellIt = dijkstraCellMap.find(neighbourCellKey);
			if (dijkstraNeighbourCellIt == dijkstraCellMap.end()) {
				continue;
			}
			auto& dijkstraNeighbourCell = dijkstraNeighbourCellIt->second;
			if (dijkstraNeighbourCell.tested == true) continue;
			float neighbourY;
			auto walkable = isWalkableInternal(neighbourX, dijkstraCell.position.getY(), neighbourZ, neighbourY);
			if (walkable == true) {
				dijkstraNeighbourCell.id = neighbourCellKey;
				dijkstraNeighbourCell.tested = true;
				dijkstraNeighbourCell.walkable = walkable;
				dijkstraNeighbourCell.position.setY(neighbourY);
				dijkstraNeighbourCell.costs = dijkstraCell.costs + 1.0f;
				dijkstraCellsToProcess.push_back(&dijkstraNeighbourCell);
			}
		}
	}

	// generate flow map
	auto flowMap = new FlowMap(stepSize);
	for (auto z = -depth / 2; z < depth / 2; z+= stepSize)
	for (auto x = -width / 2; x < width / 2; x+= stepSize) {
		auto cellPosition = Vector3(
			Math::floor((x + center.getX()) / stepSize) * stepSize,
			0.0f,
			Math::floor((z + center.getZ()) / stepSize) * stepSize
		);
		auto cellKey = toKey(
			cellPosition.getX(),
			cellPosition.getZ()
		);

		// walkable?
		auto dijkstraCellIt = dijkstraCellMap.find(cellKey);
		if (dijkstraCellIt == dijkstraCellMap.end()) {
			continue;
		}
		auto& dijkstraCell = dijkstraCellIt->second;
		if (dijkstraCell.walkable == false) continue;

		// check neighbours around our current cell
		DijkstraCellStruct* minDijkstraCell = nullptr;
		auto minCosts = 0.0f;
		for (auto _z = -1; _z <= 1; _z++)
		for (auto _x = -1; _x <= 1; _x++)
		if ((_z != 0 || _x != 0)/* &&
			(Math::abs(_x) == 1 && Math::abs(_z) == 1) == false*/) {
			//
			float neighbourX = _x * stepSize + cellPosition.getX();
			float neighbourZ = _z * stepSize + cellPosition.getZ();
			auto neighbourCellKey = toKey(
				Math::floor(neighbourX / stepSize) * stepSize,
				Math::floor(neighbourZ / stepSize) * stepSize
			);
			auto dijkstraNeighbourCellIt = dijkstraCellMap.find(neighbourCellKey);
			if (dijkstraNeighbourCellIt == dijkstraCellMap.end()) {
				continue;
			} else {
				auto& dijkstraNeighbourCell = dijkstraNeighbourCellIt->second;
				if (dijkstraNeighbourCell.walkable == true/* && flowMap->getCell(neighbourX, neighbourZ) == nullptr*/) {
					auto dijkstraNeighbourCellCosts = dijkstraNeighbourCell.costs - dijkstraCell.costs;
					if (minDijkstraCell == nullptr || dijkstraNeighbourCellCosts < minCosts) {
						minDijkstraCell = &dijkstraNeighbourCell;
						minCosts = dijkstraNeighbourCellCosts;
					}
				}
			}
		}
		if (minDijkstraCell != nullptr) {
			auto direction = minDijkstraCell->position.clone().sub(dijkstraCell.position).setY(0.0f).normalize();
			auto flowMapCell = new FlowMapCell(
				cellPosition, 
				minDijkstraCell->walkable,
				direction
			);
			flowMap->addCell(flowMapCell);
			Console::println("Neighbour: " + cellKey + " / cell: " + minDijkstraCell->id);
		} else {
			Console::println("No neighbour: " + cellKey);
		}
	}
	flowMap->dump();

	// unset actor bounding volume and remove rigid body
	this->actorBoundingVolume = nullptr;
	this->actorBoundingVolumeSlopeTest = nullptr;
	world->removeBody("tdme.pathfinding.actor");
	world->removeBody("tdme.pathfinding.actor.slopetest");

	// dispose custom test
	if (this->customTest != nullptr) {
		this->customTest->dispose();
		this->customTest = nullptr;
	}

	//
	return flowMap;
}