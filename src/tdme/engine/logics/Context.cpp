#include <tdme/engine/logics/Context.h>

#include <algorithm>
#include <deque>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/physics/WorldListener.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Transform.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/PathFinding.h>
#include <tdme/utilities/PathFindingCustomTest.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::copy;
using std::deque;
using std::map;
using std::set;
using std::string;
using std::to_string;
using std::unordered_set;
using std::vector;

using tdme::audio::Audio;
using tdme::audio::AudioEntity;
using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicNetworkPacket;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::physics::WorldListener;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::Engine;
using tdme::engine::Object;
using tdme::engine::SceneConnector;
using tdme::engine::Transform;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUI;
using tdme::math::Math;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::utilities::Console;
using tdme::utilities::PathFinding;
using tdme::utilities::PathFindingCustomTest;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

using tdme::engine::logics::Context;

Context::PathFindingThread::PathFindingThread(Context* context, int idx):
	Thread("wscontext-pathfindingthread", 4 * 1024 * 1024),
	context(context),
	idx(idx),
	timeStateStarted(-1LL),
	state(STATE_IDLE),
	alternativeEndSteps(0),
	customTest(nullptr),
	pathFindingMutex("pathfindingthread-mutex"),
	pathFindingCancelMutex("pathfindingthread-cancel-mutex"),
	worldActionsMutex("pathfindingthread-world-actions-mutex")
{
	reset();
	world = context->getWorld()->clone("pathfinding" +  to_string(idx) + "-world-" + (context->isServer() == true?"server":"client"), context->bodyCollisionTypeIdCloneMask);
	pathFinding = new tdme::utilities::PathFinding(world, true, 1000, 1.8f, 0.4f, 0.81f, 0.4f, context->skipOnBodyCollisionTypeIdMask, 5, 0.5f, 2.0f);
}

Context::PathFindingThread::~PathFindingThread() {
	delete pathFinding;
	delete world;
}

void Context::PathFindingThread::PathFindingThread::reset() {
	this->state = STATE_IDLE;
	this->timeStateStarted = -1LL;
	this->logicId.clear();
	this->startPosition.set(0.0f, 0.0f, 0.0f);
	this->endPosition.set(0.0f, 0.0f, 0.0f);
	this->actorId.clear();
	this->alternativeEndSteps = 0;
	this->customTest = nullptr;
	this->path.clear();
	this->flowMap = nullptr;
	this->createFlowMap = false;
	this->flowMapWidth = 0.0f;
	this->flowMapDepth = 0.0f;
	this->flowMap = nullptr;
}

void Context::PathFindingThread::addWorldAction(const WorldActionStruct& action) {
	worldActionsMutex.lock();
	worldActions.push_back(action);
	worldActionsMutex.unlock();
} 

