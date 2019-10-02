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
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem final
{
private:
	int32_t maxPoints;
	float pointSize;
	string textureFileName;
	string transparencyTextureFileName;
	Texture* texture { nullptr };
	bool autoEmit;

public:

	/** 
	 * @return max points
	 */
	int32_t getMaxPoints() {
		return maxPoints;
	}

	/** 
	 * Set max points
	 * @param maxPoints max points
	 */
	void setMaxPoints(int32_t maxPoints) {
		this->maxPoints = maxPoints;
	}

	/** 
	 * @return point size
	 */
	float getPointSize() {
		return pointSize;
	}

	/**
	 * Set point size
	 * @param pointSize point size
	 */
	void setPointSize(float pointSize) {
		this->pointSize = pointSize;
	}

	/**
	 * @return texture
	 */
	Texture* getTexture() {
		return texture;
	}

	/**
	 * @return texture file name
	 */
	const string& getTextureFileName() {
		return textureFileName;
	}

	/**
	 * @return transparency texture file name
	 */
	const string& getTransparencyTextureFileName() {
		return transparencyTextureFileName;
	}

	/**
	 * Set texture file name with optional transparency texture
	 * @param textureFileName texture file name
	 * @param transparencyTextureFileName transparency texture file name
	 */
	void setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName = string());

	/**
	 * @return is auto emit
	 */
	bool isAutoEmit() {
		return autoEmit;
	}

	/** 
	 * Set auto emit
	 * @param autoEmit auto emit
	 */
	void setAutoEmit(bool autoEmit) {
		this->autoEmit = autoEmit;
	}

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_PointParticleSystem();

	/**
	 * Public destructor
	 */
	~LevelEditorEntityParticleSystem_PointParticleSystem();

};
