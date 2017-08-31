// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using java::lang::String;
using tdme::engine::model::Color4;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;

/** 
 * Point particle emitter
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter
{
	friend class LevelEditorEntityParticleSystem;
	friend class LevelEditorEntityParticleSystem_Type;
	friend class LevelEditorEntityParticleSystem_ObjectParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleSystem;
	friend class LevelEditorEntityParticleSystem_Emitter;
	friend class LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;

private:
	int32_t count {  };
	int64_t lifeTime {  };
	int64_t lifeTimeRnd {  };
	float mass {  };
	float massRnd {  };
	Vector3* position {  };
	Vector3* velocity {  };
	Vector3* velocityRnd {  };
	Color4* colorStart {  };
	Color4* colorEnd {  };

public:

	/** 
	 * @return count
	 */
	virtual int32_t getCount();

	/** 
	 * Set count
	 * @param count
	 */
	virtual void setCount(int32_t count);

	/** 
	 * @return life time
	 */
	virtual int64_t getLifeTime();

	/** 
	 * Set life time
	 * @param life time
	 */
	virtual void setLifeTime(int64_t lifeTime);

	/** 
	 * @return life time rnd
	 */
	virtual int64_t getLifeTimeRnd();

	/** 
	 * Set life time rnd
	 * @param life time rnd
	 */
	virtual void setLifeTimeRnd(int64_t lifeTimeRnd);

	/** 
	 * @return mass
	 */
	virtual float getMass();

	/** 
	 * Set mass
	 * @param mass
	 */
	virtual void setMass(float mass);

	/** 
	 * @return mass rnd
	 */
	virtual float getMassRnd();

	/** 
	 * Set mass rnd
	 * @param mass rnd
	 */
	virtual void setMassRnd(float massRnd);

	/** 
	 * @return position
	 */
	virtual Vector3* getPosition();

	/** 
	 * @return velocity
	 */
	virtual Vector3* getVelocity();

	/** 
	 * @return velocity rnd
	 */
	virtual Vector3* getVelocityRnd();

	/** 
	 * @return color start
	 */
	virtual Color4* getColorStart();

	/** 
	 * @return color end
	 */
	virtual Color4* getColorEnd();

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_PointParticleEmitter();
};