Context::PathFindingThread::State Context::PathFindingThread::findPath(
	const string& logicId, 
	const string& actorId, 
	const Vector3& startPosition, 
	const Vector3& endPosition, 
	vector<Vector3>& path, 
	int alternativeEndSteps, 
	PathFindingCustomTest* customTest,
	bool createFlowMap,
	const vector<Vector3> flowMapEndPositions,
	const float flowMapWidth,
	const float flowMapDepth,
	FlowMap** flowMap
	) {
	if (pathFindingMutex.tryLock() == false) {
		return State::STATE_TRYLOCK_FAILED;
	}
	switch(state) {
		case STATE_IDLE:
			break;
		case STATE_PATHFINDING:
			if (this->actorId != actorId) {
				pathFindingMutex.unlock();
				return State::STATE_PATHFINDING_OTHER;
			}
			pathFindingMutex.unlock();
			return STATE_PATHFINDING;
		case STATE_PATHFINDING_FAILED:
			if (this->actorId != actorId) {
				auto now = Time::getCurrentMillis();
				if (now - timeStateStarted > 1000LL) {
					Console::println("Context::PathFindingThread[" + to_string(idx) + "]::findPath(): path finding result timeout: " + logicId + ": resetting!");
					reset();
				}
				pathFindingMutex.unlock();
				return State::STATE_PATHFINDING_OTHER;
			}
			reset();
			pathFindingMutex.unlock();
			return STATE_PATHFINDING_FAILED;
		case STATE_PATHFINDING_SUCCESS:
			{
				if (this->actorId != actorId) {
					auto now = Time::getCurrentMillis();
					if (now - timeStateStarted > 1000LL) {
						Console::println("Context::PathFindingThread[" + to_string(idx) + "]::findPath(): path finding result timeout: " + logicId + ": resetting!");
						reset();
					}
					pathFindingMutex.unlock();
					return State::STATE_PATHFINDING_OTHER;
				}
				path = this->path;
				if (this->endPosition.equals(endPosition) == false) {
					Console::println("Context::PathFindingThread[" + to_string(idx) + "]::findPath(): " + actorId + ": position changed!");
				}
				auto returnState = endPosition.equals(this->endPosition) == true?STATE_PATHFINDING_SUCCESS:State::STATE_PATHFINDING_OTHER;
				if (createFlowMap == true) {
					if (returnState == false) {
 						this->flowMap->releaseReference();
						this->flowMap = nullptr;
					} else {
						*flowMap = this->flowMap;
					} 
				} 
				reset();
				pathFindingMutex.unlock();
				return returnState;
			}
		default:
			break;
	}
	auto flowMapRequestIt = flowMapRequests.find(actorId);
	if (flowMapRequestIt != flowMapRequests.end()) {
		auto& flowMapRequest = flowMapRequestIt->second;
		if (flowMapRequest.flowMap != nullptr) {
			flowMapRequest.flowMap->releaseReference();
		}
		flowMapRequests.erase(flowMapRequestIt);
	}
	this->logicId = logicId;
	this->startPosition = startPosition;
	this->endPosition = endPosition;
	this->actorId = actorId;
	this->alternativeEndSteps = alternativeEndSteps;
	this->customTest = customTest;
	this->createFlowMap = createFlowMap;
	this->flowMapWidth = flowMapWidth;
	this->flowMapDepth = flowMapDepth;
	this->flowMap = nullptr;
	state = STATE_PATHFINDING;
	timeStateStarted = Time::getCurrentMillis();
	pathFindingMutex.unlock();
	return STATE_PATHFINDING;
}

Context::PathFindingThread::FlowMapExtensionState Context::PathFindingThread::getFlowMapExtension(const string& actorId, FlowMap** flowMap) {
	if (pathFindingMutex.tryLock() == false) return FLOWMAPEXTENSIONSTATE_TRYLOCK_FAILED;
	auto flowMapRequestIt = flowMapRequests.find(actorId);
	if (flowMapRequestIt == flowMapRequests.end()) {
		pathFindingMutex.unlock();
		return FLOWMAPEXTENSIONSTATE_REQUEST_NONE;
	}
	auto& flowMapRequest = flowMapRequestIt->second;
	*flowMap = flowMapRequest.flowMap;
	flowMapRequest.flowMap = nullptr;
	if (flowMapRequest.pathIdx >= flowMapRequest.path.size()) {
		flowMapRequests.erase(flowMapRequestIt);
		pathFindingMutex.unlock();
		return FLOWMAPEXTENSIONSTATE_REQUEST_FINISHED;
	}
	pathFindingMutex.unlock();
	return FLOWMAPEXTENSIONSTATE_REQUEST_NOTFINISHED;
}

void Context::PathFindingThread::cancel(const string& actorId) {
	pathFindingCancelMutex.lock();
	cancelActorIds.push_back(actorId);
	pathFindingCancelMutex.unlock();
}

