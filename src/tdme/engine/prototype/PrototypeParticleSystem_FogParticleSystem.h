#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::string;

using tdme::engine::Texture;

/**
 * Prototype point particle system definition
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeParticleSystem_FogParticleSystem final
{
private:
	int maxPoints { 4000 };
	float pointSize{ 0.1f };
	string textureFileName;
	string transparencyTextureFileName;
	Texture* texture { nullptr };
	int textureHorizontalSprites{ 1 };
	int textureVerticalSprites{ 1 };
	float textureSpritesFPS { 10.0f };

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeParticleSystem_FogParticleSystem)

	/**
	 * Public constructor
	 */
	PrototypeParticleSystem_FogParticleSystem();

	/**
	 * Public destructor
	 */
	~PrototypeParticleSystem_FogParticleSystem();

	/**
	 * @returns max points
	 */
	inline int getMaxPoints() {
		return maxPoints;
	}

	/**
	 * Set max points
	 * @param maxPoints max points
	 */
	inline void setMaxPoints(int maxPoints) {
		this->maxPoints = maxPoints;
	}

	/**
	 * @returns point size
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
	 * @returns texture
	 */
	inline Texture* getTexture() {
		return texture;
	}

	/**
	 * @returns texture with acquired reference
	 */
	Texture* getTextureReference();

	/**
	 * @returns texture file name
	 */
	inline const string& getTextureFileName() {
		return textureFileName;
	}

	/**
	 * @returns transparency texture file name
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
	 * @returns horizontal number of sprites in texture
	 */
	inline int getTextureHorizontalSprites() {
		return textureHorizontalSprites;
	}

	/**
	 * Set texture horizontal number of sprites
	 * @param textureHorizontalSprites horizontal number of sprites
	 */
	inline void setTextureHorizontalSprites(int textureHorizontalSprites) {
		this->textureHorizontalSprites = textureHorizontalSprites;
	}

	/**
	 * @returns vertical number of sprites in texture
	 */
	inline int getTextureVerticalSprites() {
		return textureVerticalSprites;
	}

	/**
	 * Set texture vertical number of sprites
	 * @param textureVerticalSprites vertical number of sprites
	 */
	inline void setTextureVerticalSprites(int textureVerticalSprites) {
		this->textureVerticalSprites = textureVerticalSprites;
	}

	/**
	 * @returns texture sprites frames per second
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

};
