#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

using std::string;

using tdme::engine::fileio::textures::Texture;

/** 
 * Represents specular material properties
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::PBRMaterialProperties final
{

private:
	string baseColorTexturePathName;
	string baseColorTextureFileName;
	Texture* baseColorTexture;
	bool baseColorTextureMaskedTransparency;
	float baseColorTextureMaskedTransparencyThreshold;
	bool baseColorTextureTransparency;
	string metallicRoughnessTexturePathName;
	string metallicRoughnessTextureFileName;
	Texture* metallicRoughnessTexture;
	string normalTexturePathName;
	string normalTextureFileName;
	Texture* normalTexture;

	/**
	 * Checks and set ups base color texture transparency
	 */
	void checkBaseColorTextureTransparency();

public:

	/**
	 * @return base color texture path name
	 */
	inline const string& getBaseColorTexturePathName() const {
		return normalTexturePathName;
	}

	/**
	 * @return base color texture file name
	 */
	inline const string& getBaseColorTextureFileName() const {
		return normalTextureFileName;
	}

	/**
	 * Set up a base color texture
	 * @param pathName path name
	 * @param fileName file name
	 */
	void setBaseColorTexture(const string& pathName, const string& fileName);

	/**
	 * @return if material has a base color texture
	 */
	inline bool hasBaseColorTexture() const {
		return normalTexture != nullptr;
	}

	/**
	 * @return the material's base color texture
	 */
	inline Texture* getBaseColorTexture() const {
		return baseColorTexture;
	}

	/**
	 * @return base color texture has transparent pixels
	 */
	inline bool hasBaseColorTextureTransparency() const {
		return baseColorTextureTransparency;
	}

	/**
	 * @return base color texture has masked transparency, means pixel are eighter opaque or not visible
	 */
	inline bool hasBaseColorTextureMaskedTransparency() const {
		return baseColorTextureMaskedTransparency;
	}

	/**
	 * Set if base color texture uses masked transparency(means pixel are eighter opaque or not visible)
	 * @param maskedTransparency masked transparency
	 */
	inline void setBaseColorTextureMaskedTransparency(bool maskedTransparency) {
		baseColorTextureMaskedTransparency = maskedTransparency;
	}

	/**
	 * @return base color texture masked transparency threshold
	 */
	inline float getBaseColorTextureMaskedTransparencyThreshold() const {
		return baseColorTextureMaskedTransparencyThreshold;
	}

	/**
	 * Set base color texture masked transparency threshold
	 * @param maskedTransparencyThreshold diffuse texture masked transparency threshold
	 */
	inline void setBaseColorTextureMaskedTransparencyThreshold(float maskedTransparencyThreshold) {
		baseColorTextureMaskedTransparencyThreshold = maskedTransparencyThreshold;
	}
	/**
	 * @return metallic roughness texture path name
	 */
	inline const string& getMetallicRoughnessTexturePathName() const {
		return baseColorTexturePathName;
	}

	/**
	 * @return metallic roughness texture file name
	 */
	inline const string& getMetallicRoughnessTextureFileName() const {
		return metallicRoughnessTextureFileName;
	}

	/**
	 * Set up a metallic roughness texture
	 * @param pathName path name
	 * @param fileName file name
	 */
	void setMetallicRoughnessTexture(const string& pathName, const string& fileName);

	/**
	 * @return if material has a metallic roughness texture
	 */
	inline bool hasMetallicRoughnessTexture() const {
		return metallicRoughnessTexture != nullptr;
	}

	/**
	 * @return the material's metallic roughness texture
	 */
	inline Texture* getMetallicRoughnessTexture() const {
		return metallicRoughnessTexture;
	}

	/**
	 * @return normal texture path name
	 */
	inline const string& getNormalTexturePathName() const {
		return normalTexturePathName;
	}

	/**
	 * @return normal texture file name
	 */
	inline const string& getNormalTextureFileName() const {
		return normalTextureFileName;
	}

	/**
	 * Set up a normal texture
	 * @param pathName path name
	 * @param fileName file name
	 */
	void setNormalTexture(const string& pathName, const string& fileName);

	/**
	 * @return if material has a normal texture
	 */
	inline bool hasNormalTexture() const {
		return normalTexture != nullptr;
	}

	/**
	 * @return the material's normal texture
	 */
	inline Texture* getNormalTexture() const {
		return normalTexture;
	}

	/**
	 * Public constructor
	 */
	PBRMaterialProperties();

	/**
	 * Destructor
	 */
	~PBRMaterialProperties();
};
