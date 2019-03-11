#include <tdme/engine/model/Material.h>

#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Math.h>
#include <tdme/utils/ByteBuffer.h>

using std::string;

using tdme::engine::model::Material;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::Color4;
using tdme::math::Math;
using tdme::utils::ByteBuffer;

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
	diffuseTextureMaskedTransparency = false;
	diffuseTextureMaskedTransparencyThreshold = 0.1f;
	specularTexture = nullptr;
	normalTexture = nullptr;
	displacementTexture = nullptr;
	textureMatrix.identity();
}

Material::~Material() {
	if (diffuseTexture != nullptr) diffuseTexture->releaseReference();
	if (specularTexture != nullptr) specularTexture->releaseReference();
	if (normalTexture != nullptr) normalTexture->releaseReference();
	if (displacementTexture != nullptr) displacementTexture->releaseReference();
}

void Material::setDiffuseTexture(const string& pathName, const string& fileName, const string& transparencyPathName, const string& transparencyFileName)
{
	// load diffuse texture
	diffuseTexturePathName = pathName;
	diffuseTextureFileName = fileName;
	diffuseTransparencyTexturePathName = transparencyPathName;
	diffuseTransparencyTextureFileName = transparencyFileName;
	if (diffuseTransparencyTextureFileName.size() > 0) {
		diffuseTexture = TextureReader::read(
			diffuseTexturePathName,
			diffuseTextureFileName,
			diffuseTransparencyTexturePathName,
			diffuseTransparencyTextureFileName
		);
	} else {
		diffuseTexture = TextureReader::read(
			diffuseTexturePathName,
			diffuseTextureFileName
		);
	}
	checkDiffuseTextureTransparency();
}

void Material::checkDiffuseTextureTransparency()
{
	diffuseTextureTransparency = false;
	auto diffuseTextureMaskedTransparencyTest = true;
	if (diffuseTexture != nullptr && diffuseTexture->getDepth() == 32) {
		auto textureData = diffuseTexture->getTextureData();
		for (auto i = 0; i < diffuseTexture->getTextureWidth() * diffuseTexture->getTextureHeight(); i++) {
			auto alpha = textureData->get(i * 4 + 3);
			if (alpha != 255) diffuseTextureTransparency = true;
			if (alpha > 5 || alpha < 250) diffuseTextureMaskedTransparencyTest = false;
		}
	}
	if (diffuseTextureMaskedTransparency == false) diffuseTextureMaskedTransparency = diffuseTextureMaskedTransparencyTest;
}

void Material::setSpecularTexture(const string& pathName, const string& fileName)
{
	specularTexturePathName = pathName;
	specularTextureFileName = fileName;
	specularTexture = TextureReader::read(pathName, fileName);
}

void Material::setNormalTexture(const string& pathName, const string& fileName)
{
	normalTexturePathName = pathName;
	normalTextureFileName = fileName;
	normalTexture = TextureReader::read(pathName, fileName);
}

void Material::setDisplacementTexture(const string& pathName, const string& fileName)
{
	displacementTexturePathName = pathName;
	displacementTextureFileName = fileName;
	displacementTexture = TextureReader::read(pathName, fileName);
}

string Material::defaultMaterialId = "tdme.default_material";
Material* Material::defaultMaterial = new Material(Material::defaultMaterialId);
