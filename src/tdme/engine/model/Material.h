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
	static Material* getDefaultMaterial();

private:
	string id {  };
	Color4 ambientColor {  };
	Color4 diffuseColor {  };
	Color4 specularColor {  };
	Color4 emissionColor {  };
	float shininess {  };
	string diffuseTexturePathName {  };
	string diffuseTextureFileName {  };
	Texture* diffuseTexture {  };
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

public:

	/** 
	 * @return material id
	 */
	const string& getId();

	/** 
	 * @return ambient color
	 */
	Color4& getAmbientColor();

	/** 
	 * @return diffuse color
	 */
	Color4& getDiffuseColor();

	/** 
	 * @return specular color
	 */
	Color4& getSpecularColor();

	/** 
	 * @return emission color
	 */
	Color4& getEmissionColor();

	/** 
	 * @return shininess
	 */
	float getShininess();

	/** 
	 * Set up material shininess
	 * @param shininess
	 */
	void setShininess(float shininess);

	/** 
	 * @return diffuse texture path name
	 */
	const string& getDiffuseTexturePathName();

	/** 
	 * @return diffuse texture file name
	 */
	const string& getDiffuseTextureFileName();

	/** 
	 * Set up a diffuse texture
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	void setDiffuseTexture(const string& pathName, const string& fileName);

	/** 
	 * @return if material has a diffuse texture
	 */
	bool hasDiffuseTexture();

	/** 
	 * @return the material's diffuse texture
	 */
	Texture* getDiffuseTexture();

	/** 
	 * @return texture has transparent pixels
	 */
	bool hasDiffuseTextureTransparency();

private:

	/** 
	 * Checks and set ups diffuse texture transparency
	 */
	void checkDiffuseTextureTransparency();

public:

	/** 
	 * @return specular texture path name
	 */
	const string& getSpecularTexturePathName();

	/** 
	 * @return specular texture file name
	 */
	const string& getSpecularTextureFileName();

	/** 
	 * Set up a specular texture
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	void setSpecularTexture(const string& pathName, const string& fileName);

	/** 
	 * @return if material has a specular texture
	 */
	bool hasSpecularTexture();

	/** 
	 * @return the material's specular texture
	 */
	Texture* getSpecularTexture();

	/** 
	 * @return normal texture path name
	 */
	const string& getNormalTexturePathName();

	/** 
	 * @return normal texture file name
	 */
	const string& getNormalTextureFileName();

	/** 
	 * Set up a normal texture
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	void setNormalTexture(const string& pathName, const string& fileName);

	/** 
	 * @return if material has a normal texture
	 */
	bool hasNormalTexture();

	/** 
	 * @return the material's normal texture
	 */
	Texture* getNormalTexture();

	/** 
	 * @return displacement texture path name
	 */
	const string& getDisplacementTexturePathName();

	/** 
	 * @return displacement texture file name
	 */
	const string& getDisplacementTextureFileName();

	/** 
	 * Set up a displacement texture
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	void setDisplacementTexture(const string& pathName, const string& fileName);

	/** 
	 * @return if material has a displacement texture
	 */
	bool hasDisplacementTexture();

	/** 
	 * @return the material's displacement texture
	 */
	Texture* getDisplacementTexture();

	/** 
	 * @return if material is transparent
	 */
	bool hasTransparency();

	/**
	 * Public constructor
	 * @param id
	 */
	Material(const string& id);

	/**
	 * Destructor
	 */
	~Material();
};
