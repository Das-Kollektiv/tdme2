// Generated from /tdme/src/tdme/engine/model/Material.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <java/lang/Object.h>

using std::wstring;

using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Color4;


struct default_init_tag;

/** 
 * Represents a object material
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Material final
	: public Object
{

public:
	typedef Object super;

private:
	static wstring defaultMaterialId;
	static Material* defaultMaterial;

public:

	/** 
	 * @return default material
	 */
	static Material* getDefaultMaterial();

private:
	wstring id {  };
	Color4* ambientColor {  };
	Color4* diffuseColor {  };
	Color4* specularColor {  };
	Color4* emissionColor {  };
	float shininess {  };
	wstring diffuseTexturePathName {  };
	wstring diffuseTextureFileName {  };
	Texture* diffuseTexture {  };
	bool diffuseTextureTransparency {  };
	wstring specularTexturePathName {  };
	wstring specularTextureFileName {  };
	Texture* specularTexture {  };
	wstring normalTexturePathName {  };
	wstring normalTextureFileName {  };
	Texture* normalTexture {  };
	wstring displacementTexturePathName {  };
	wstring displacementTextureFileName {  };
	Texture* displacementTexture {  };
protected:

	/** 
	 * Public constructor
	 * @param name
	 */
	void ctor(const wstring& id);

public:

	/** 
	 * @return material id
	 */
	const wstring& getId();

	/** 
	 * @return ambient color
	 */
	Color4* getAmbientColor();

	/** 
	 * @return diffuse color
	 */
	Color4* getDiffuseColor();

	/** 
	 * @return specular color
	 */
	Color4* getSpecularColor();

	/** 
	 * @return emission color
	 */
	Color4* getEmissionColor();

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
	const wstring& getDiffuseTexturePathName();

	/** 
	 * @return diffuse texture file name
	 */
	const wstring& getDiffuseTextureFileName();

	/** 
	 * Set up a diffuse texture
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	void setDiffuseTexture(const wstring& pathName, const wstring& fileName);

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
	const wstring& getSpecularTexturePathName();

	/** 
	 * @return specular texture file name
	 */
	const wstring& getSpecularTextureFileName();

	/** 
	 * Set up a specular texture
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	void setSpecularTexture(const wstring& pathName, const wstring& fileName);

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
	const wstring& getNormalTexturePathName();

	/** 
	 * @return normal texture file name
	 */
	const wstring& getNormalTextureFileName();

	/** 
	 * Set up a normal texture
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	void setNormalTexture(const wstring& pathName, const wstring& fileName);

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
	const wstring& getDisplacementTexturePathName();

	/** 
	 * @return displacement texture file name
	 */
	const wstring& getDisplacementTextureFileName();

	/** 
	 * Set up a displacement texture
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	void setDisplacementTexture(const wstring& pathName, const wstring& fileName);

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
	String* toString() override;

	// Generated
	Material(const wstring& id);
protected:
	Material(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
