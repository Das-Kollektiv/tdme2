#include <tdme/engine/model/SpecularMaterialProperties.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/ByteBuffer.h>

using std::string;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::Color4;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::math::Math;
using tdme::utilities::ByteBuffer;

SpecularMaterialProperties::SpecularMaterialProperties()
{
	ambientColor.set(0.2f, 0.2f, 0.2f, 0.0f);
	diffuseColor.set(0.8f, 0.8f, 0.8f, 1.0f);
	specularColor.set(0.0f, 0.0f, 0.0f, 0.0f);
	emissionColor.set(0.0f, 0.0f, 0.0f, 0.0f);
	shininess = 0.0f;
	reflection = 0.0f;
	diffuseTexture = nullptr;
	diffuseTextureTransparency = false;
	diffuseTextureMaskedTransparency = false;
	diffuseTextureMaskedTransparencyThreshold = 0.1f;
	specularTexture = nullptr;
	normalTexture = nullptr;
	textureAtlasSize = 1;
}

SpecularMaterialProperties::~SpecularMaterialProperties() {
	if (diffuseTexture != nullptr) diffuseTexture->releaseReference();
	if (specularTexture != nullptr) specularTexture->releaseReference();
	if (normalTexture != nullptr) normalTexture->releaseReference();
}

void SpecularMaterialProperties::setDiffuseTexture(Texture* diffuseTexture) {
	if (this->diffuseTexture == diffuseTexture) return;
	if (this->diffuseTexture != nullptr) this->diffuseTexture->releaseReference();
	diffuseTexturePathName.clear();
	diffuseTextureFileName = diffuseTexture->getId();
	diffuseTransparencyTexturePathName.clear();
	diffuseTransparencyTextureFileName.clear();
	diffuseTexture->acquireReference();
	this->diffuseTexture = diffuseTexture;
	checkDiffuseTextureTransparency();
}

void SpecularMaterialProperties::setDiffuseTexture(const string& pathName, const string& fileName, const string& transparencyPathName, const string& transparencyFileName)
{
	if (diffuseTexture != nullptr) diffuseTexture->releaseReference();
	diffuseTexture = nullptr;
	// load diffuse texture
	diffuseTexturePathName = pathName;
	diffuseTextureFileName = fileName;
	diffuseTransparencyTexturePathName = transparencyPathName;
	diffuseTransparencyTextureFileName = transparencyFileName;
	if (diffuseTransparencyTextureFileName.size() > 0) {
		diffuseTexture = TextureReader::read2(
			diffuseTexturePathName,
			diffuseTextureFileName,
			diffuseTransparencyTexturePathName,
			diffuseTransparencyTextureFileName,
			true,
			textureAtlasSize > 1?false:true
		);
		if (diffuseTexture != nullptr) diffuseTexture->setAtlasSize(textureAtlasSize);
	} else {
		diffuseTexture = TextureReader::read(
			diffuseTexturePathName,
			diffuseTextureFileName,
			true,
			textureAtlasSize > 1?false:true
		);
		if (diffuseTexture != nullptr) diffuseTexture->setAtlasSize(textureAtlasSize);
	}
	checkDiffuseTextureTransparency();
}

void SpecularMaterialProperties::checkDiffuseTextureTransparency()
{
	diffuseTextureTransparency = false;
	auto diffuseTextureMaskedTransparencyTest = true;
	if (diffuseTexture != nullptr && diffuseTexture->getRGBDepthBitsPerPixel() == 32) {
		auto textureData = diffuseTexture->getRGBTextureData();
		for (auto i = 0; i < diffuseTexture->getTextureWidth() * diffuseTexture->getTextureHeight(); i++) {
			auto alpha = textureData.get(i * 4 + 3);
			if (alpha != 255) diffuseTextureTransparency = true;
			if (alpha > 5 || alpha < 250) diffuseTextureMaskedTransparencyTest = false;
		}
	}
	if (diffuseTextureMaskedTransparency == false) diffuseTextureMaskedTransparency = diffuseTextureMaskedTransparencyTest;
}

void SpecularMaterialProperties::setSpecularTexture(Texture* specularTexture) {
	if (this->specularTexture == specularTexture) return;
	if (this->specularTexture != nullptr) this->specularTexture->releaseReference();
	specularTexturePathName.clear();
	specularTextureFileName = specularTexture->getId();
	specularTexture->acquireReference();
	this->specularTexture = specularTexture;
}

void SpecularMaterialProperties::setSpecularTexture(const string& pathName, const string& fileName)
{
	if (specularTexture != nullptr) specularTexture->releaseReference();
	specularTexture = nullptr;
	specularTexturePathName = pathName;
	specularTextureFileName = fileName;
	specularTexture = TextureReader::read(pathName, fileName);
}

void SpecularMaterialProperties::setNormalTexture(Texture* normalTexture) {
	if (this->normalTexture == normalTexture) return;
	if (this->normalTexture != nullptr) this->normalTexture->releaseReference();
	normalTexturePathName.clear();
	normalTextureFileName = normalTexture->getId();
	normalTexture->acquireReference();
	this->normalTexture = normalTexture;
}

void SpecularMaterialProperties::setNormalTexture(const string& pathName, const string& fileName)
{
	if (normalTexture != nullptr) normalTexture->releaseReference();
	normalTexturePathName = pathName;
	normalTextureFileName = fileName;
	normalTexture = TextureReader::read(pathName, fileName);
}
