
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/model/LevelEditorEntityPhysics_BodyType.h>

using std::string;

using tdme::tools::shared::model::LevelEditorEntity;

/** 
 * Level editor entity physics body settings
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityPhysics
{
private:
	LevelEditorEntityPhysics_BodyType* type { LevelEditorEntityPhysics_BodyType::STATIC_RIGIDBODY };
	float mass { 0.0f };
	float restitution { 0.5f };
	float friction { 0.5f };

public:

	/**
	 * Public constructor
	 */
	inline LevelEditorEntityPhysics() {
	}

	/**
	 * Destructor
	 */
	~LevelEditorEntityPhysics();

	/**
	 * @return type
	 */
	inline LevelEditorEntityPhysics_BodyType* getType() const {
		return type;
	}

	/**
	 * Set type
	 * @param type
	 */
	inline void setType(LevelEditorEntityPhysics_BodyType* type) {
		this->type = type;
	}

	/**
	 * @return friction
	 */
	inline float getFriction() const {
		return friction;
	}

	/**
	 * Set friction
	 * @param friction
	 */
	inline void setFriction(float friction) {
		this->friction = friction;
	}

	/**
	 * @return mass
	 */
	inline float getMass() const {
		return mass;
	}

	/**
	 * Set mass in kg
	 * @param mass
	 */
	inline void setMass(float mass) {
		this->mass = mass;
	}

	/**
	 * @return restitution / bounciness
	 */
	inline float getRestitution() const {
		return restitution;
	}

	/**
	 * Set restitution
	 * @param restitution
	 */
	inline void setRestitution(float restitution) {
		this->restitution = restitution;
	}

};
