#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;

/** 
 * Object particle system
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem
{
	friend class LevelEditorEntityParticleSystem;
	friend class LevelEditorEntityParticleSystem_Type;
	friend class LevelEditorEntityParticleSystem_PointParticleSystem;
	friend class LevelEditorEntityParticleSystem_Emitter;
	friend class LevelEditorEntityParticleSystem_PointParticleEmitter;
	friend class LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;

private:
	Vector3 scale {  };
	int32_t maxCount {  };
	bool autoEmit {  };
	Model* model {  };
	string modelFileName {  };

public:

	/** 
	 * @return scale
	 */
	inline virtual Vector3& getScale() {
		return scale;
	}

	/** 
	 * @return max count
	 */
	inline virtual int32_t getMaxCount() {
		return maxCount;
	}

	/** 
	 * Set max count
	 * @param maxCount max count
	 */
	inline virtual void setMaxCount(int32_t maxCount) {
		this->maxCount = maxCount;
	}

	/** 
	 * @return is auto emit
	 */
	inline virtual bool isAutoEmit() {
		return autoEmit;
	}

	/** 
	 * Set auto emit 
	 * @param autoEmit autoEmit
	 */
	inline virtual void setAutoEmit(bool autoEmit) {
		this->autoEmit = autoEmit;
	}

	/** 
	 * @return model
	 */
	inline virtual Model* getModel() {
		return model;
	}

	/** 
	 * @return model file
	 */
	inline virtual const string& getModelFile() {
		return modelFileName;
	}

	/** 
	 * Set model file
	 * @param modelFileName model file name
	 */
	virtual void setModelFile(const string& modelFileName) /* throws(Exception) */;

	/**
	 * Public constructor
	 */
	inline LevelEditorEntityParticleSystem_ObjectParticleSystem() {
		scale.set(1.0f, 1.0f, 1.0f);
		maxCount = 10;
		autoEmit = true;
		model = nullptr;
		modelFileName = "";
	}

	/**
	 * Destructor
	 */
	virtual ~LevelEditorEntityParticleSystem_ObjectParticleSystem();

};
