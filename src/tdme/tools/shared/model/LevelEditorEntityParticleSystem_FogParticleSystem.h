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
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_FogParticleSystem final
{
private:
	int32_t maxPoints { 4000 };
	float pointSize{ 10.0f };
	string textureFileName;
	string transparencyTextureFileName;
	Texture* texture { nullptr };
	int32_t textureHorizontalSprites{ 1 };
	int32_t textureVerticalSprites{ 1 };
	float textureSpritesFPS { 10.0f };

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
	 * @return horizontal number of sprites in texture
	 */
	int32_t getTextureHorizontalSprites() {
		return textureHorizontalSprites;
	}

	/**
	 * Set texture horizontal number of sprites
	 * @param textureHorizontalSprites horizontal number of sprites
	 */
	void setTextureHorizontalSprites(int32_t textureHorizontalSprites) {
		this->textureHorizontalSprites = textureHorizontalSprites;
	}

	/**
	 * @return vertical number of sprites in texture
	 */
	int32_t getTextureVerticalSprites() {
		return textureVerticalSprites;
	}

	/**
	 * Set texture vertical number of sprites
	 * @param textureVerticalSprites vertical number of sprites
	 */
	void setTextureVerticalSprites(int32_t textureVerticalSprites) {
		this->textureVerticalSprites = textureVerticalSprites;
	}

	/**
	 * @return texture sprites frames per second
	 */
	inline float getTextureSpritesFPS() {
		return textureSpritesFPS;
	}

	/**
	 * Set texture sprites frames per second
	 * @param textureSpritesFPS frames per second
	 */
	inline void setTextureSpritesFPS(float textureSpritesFPS) {
		this->textureSpritesFPS = textureSpritesFPS;
	}

	/**
	 * Public constructor
	 */
	LevelEditorEntityParticleSystem_FogParticleSystem();

	/**
	 * Public destructor
	 */
	~LevelEditorEntityParticleSystem_FogParticleSystem();

};
