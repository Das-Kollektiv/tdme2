#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/engine/logics/NetworkLogic.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/physics/WorldListener.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/PathFinding.h>
#include <tdme/utilities/PathFindingCustomTest.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using tdme::audio::Audio;
using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicNetworkPacket;
using tdme::engine::logics::NetworkLogic;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::physics::WorldListener;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Vector3;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::utilities::Console;
using tdme::utilities::PathFinding;
using tdme::utilities::PathFindingCustomTest;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

/** 
 * Logics context
 * @author Andreas Drewke
 */
class tdme::engine::logics::Context
{
public:
	static constexpr bool VERBOSE { false };

public:
	/**
	 * Path finding thread
	 * @author Andreas Drewke
	 */
	class PathFindingThread: public Thread {
	public:
		enum State {
			STATE_IDLE,
			STATE_TRYLOCK_FAILED,
			STATE_PATHFINDING_OTHER,
			STATE_PATHFINDING,
			STATE_PATHFINDING_FAILED,
			STATE_PATHFINDING_SUCCESS
		};

		struct WorldActionStruct {
			enum Action {ACTION_ADDED, ACTION_REMOVED};
			Action action;
			string id;
			int32_t type;
			bool enabled;
			int32_t collisionTypeId;
			Transform transform;
			float restitution;
			float friction;
			float mass;
			Vector3 inertiaTensor;
			vector<BoundingVolume*> boundingVolumes;
			bool hierarchy;
		};

		enum FlowMapExtensionState {
			FLOWMAPEXTENSIONSTATE_TRYLOCK_FAILED,
			FLOWMAPEXTENSIONSTATE_REQUEST_NONE,
			FLOWMAPEXTENSIONSTATE_REQUEST_NOTFINISHED,
			FLOWMAPEXTENSIONSTATE_REQUEST_FINISHED,
		};

	private:
		struct FlowMapRequest {
			float flowMapWidth;
			float flowMapDepth;
			int pathIdx;
			vector<Vector3> path;
			FlowMap* flowMap { nullptr };
		};

		Context* context;
		int idx;
		volatile State state;
		int64_t timeStateStarted;
		string logicId;
		Vector3 startPosition;
		Vector3 endPosition;
		string actorId;
		int alternativeEndSteps;
		PathFindingCustomTest* customTest;
		vector<Vector3> path;
		vector<string> cancelActorIds;
		bool createFlowMap;
		float flowMapWidth;
		float flowMapDepth;
		FlowMap* flowMap;
		unordered_map<string, FlowMapRequest> flowMapRequests;
		unique_ptr<World> world;
		unique_ptr<PathFinding> pathFinding;
		Mutex pathFindingMutex;
		Mutex pathFindingCancelMutex;
		vector<WorldActionStruct> worldActions;
		Mutex worldActionsMutex;

		/**
		 * Run
		 */
		virtual void run();

	public:
		/**
		 * Public constructor
		 * @param context context
		 * @param idx index
		 */
		PathFindingThread(Context* context, int idx);

		/**
		 * Public destructor
		 */
		virtual ~PathFindingThread();

		/**
		 * @return thread index
		 */
		inline int getThreadIdx() {
			return idx;
		}

		/**
		 * Add world action
		 * @param action action
		 */
		void addWorldAction(const WorldActionStruct& action);

		/**
		 * Find path
		 * @param logicId logic id
		 * @param actorId actor id
		 * @param startPosition start position
		 * @param endPosition end position
		 * @param path path
		 * @param alternativeEndSteps alternative end steps
		 * @param customTest custom test
		 * @param createFlowMap create flow map
		 * @param flowMapEndPositions flow map end positions
		 * @param flowMapWidth flow map width
		 * @param flowMapDepth flow map height
		 * @param flowMap pointer to flowmap variable to store flowmap into
		 */
		State findPath(
			const string& logicId, 
			const string& actorId, 
			const Vector3& startPosition, 
			const Vector3& endPosition, 
			vector<Vector3>& path, 
			int alternativeEndSteps = 0,
			PathFindingCustomTest* customTest = nullptr,
			bool createFlowMap = false,
			const vector<Vector3> flowMapEndPositions = vector<Vector3>(),
			const float flowMapWidth = 0.0,
			const float flowMapDepth = 0.0,
			FlowMap** flowMap = nullptr
		);

