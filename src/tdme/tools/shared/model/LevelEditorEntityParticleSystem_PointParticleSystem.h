
#pragma once

#include <tdme/tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;

/** 
 * Point particle system
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem
{
	friend class LevelEditorEntityParticleSystem;
	friend class LevelEditorEntityParticleSystem_Type;
	friend class LevelEditorEntityParticleSystem_ObjectParticleSystem;
	friend class LevelEditorEntityParticleSystem_Emitter;
	friend class LevelEditorEntityParticleSystem_PointParticleEmitter;
	friend class LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;

private:
	int32_t maxPoints {  };
	bool autoEmit {  };

public:

	/** 
	 * @return max points
	 */
	virtual int32_t getMaxPoints();

	/** 
	 * Set max points
	 * @param maxPoints max points
	 */
	virtual void setMaxPoints(int32_t maxPoints);

	/** 
	 * @return is auto emit
	 */
	virtual bool isAutoEmit();

	/** 
	 * Set auto emit
	 * @param autoEmit auto emit
	 */
	virtual void setAutoEmit(bool autoEmit);

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_PointParticleSystem();
};
