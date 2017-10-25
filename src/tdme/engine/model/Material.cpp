#include <tdme/engine/model/Material.h>

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/MathTools.h>

using std::string;

using tdme::engine::model::Material;
using tdme::utils::ByteBuffer;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::model::Color4;
using tdme::math::MathTools;

Material::Material(const string& id)
{
	this->id = id;
	ambientColor.set(0.2f, 0.2f, 0.2f, 0.0f);
	diffuseColor.set(0.8f, 0.8f, 0.8f, 1.0f);
	specularColor.set(0.0f, 0.0f, 0.0f, 0.0f);
	emissionColor.set(0.0f, 0.0f, 0.0f, 0.0f);
	shininess = 0.0f;
	diffuseTexture = nullptr;
	diffuseTextureTransparency = false;
	specularTexture = nullptr;
	normalTexture = nullptr;
	displacementTexture = nullptr;
}

Material::~Material() {
	if (diffuseTexture != nullptr) delete diffuseTexture;
	if (specularTexture != nullptr) delete specularTexture;
	if (normalTexture != nullptr) delete normalTexture;
	if (displacementTexture != nullptr) delete displacementTexture;
}

Material* Material::getDefaultMaterial()
{
	return defaultMaterial;
}

const string& Material::getId()
{
	return id;
}

Color4& Material::getAmbientColor()
{
	return ambientColor;
}

Color4& Material::getDiffuseColor()
{
	return diffuseColor;
}

Color4& Material::getSpecularColor()
{
	return specularColor;
}

Color4& Material::getEmissionColor()
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

const string& Material::getDiffuseTexturePathName()
{
	return diffuseTexturePathName;
}

const string& Material::getDiffuseTextureFileName()
{
	return diffuseTextureFileName;
}

void Material::setDiffuseTexture(const string& pathName, const string& fileName)
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
			if (alpha != 255) {
				diffuseTextureTransparency = true;
				break;
			}
		}
	}
}

const string& Material::getSpecularTexturePathName()
{
	return specularTexturePathName;
}

const string& Material::getSpecularTextureFileName()
{
	return specularTextureFileName;
}

void Material::setSpecularTexture(const string& pathName, const string& fileName)
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

const string& Material::getNormalTexturePathName()
{
	return normalTexturePathName;
}

const string& Material::getNormalTextureFileName()
{
	return normalTextureFileName;
}

void Material::setNormalTexture(const string& pathName, const string& fileName)
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

const string& Material::getDisplacementTexturePathName()
{
	return displacementTexturePathName;
}

const string& Material::getDisplacementTextureFileName()
{
	return displacementTextureFileName;
}

void Material::setDisplacementTexture(const string& pathName, const string& fileName)
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
	return diffuseColor.getAlpha() < 1.0f - MathTools::EPSILON || diffuseTextureTransparency;
}

string Material::defaultMaterialId = "tdme.default_material";
Material* Material::defaultMaterial = new Material(Material::defaultMaterialId);
