#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>

using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Color4;

/** 
 * Represents a object material
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Material final
{
private:
	static string defaultMaterialId;
	static Material* defaultMaterial;

public:

	/** 
	 * @return default material
	 */
	inline static Material* getDefaultMaterial() {
		return defaultMaterial;
	}

private:
	string id {  };
	Color4 ambientColor {  };
	Color4 diffuseColor {  };
	Color4 specularColor {  };
	Color4 emissionColor {  };
	float shininess {  };
	string diffuseTexturePathName {  };
	string diffuseTextureFileName {  };
	string diffuseTransparencyTexturePathName {  };
	string diffuseTransparencyTextureFileName {  };
	Texture* diffuseTexture {  };
	bool diffuseTextureMaskedTransparency { };
	float diffuseTextureMaskedTransparencyThreshold { };
	bool diffuseTextureTransparency {  };
	string specularTexturePathName {  };
	string specularTextureFileName {  };
	Texture* specularTexture {  };
	string normalTexturePathName {  };
	string normalTextureFileName {  };
	Texture* normalTexture {  };
	string displacementTexturePathName {  };
	string displacementTextureFileName {  };
	Texture* displacementTexture {  };

	/**
	 * Checks and set ups diffuse texture transparency
	 */
	void checkDiffuseTextureTransparency();

public:

	/** 
	 * @return material id
	 */
	inline const string& getId() const {
		return id;
	}

	/** 
	 * @return ambient color
	 */
	inline const Color4& getAmbientColor() const {
		return ambientColor;
	}

	/**
	 * Set ambient color component
	 * @param ambientColor ambient color
	 */
	inline void setAmbientColor(const Color4& ambientColor) {
		this->ambientColor = ambientColor;
	}

	/** 
	 * @return diffuse color
	 */
	inline const Color4& getDiffuseColor() const {
		return diffuseColor;
	}

	/**
	 * Set diffuse color component
	 * @param diffuseColor diffuse color
	 */
	inline void setDiffuseColor(const Color4& diffuseColor) {
		this->diffuseColor = diffuseColor;
	}

	/** 
	 * @return specular color
	 */
	inline const Color4& getSpecularColor() const {
		return specularColor;
	}

	/**
	 * Set specular color component
	 * @param specularColor specular color
	 */
	inline void setSpecularColor(const Color4& specularColor) {
		this->specularColor = specularColor;
	}

	/** 
	 * @return emission color
	 */
	inline const Color4& getEmissionColor() const {
		return emissionColor;
	}

	/**
	 * Set emission color component
	 * @param emissionColor emission color
	 */
	inline void setEmissionColor(const Color4& emissionColor) {
		this->emissionColor = emissionColor;
	}

	/** 
	 * @return shininess
	 */
	inline float getShininess() const {
		return shininess;
	}

	/** 
	 * Set up material shininess
	 * @param shininess shininess
	 */
	inline void setShininess(float shininess) {
		this->shininess = shininess;
	}

	/** 
	 * @return diffuse texture path name
	 */
	inline const string& getDiffuseTexturePathName() const {
		return diffuseTexturePathName;
	}

	/** 
	 * @return diffuse texture file name
	 */
	inline const string& getDiffuseTextureFileName() const {
		return diffuseTextureFileName;
	}

	/** 
	 * @return diffuse transparency texture path name
	 */
	inline const string& getDiffuseTransparencyTexturePathName() const {
		return diffuseTransparencyTexturePathName;
	}

	/**
	 * @return diffuse transparency texture file name
	 */
	inline const string& getDiffuseTransparencyTextureFileName() const {
		return diffuseTransparencyTextureFileName;
	}

	/**
	 * Set up a diffuse texture
	 * @param pathName path name
	 * @param fileName file name
	 * @param transparencyPathName transparency path name
	 * @param transparencyFileName transparency file name
	 */
	void setDiffuseTexture(const string& pathName, const string& fileName, const string& transparencyPathName = "", const string& transparencyFileName = "");

	/**
	 * @return if material has a diffuse texture
	 */
	inline bool hasDiffuseTexture() const {
		return diffuseTexture != nullptr;
	}

	/** 
	 * @return the material's diffuse texture
	 */
	inline Texture* getDiffuseTexture() {
		return diffuseTexture;
	}

	/** 
	 * @return diffuse texture has transparent pixels
	 */
	inline bool hasDiffuseTextureTransparency() const {
		return diffuseTextureTransparency;
	}

	/**
	 * @return diffuse texture has masked transparency, means pixel are eighter opaque or not visible
	 */
	inline bool hasDiffuseTextureMaskedTransparency() const {
		return diffuseTextureMaskedTransparency;
	}

	/**
	 * Set if diffuse texture uses masked transparency(means pixel are eighter opaque or not visible)
	 * @param maskedTransparency masked transparency
	 */
	inline void setDiffuseTextureMaskedTransparency(bool maskedTransparency) {
		diffuseTextureMaskedTransparency = maskedTransparency;
	}

	/**
	 * @return diffuse masked transparency threshold
	 */
	inline float getDiffuseTextureMaskedTransparencyThreshold() const {
		return diffuseTextureMaskedTransparencyThreshold;
	}

	/**
	 * Set diffuse texture masked transparency threshold
	 * @param maskedTransparencyThreshold diffuse texture masked transparency threshold
	 */
	inline void setDiffuseTextureMaskedTransparencyThreshold(float maskedTransparencyThreshold) {
		diffuseTextureMaskedTransparencyThreshold = maskedTransparencyThreshold;
	}

	/** 
	 * @return specular texture path name
	 */
	inline const string& getSpecularTexturePathName() const {
		return specularTexturePathName;
	}

	/** 
	 * @return specular texture file name
	 */
	inline const string& getSpecularTextureFileName() const {
		return specularTextureFileName;
	}

	/** 
	 * Set up a specular texture
	 * @param pathName path name
	 * @param fileName file name
	 */
	void setSpecularTexture(const string& pathName, const string& fileName);

	/** 
	 * @return if material has a specular texture
	 */
	inline bool hasSpecularTexture() const {
		return specularTexture != nullptr;
	}

	/** 
	 * @return the material's specular texture
	 */
	inline Texture* getSpecularTexture() {
		return specularTexture;
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
	inline Texture* getNormalTexture() {
		return normalTexture;
	}

	/** 
	 * @return displacement texture path name
	 */
	inline const string& getDisplacementTexturePathName() const {
		return displacementTexturePathName;
	}

	/** 
	 * @return displacement texture file name
	 */
	inline const string& getDisplacementTextureFileName() const {
		return displacementTextureFileName;
	}

	/** 
	 * Set up a displacement texture
	 * @param pathName path name
	 * @param fileName file name
	 */
	void setDisplacementTexture(const string& pathName, const string& fileName);

	/** 
	 * @return if material has a displacement texture
	 */
	inline bool hasDisplacementTexture() const {
		return displacementTexture != nullptr;
	}

	/** 
	 * @return the material's displacement texture
	 */
	inline Texture* getDisplacementTexture() {
		return displacementTexture;
	}

	/** 
	 * @return if color is transparent
	 */
	inline bool hasColorTransparency() const {
		return diffuseColor.getAlpha() < 1.0f - Math::EPSILON;
	}

	/**
	 * @return if texture has transparency with masked transparency disabled
	 */
	inline bool hasTextureTransparency() const {
		return diffuseTextureTransparency == true && diffuseTextureMaskedTransparency == false;
	}

	/**
	 * Public constructor
	 * @param id id
	 */
	Material(const string& id);

	/**
	 * Destructor
	 */
	~Material();
};
