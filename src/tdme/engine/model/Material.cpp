#include <tdme/engine/model/Material.h>

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/MathTools.h>

using std::wstring;

using tdme::engine::model::Material;
using tdme::utils::ByteBuffer;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::model::Color4;
using tdme::math::MathTools;

Material::Material(const wstring& id)
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

Material* Material::getDefaultMaterial()
{
	return defaultMaterial;
}

const wstring& Material::getId()
{
	return id;
}

Color4* Material::getAmbientColor()
{
	return &ambientColor;
}

Color4* Material::getDiffuseColor()
{
	return &diffuseColor;
}

Color4* Material::getSpecularColor()
{
	return &specularColor;
}

Color4* Material::getEmissionColor()
{
	return &emissionColor;
}

float Material::getShininess()
{
	return shininess;
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}

const wstring& Material::getDiffuseTexturePathName()
{
	return diffuseTexturePathName;
}

const wstring& Material::getDiffuseTextureFileName()
{
	return diffuseTextureFileName;
}

void Material::setDiffuseTexture(const wstring& pathName, const wstring& fileName)
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

const wstring& Material::getSpecularTexturePathName()
{
	return specularTexturePathName;
}

const wstring& Material::getSpecularTextureFileName()
{
	return specularTextureFileName;
}

void Material::setSpecularTexture(const wstring& pathName, const wstring& fileName)
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

const wstring& Material::getNormalTexturePathName()
{
	return normalTexturePathName;
}

const wstring& Material::getNormalTextureFileName()
{
	return normalTextureFileName;
}

void Material::setNormalTexture(const wstring& pathName, const wstring& fileName)
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

const wstring& Material::getDisplacementTexturePathName()
{
	return displacementTexturePathName;
}

const wstring& Material::getDisplacementTextureFileName()
{
	return displacementTextureFileName;
}

void Material::setDisplacementTexture(const wstring& pathName, const wstring& fileName)
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

wstring Material::defaultMaterialId = L"tdme.default_material";
Material* Material::defaultMaterial = new Material(Material::defaultMaterialId);
