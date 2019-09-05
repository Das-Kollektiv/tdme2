#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::engine::fileio::textures::Texture;

/** 
 * Point particle system
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_FogParticleSystem
{
private:
	int32_t maxPoints {  };
	float pointSize {  };
	string textureFileName {  };
	string transparencyTextureFileName {  };
	Texture* texture {  };

public:

	/** 
	 * @return max points
	 */
	inline int32_t getMaxPoints() {
		return maxPoints;
	}

	/** 
	 * Set max points
	 * @param maxPoints max points
	 */
	inline void setMaxPoints(int32_t maxPoints) {
		this->maxPoints = maxPoints;
	}

	/** 
	 * @return point size
	 */
	inline float getPointSize() {
		return pointSize;
	}

	/**
	 * Set point size
	 * @param pointSize point size
	 */
	inline void setPointSize(float pointSize) {
		this->pointSize = pointSize;
	}

	/**
	 * @return texture
	 */
	inline Texture* getTexture() {
		return texture;
	}

	/**
	 * @return texture file name
	 */
	inline const string& getTextureFileName() {
		return textureFileName;
	}

	/**
	 * @return transparency texture file name
	 */
	inline const string& getTransparencyTextureFileName() {
		return transparencyTextureFileName;
	}

	/**
	 * Set texture file name with optional transparency texture
	 * @param textureFileName texture file name
	 * @param transparencyTextureFileName transparency texture file name
	 */
	void setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName = string());

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_FogParticleSystem();

	/**
	 * Public destructor
	 */
	~LevelEditorEntityParticleSystem_FogParticleSystem();

};