void Context::PathFindingThread::run() {
	Console::println(string(context->server == true?"SERVER::":"CLIENT") + "|ws::Context::PathFindingThread[" + to_string(idx) + "]::run(): init");
	while (isStopRequested() == false) {
		// synch path finding physics world with world
		context->logicsMutex->lock();
		worldActionsMutex.lock();
		auto worldActionsCopy = worldActions;
		worldActions.clear();
		worldActionsMutex.unlock();
		if (worldActionsCopy.size() > 0) {
			pathFinding->reset();
		}
		for (auto& worldActionStruct: worldActionsCopy) {
			if (worldActionStruct.action == WorldActionStruct::ACTION_ADDED) {
				if ((worldActionStruct.collisionTypeId & context->bodyCollisionTypeIdCloneMask) != 0) {
					world->addStaticRigidBody(
						worldActionStruct.id,
						worldActionStruct.collisionTypeId,
						worldActionStruct.enabled,
						worldActionStruct.transform,
						worldActionStruct.friction,
						worldActionStruct.boundingVolumes
					);
				}
			} else
			if (worldActionStruct.action == WorldActionStruct::ACTION_REMOVED) {
				if (worldActionStruct.collisionTypeId & context->bodyCollisionTypeIdCloneMask != 0) {
					world->removeBody(
						worldActionStruct.id
					);
				}
			}
		}
		worldActions.clear();
		context->logicsMutex->unlock();

		// do cancelling
		pathFindingMutex.lock();
		pathFindingCancelMutex.lock();
		for (auto actorId: cancelActorIds) {
			switch(state) {
				case STATE_IDLE:
					{
						continue;
					}
				default:
					break;
			}
			if (this->actorId != actorId) continue;
			auto flowMapRequestIt = flowMapRequests.find(actorId);
			if (flowMapRequestIt != flowMapRequests.end()) {
				auto& flowMapRequest = flowMapRequestIt->second;
				if (flowMapRequest.flowMap != nullptr) {
					flowMapRequest.flowMap->releaseReference();
				}
				flowMapRequests.erase(flowMapRequestIt);
			}
			reset();
			context->getPathFinding()->notifyCancel(actorId);
			break;
		}
		cancelActorIds.clear();
		pathFindingCancelMutex.unlock();

		// do pathfinding action
		switch(state) {
			case STATE_PATHFINDING:
				if (createFlowMap == true) {
					if (pathFinding->findFlowMapPath(
						startPosition,
						endPosition,
						context->bodyCollisionTypeIdMask,
						path,
						alternativeEndSteps/*,
						customTest*/
						) == true) {
						timeStateStarted = Time::getCurrentMillis();
						auto pathIdx = 0;
						if (path.size() > 20) {
							FlowMapRequest flowMapRequest;
							flowMapRequest.flowMapWidth = flowMapWidth;
							flowMapRequest.flowMapDepth = flowMapDepth;
							flowMapRequest.pathIdx = 20;
							flowMapRequest.path = path;
							flowMapRequest.flowMap = nullptr;
							flowMapRequests[actorId] = flowMapRequest;
						}	
						vector<Vector3> partialPath(Math::min(path.size() - pathIdx, 20));
						copy(path.begin() + pathIdx, path.begin() + pathIdx + Math::min(path.size() - pathIdx, 20), partialPath.begin());
						this->flowMap = pathFinding->createFlowMap(
							{ partialPath[partialPath.size() - 1] },
							Vector3(),
							flowMapWidth,
							flowMapDepth,
							context->bodyCollisionTypeIdMask,
							partialPath,
							path.size() > 20?false:true
						);
						state = STATE_PATHFINDING_SUCCESS;
					} else {
						timeStateStarted = Time::getCurrentMillis();
						state = STATE_PATHFINDING_FAILED;
					}
				} else {
					if (pathFinding->findPath(
						startPosition,
						endPosition,
						context->bodyCollisionTypeIdMask,
						path,
						alternativeEndSteps/*,
						customTest*/
						) == true) {
						timeStateStarted = Time::getCurrentMillis();
						state = STATE_PATHFINDING_SUCCESS;
					} else {
						timeStateStarted = Time::getCurrentMillis();
						state = STATE_PATHFINDING_FAILED;
					}
				}
				break;
			default:
				for (auto& flowMapRequestIt: flowMapRequests) {
					auto& flowMapRequest = flowMapRequestIt.second;
					if (flowMapRequest.flowMap != nullptr) continue;
					auto pathIdx = flowMapRequest.pathIdx - 2;
					auto partialPathLength = Math::min(flowMapRequest.path.size() - pathIdx, 22);
					vector<Vector3> partialPath(partialPathLength);
					copy(flowMapRequest.path.begin() + pathIdx, flowMapRequest.path.begin() + pathIdx + partialPathLength, partialPath.begin());
					flowMapRequest.flowMap = pathFinding->createFlowMap(
						{ partialPath[partialPath.size() - 1] },
						Vector3(),
						flowMapRequest.flowMapWidth,
						flowMapRequest.flowMapDepth,
						context->bodyCollisionTypeIdMask,
						partialPath,
						pathIdx >= path.size()?true:false
					);
					flowMapRequest.pathIdx+= Math::min(flowMapRequest.path.size() - flowMapRequest.pathIdx, 20);
				}
				break;
		}
		pathFindingMutex.unlock();

		// get some rest
		sleep(50L);
	}
	Console::println(string(context->server == true?"SERVER::":"CLIENT") + "|ws::Context::PathFindingThread[" + to_string(idx) + "]::run(): done");
}

