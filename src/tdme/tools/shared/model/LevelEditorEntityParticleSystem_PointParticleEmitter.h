
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
 * Point particle emitter
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter
{
private:
	int32_t count {  };
	int64_t lifeTime {  };
	int64_t lifeTimeRnd {  };
	float mass {  };
	float massRnd {  };
	Vector3 position {  };
	Vector3 velocity {  };
	Vector3 velocityRnd {  };
	Color4 colorStart {  };
	Color4 colorEnd {  };

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
	 * @return position
	 */
	Vector3& getPosition();

	/** 
	 * @return velocity
	 */
	Vector3& getVelocity();

	/** 
	 * @return velocity rnd
	 */
	Vector3& getVelocityRnd();

	/** 
	 * @return color start
	 */
	Color4& getColorStart();

	/** 
	 * @return color end
	 */
	Color4& getColorEnd();

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_PointParticleEmitter();
};
