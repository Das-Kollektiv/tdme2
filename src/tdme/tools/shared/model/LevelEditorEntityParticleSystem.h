// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;


struct default_init_tag;

/** 
 * Level editor entity particle system
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityParticleSystem
	: public virtual Object
{

public:
	typedef Object super;

private:
	LevelEditorEntityParticleSystem_Type* type {  };
	LevelEditorEntityParticleSystem_ObjectParticleSystem* ops {  };
	LevelEditorEntityParticleSystem_PointParticleSystem* pps {  };
	LevelEditorEntityParticleSystem_Emitter* emitter {  };
	LevelEditorEntityParticleSystem_PointParticleEmitter* ppe {  };
	LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter* bbpe {  };
	LevelEditorEntityParticleSystem_CircleParticleEmitter* cpe {  };
	LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity* cpepv {  };
	LevelEditorEntityParticleSystem_SphereParticleEmitter* spe {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * @return particle system type
	 */
	virtual LevelEditorEntityParticleSystem_Type* getType();

	/** 
	 * Set particle system type
	 * @param type
	 */
	virtual void setType(LevelEditorEntityParticleSystem_Type* type);

	/** 
	 * @return object particle system
	 */
	virtual LevelEditorEntityParticleSystem_ObjectParticleSystem* getObjectParticleSystem();

	/** 
	 * @return point particle system
	 */
	virtual LevelEditorEntityParticleSystem_PointParticleSystem* getPointParticleSystem();

	/** 
	 * @return particle system emitter
	 */
	virtual LevelEditorEntityParticleSystem_Emitter* getEmitter();

	/** 
	 * Set emitter
	 * @param emitter
	 */
	virtual void setEmitter(LevelEditorEntityParticleSystem_Emitter* emitter);

	/** 
	 * @return point particle emitter
	 */
	virtual LevelEditorEntityParticleSystem_PointParticleEmitter* getPointParticleEmitter();

	/** 
	 * @return bounding box particle emitter
	 */
	virtual LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter* getBoundingBoxParticleEmitters();

	/** 
	 * @return circle particle emitter
	 */
	virtual LevelEditorEntityParticleSystem_CircleParticleEmitter* getCircleParticleEmitter();

	/** 
	 * @return circle particle emitter plane velocity
	 */
	virtual LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity* getCircleParticleEmitterPlaneVelocity();

	/** 
	 * @return sphere particle emitter
	 */
	virtual LevelEditorEntityParticleSystem_SphereParticleEmitter* getSphereParticleEmitter();
	String* toString() override;

	// Generated
	LevelEditorEntityParticleSystem();
protected:
	LevelEditorEntityParticleSystem(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorEntityParticleSystem_Type;
	friend class LevelEditorEntityParticleSystem_ObjectParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleSystem;
	friend class LevelEditorEntityParticleSystem_Emitter;
	friend class LevelEditorEntityParticleSystem_PointParticleEmitter;
	friend class LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;
};
