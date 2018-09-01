#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/leveleditor/logic/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Transformations;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::utils::MutableString;

/** 
 * Level Editor Level Logic
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::logic::Level
{

public:
	static constexpr int32_t RIGIDBODY_TYPEID_STATIC { 1 };
	static constexpr int32_t RIGIDBODY_TYPEID_DYNAMIC { 2 };
	static constexpr int32_t RIGIDBODY_TYPEID_COLLISION { 4 };
	static constexpr int32_t RIGIDBODY_TYPEID_TRIGGER { 8 };

public:

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
	 * @return entity
	 */
	static Entity* createEntity(LevelEditorEntity* levelEditorEntity, const string& id, const Transformations& transformations);

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
	 */
	static void addLevel(Engine* engine, LevelEditorLevel* level, bool addEmpties, bool addTrigger, bool pickable, bool enable = true, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Create rigid body
	 * @param world world
	 * @param levelEditorEntity level editor entity
	 * @param id id
	 * @param transformations transformations
	 * @param collisionTypeId collision type id or 0 for default
	 * @return rigid body
	 */
	static Body* createBody(World* world, LevelEditorEntity* levelEditorEntity, const string& id, const Transformations& transformations, uint16_t collisionTypeId = 0);

	/**
	 * Create rigid body
	 * @param world world
	 * @param levelEditorObject level editor object
	 * @param translation translation
	 * @param collisionTypeId collision type id or 0 for default
	 * @return rigid body
	 */
	static Body* createBody(World* world, LevelEditorObject* levelEditorObject, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), uint16_t collisionTypeId = 0);

	/** 
	 * Add level to physics world
	 * @param world world
	 * @param level level
	 * @param enable enable
	 * @param translation translation
	 */
	static void addLevel(World* world, LevelEditorLevel* level, bool enable = true, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

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

private:
	static Model* emptyModel;
};