string Context::PathFindingThread::getActorId() {
	pathFindingMutex.lock();
	auto _actorId = actorId;
	pathFindingMutex.unlock();
	return _actorId;
}

Context::PathFinding::PathFinding(Context* context, int threadCount):
	context(context),
	actorThreadMapMutex("wspathfinding-threadmap-mutex")
{
	setThreadCount(threadCount);
}

void Context::PathFinding::setThreadCount(int threadCount) {
	this->threadCount = threadCount > 0?threadCount:Math::clamp(static_cast<int>(Math::ceil(Thread::getHardwareThreadCount() / 3)), 1, 4);
}

void Context::PathFinding::start() {
	threads.resize(threadCount);
	for (auto i = 0; i < threads.size(); i++) {
		threads[i] = new PathFindingThread(context, i);
	}
	for (auto thread: threads) thread->start();
}

void Context::PathFinding::shutdown() {
	for (auto thread: threads) thread->stop();
	for (auto thread: threads) thread->join();
	for (auto thread: threads) delete thread;
	threads.clear();
}

void Context::PathFinding::addWorldAction(const Context::PathFindingThread::WorldActionStruct& action) {
	for (auto thread: threads) thread->addWorldAction(action);
}

void Context::PathFinding::reset() {
	for (auto thread: threads) thread->reset();
}

Context::PathFindingThread::State Context::PathFinding::findPath(
	const string& logicId, 
	const string& actorId, 
	const Vector3& startPosition, 
	const Vector3& endPosition, 
	vector<Vector3>& path, 
	int alternativeEndSteps, 
	PathFindingCustomTest* customTest,
	bool createFlowMap,
	const vector<Vector3> flowMapEndPositions,
	const float flowMapWidth,
	const float flowMapDepth,
	FlowMap** flowMap
	) {
	actorThreadMapMutex.lock();
	auto actorThreadMapIt = actorThreadMap.find(actorId);
	actorThreadMapMutex.unlock();
	auto threadIdx = actorThreadMapIt == actorThreadMap.end()?-1:actorThreadMapIt->second;
	if (threadIdx != -1) {
		auto threadPathFindingState = threads[threadIdx]->findPath(
			logicId,
			actorId,
			startPosition,
			endPosition,
			path,
			alternativeEndSteps,
			customTest,
			createFlowMap,
			flowMapEndPositions,
			flowMapWidth,
			flowMapDepth,
			flowMap
		);
		switch(threadPathFindingState) {
			case Context::PathFindingThread::STATE_IDLE:
				actorThreadMapMutex.lock();
				actorThreadMap.erase(actorId);
				actorThreadMapMutex.unlock();
				break;
			case Context::PathFindingThread::STATE_TRYLOCK_FAILED:
				return Context::PathFindingThread::STATE_TRYLOCK_FAILED;
			case Context::PathFindingThread::STATE_PATHFINDING_OTHER:
				actorThreadMapMutex.lock();
				actorThreadMap.erase(actorId);
				actorThreadMapMutex.unlock();
				break;
			case Context::PathFindingThread::STATE_PATHFINDING:
				return Context::PathFindingThread::STATE_PATHFINDING;
			case Context::PathFindingThread::STATE_PATHFINDING_FAILED:
				actorThreadMapMutex.lock();
				actorThreadMap.erase(actorId);
				actorThreadMapMutex.unlock();
				return Context::PathFindingThread::STATE_PATHFINDING_FAILED;
			case Context::PathFindingThread::STATE_PATHFINDING_SUCCESS:
				actorThreadMapMutex.lock();
				actorThreadMap.erase(actorId);
				actorThreadMapMutex.unlock();
				return Context::PathFindingThread::STATE_PATHFINDING_SUCCESS;
		}
	}
	for (auto thread: threads) {
		auto threadPathFindingState = thread->findPath(
			logicId,
			actorId,
			startPosition,
			endPosition,
			path,
			alternativeEndSteps,
			customTest,
			createFlowMap,
			flowMapEndPositions,
			flowMapWidth,
			flowMapDepth,
			flowMap
		);
		switch(threadPathFindingState) {
			case Context::PathFindingThread::STATE_IDLE:
				break;
			case Context::PathFindingThread::STATE_TRYLOCK_FAILED:
				break;
			case Context::PathFindingThread::STATE_PATHFINDING_OTHER:
				break;
			case Context::PathFindingThread::STATE_PATHFINDING:
				actorThreadMapMutex.lock();
				actorThreadMap[actorId] = thread->getThreadIdx();
				actorThreadMapMutex.unlock();
				return Context::PathFindingThread::STATE_PATHFINDING;
			case Context::PathFindingThread::STATE_PATHFINDING_FAILED:
				actorThreadMapMutex.lock();
				actorThreadMap.erase(actorId);
				actorThreadMapMutex.unlock();
				return Context::PathFindingThread::STATE_PATHFINDING_FAILED;
			case Context::PathFindingThread::STATE_PATHFINDING_SUCCESS:
				actorThreadMapMutex.lock();
				actorThreadMap.erase(actorId);
				actorThreadMapMutex.unlock();
				return Context::PathFindingThread::STATE_PATHFINDING_SUCCESS;
		}
	}
	return Context::PathFindingThread::STATE_PATHFINDING_OTHER;
}

