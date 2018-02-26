
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
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::LevelEditorLevel;
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
	static constexpr int32_t RIGIDBODY_TYPEID_PLAYER { 2 };

public:

	/** 
	 * Set lights from level
	 * @param engine
	 * @param level
	 * @param translation
	 */
	static void setLight(Engine* engine, LevelEditorLevel* level, const Vector3& translation);

	/** 
	 * Create particle system
	 * @param level editor entity particle system
	 * @param id
	 * @param enable dynamic shadows
	 * @return engine particle system entity
	 */
	static Entity* createParticleSystem(LevelEditorEntityParticleSystem* particleSystem, const string& id, bool enableDynamicShadows);

	/** 
	 * Add level to engine
	 * @param engine
	 * @param level
	 * @param add empties
	 * @param add trigger
	 * @param pickable
	 * @param translation
	 */
	static void addLevel(Engine* engine, LevelEditorLevel* level, bool addEmpties, bool addTrigger, bool pickable, const Vector3& translation);

	/** 
	 * Add level to engine
	 * @param engine
	 * @param level
	 * @param add empties
	 * @param add trigger
	 * @param pickable
	 * @param translation
	 * @param enable
	 */
	static void addLevel(Engine* engine, LevelEditorLevel* level, bool addEmpties, bool addTrigger, bool pickable, const Vector3& translation, bool enable);

	/** 
	 * Add level to physics world
	 * @param world
	 * @param level
	 * @param rigid bodies (will be filled by logic)
	 * @param translation
	 */
	static void addLevel(World* world, LevelEditorLevel* level, vector<RigidBody*>& rigidBodies, const Vector3& translation);

	/** 
	 * Add level to physics world
	 * @param world
	 * @param level
	 * @param rigid bodies (will be filled by logic)
	 * @param translation
	 */
	static void addLevel(World* world, LevelEditorLevel* level, vector<RigidBody*>&, const Vector3& translation, bool enable);

	/** 
	 * Disable level in engine
	 * @param engine
	 * @param level
	 */
	static void disableLevel(Engine* engine, LevelEditorLevel* level);

	/** 
	 * Disable level in physics world
	 * @param world
	 * @param rigid bodies
	 */
	static void disableLevel(World* world, vector<RigidBody*>& rigidBodies);

	/** 
	 * Enable disabled level in engine
	 * @param engine
	 * @param level
	 * @param translation
	 */
	static void enableLevel(Engine* engine, LevelEditorLevel* level, const Vector3& translation);

	/** 
	 * Enable disabled level in physics world
	 * @param world
	 * @param level
	 * @param rigid bodies
	 * @param translation
	 */
	static void enableLevel(World* world, LevelEditorLevel* level, vector<RigidBody*>& rigidBodies, const Vector3& translation);

	/**
	 * Public constructor
	 */
	Level();
};
