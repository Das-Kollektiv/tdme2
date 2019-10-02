#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using tdme::engine::model::Color4;
using tdme::math::Vector3;

/** 
 * Circle particle emitter plane velocity
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity final
{
private:
	int32_t count;
	int64_t lifeTime;
	int64_t lifeTimeRnd;
	float mass;
	float massRnd;
	float velocity;
	float velocityRnd;
	Color4 colorStart;
	Color4 colorEnd;
	Vector3 center;
	float radius;
	Vector3 axis0;
	Vector3 axis1;

public:

	/** 
	 * @return count
	 */
	inline int32_t getCount() {
		return count;
	}

	/** 
	 * Set count
	 * @param count count
	 */
	inline void setCount(int32_t count) {
		this->count = count;
	}

	/** 
	 * @return life time
	 */
	inline int64_t getLifeTime() {
		return lifeTime;
	}

	/** 
	 * Set life time
	 * @param lifeTime life time
	 */
	inline void setLifeTime(int64_t lifeTime) {
		this->lifeTime = lifeTime;
	}

	/** 
	 * @return life time rnd
	 */
	inline int64_t getLifeTimeRnd() {
		return lifeTimeRnd;
	}

	/** 
	 * Set life time rnd
	 * @param lifeTimeRnd life time rnd
	 */
	inline void setLifeTimeRnd(int64_t lifeTimeRnd) {
		this->lifeTimeRnd = lifeTimeRnd;
	}

	/** 
	 * @return mass
	 */
	inline float getMass() {
		return mass;
	}

	/** 
	 * Set mass
	 * @param mass mass
	 */
	inline void setMass(float mass) {
		this->mass = mass;
	}

	/** 
	 * @return mass rnd
	 */
	inline float getMassRnd() {
		return massRnd;
	}

	/** 
	 * Set mass rnd
	 * @param massRnd mass rnd
	 */
	inline void setMassRnd(float massRnd) {
		this->massRnd = massRnd;
	}

	/** 
	 * @return velocity
	 */
	inline float getVelocity() {
		return velocity;
	}

	/** 
	 * Set velocity
	 * @param velocity velocity
	 */
	inline void setVelocity(float velocity) {
		this->velocity = velocity;
	}

	/** 
	 * @return velocity rnd
	 */
	inline float getVelocityRnd() {
		return velocityRnd;
	}

	/** 
	 * Set velocity rnd
	 * @param velocityRnd velocity rnd
	 */
	inline void setVelocityRnd(float velocityRnd) {
		this->velocityRnd = velocityRnd;
	}

	/** 
	 * @return color start
	 */
	inline Color4& getColorStart() {
		return colorStart;
	}

	/** 
	 * @return color end
	 */
	inline Color4& getColorEnd() {
		return colorEnd;
	}

	/** 
	 * @return center
	 */
	inline Vector3& getCenter() {
		return center;
	}

	/** 
	 * @return radius
	 */
	inline float getRadius() {
		return radius;
	}

	/** 
	 * Set radius
	 * @param radius radius
	 */
	inline void setRadius(float radius) {
		this->radius = radius;
	}

	/** 
	 * @return axis 0
	 */
	inline Vector3& getAxis0() {
		return axis0;
	}

	/** 
	 * @return axis 1
	 */
	inline Vector3& getAxis1() {
		return axis1;
	}

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity();
};
