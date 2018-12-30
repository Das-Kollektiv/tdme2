#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::engine::fileio::textures::Texture;
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
	float pointSize {  };
	string textureFileName {  };
	Texture* texture {  };
	bool autoEmit {  };

public:

	/** 
	 * @return max points
	 */
	inline virtual int32_t getMaxPoints() {
		return maxPoints;
	}

	/** 
	 * Set max points
	 * @param maxPoints max points
	 */
	inline virtual void setMaxPoints(int32_t maxPoints) {
		this->maxPoints = maxPoints;
	}

	/** 
	 * @return point size
	 */
	inline virtual float getPointSize() {
		return pointSize;
	}

	/**
	 * Set point size
	 * @param pointSize point size
	 */
	inline virtual void setPointSize(float pointSize) {
		this->pointSize = pointSize;
	}

	/**
	 * @return texture
	 */
	inline virtual Texture* getTexture() {
		return texture;
	}

	/**
	 * @return texture file name
	 */
	inline virtual const string& getTextureFileName() {
		return textureFileName;
	}

	/**
	 * Set texture file name
	 * @param textureFileName texture file name
	 */
	virtual void setTextureFileName(const string& textureFileName);

	/**
	 * @return is auto emit
	 */
	inline virtual bool isAutoEmit() {
		return autoEmit;
	}

	/** 
	 * Set auto emit
	 * @param autoEmit auto emit
	 */
	inline virtual void setAutoEmit(bool autoEmit) {
		this->autoEmit = autoEmit;
	}

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_PointParticleSystem();

	/**
	 * Public destructor
	 */
	virtual ~LevelEditorEntityParticleSystem_PointParticleSystem();

};
