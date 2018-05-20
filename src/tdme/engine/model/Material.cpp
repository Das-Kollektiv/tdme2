#include <tdme/engine/model/Material.h>

#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Math.h>
#include <tdme/utils/ByteBuffer.h>

using std::string;

using tdme::engine::model::Material;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureLoader;
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

const string& Material::getDiffuseTransparencyTexturePathName()
{
	return diffuseTransparencyTexturePathName;
}

const string& Material::getDiffuseTransparencyTextureFileName()
{
	return diffuseTransparencyTextureFileName;
}

void Material::setDiffuseTexture(const string& pathName, const string& fileName, const string& transparencyPathName, const string& transparencyFileName)
{
	// load diffuse texture
	diffuseTexturePathName = pathName;
	diffuseTextureFileName = fileName;
	diffuseTexture = TextureLoader::loadTexture(pathName, fileName);
	diffuseTransparencyTexturePathName = "";
	diffuseTransparencyTextureFileName = "";
	// check if we have a additional transparency texture
	if (transparencyFileName.length() != 0) {
		diffuseTransparencyTexturePathName = transparencyPathName;
		diffuseTransparencyTextureFileName = transparencyFileName;
		// yep
		auto transparencyTexture = TextureLoader::loadTexture(transparencyPathName, transparencyFileName);
		// laoded?
		if (transparencyTexture != nullptr) {
			// same dimensions and supported pixel depth?
			if (diffuseTexture->getWidth() == transparencyTexture->getWidth() &&
				diffuseTexture->getHeight() == transparencyTexture->getHeight()) {
				// yep, combine diffuse map + diffuse transparency map
				int width = diffuseTexture->getWidth();
				int height = diffuseTexture->getHeight();
				ByteBuffer* pixelByteBuffer = new ByteBuffer(diffuseTexture->getWidth() * diffuseTexture->getHeight() * 4);
				auto diffuseTextureWithTransparency = new Texture(
					diffuseTexture->getId() + "+transparency",
					32,
					diffuseTexture->getWidth(),
					diffuseTexture->getHeight(),
					diffuseTexture->getTextureWidth(),
					diffuseTexture->getTextureHeight(),
					pixelByteBuffer
				);
				int diffuseTextureBytesPerPixel = diffuseTexture->getDepth() / 8;
				int transparencyTextureBytesPerPixel = diffuseTexture->getDepth() / 8;
				for (int y = 0; y < height; y++)
				for (int x = 0; x < width; x++) {
					pixelByteBuffer->put(diffuseTexture->getTextureData()->get((y * width * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 0));
					pixelByteBuffer->put(diffuseTexture->getTextureData()->get((y * width * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 1));
					pixelByteBuffer->put(diffuseTexture->getTextureData()->get((y * width * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 2));
					pixelByteBuffer->put(
						(uint8_t)((
							transparencyTexture->getTextureData()->get((y * width * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 0) +
							transparencyTexture->getTextureData()->get((y * width * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 1) +
							transparencyTexture->getTextureData()->get((y * width * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 2)
						) * 0.33f)
					);
				}
				delete diffuseTexture;
				diffuseTexture = diffuseTextureWithTransparency;
			}
			delete transparencyTexture;
		}
	}
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

bool Material::hasDiffuseTextureMaskedTransparency() {
	return diffuseTextureMaskedTransparency;
}

void Material::setDiffuseTextureMaskedTransparency(bool maskedTransparency) {
	diffuseTextureMaskedTransparency = maskedTransparency;
}

float Material::getDiffuseTextureMaskedTransparencyThreshold() {
	return diffuseTextureMaskedTransparencyThreshold;
}

void Material::setDiffuseTextureMaskedTransparencyThreshold(float maskedTransparencyThreshold) {
	diffuseTextureMaskedTransparencyThreshold = maskedTransparencyThreshold;
}

void Material::checkDiffuseTextureTransparency()
{
	// TODO: check if masked transparency is used
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

bool Material::hasColorTransparency()
{
	return diffuseColor.getAlpha() < 1.0f - Math::EPSILON;
}

bool Material::hasTextureTransparency()
{
	return diffuseTextureTransparency == true && diffuseTextureMaskedTransparency == false;
}

string Material::defaultMaterialId = "tdme.default_material";
Material* Material::defaultMaterial = new Material(Material::defaultMaterialId);
