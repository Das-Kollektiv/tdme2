#pragma once

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
	static constexpr int32_t SOUNDPOOL_SIZE { 10 };
	static constexpr bool VERBOSE { false };

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
		World* world { nullptr };
		PathFinding* pathFinding { nullptr };
		Mutex pathFindingMutex;
		Mutex pathFindingCancelMutex;
		vector<WorldActionStruct> worldActions;
		Mutex worldActionsMutex;

	public:
		/**
		 * Public constructor
		 * @param context context
		 * @param idx index
		 * @param rigidBodyTypeIdStaticMask rigid body type id static mask
		 * @param rigidBodyTypeIdCloneMask rigid body type id clone mask
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
		 * Run
		 */
		virtual void run();

		/**
		 * @return current pathfinding actor id
		 */
		string getActorId();

	};

	class WSPathFinding {
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
		 * @param threadCount thread count
		 * @param rigidBodyTypeIdStaticMask rigid body type id static mask
		 * @param rigidBodyTypeIdCloneMask rigid body type id clone mask
		 */
		WSPathFinding(Context* context, int threadCount = 0);

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

	class ContextWorldListener: public WorldListener {
		friend class Context;
	private:
		Context* context { nullptr };
	public:
		ContextWorldListener(Context* context);
		virtual void onAddedBody(const string& id, int32_t type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes) override;
		virtual void onRemovedBody(const string& id, int32_t type, uint16_t collisionTypeId) override;
	};

	struct PacketState {
		int64_t timeCreated;
		uint32_t messageId;
	};

	int64_t timeStarted;

	// path finding which is context bound too
	uint16_t rigidBodyTypeIdStaticMask { 1/*Body::TYPEID_STATIC*/ };
	uint16_t rigidBodyTypeIdCloneMask { 1/*Body::TYPEID_STATIC*/ };
	WSPathFinding pathFinding;

	// context main data
	volatile bool initialized;
	bool server;
	Mutex* gameLogicMutex { nullptr };
	Engine* engine { nullptr };
	Engine* guiEngine { nullptr };
	Audio* audio { nullptr };
	World* world { nullptr };
	ContextWorldListener* worldListener { nullptr };
	Scene* scene { nullptr };
	unordered_map<string, Logic*> gameLogicsById;
	vector<Logic*> gameLogics;
	vector<Logic*> gameLogicsNew;
	unordered_map<string, PacketState> packetStates;

public:
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
	 * @return game logic mutex
	 */
	inline Mutex* getGameLogicMutex() {
		return gameLogicMutex;
	}

	/**
	 * Set game logic mutex
	 */
	inline void setGameLogicMutex(Mutex* gameLogicMutex) {
		this->gameLogicMutex = gameLogicMutex;
	}

	/**
	 * @return server
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
	 * @return world
	 */
	inline World* getWorld() {
		return world;
	}

	/**
	 * Set world
	 * @param world world
	 */
	inline void setWorld(World* world) {
		this->world = world;
	}

	/**
	 * @return level
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
	 * Initialize game logics
	 */
	virtual void initialize();

	/**
	 * Shut down
	 */
	virtual void shutdown();

	/**
	 * Add game logic
	 * @param gameLogic game logic
	 */
	void addGameLogic(Logic* gameLogic);

	/**
	 * Get game logic
	 * @param id id
	 * @return game logic or nullptr
	 */
	inline Logic* getGameLogic(const string& id) {
		auto gameLogicIt = gameLogicsById.find(id);
		return gameLogicIt != gameLogicsById.end()?gameLogicIt->second:nullptr;
	}

	/**
	 * On game logics processed
	 */
	inline int addGameLogicsNew() {
		int gameLogicsNewCount = gameLogicsNew.size();
		// add new game logics
		for (auto gameLogic: gameLogicsNew) {
			// add game logic to lists
			gameLogicsById[gameLogic->getId()] = gameLogic;
			gameLogics.push_back(gameLogic);
		}
		gameLogicsNew.clear();
		return gameLogicsNewCount;
	}

	/**
	 * @return game logics
	 */
	inline const vector<Logic*>& getGameLogics() {
		return gameLogics;
	}

	/**
	 * @return game logics new
	 */
	inline const vector<Logic*>& getGameLogicsNew() {
		return gameLogicsNew;
	}

	/**
	 * @return rigid body type id static mask
	 */
	inline uint16_t getRigidBodyTypeIdStaticMask() {
		return rigidBodyTypeIdStaticMask;
	}

	/**
	 * Set rigid body type id static mask, which is used for path finding
	 * @param rigidBodyTypeIdStaticMask rigid body type id static mask
	 */
	inline void setRigidBodyTypeIdStaticMask(uint16_t rigidBodyTypeIdStaticMask) {
		this->rigidBodyTypeIdStaticMask = rigidBodyTypeIdStaticMask;
	}

	/**
	 * @return rigid body type id clone mask
	 */
	inline uint16_t getRigidBodyTypeIdCloneMask() {
		return rigidBodyTypeIdCloneMask;
	}

	/**
	 * Set rigid body type id clone mask, which is used for path finding
	 * @param rigidBodyTypeIdCloneMask rigid body type id clone mask
	 */
	inline void setRigidBodyTypeIdCloneMask(uint16_t rigidBodyTypeIdCloneMask) {
		this->rigidBodyTypeIdCloneMask = rigidBodyTypeIdCloneMask;
	}

	/**
	 * Get path finding thread
	 */
	inline WSPathFinding* getPathFinding() {
		return &pathFinding;
	}

	/**
	 * Returns if to process packet or not
	 * @param gameLogic game logic
	 * @param packet packet
	 * @param key key
	 * @return if to process packet
	 */
	bool doProcessPacket(NetworkLogic* gameLogic, LogicNetworkPacket& packet, const string& key);

	/**
	 * Returns if to process packet or not
	 * @param gameLogic game logic
	 * @param packet packet
	 * @param line line
	 * @param key key
	 * @return if to process packet
	 */
	inline bool doProcessPacketAtLine(NetworkLogic* gameLogic, LogicNetworkPacket& packet, uint32_t line, const string& key = string()) {
		return doProcessPacket(gameLogic, packet, to_string(line) + (key.length() == 0?"":"_" + key));
	}

	/**
	 * Unsets if to process packet or not
	 * @param gameLogic game logic
	 * @param packet packet
	 * @param key key
	 */
	void unsetProcessPacket(NetworkLogic* gameLogic, LogicNetworkPacket& packet, const string& key);

	/**
	 * Unset if to process packet or not
	 * @param gameLogic game logic
	 * @param packet packet
	 * @param line line
	 * @param key key
	 */
	inline void unsetProcessPacketAtLine(NetworkLogic* gameLogic, LogicNetworkPacket& packet, uint32_t line, const string& key = string()) {
		unsetProcessPacket(gameLogic, packet, to_string(line) + (key.length() == 0?"":"_" + key));
	}

	/**
	 * Update engine initialization, which is called once per frame before calling game logic updateEngine() methods
	 */
	virtual void initUpdateEngine();

	/**
	 * Update engine done, which is called once per frame after calling game logic updateEngine() methods
	 */
	virtual void doneUpdateEngine();

	/**
	 * Game logics initialization, which is called once per game logics updates
	 */
	virtual void initGameLogics();

	/**
	 * Game logics finalizations, which is called once per game logics updates
	 */
	virtual void doneGameLogics();

};
