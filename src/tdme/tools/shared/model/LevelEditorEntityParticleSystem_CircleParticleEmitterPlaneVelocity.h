
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
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity
{
private:
	int32_t count {  };
	int64_t lifeTime {  };
	int64_t lifeTimeRnd {  };
	float mass {  };
	float massRnd {  };
	float velocity {  };
	float velocityRnd {  };
	Color4 colorStart {  };
	Color4 colorEnd {  };
	Vector3 center {  };
	float radius {  };
	Vector3 axis0 {  };
	Vector3 axis1 {  };

public:

	/** 
	 * @return count
	 */
	int32_t getCount();

	/** 
	 * Set count
	 * @param count count
	 */
	void setCount(int32_t count);

	/** 
	 * @return life time
	 */
	int64_t getLifeTime();

	/** 
	 * Set life time
	 * @param lifeTime life time
	 */
	void setLifeTime(int64_t lifeTime);

	/** 
	 * @return life time rnd
	 */
	int64_t getLifeTimeRnd();

	/** 
	 * Set life time rnd
	 * @param lifeTimeRnd life time rnd
	 */
	void setLifeTimeRnd(int64_t lifeTimeRnd);

	/** 
	 * @return mass
	 */
	float getMass();

	/** 
	 * Set mass
	 * @param mass mass
	 */
	void setMass(float mass);

	/** 
	 * @return mass rnd
	 */
	float getMassRnd();

	/** 
	 * Set mass rnd
	 * @param massRnd mass rnd
	 */
	void setMassRnd(float massRnd);

	/** 
	 * @return velocity
	 */
	float getVelocity();

	/** 
	 * Set velocity
	 * @param velocity velocity
	 */
	void setVelocity(float velocity);

	/** 
	 * @return velocity rnd
	 */
	float getVelocityRnd();

	/** 
	 * Set velocity rnd
	 * @param velocityRnd velocity rnd
	 */
	void setVelocityRnd(float velocityRnd);

	/** 
	 * @return color start
	 */
	Color4& getColorStart();

	/** 
	 * @return color end
	 */
	Color4& getColorEnd();

	/** 
	 * @return center
	 */
	Vector3& getCenter();

	/** 
	 * @return radius
	 */
	float getRadius();

	/** 
	 * Set radius
	 * @param radius radius
	 */
	void setRadius(float radius);

	/** 
	 * @return axis 0
	 */
	Vector3& getAxis0();

	/** 
	 * @return axis 1
	 */
	Vector3& getAxis1();

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity();
};
