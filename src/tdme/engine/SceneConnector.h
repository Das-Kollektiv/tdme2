#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fileio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::audio::Audio;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::BodyHierarchy;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::engine::prototype::PrototypePhysics_BodyType;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Transform;
using tdme::math::Vector3;
using tdme::utilities::MutableString;

/**
 * Scene engine/physics connector
 * @author Andreas Drewke
 */
class tdme::engine::SceneConnector final
{

public:
	static constexpr uint16_t BODY_TYPEID_STATIC { 1 };
	static constexpr uint16_t BODY_TYPEID_DYNAMIC { 2 };
	static constexpr uint16_t BODY_TYPEID_COLLISION { 4 };
	static constexpr uint16_t BODY_TYPEID_TRIGGER { 8 };

	static constexpr int BODY_TYPEID_STANDARD { 0 };
	static constexpr int BOUNDINGVOLUME_INDEX_NONE { -1 };

	STATIC_DLL_IMPEXT static float renderGroupsPartitionWidth;
	STATIC_DLL_IMPEXT static float renderGroupsPartitionHeight;
	STATIC_DLL_IMPEXT static float renderGroupsPartitionDepth;
	STATIC_DLL_IMPEXT static int renderGroupsReduceBy;
	STATIC_DLL_IMPEXT static int renderGroupsLODLevels;
	STATIC_DLL_IMPEXT static float renderGroupsLOD2MinDistance;
	STATIC_DLL_IMPEXT static float renderGroupsLOD3MinDistance;
	STATIC_DLL_IMPEXT static int renderGroupsLOD2ReduceBy;
	STATIC_DLL_IMPEXT static int renderGroupsLOD3ReduceBy;

	/**
	 * @return render groups partition size / width
	 */
	inline static float getRenderGroupsPartitionWidth() {
		return renderGroupsPartitionWidth;
	}

	/**
	 * Set render groups partition size / width
	 * @param renderNodesPartitionDepth render groups partition size / width
	 */
	inline static void setRenderGroupsPartitionWidth(float renderNodesPartitionWidth) {
		SceneConnector::renderGroupsPartitionWidth = renderNodesPartitionWidth;
	}

	/**
	 * @return render groups partition size / height
	 */
	inline static float getRenderGroupsPartitionHeight() {
		return renderGroupsPartitionHeight;
	}

	/**
	 * Set render groups partition size / height
	 * @param renderNodesPartitionDepth render groups partition size / height
	 */
	inline static void setRenderGroupsPartitionHeight(float renderNodesPartitionHeight) {
		SceneConnector::renderGroupsPartitionHeight = renderNodesPartitionHeight;
	}

	/**
	 * @return render groups partition size / depth
	 */
	inline static float getRenderGroupsPartitionDepth() {
		return renderGroupsPartitionDepth;
	}

	/**
	 * Set render groups partition size / depth
	 * @param renderNodesPartitionDepth render groups partition size / depth
	 */
	inline static void setRenderGroupsPartitionDepth(float renderNodesPartitionDepth) {
		SceneConnector::renderGroupsPartitionDepth = renderNodesPartitionDepth;
	}

	/**
 	 * Set render groups reduce objects by a given factor
 	 * @param reduceBy render groups objects reduce by factor
 	 */
	inline static void setRenderGroupsReduceBy(int reduceBy) {
		SceneConnector::renderGroupsReduceBy = reduceBy;
	}

	/**
	 * @return render groups objects reduce by factor
	 */
	inline static int getRenderGroupsReduceBy() {
		return renderGroupsReduceBy;
	}

	/**
	 * @return render groups LOD levels
	 */
	inline static int getRenderGroupsLodLevels() {
		return renderGroupsLODLevels;
	}

	/**
	 * Set render groups LOD levels
	 * @param lodLevels render groups LOD levels
	 */
	inline static void setRenderGroupsLodLevels(int lodLevels) {
		renderGroupsLODLevels = lodLevels;
	}