bool Context::PathFinding::getFlowMapExtension(const string& actorId, FlowMap** flowMap) {
	*flowMap = nullptr;
	for (auto thread: threads) {
		auto lastExtensionState = thread->getFlowMapExtension(actorId, flowMap);
		switch(lastExtensionState) {
			case Context::PathFindingThread::FLOWMAPEXTENSIONSTATE_TRYLOCK_FAILED: break;
			case Context::PathFindingThread::FLOWMAPEXTENSIONSTATE_REQUEST_NONE: break;
			case Context::PathFindingThread::FLOWMAPEXTENSIONSTATE_REQUEST_NOTFINISHED: return false;
			case Context::PathFindingThread::FLOWMAPEXTENSIONSTATE_REQUEST_FINISHED: return true;
		}
	}
	return false;
}

void Context::PathFinding::cancel(const string& actorId) {
	for (auto thread: threads) thread->cancel(actorId);
}

void Context::PathFinding::notifyCancel(const string& actorId) {
	actorThreadMapMutex.lock();
	actorThreadMap.erase(actorId);
	actorThreadMapMutex.unlock();
}

Context::ContextWorldListener::ContextWorldListener(Context* context): context(context) {
}

void Context::ContextWorldListener::onAddedBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, bool enabled, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy) {
	if (type != Body::BODYTYPE_STATIC) return;
	Context::PathFindingThread::WorldActionStruct worldAction;
	worldAction.action = Context::PathFindingThread::WorldActionStruct::ACTION_ADDED;
	worldAction.id = id;
	worldAction.type = type;
	worldAction.enabled = enabled;
	worldAction.collisionTypeId = collisionTypeId;
	worldAction.transform = transform;
	worldAction.restitution = restitution;
	worldAction.friction = friction;
	worldAction.mass = mass;
	worldAction.inertiaTensor = inertiaTensor;
	worldAction.boundingVolumes = boundingVolumes;
	worldAction.hierarchy = hierarchy;
	context->getPathFinding()->addWorldAction(worldAction);
}

void Context::ContextWorldListener::onRemovedBody(const string& id, Body::BodyType type, uint16_t collisionTypeId) {
	if (type != Body::BODYTYPE_STATIC) return;
	Context::PathFindingThread::WorldActionStruct worldAction;
	worldAction.action = Context::PathFindingThread::WorldActionStruct::ACTION_REMOVED;
	worldAction.id = id;
	worldAction.type = type;
	worldAction.collisionTypeId = collisionTypeId;
	context->getPathFinding()->addWorldAction(worldAction);
}

void Context::ContextWorldListener::onAddedSubBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, const string& subBodyParentId, const string& subBodyId, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes) {
	// TODO
}

void Context::ContextWorldListener::onRemovedSubBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, const string& subBodyParentId, const string& subBodyId) {
	// TODO
}

Context::Context(bool server): pathFinding(this), world(nullptr), server(server), initialized(false) {
	Console::println("Context::Context(): " + to_string(server));
	timeStarted = -1;
}

