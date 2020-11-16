#pragma once

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/leveleditor/logic/fwd-tdme.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::audio::Audio;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Transformations;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::math::Vector3;
using tdme::tools::shared::files::ProgressCallback;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityPhysics_BodyType;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::utilities::MutableString;

/**
 * Level Editor Level Logic
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::logic::Level final
{

public:
	static constexpr int32_t RIGIDBODY_TYPEID_STATIC { 1 };
	static constexpr int32_t RIGIDBODY_TYPEID_DYNAMIC { 2 };
	static constexpr int32_t RIGIDBODY_TYPEID_COLLISION { 4 };
	static constexpr int32_t RIGIDBODY_TYPEID_TRIGGER { 8 };

	static float renderNodesPartitionWidth;
	static float renderNodesPartitionHeight;
	static float renderNodesPartitionDepth;
	static int renderNodesReduceBy;
	static int renderNodesLODLevels;
	static float renderNodesLOD2MinDistance;
	static float renderNodesLOD3MinDistance;
	static int renderNodesLOD2ReduceBy;
	static int renderNodesLOD3ReduceBy;
	static bool enableEarlyZRejection;

public:

	/**
	 * @return render nodes partition size / width
	 */
	inline static float getRenderNodesPartitionWidth() {
		return renderNodesPartitionWidth;
	}

	/**
	 * Set render nodes partition size / width
	 * @param renderNodesPartitionDepth render nodes partition size / width
	 */
	inline static void setRenderNodesPartitionWidth(float renderNodesPartitionWidth) {
		Level::renderNodesPartitionWidth = renderNodesPartitionWidth;
	}

	/**
	 * @return render nodes partition size / height
	 */
	inline static float getRenderNodesPartitionHeight() {
		return renderNodesPartitionHeight;
	}

	/**
	 * Set render nodes partition size / height
	 * @param renderNodesPartitionDepth render nodes partition size / height
	 */
	inline static void setRenderNodesPartitionHeight(float renderNodesPartitionHeight) {
		Level::renderNodesPartitionHeight = renderNodesPartitionHeight;
	}

	/**
	 * @return render nodes partition size / depth
	 */
	inline static float getRenderNodesPartitionDepth() {
		return renderNodesPartitionDepth;
	}

	/**
	 * Set render nodes partition size / depth
	 * @param renderNodesPartitionDepth render nodes partition size / depth
	 */
	inline static void setRenderNodesPartitionDepth(float renderNodesPartitionDepth) {
		Level::renderNodesPartitionDepth = renderNodesPartitionDepth;
	}

	/**
 	 * Set render nodes reduce objects by a given factor
 	 * @param reduceBy render nodes objects reduce by factor
 	 */
	inline static void setRenderNodesReduceBy(int32_t reduceBy) {
		Level::renderNodesReduceBy = reduceBy;
	}

	/**
	 * @return render nodes objects reduce by factor
	 */
	inline static int getRenderNodesReduceBy() {
		return renderNodesReduceBy;
	}

	/**
	 * @return render nodes LOD levels
	 */
	inline static int getRenderNodesLodLevels() {
		return renderNodesLODLevels;
	}

	/**
	 * Set render nodes LOD levels
	 * @param renderNodesLodLevels render nodes LOD levels
	 */
	inline static void setRenderNodesLodLevels(int lodLevels) {
		renderNodesLODLevels = lodLevels;
	}

	/**
	 * @return render nodes LOD2 minumum distance
	 */
	inline static float getRenderNodesLod2MinDistance() {
		return renderNodesLOD2MinDistance;
	}

	/**
	 * Set render nodes LOD2 minumum distance
	 * @param renderNodesLod2MinDistance render nodes LOD2 minumum distance
	 */
	inline static void setRenderNodesLod2MinDistance(float minDistance) {
		renderNodesLOD2MinDistance = minDistance;
	}

	/**
	 * @return render nodes LOD3 minumum distance
	 */
	inline static float getRenderNodesLod3MinDistance() {
		return renderNodesLOD3MinDistance;
	}

	/**
	 * Set render nodes LOD3 minumum distance
	 * @param renderNodesLod3MinDistance render nodes LOD3 minumum distance
	 */
	inline static void setRenderNodesLod3MinDistance(float minDistance) {
		renderNodesLOD3MinDistance = minDistance;
	}

	/**
	 * @return render nodes LOD2 reduce by factor
	 */
	inline static int getRenderNodesLod2ReduceBy() {
		return renderNodesLOD2ReduceBy;
	}

	/**
	 * Set render nodes LOD2 reduce by factor
	 * @param renderNodesLod2ReduceBy render nodes LOD2 reduce by factor
	 */
	inline static void setRenderNodesLod2ReduceBy(int reduceBy) {
		renderNodesLOD2ReduceBy = reduceBy;
	}

	/**
	 * @return render nodes LOD3 reduce by factor
	 */
	inline static int getRenderNodesLod3ReduceBy() {
		return renderNodesLOD3ReduceBy;
	}

	/**
	 * Set render nodes LOD3 reduce by factor
	 * @param renderNodesLod3ReduceBy render nodes LOD3 reduce by factor
	 */
	inline static void setRenderNodesLod3ReduceBy(int reduceBy) {
		renderNodesLOD3ReduceBy = reduceBy;
	}

	/**
	 * @return If early z rejection is enabled, in level loading case its used for render nodes and terrain
	 */
	inline static bool isEnableEarlyZRejection() {
		return enableEarlyZRejection;
	}

	/**
	 * Enable/disable early z rejection, in level loading case its used for render nodes and terrain
	 * @param enableEarlyZRejection enable early z rejection
	 */
	inline static void setEnableEarlyZRejection(bool enableEarlyZRejection) {
		Level::enableEarlyZRejection = enableEarlyZRejection;
	}

	/**
	 * Set lights from level
	 * @param engine engine
	 * @param level level
	 * @param translation translation
	 */
	static void setLight(Engine* engine, LevelEditorLevel* level, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Create particle system
	 * @param particleSystem level editor entity particle system
	 * @param id id
	 * @param enableDynamicShadows enable dynamic shadows
	 * @return engine particle system entity
	 */
	static Entity* createParticleSystem(LevelEditorEntityParticleSystem* particleSystem, const string& id, bool enableDynamicShadows = true);

	/**
	 * Create engine entity
	 * @param id id
	 * @param transformations transformations
	 * @return entity
	 */
	static Entity* createEmpty(const string& id, const Transformations& transformations);

	/**
	 * Create engine entity
	 * @param levelEditorEntity level editor entity
	 * @param id id
	 * @param transformations transformations
	 * @param instances instances which applies only for skinned objects
	 * @return entity
	 */
	static Entity* createEntity(LevelEditorEntity* levelEditorEntity, const string& id, const Transformations& transformations, int instances = 1);

	/**
	 * Create engine entity
	 * @param levelEditorObject level editor object
	 * @param translation translation
	 * @return entity
	 */
	static Entity* createEntity(LevelEditorObject* levelEditorObject, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Add level to engine
	 * @param engine engine
	 * @param level level
	 * @param addEmpties add empties
	 * @param addTrigger add trigger
	 * @param pickable pickable
	 * @param enable enable
	 * @param translation translation
	 * @param progressCallback progress callback
	 */
	static void addLevel(Engine* engine, LevelEditorLevel* level, bool addEmpties, bool addTrigger, bool pickable, bool enable = true, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), ProgressCallback* progressCallback = nullptr);

	/**
	 * Create rigid body
	 * @param world world
	 * @param levelEditorEntity level editor entity
	 * @param id id
	 * @param transformations transformations
	 * @param collisionTypeId collision type id or 0 for default
	 * @param index use a optional index or all bounding volumes
	 * @param overrideType override physics type if required
	 * @return rigid body
	 */
	static Body* createBody(World* world, LevelEditorEntity* levelEditorEntity, const string& id, const Transformations& transformations, uint16_t collisionTypeId = 0, int index = -1, LevelEditorEntityPhysics_BodyType* overrideType = nullptr);

	/**
	 * Create rigid body
	 * @param world world
	 * @param levelEditorObject level editor object
	 * @param translation translation
	 * @param collisionTypeId collision type id or 0 for default
	 * @param index use a optional index or all bounding volumes
	 * @param overrideType override physics type if required
	 * @return rigid body
	 */
	static Body* createBody(World* world, LevelEditorObject* levelEditorObject, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), uint16_t collisionTypeId = 0, int index = -1, LevelEditorEntityPhysics_BodyType* overrideType = nullptr);

	/**
	 * Add level to physics world
	 * @param world world
	 * @param level level
	 * @param enable enable
	 * @param translation translation
	 * @param progressCallback progress callback
	 */
	static void addLevel(World* world, LevelEditorLevel* level, bool enable = true, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), ProgressCallback* progressCallback = nullptr);

	/**
	 * Disable level in engine
	 * @param engine engine
	 * @param level level
	 */
	static void disableLevel(Engine* engine, LevelEditorLevel* level);

	/**
	 * Disable level in physics world
	 * @param world world
	 * @param level level
	 */
	static void disableLevel(World* world, LevelEditorLevel* level);

	/**
	 * Enable disabled level in engine
	 * @param engine engine
	 * @param level level
	 * @param translation translation
	 */
	static void enableLevel(Engine* engine, LevelEditorLevel* level, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Enable disabled level in physics world
	 * @param world world
	 * @param level level
	 * @param translation translation
	 */
	static void enableLevel(World* world, LevelEditorLevel* level, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Add level editor entity sounds into given audio instance associated with given id
	 * @param audio audio instance to load sounds into
	 * @param levelEditorEntity level editor entity
	 * @param id audio entity id
	 * @param poolSize pool size, which is optional if you want to use a pool for each sound
	 */
	static void addEntitySounds(Audio* audio, LevelEditorEntity* levelEditorEntity, const string& id, const int poolSize = 1);

private:
	static Model* emptyModel;
};
