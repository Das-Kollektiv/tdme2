#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/leveleditor/logic/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Transformations;
using tdme::engine::physics::RigidBody;
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
	 * @param engine
	 * @param level
	 * @param translation
	 */
	static void setLight(Engine* engine, LevelEditorLevel* level, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/** 
	 * Create particle system
	 * @param level editor entity particle system
	 * @param id
	 * @param enable dynamic shadows
	 * @return engine particle system entity
	 */
	static Entity* createParticleSystem(LevelEditorEntityParticleSystem* particleSystem, const string& id, bool enableDynamicShadows = true);

	/**
	 * Create engine entity
	 * @param level editor entity
	 * @param id
	 * @param transformations
	 * @return entity
	 */
	static Entity* createEntity(LevelEditorEntity* levelEditorEntity, const string& id, const Transformations& transformations);

	/**
	 * Create engine entity
	 * @param level editor object
	 * @return entity
	 */
	static Entity* createEntity(LevelEditorObject* levelEditorObject, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/** 
	 * Add level to engine
	 * @param engine
	 * @param level
	 * @param add empties
	 * @param add trigger
	 * @param pickable
	 * @param translation
	 * @param enable
	 * @param translation
	 */
	static void addLevel(Engine* engine, LevelEditorLevel* level, bool addEmpties, bool addTrigger, bool pickable, bool enable = true, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/**
	 * Create rigid body
	 * @param world
	 * @param level editor entity
	 * @param id
	 * @param transformations
	 * @param collision type id or 0 for default
	 * @return rigid body
	 */
	static RigidBody* createRigidBody(World* world, LevelEditorEntity* levelEditorEntity, const string& id, const Transformations& transformations, uint16_t collisionTypeId = 0);

	/**
	 * Create rigid body
	 * @param world
	 * @param level editor object
	 * @param translation
	 * @param collision type id or 0 for default
	 * @return rigid body
	 */
	static RigidBody* createRigidBody(World* world, LevelEditorObject* levelEditorObject, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f), uint16_t collisionTypeId = 0);

	/** 
	 * Add level to physics world
	 * @param world
	 * @param level
	 * @param enable
	 * @param translation
	 */
	static void addLevel(World* world, LevelEditorLevel* level, bool enable = true, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/** 
	 * Disable level in engine
	 * @param engine
	 * @param level
	 */
	static void disableLevel(Engine* engine, LevelEditorLevel* level);

	/** 
	 * Disable level in physics world
	 * @param world
	 * @param level
	 */
	static void disableLevel(World* world, LevelEditorLevel* level);

	/** 
	 * Enable disabled level in engine
	 * @param engine
	 * @param level
	 * @param translation
	 */
	static void enableLevel(Engine* engine, LevelEditorLevel* level, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

	/** 
	 * Enable disabled level in physics world
	 * @param world
	 * @param level
	 * @param translation
	 */
	static void enableLevel(World* world, LevelEditorLevel* level, const Vector3& translation = Vector3(0.0f, 0.0f, 0.0f));

};
