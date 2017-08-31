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
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;

/** 
 * Bounding box particle emitter 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter
{
	friend class LevelEditorEntityParticleSystem;
	friend class LevelEditorEntityParticleSystem_Type;
	friend class LevelEditorEntityParticleSystem_ObjectParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleSystem;
	friend class LevelEditorEntityParticleSystem_Emitter;
	friend class LevelEditorEntityParticleSystem_PointParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;

private:
	int32_t count {  };
	int64_t lifeTime {  };
	int64_t lifeTimeRnd {  };
	float mass {  };
	float massRnd {  };
	Vector3* velocity {  };
	Vector3* velocityRnd {  };
	Color4* colorStart {  };
	Color4* colorEnd {  };
	Vector3* obbCenter {  };
	Vector3* obbHalfextension {  };
	Vector3* obbAxis0 {  };
	Vector3* obbAxis1 {  };
	Vector3* obbAxis2 {  };

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
	 * @return obb center
	 */
	virtual Vector3* getObbCenter();

	/** 
	 * @return obb half extension
	 */
	virtual Vector3* getObbHalfextension();

	/** 
	 * @return obb axis 0
	 */
	virtual Vector3* getObbAxis0();

	/** 
	 * @return obb axis 1
	 */
	virtual Vector3* getObbAxis1();

	/** 
	 * @return obb axis 2
	 */
	virtual Vector3* getObbAxis2();

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter();
};