	/**
	 * @return render groups LOD2 minumum distance
	 */
	inline static float getRenderGroupsLod2MinDistance() {
		return renderGroupsLOD2MinDistance;
	}

	/**
	 * Set render groups LOD2 minumum distance
	 * @param minDistance render groups LOD2 minumum distance
	 */
	inline static void setRenderGroupsLod2MinDistance(float minDistance) {
		renderGroupsLOD2MinDistance = minDistance;
	}

	/**
	 * @return render groups LOD3 minumum distance
	 */
	inline static float getRenderGroupsLod3MinDistance() {
		return renderGroupsLOD3MinDistance;
	}

	/**
	 * Set render groups LOD3 minumum distance
	 * @param minDistance render groups LOD3 minumum distance
	 */
	inline static void setRenderGroupsLod3MinDistance(float minDistance) {
		renderGroupsLOD3MinDistance = minDistance;
	}

	/**
	 * @return render groups LOD2 reduce by factor
	 */
	inline static int getRenderGroupsLod2ReduceBy() {
		return renderGroupsLOD2ReduceBy;
	}

	/**
	 * Set render groups LOD2 reduce by factor
	 * @param reduceBy render groups LOD2 reduce by factor
	 */
	inline static void setRenderGroupsLod2ReduceBy(int reduceBy) {
		renderGroupsLOD2ReduceBy = reduceBy;
	}

	/**
	 * @return render groups LOD3 reduce by factor
	 */
	inline static int getRenderGroupsLod3ReduceBy() {
		return renderGroupsLOD3ReduceBy;
	}

	/**
	 * Set render groups LOD3 reduce by factor
	 * @param reduceBy render groups LOD3 reduce by factor
	 */
	inline static void setRenderGroupsLod3ReduceBy(int reduceBy) {
		renderGroupsLOD3ReduceBy = reduceBy;
	}

	/**
	 * Set lights from scene
	 * @param engine engine
	 * @param scene scene
	 * @param translation translation
	 */
	static void setLights(Engine* engine, Scene* scene, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Create particle system
	 * @param particleSystem prototype particle system
	 * @param id id
	 * @param enableDynamicShadows enable dynamic shadows
	 * @return engine particle system entity
	 */
	static Entity* createParticleSystem(PrototypeParticleSystem* particleSystem, const string& id, bool enableDynamicShadows = true);

	/**
	 * Create engine entity
	 * @param id id
	 * @param transform transform
	 * @return entity
	 */
	static Entity* createEmpty(const string& id, const Transform& transform);

	/**
	 * Create editor decal engine entity
	 * @param prototype prototype
	 * @param id id
	 * @param transform transform
	 * @param instances instances which applies only for skinned objects
	 * @return entity
	 */
	static Entity* createEditorDecalEntity(Prototype* prototype, const string& id, const Transform& transform, int instances = 1);

	/**
	 * Create engine entity
	 * @param prototype prototype
	 * @param id id
	 * @param transform transform
	 * @param instances instances which applies only for skinned objects
	 * @param noEntityHierarchy do not create a entity hierarchy
	 * @return entity
	 */
	static Entity* createEntity(Prototype* prototype, const string& id, const Transform& transform, int instances = 1, bool noEntityHierarchy = false);

	/**
	 * Create editor decal engine entity
	 * @param sceneEntity scene object
	 * @param translation translation
	 * @param instances instances which applies only for skinned objects
	 * @return entity
	 */
	static Entity* createEditorDecalEntity(SceneEntity* sceneEntity, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), int instances = 1);

