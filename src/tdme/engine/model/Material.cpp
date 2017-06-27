// Generated from /tdme/src/tdme/engine/model/Material.java
#include <tdme/engine/model/Material.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/nio/ByteBuffer.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/MathTools.h>

using tdme::engine::model::Material;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::nio::ByteBuffer;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::model::Color4;
using tdme::math::MathTools;

Material::Material(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Material::Material(String* id) 
	: Material(*static_cast< ::default_init_tag* >(0))
{
	ctor(id);
}

String* Material::defaultMaterialId;

Material* Material::defaultMaterial;

Material* Material::getDefaultMaterial()
{
	clinit();
	return defaultMaterial;
}

void Material::ctor(String* id)
{
	super::ctor();
	this->id = id;
	ambientColor = new Color4(0.2f, 0.2f, 0.2f, 0.0f);
	diffuseColor = new Color4(0.8f, 0.8f, 0.8f, 1.0f);
	specularColor = new Color4(0.0f, 0.0f, 0.0f, 0.0f);
	emissionColor = new Color4(0.0f, 0.0f, 0.0f, 0.0f);
	shininess = 0.0f;
	diffuseTexturePathName = nullptr;
	diffuseTextureFileName = nullptr;
	diffuseTexture = nullptr;
	diffuseTextureTransparency = false;
	specularTexturePathName = nullptr;
	specularTextureFileName = nullptr;
	specularTexture = nullptr;
	normalTexturePathName = nullptr;
	normalTextureFileName = nullptr;
	normalTexture = nullptr;
	displacementTexturePathName = nullptr;
	displacementTextureFileName = nullptr;
	displacementTexture = nullptr;
}

String* Material::getId()
{
	return id;
}

Color4* Material::getAmbientColor()
{
	return ambientColor;
}

Color4* Material::getDiffuseColor()
{
	return diffuseColor;
}

Color4* Material::getSpecularColor()
{
	return specularColor;
}

Color4* Material::getEmissionColor()
{
	return emissionColor;
}

float Material::getShininess()
{
	return shininess;
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}

String* Material::getDiffuseTexturePathName()
{
	return diffuseTexturePathName;
}

String* Material::getDiffuseTextureFileName()
{
	return diffuseTextureFileName;
}

void Material::setDiffuseTexture(String* pathName, String* fileName)
{
	diffuseTexturePathName = pathName;
	diffuseTextureFileName = fileName;
	diffuseTexture = TextureLoader::loadTexture(pathName, fileName);
	checkDiffuseTextureTransparency();
}

bool Material::hasDiffuseTexture()
{
	return diffuseTexture != nullptr;
}

Texture* Material::getDiffuseTexture()
{
	return diffuseTexture;
}

bool Material::hasDiffuseTextureTransparency()
{
	return diffuseTextureTransparency;
}

void Material::checkDiffuseTextureTransparency()
{
	diffuseTextureTransparency = false;
	if (diffuseTexture != nullptr && diffuseTexture->getDepth() == 32) {
		auto textureData = diffuseTexture->getTextureData();
		for (auto i = 0; i < diffuseTexture->getTextureWidth() * diffuseTexture->getTextureHeight(); i++) {
			auto alpha = textureData->get(i * 4 + 3);
			if (alpha != static_cast< int8_t >(255)) {
				diffuseTextureTransparency = true;
				break;
			}
		}
	}
}

String* Material::getSpecularTexturePathName()
{
	return specularTexturePathName;
}

String* Material::getSpecularTextureFileName()
{
	return specularTextureFileName;
}

void Material::setSpecularTexture(String* pathName, String* fileName)
{
	specularTexturePathName = pathName;
	specularTextureFileName = fileName;
	specularTexture = TextureLoader::loadTexture(pathName, fileName);
}

bool Material::hasSpecularTexture()
{
	return specularTexture != nullptr;
}

Texture* Material::getSpecularTexture()
{
	return specularTexture;
}

String* Material::getNormalTexturePathName()
{
	return normalTexturePathName;
}

String* Material::getNormalTextureFileName()
{
	return normalTextureFileName;
}

void Material::setNormalTexture(String* pathName, String* fileName)
{
	normalTexturePathName = pathName;
	normalTextureFileName = fileName;
	normalTexture = TextureLoader::loadTexture(pathName, fileName);
}

bool Material::hasNormalTexture()
{
	return normalTexture != nullptr;
}

Texture* Material::getNormalTexture()
{
	return normalTexture;
}

String* Material::getDisplacementTexturePathName()
{
	return displacementTexturePathName;
}

String* Material::getDisplacementTextureFileName()
{
	return displacementTextureFileName;
}

void Material::setDisplacementTexture(String* pathName, String* fileName)
{
	displacementTexturePathName = pathName;
	displacementTextureFileName = fileName;
	displacementTexture = TextureLoader::loadTexture(pathName, fileName);
}

bool Material::hasDisplacementTexture()
{
	return displacementTexture != nullptr;
}

Texture* Material::getDisplacementTexture()
{
	return displacementTexture;
}

bool Material::hasTransparency()
{
	return diffuseColor->getAlpha() < 1.0f - MathTools::EPSILON || diffuseTextureTransparency;
}

String* Material::toString()
{
	return ::java::lang::StringBuilder().append(u"Material [id="_j)->append(id)
		->append(u", ambientColor="_j)
		->append(static_cast< Object* >(ambientColor))
		->append(u", diffuseColor="_j)
		->append(static_cast< Object* >(diffuseColor))
		->append(u", specularColor="_j)
		->append(static_cast< Object* >(specularColor))
		->append(u", emissionColor="_j)
		->append(static_cast< Object* >(emissionColor))
		->append(u", shininess="_j)
		->append(shininess)
		->append(u", diffuseTexture="_j)
		->append(static_cast< Object* >(diffuseTexture))
		->append(u", diffuseTextureTransparency="_j)
		->append(diffuseTextureTransparency)
		->append(u", specularTexture="_j)
		->append(static_cast< Object* >(specularTexture))
		->append(u", normalTexture="_j)
		->append(static_cast< Object* >(normalTexture))
		->append(u", displacementTexture="_j)
		->append(static_cast< Object* >(displacementTexture))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Material::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Material", 26);
    return c;
}

void Material::clinit()
{
struct string_init_ {
	string_init_() {
	defaultMaterialId = u"tdme.default_material"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		defaultMaterial = new Material(defaultMaterialId);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* Material::getClass0()
{
	return class_();
}