		/**
		 * Get flow map extension
		 * @param actorId actor id
		 * @param flowMap pointer to flowmap variable to store flowmap into
		 * @return flow map extension state
		 */
		FlowMapExtensionState getFlowMapExtension(const string& actorId, FlowMap** flowMap);

		/**
		 * Reset current path finding
		 */
		void reset();

		/**
		 * Cancel
		 * @param actorId actor id
		 */
		void cancel(const string& actorId);

		/**
		 * @return current pathfinding actor id
		 */
		string getActorId();
	};

	/**
	 * Path Finding
	 * @author Andreas Drewke
	 */
	class PathFinding {
	private:
		Context* context { nullptr };
		int threadCount;
		vector<PathFindingThread*> threads;
		unordered_map<string, int> actorThreadMap;
		int scheduleThreadIdx { 0 };
		Mutex actorThreadMapMutex;
	public:
		/**
		 * Public constructor
		 * @param context context
		 * @param threadCount thread count or 0 for default
		 */
		PathFinding(Context* context, int threadCount = 0);

		/**
		 * Set thread count
		 * @param threadCount thread count
		 */
		void setThreadCount(int threadCount);

		/**
		 * Start path finding
		 */
		void start();

		/**
		 * Shutdown path finding
		 */
		void shutdown();

		/**
		 * Add world action
		 * @param action action
		 */
		void addWorldAction(const Context::PathFindingThread::WorldActionStruct& action);

		/**
		 * Find path
		 * @param logicId logic id
		 * @param actorId actor id
		 * @param startPosition start position
		 * @param endPosition end position
		 * @param path path
		 * @param alternativeEndSteps alternative end steps
		 * @param customTest custom test
		 * @param createFlowMap create flow map
		 * @param flowMapEndPositions flow map end positions
		 * @param flowMapWidth flow map width
		 * @param flowMapDepth flow map height
		 * @param flowMap pointer to flowmap variable to store flowmap into
		 */
		PathFindingThread::State findPath(
			const string& logicId, 
			const string& actorId, 
			const Vector3& startPosition, 
			const Vector3& endPosition, 
			vector<Vector3>& path, 
			int alternativeEndSteps = 0,
			PathFindingCustomTest* customTest = nullptr,
			bool createFlowMap = false,
			const vector<Vector3> flowMapEndPositions = vector<Vector3>(),
			const float flowMapWidth = 0.0,
			const float flowMapDepth = 0.0,
			FlowMap** flowMap = nullptr
		);

		/**
		 * Get flow map extension
		 * @param actorId actor id
		 * @param flowMap pointer to flowmap variable to store flowmap into
		 * @return if this is the last flow map extensions
		 */
		bool getFlowMapExtension(const string& actorId, FlowMap** flowMap);

		/**
		 * Reset current path finding
		 */
		void reset();

		/**
		 * Cancel
		 * @param actorId actor id
		 */
		void cancel(const string& actorId);

		/**
		 * Notify a cancelled actor path finding
		 * @param actorId actor id
		 */
		void notifyCancel(const string& actorId);
	};

private:

	/**
	 * Context physics world listener
	 */
	class ContextWorldListener: public WorldListener {
		friend class Context;
	private:
		Context* context { nullptr };
	public:
		/**
		 * Constructor
		 * @param context context
		 */
		ContextWorldListener(Context* context);

		// overridden methods
		void onAddedBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, bool enabled, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy = false) override;
		void onRemovedBody(const string& id, Body::BodyType type, uint16_t collisionTypeId) override;
		void onAddedSubBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, const string& subBodyParentId, const string& subBodyId, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes) override;
		void onRemovedSubBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, const string& subBodyParentId, const string& subBodyId) override;
	};

	struct PacketState {
		int64_t timeCreated;
		uint32_t messageId;
	};

	string applicationRootPathName;

	int64_t timeStarted;

	// path finding which is context bound too
	uint16_t bodyCollisionTypeIdMask { 1/*Body::TYPEID_STATIC*/ };
	uint16_t skipOnBodyCollisionTypeIdMask { 0 };
	uint16_t bodyCollisionTypeIdCloneMask { 1/*Body::TYPEID_STATIC*/ };
	PathFinding pathFinding;

	// context main data
	volatile bool initialized;
	Mutex* logicsMutex { nullptr };
	ContextWorldListener* worldListener { nullptr };
	Scene* scene { nullptr };
	unordered_map<string, Logic*> logicsById;
	vector<Logic*> logics;
	vector<Logic*> newLogics;
	unordered_map<string, PacketState> packetStates;
	int soundPoolSize { 10 };