	/**
	 * Create engine entity
	 * @param sceneEntity scene object
	 * @param translation translation
	 * @param instances instances which applies only for skinned objects
	 * @param noEntityHierarchy do not create a entity hierarchy
	 * @return entity
	 */
	static Entity* createEntity(SceneEntity* sceneEntity, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), int instances = 1, bool noEntityHierarchy = false);

	/**
	 * Add scene to engine
	 * @param engine engine
	 * @param scene scene
	 * @param addEmpties add empties
	 * @param addTrigger add trigger
	 * @param addEnvironmentMapping add environment mapping
	 * @param useEditorDecals use editor decals
	 * @param pickable pickable
	 * @param enable enable
	 * @param translation translation
	 * @param progressCallback progress callback
	 */
	static void addScene(Engine* engine, Scene* scene, bool addEmpties, bool addTrigger, bool addEnvironmentMapping, bool useEditorDecals, bool pickable, bool enable = true, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), ProgressCallback* progressCallback = nullptr);

	/**
	 * Create body
	 * @param world world
	 * @param prototype prototype
	 * @param id id
	 * @param transform transform
	 * @param collisionTypeId collision type id or 0 for default
	 * @param hierarchy hierarchy
	 * @param index use a optional index or all bounding volumes
	 * @param overrideType override physics type if required
	 * @return body
	 */
	static Body* createBody(World* world, Prototype* prototype, const string& id, const Transform& transform, uint16_t collisionTypeId = BODY_TYPEID_STANDARD, bool hierarchy = false, int index = BOUNDINGVOLUME_INDEX_NONE, PrototypePhysics_BodyType* overrideType = nullptr);

	/**
	 * Create body
	 * @param world world
	 * @param sceneEntity scene entity
	 * @param translation translation
	 * @param collisionTypeId collision type id or 0 for default
	 * @param hierarchy hierarchy
	 * @param index use a optional index or all bounding volumes
	 * @param overrideType override physics type if required
	 * @return body
	 */
	static Body* createBody(World* world, SceneEntity* sceneEntity, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), uint16_t collisionTypeId = BODY_TYPEID_STANDARD, bool hierarchy = false, int index = BOUNDINGVOLUME_INDEX_NONE, PrototypePhysics_BodyType* overrideType = nullptr);

	/**
	 * Create sub body in body hierarchy
	 * @param world world
	 * @param prototype prototype
	 * @param id id
	 * @param transform transform
	 * @param bodyHierarchyId body hierarchy id
	 * @param bodyHierarchyParentId body hierarchy parent id
	 * @return body hierarchy
	 */
	static BodyHierarchy* createSubBody(World* world, Prototype* prototype, const string& id, const Transform& transform, const string& bodyHierarchyId, const string& bodyHierarchyParentId);

	/**
	 * Add scene to physics world
	 * @param world world
	 * @param scene scene
	 * @param enable enable
	 * @param translation translation
	 * @param progressCallback progress callback
	 */
	static void addScene(World* world, Scene* scene, bool enable = true, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), ProgressCallback* progressCallback = nullptr);

	/**
	 * Disable scene in engine
	 * @param engine engine
	 * @param scene scene
	 */
	static void disableScene(Engine* engine, Scene* scene);

	/**
	 * Disable scene in physics world
	 * @param world world
	 * @param scene scene
	 */
	static void disableScene(World* world, Scene* scene);

	/**
	 * Enable disabled scene in engine
	 * @param engine engine
	 * @param scene scene
	 * @param translation translation
	 */
	static void enableScene(Engine* engine, Scene* scene, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Enable disabled scene in physics world
	 * @param world world
	 * @param scene scene
	 * @param translation translation
	 */
	static void enableScene(World* world, Scene* scene, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Reset engine regarding given scene
	 * @param engine engine
	 * @param scene scene
	 */
	static void resetEngine(Engine* engine, Scene* scene);

	/**
	 * Add scene entity sounds into given audio instance associated with given id
	 * @param audio audio instance to load sounds into
	 * @param prototype scene entity
	 * @param id audio entity id
	 * @param poolSize pool size, which is optional if you want to use a pool for each sound
	 */
	static void addSounds(Audio* audio, Prototype* prototype, const string& id, int poolSize = 1);

private:
	STATIC_DLL_IMPEXT static Model* emptyModel;
};
