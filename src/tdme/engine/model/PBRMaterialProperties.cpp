#include <tdme/engine/model/PBRMaterialProperties.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/Color4.h>

using std::string;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::Color4;
using tdme::engine::model::PBRMaterialProperties;

PBRMaterialProperties::PBRMaterialProperties()
{
	baseColorFactor.set(1.0f, 1.0f, 1.0f, 1.0f);
	baseColorTexture = nullptr;
	baseColorTextureTransparency = false;
	baseColorTextureMaskedTransparency = false;
	baseColorTextureMaskedTransparencyThreshold = 0.1f;
	metallicFactor = 1.0f;
	roughnessFactor = 1.0f;
	metallicRoughnessTexture = nullptr;
	normalScale = 1.0f;
	normalTexture = nullptr;
	emissiveTexture = nullptr;
	emissiveFactor.set(1.0f, 1.0f, 1.0f, 1.0f);
	exposure = 1.0f;
}

PBRMaterialProperties::~PBRMaterialProperties() {
	if (baseColorTexture != nullptr) baseColorTexture->releaseReference();
	if (metallicRoughnessTexture != nullptr) metallicRoughnessTexture->releaseReference();
	if (normalTexture != nullptr) normalTexture->releaseReference();
}

void PBRMaterialProperties::setBaseColorTexture(Texture* baseColorTexture) {
	if (this->baseColorTexture == baseColorTexture) return;
	if (this->baseColorTexture != nullptr) this->baseColorTexture->releaseReference();
	baseColorTexturePathName.clear();
	baseColorTextureFileName = baseColorTexture->getId();
	baseColorTexture->acquireReference();
	this->baseColorTexture = baseColorTexture;
	checkBaseColorTextureTransparency();
}

void PBRMaterialProperties::setBaseColorTexture(const string& pathName, const string& fileName)
{
	if (baseColorTexture != nullptr) baseColorTexture->releaseReference();
	baseColorTexturePathName = pathName;
	baseColorTextureFileName = fileName;
	baseColorTexture = TextureReader::read(pathName, fileName);
	checkBaseColorTextureTransparency();
}

void PBRMaterialProperties::setMetallicRoughnessTexture(Texture* metallicRoughnessTexture) {
	if (this->metallicRoughnessTexture == metallicRoughnessTexture) return;
	if (this->metallicRoughnessTexture != nullptr) this->metallicRoughnessTexture->releaseReference();
	metallicRoughnessTexturePathName.clear();
	metallicRoughnessTextureFileName = metallicRoughnessTexture->getId();
	metallicRoughnessTexture->acquireReference();
	this->metallicRoughnessTexture = metallicRoughnessTexture;
}

void PBRMaterialProperties::setMetallicRoughnessTexture(const string& pathName, const string& fileName)
{
	if (metallicRoughnessTexture != nullptr) metallicRoughnessTexture->releaseReference();
	metallicRoughnessTexturePathName = pathName;
	metallicRoughnessTextureFileName = fileName;
	metallicRoughnessTexture = TextureReader::read(pathName, fileName);
}

void PBRMaterialProperties::setNormalTexture(Texture* normalTexture) {
	if (this->normalTexture == normalTexture) return;
	if (this->normalTexture != nullptr) this->normalTexture->releaseReference();
	normalTexturePathName.clear();
	normalTextureFileName = normalTexture->getId();
	normalTexture->acquireReference();
	this->normalTexture = normalTexture;
}

void PBRMaterialProperties::setNormalTexture(const string& pathName, const string& fileName)
{
	if (normalTexture != nullptr) normalTexture->releaseReference();
	normalTexturePathName = pathName;
	normalTextureFileName = fileName;
	normalTexture = TextureReader::read(pathName, fileName);
}

void PBRMaterialProperties::setEmissiveTexture(Texture* emissiveTexture) {
	if (this->emissiveTexture == emissiveTexture) return;
	if (this->emissiveTexture != nullptr) this->emissiveTexture->releaseReference();
	emissiveTexturePathName.clear();
	emissiveTextureFileName = emissiveTexture->getId();
	emissiveTexture->acquireReference();
	this->emissiveTexture = emissiveTexture;
}

void PBRMaterialProperties::setEmissiveTexture(const string& pathName, const string& fileName) {
	if (emissiveTexture != nullptr) emissiveTexture->releaseReference();
	emissiveTexturePathName = pathName;
	emissiveTextureFileName = fileName;
	emissiveTexture = TextureReader::read(pathName, fileName);
}

void PBRMaterialProperties::checkBaseColorTextureTransparency()
{
	baseColorTextureTransparency = false;
	auto baseColorTextureMaskedTransparencyTest = true;
	if (baseColorTexture != nullptr && baseColorTexture->getRGBDepthBitsPerPixel() == 32) {
		auto textureData = baseColorTexture->getRGBTextureData();
		for (auto i = 0; i < baseColorTexture->getTextureWidth() * baseColorTexture->getTextureHeight(); i++) {
			auto alpha = textureData.get(i * 4 + 3);
			if (alpha != 255) baseColorTextureTransparency = true;
			if (alpha > 5 || alpha < 250) baseColorTextureMaskedTransparencyTest = false;
		}
	}
	if (baseColorTextureMaskedTransparency == false) baseColorTextureMaskedTransparency = baseColorTextureMaskedTransparencyTest;
}