protected:
	Engine* engine { nullptr };
	Engine* guiEngine { nullptr };
	Audio* audio { nullptr };
	World* world { nullptr };
	bool server;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Context)

	/**
	 * Public constructor
	 * @param server server
	 */
	Context(bool server);

	/**
	 * Destructor
	 */
	virtual ~Context();

	/**
	 * @return application root path name
	 */
	inline const string& getApplicationRootPathName() {
		return applicationRootPathName;
	}

	/**
	 * Set application root path name
	 * @param applicationRootPathName application root path name
	 */
	inline void setApplicationRootPathName(const string& applicationRootPathName) {
		this->applicationRootPathName = applicationRootPathName;
	}

	/**
	 * @return time started
	 */
	inline int64_t getTimeStarted() {
		return timeStarted;
	}

	/**
	 * @return if initialized
	 */
	inline bool isInitialized() {
		return initialized;
	}

	/**
	 * @return logics mutex
	 */
	inline Mutex* getLogicsMutex() {
		return logicsMutex;
	}

	/**
	 * Set logics mutex
	 */
	inline void setLogicsMutex(Mutex* logicsMutex) {
		this->logicsMutex = logicsMutex;
	}

	/**
	 * @return is context is server context
	 */
	inline bool isServer() {
		return server;
	}

	/**
	 * @return engine
	 */
	inline Engine* getEngine() {
		return engine;
	}

	/**
	 * Set engine
	 * @param engine engine
	 */
	inline void setEngine(Engine* engine) {
		this->engine = engine;
	}

	/**
	 * @return GUI engine
	 */
	inline Engine* getGUIEngine() {
		return guiEngine;
	}

	/**
	 * Set GUI engine
	 * @param guiEngine engine
	 */
	inline void setGUIEngine(Engine* guiEngine) {
		this->guiEngine = guiEngine;
	}

	/**
	 * @return audio instance
	 */
	inline Audio* getAudio() {
		return audio;
	}

	/**
	 * Set audio
	 * @param audio audio
	 */
	inline void setAudio(Audio* audio) {
		this->audio = audio;
	}

	/**
	 * @return physics world
	 */
	inline World* getWorld() {
		return world;
	}

	/**
	 * Set physics world
	 * @param world physics world
	 */
	inline void setWorld(World* world) {
		this->world = world;
	}

	/**
	 * @return scene
	 */
	inline Scene* getScene() {
		return scene;
	}

	/**
	 * Set scene
	 * @param scene scene
	 */
	inline void setScene(Scene* scene) {
		if (this->scene == scene) return;
		if (this->scene != nullptr) delete this->scene;
		this->scene = scene;
	}

	/**
	 * Unset scene
	 */
	inline void unsetScene() {
		this->scene = nullptr;
	}

	/**
	 * Initialize logics
	 */
	virtual void initialize();

	/**
	 * Shut down logics
	 */
	virtual void shutdown();

	/**
	 * Add logic
	 * @param logic logic
	 */
	void addLogic(Logic* logic);

	/**
	 * Get logic
	 * @param id id
	 * @return logic or nullptr
	 */
	inline Logic* getLogic(const string& id) {
		auto logicIt = logicsById.find(id);
		return logicIt != logicsById.end()?logicIt->second:nullptr;
	}

	/**
	 * Add logics that have been added and tagged as new
	 * @return count of new logics that have been finally added to context
	 */
	inline int addNewLogics() {
		int newLogicsCount = newLogics.size();
		// add new game logics
		for (auto logic: newLogics) {
			// add game logic to lists
			logicsById[logic->getId()] = logic;
			logics.push_back(logic);
		}
		newLogics.clear();
		return newLogicsCount;
	}

	/**
	 * @return logics
	 */
	inline const vector<Logic*>& getLogics() {
		return logics;
	}

	/**
	 * @return new logics
	 */
	inline const vector<Logic*>& getNewLogics() {
		return newLogics;
	}

	/**
	 * @return path finding body collision type id mask
	 */
	inline uint16_t getBodyCollisionTypeIdMask() {
		return bodyCollisionTypeIdMask;
	}

	/**
	 * Set path finding body collision type id mask
	 * @param bodyCollisionTypeIdMask body collision type id mask
	 */
	inline void setBodyCollisionTypeIdMask(uint16_t bodyCollisionTypeIdMask) {
		this->bodyCollisionTypeIdMask = bodyCollisionTypeIdMask;
	}

	/**
	 * @return body collision type id mask to skip on in path finding
	 */
	inline uint16_t getSkipOnBodyCollisionTypeIdMask() {
		return skipOnBodyCollisionTypeIdMask;
	}

	/**
	 * Set body collision type id mask to skip on in path finding
	 * @param skipOnBodyCollisionTypeIdMask skip on body collision type id mask
	 */
	inline void setSkipOnBodyCollisionTypeIdMask(uint16_t skipOnBodyCollisionTypeIdMask) {
		this->skipOnBodyCollisionTypeIdMask = skipOnBodyCollisionTypeIdMask;
	}

	/**
	 * @return body collision type id clone mask
	 */
	inline uint16_t getBodyCollisionTypeIdCloneMask() {
		return bodyCollisionTypeIdCloneMask;
	}

	/**
	 * Set body collision type id clone mask, which is used for path finding
	 * @param bodyCollisionTypeIdCloneMask body type id clone mask
	 */
	inline void setBodyCollisionTypeIdCloneMask(uint16_t bodyCollisionTypeIdCloneMask) {
		this->bodyCollisionTypeIdCloneMask = bodyCollisionTypeIdCloneMask;
	}

	/**
	 * @return sound pool size
	 */
	inline int getSoundPoolSize() {
		return soundPoolSize;
	}

	/**
	 * Set sound pool size
	 * @param soundPoolSize sound pool size
	 */
	inline void setSoundPoolSize(int soundPoolSize) {
		this->soundPoolSize = soundPoolSize;
	}

	/**
	 * Get path finding thread
	 */
	inline PathFinding* getPathFinding() {
		return &pathFinding;
	}

	/**
	 * Returns if to process packet or not
	 * @param logic logic
	 * @param packet packet
	 * @param key key
	 * @return if to process packet
	 */
	bool doProcessPacket(NetworkLogic* logic, LogicNetworkPacket& packet, const string& key);

	/**
	 * Returns if to process packet or not
	 * @param logic logic
	 * @param packet packet
	 * @param line line
	 * @param key key
	 * @return if to process packet
	 */
	inline bool doProcessPacketAtLine(NetworkLogic* logic, LogicNetworkPacket& packet, uint32_t line, const string& key = string()) {
		return doProcessPacket(logic, packet, to_string(line) + (key.length() == 0?"":"_" + key));
	}

	/**
	 * Unsets if to process packet or not
	 * @param logic logic
	 * @param packet packet
	 * @param key key
	 */
	void unsetProcessPacket(NetworkLogic* logic, LogicNetworkPacket& packet, const string& key);

	/**
	 * Unset if to process packet or not
	 * @param logic logic
	 * @param packet packet
	 * @param line line
	 * @param key key
	 */
	inline void unsetProcessPacketAtLine(NetworkLogic* logic, LogicNetworkPacket& packet, uint32_t line, const string& key = string()) {
		unsetProcessPacket(logic, packet, to_string(line) + (key.length() == 0?"":"_" + key));
	}

	/**
	 * Update engine initialization, which is called once per frame before calling logic updateEngine() methods
	 */
	virtual void initUpdateEngine();

	/**
	 * Update engine done, which is called once per frame after calling logic updateEngine() methods
	 */
	virtual void doneUpdateEngine();

	/**
	 * Logics initialization, which is called once per logics updates
	 */
	virtual void initUpdateLogics();

	/**
	 * Logics finalizations, which is called once per logics updates
	 */
	virtual void doneUpdateLogics();

};