Context::~Context() {
	Console::println("Context::~Context()");
	if (world != nullptr) delete world;
	if (scene != nullptr) delete scene;
}

void Context::initialize() {
	// TODO: optionally pathfinding should be set enabled in client and/or server
	// path finding is only required for server
	// if (server == true) {

	// world listener
	worldListener = new ContextWorldListener(this);
	world->addWorldListener(worldListener);

	// path finding thread
	pathFinding.start();

	// }

	//
	timeStarted = Time::getCurrentMillis();

	//
	initialized = true;
}

void Context::shutdown() {
	Console::println("Context::shutdown()");
	// TODO: optionally pathfinding should be set enabled in client and/or server
	pathFinding.shutdown();
	world->removeWorldListener(worldListener);
	//
	for (auto logic: logics) delete logic;
	logics.clear();
	logicsById.clear();
}

void Context::addLogic(Logic* logic) {
	Console::println(string(server == true?"SERVER":"CLIENT") + "|Context::addLogic(): adding '" + logic->getId() + "'");
	// check if exists in current game logics
	if (logicsById.find(logic->getId()) != logicsById.end()) {
		Console::println(string(server == true?"SERVER":"CLIENT") + "|Context::addLogic(): NOT adding '" + logic->getId() + "', logic exists!");
		return;
	}
	// check if exists in new game logics
	for (auto newLogic: newLogics) {
		if (logic->getId() == newLogic->getId()) {
			Console::println(string(server == true?"SERVER":"CLIENT") + "|Context::addLogic(): NOT adding '" + logic->getId() + "', logic exists!");
			return;
		}
	}
	//
	newLogics.push_back(logic);
	// call event
	logic->onLogicAdded();
}


bool Context::doProcessPacket(NetworkLogic* logic, LogicNetworkPacket& packet, const string& key) {
	auto now = Time::getCurrentMillis();

	// clean up packet states
	vector<string> packetsToRemove;
	for (auto& packetStateIt: packetStates) {
		if (packetStateIt.second.timeCreated > now - 120000L) {
			packetsToRemove.push_back(packetStateIt.first);
		}
	}
	for (auto& packetToRemove: packetsToRemove) {
		// Console::println(string(server == true?"SERVER":"CLIENT") + "|Context::doProcessPacket(): " + packetToRemove + ": removing");
		packetStates.erase(packetToRemove);
	}

	// add packet state or report that we have processed it already
	string _key;
	_key+= logic->getNetworkPacketTypeId();
	_key+= '_';
	_key+= logic->getId();
	_key+= '_';
	_key+= key;
	auto packetStateIt = packetStates.find(_key);
	if (packetStateIt == packetStates.end()) {
		PacketState packetState;
		packetState.timeCreated = now;
		packetState.messageId = packet.getMessageId();
		packetStates[_key] = packetState;
		// Console::println(string(server == true?"SERVER":"CLIENT") + "|Context::doProcessPacket(): " + _key + ": new (" + to_string(packetStates.size()) + ")");
		return true;
	} else {
		auto& packetState = packetStateIt->second;
		if (packet.getMessageId() <= packetState.messageId) {
			return packet.isReinjected() == true && packet.isProcessed() == false;
		} else {
			packetState.messageId = packet.getMessageId();
			packetState.timeCreated = Time::getCurrentMillis();
			// Console::println(string(server == true?"SERVER":"CLIENT") + "|Context::doProcessPacket(): " + _key + " " + to_string(packet.getMessageId()) + " > " + to_string(packetState.messageId) + " " + to_string(packetStates.size()) + ")");
			return true;
		}
	}
}

void Context::unsetProcessPacket(NetworkLogic* logic, LogicNetworkPacket& packet, const string& key) {
	// add packet state or report that we have processed it already
	string _key;
	_key+= logic->getNetworkPacketTypeId();
	_key+= '_';
	_key+= logic->getId();
	_key+= '_';
	_key+= key;
	auto packetStateIt = packetStates.find(_key);
	if (packetStateIt != packetStates.end()) {
		packetStates.erase(packetStateIt);
	}
}


void Context::initUpdateEngine() {
}

void Context::doneUpdateEngine() {
}

void Context::initUpdateLogics() {
}

void Context::doneUpdateLogics() {
}
