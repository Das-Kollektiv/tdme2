#include <tdme/engine/fileio/textures/TextureReader.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/ByteBuffer.h>

#include <tdme/engine/fileio/textures/PNGTextureReader.h>
#include <tdme/engine/Texture.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Vector2.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::engine::fileio::textures::TextureReader;

using tdme::engine::fileio::textures::PNGTextureReader;
using tdme::engine::Texture;
using tdme::math::Matrix3x3;
using tdme::math::Vector2;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Mutex;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

vector<string> TextureReader::extensions = {"png"};
Mutex TextureReader::textureCacheMutex ("texturecache-mutex");
unordered_map<string, Texture*> TextureReader::textureCache;

const vector<string>& TextureReader::getTextureExtensions() {
	return extensions;
}

Texture* TextureReader::read(const string& pathName, const string& fileName, bool useCache, bool powerOfTwo, const string& idPrefix)
{
	Texture* texture = nullptr;

	// make canonical
	auto canonicalFilePath = FileSystem::getInstance()->getCanonicalPath(pathName, fileName);
	auto canonicalPathName = FileSystem::getInstance()->getPathName(canonicalFilePath);
	auto canonicalFileName = FileSystem::getInstance()->getFileName(canonicalFilePath);

	// do cache look up
	if (useCache == true) {
		textureCacheMutex.lock();
		auto textureCacheIt = textureCache.find(idPrefix + canonicalFilePath);
		if (textureCacheIt != textureCache.end()) {
			texture = textureCacheIt->second;
		}
	}

	// have texture?
	if (texture == nullptr) {
		// nope try to load
		try {
			if (StringTools::endsWith(StringTools::toLowerCase(canonicalFileName), ".png") == true) {

				// create PNG input stream
				vector<uint8_t> data;
				FileSystem::getInstance()->getContent(pathName, fileName, data);

				texture = PNGTextureReader::read(canonicalFilePath, data, powerOfTwo, idPrefix);
				if (texture != nullptr && useCache == true) {
					textureCache[texture->getId()] = texture;
				}
			}
		} catch (Exception& exception) {
			Console::println("TextureReader::read(): Could not load texture: " + canonicalPathName + "/" + canonicalFileName + ": " + (exception.what()));
		}
	} else {
		texture->acquireReference();
	}

	//
	if (useCache == true) textureCacheMutex.unlock();

	// done
	return texture;
}

Texture* TextureReader::read2(const string& texturePathName, const string& textureFileName, const string& transparencyTexturePathName, const string& transparencyTextureFileName, bool useCache, bool powerOfTwo, const string& idPrefix) {
	// make canonical
	auto canonicalFile = FileSystem::getInstance()->getCanonicalPath(texturePathName, textureFileName);
	auto canonicalPathName = FileSystem::getInstance()->getPathName(canonicalFile);
	auto canonicalFileName = FileSystem::getInstance()->getFileName(canonicalFile);
	auto cacheId = idPrefix + canonicalPathName + "/" + canonicalFileName + "/transparency";

	// do cache look up
	if (useCache == true) {
		textureCacheMutex.lock();
		auto textureCacheIt = textureCache.find(cacheId);
		if (textureCacheIt != textureCache.end()) {
			auto texture = textureCacheIt->second;
			texture->acquireReference();
			textureCacheMutex.unlock();
			return texture;
		}
	}

	// load diffuse texture
	auto texture = unique_ptr<Texture, decltype([](Texture* texture){ texture->releaseReference(); })>(TextureReader::read(texturePathName, textureFileName, false, powerOfTwo, idPrefix));
	if (texture == nullptr) {
		if (useCache == true) textureCacheMutex.unlock();
		return nullptr;
	}
	// additional transparency texture
	auto transparencyTexture = unique_ptr<Texture, decltype([](Texture* texture){ texture->releaseReference(); })>(TextureReader::read(transparencyTexturePathName, transparencyTextureFileName, false, powerOfTwo, idPrefix));
	// do we have one?
	if (transparencyTexture == nullptr) {
		Console::println("TextureReader::read2(): transparency texture: failed: " + texturePathName + "/" + textureFileName + ";" + transparencyTexturePathName + "/" + transparencyTextureFileName);
		if (useCache == true) {
			textureCache[cacheId] = texture.get();
			textureCacheMutex.unlock();
		}
		return texture.release();
	}
	// same dimensions and supported pixel depth?
	if (texture->getTextureWidth() != transparencyTexture->getTextureWidth() || texture->getTextureHeight() != transparencyTexture->getTextureHeight()) {
		Console::println("TextureReader::read2(): texture does not match transparency texture dimension: " + texturePathName + "/" + textureFileName + ";" + transparencyTexturePathName + "/" + transparencyTextureFileName);
		if (useCache == true) {
			textureCache[cacheId] = texture.get();
			textureCacheMutex.unlock();
		}
		return texture.release();
	}
	// yep, combine diffuse map + diffuse transparency map
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto textureByteBuffer = ByteBuffer(textureWidth * textureHeight * 4);
	auto diffuseTextureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;
	auto transparencyTextureBytesPerPixel = transparencyTexture->getRGBDepthBitsPerPixel() / 8;
	auto transparencyTextureTextureData = transparencyTexture->getRGBTextureData();
	auto textureTextureData = texture->getRGBTextureData();
	for (auto y = 0; y < textureHeight; y++) {
		for (auto x = 0; x < textureWidth; x++) {
			auto transparencyTextureRed = transparencyTextureTextureData.get((y * textureWidth * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 0);
			auto transparencyTextureGreen = transparencyTextureTextureData.get((y * textureWidth * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 1);
			auto transparencyTextureBlue = transparencyTextureTextureData.get((y * textureWidth * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 2);
			textureByteBuffer.put(textureTextureData.get((y * textureWidth * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 0));
			textureByteBuffer.put(textureTextureData.get((y * textureWidth * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 1));
			textureByteBuffer.put(textureTextureData.get((y * textureWidth * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 2));
			textureByteBuffer.put((uint8_t)((transparencyTextureRed + transparencyTextureGreen + transparencyTextureBlue) * 0.3333f));
		}
	}
	//
	auto textureWithTransparency =
		unique_ptr<
			Texture,
			decltype([](Texture* texture){ texture->releaseReference(); })
		>(
			new Texture(
				idPrefix + texture->getId() + "/transparency",
				Texture::TEXTUREDEPTH_RGBA,
				Texture::TEXTUREFORMAT_RGBA_PNG,
				texture->getWidth(),
				texture->getHeight(),
				texture->getTextureWidth(),
				texture->getTextureHeight(),
				Texture::TEXTUREFORMAT_RGBA,
				textureByteBuffer
			)
		);
	textureWithTransparency->acquireReference();
	if (useCache == true) {
		textureCache[cacheId] = textureWithTransparency.get();
		textureCacheMutex.unlock();
	}
	return textureWithTransparency.release();
}

void TextureReader::scaleTextureLine(const ByteBuffer& pixelByteBuffer, ByteBuffer& pixelByteBufferScaled, int width, int textureWidth, int bytesPerPixel, int y) {
	auto textureXIncrement = (float)textureWidth / (float)width;
	auto textureXPixelRest = 0.0f;
	auto textureX = 0;
	for (auto x = 0; x < width; x++) {
		for (auto i = 0; i < (int)textureXIncrement + (int)textureXPixelRest; i++) {
			for (auto bytePerPixel = 0; bytePerPixel < bytesPerPixel; bytePerPixel++) {
				pixelByteBufferScaled.put(pixelByteBuffer.get((y * width * bytesPerPixel) + (x * bytesPerPixel) + bytePerPixel));
			}
			textureX++;
		}
		textureXPixelRest-= (int)textureXPixelRest;
		textureXPixelRest+= textureXIncrement - (int)textureXIncrement;
	}
	{
		auto x = width - 1;
		while (textureX < textureWidth) {
			for (auto bytePerPixel = 0; bytePerPixel < bytesPerPixel; bytePerPixel++) {
				pixelByteBufferScaled.put(pixelByteBuffer.get((y * width * bytesPerPixel) + (x * bytesPerPixel) + bytePerPixel));
			}
			textureX++;
		}
	}
}

void TextureReader::removeFromCache(Texture* texture) {
	textureCacheMutex.lock();
	auto textureCacheIt = textureCache.find(texture->getId());
	if (textureCacheIt != textureCache.end()) textureCache.erase(textureCacheIt);
	textureCacheMutex.unlock();
}

Texture* TextureReader::rotate(Texture* texture, float rotation, const string& idSuffix) {
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto textureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;
	auto textureWidthRotated = -1;
	auto textureHeightRotated = -1;
	{
		auto rotationsMatrix = Matrix3x3::rotateAroundPoint(Vector2(textureWidth / 2.0f, textureHeight / 2.0f), rotation);
		Vector2 leftTop(0.0f, 0.0f);
		Vector2 rightTop(textureWidth, 0.0f);
		Vector2 leftBottom(0.0f, textureHeight);
		Vector2 rightBottom(textureWidth, textureHeight);
		auto leftTopRotated = rotationsMatrix.multiply(leftTop);
		auto rightTopRotated = rotationsMatrix.multiply(rightTop);
		auto leftBottomRotated = rotationsMatrix.multiply(leftBottom);
		auto rightBottomRotated = rotationsMatrix.multiply(rightBottom);
		auto textureWidthTransformedMin = Math::min(leftTopRotated.getX(),
				Math::min(rightTopRotated.getX(),
						Math::min(leftBottomRotated.getX(),
								rightBottomRotated.getX())));
		auto textureWidthTransformedMax = Math::max(leftTopRotated.getX(),
				Math::max(rightTopRotated.getX(),
						Math::max(leftBottomRotated.getX(),
								rightBottomRotated.getX())));
		auto textureHeightTransformedMin = Math::min(leftTopRotated.getY(),
				Math::min(rightTopRotated.getY(),
						Math::min(leftBottomRotated.getY(),
								rightBottomRotated.getY())));
		auto textureHeightTransformedMax = Math::max(leftTopRotated.getY(),
				Math::max(rightTopRotated.getY(),
						Math::max(leftBottomRotated.getY(),
								rightBottomRotated.getY())));
		textureWidthRotated = static_cast<int>(textureWidthTransformedMax
				- textureWidthTransformedMin);
		textureHeightRotated = static_cast<int>(textureHeightTransformedMax
				- textureHeightTransformedMin);
	}
	auto textureTextureData = texture->getRGBTextureData();
	auto rotatedTextureByteBuffer = ByteBuffer(textureWidthRotated * textureHeightRotated * textureBytesPerPixel);
	auto rotationsMatrix = Matrix3x3::rotateAroundPoint(Vector2(textureWidth / 2.0f, textureHeight / 2.0f), rotation);
	for (auto y = 0; y < textureHeightRotated; y++) {
		for (auto x = 0; x < textureWidthRotated; x++) {
			auto originalTexturePoint = rotationsMatrix.multiply(
				Vector2(
					x - (textureWidthRotated - textureWidth) / 2.0f,
					y - (textureHeightRotated - textureHeight) / 2.0f
				)
			);
			auto red = 0;
			auto green = 0;
			auto blue = 0;
			auto alpha = 0;
			auto originalX = static_cast<int>(originalTexturePoint.getX());
			auto originalY = static_cast<int>(originalTexturePoint.getY());
			if (originalX >= 0 && originalX < textureWidth && originalY >= 0 && originalY < textureHeight) {
				red = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 0);
				green = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 1);
				blue = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 2);
				alpha = textureBytesPerPixel == 4?textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 3):255;
			}
			rotatedTextureByteBuffer.put(red);
			rotatedTextureByteBuffer.put(green);
			rotatedTextureByteBuffer.put(blue);
			if (textureBytesPerPixel == 4) rotatedTextureByteBuffer.put(alpha);
		}
	}
	//
	auto rotatedTexture =
		unique_ptr<
			Texture,
			decltype([](Texture* texture){ texture->releaseReference(); })
		>(
			new Texture(
				texture->getId() + idSuffix + ":tmp",
				textureBytesPerPixel == 4?Texture::TEXTUREDEPTH_RGBA:Texture::TEXTUREDEPTH_RGB,
				textureBytesPerPixel == 4?Texture::TEXTUREFORMAT_RGBA_PNG:Texture::TEXTUREFORMAT_RGB_PNG,
				textureWidthRotated,
				textureHeightRotated,
				textureWidthRotated,
				textureHeightRotated,
				textureBytesPerPixel == 4?Texture::TEXTUREFORMAT_RGBA:Texture::TEXTUREFORMAT_RGB,
				rotatedTextureByteBuffer
			)
		);
	rotatedTexture->acquireReference();
	// do smooooth
	return smooth(rotatedTexture.get(), idSuffix);
}

Texture* TextureReader::scale(Texture* texture, int width, int height, const string& idSuffix) {
	auto textureTextureData = texture->getRGBTextureData();
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto textureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;
	auto textureWidthScaled = width;
	auto textureHeightScaled = height;
	auto scaledTextureByteBuffer = ByteBuffer(textureWidthScaled * textureHeightScaled * textureBytesPerPixel);
	auto scaleX = static_cast<float>(textureWidth) / static_cast<float>(textureWidthScaled);
	auto scaleY = static_cast<float>(textureHeight) / static_cast<float>(textureHeightScaled);
	for (auto y = 0; y < textureHeightScaled; y++) {
		for (auto x = 0; x < textureWidthScaled; x++) {
			auto originalTexturePoint = Vector2(static_cast<float>(x) * scaleX, static_cast<float>(y) * scaleY);
			auto red = 0;
			auto green = 0;
			auto blue = 0;
			auto alpha = 0;
			auto originalX = static_cast<int>(originalTexturePoint.getX());
			auto originalY = static_cast<int>(originalTexturePoint.getY());
			if (originalX >= 0 && originalX < textureWidth && originalY >= 0 && originalY < textureHeight) {
				red = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 0);
				green = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 1);
				blue = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 2);
				alpha = textureBytesPerPixel == 4?textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 3):255;
			}
			scaledTextureByteBuffer.put(red);
			scaledTextureByteBuffer.put(green);
			scaledTextureByteBuffer.put(blue);
			if (textureBytesPerPixel == 4) scaledTextureByteBuffer.put(alpha);
		}
	}
	//
	auto scaledTexture =
		unique_ptr<
			Texture,
			decltype([](Texture* texture){ texture->releaseReference(); })
		>(
			new Texture(
				texture->getId() + idSuffix,
				textureBytesPerPixel == 4?Texture::TEXTUREDEPTH_RGBA:Texture::TEXTUREDEPTH_RGB,
				textureBytesPerPixel == 4?Texture::TEXTUREFORMAT_RGBA_PNG:Texture::TEXTUREFORMAT_RGB_PNG,
				textureWidthScaled,
				textureHeightScaled,
				textureWidthScaled,
				textureHeightScaled,
				textureBytesPerPixel == 4?Texture::TEXTUREFORMAT_RGBA:Texture::TEXTUREFORMAT_RGB,
				scaledTextureByteBuffer
			)
		);
	scaledTexture->acquireReference();
	// no smoothing if texture got smaller
	if (textureWidthScaled < textureWidth) return scaledTexture.release();
	// otherwise do smoothing
	return smooth(scaledTexture.get(), idSuffix);
}

Texture* TextureReader::smooth(Texture* texture, const string& idSuffix, float adjacentSampleWeight) {
	//
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto textureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;

	//
	auto textureTextureData = texture->getRGBTextureData();

	//
	auto filteredTextureByteBuffer = ByteBuffer(textureWidth * textureHeight * textureBytesPerPixel);
	for (auto y = 0; y < textureHeight; y++) {
		for (auto x = 0; x < textureWidth; x++) {
			auto samples = 0.0f;
			auto red = 0.0f;
			auto green = 0.0f;
			auto blue = 0.0f;
			auto alpha = 0.0f;
			{
				auto pixelOffset = (y * textureWidth * textureBytesPerPixel) + (x * textureBytesPerPixel);
				red+= textureTextureData.get(pixelOffset + 0) * 1.0f;
				green+= textureTextureData.get(pixelOffset + 1) * 1.0f;
				blue+= textureTextureData.get(pixelOffset + 2) * 1.0f;
				alpha+= (textureBytesPerPixel == 4?textureTextureData.get(pixelOffset + 3):255.0f) * 1.0f;
				samples+=1.0f;
			}
			for (auto _y = -1; _y <= 1; _y++) {
				for (auto _x = -1; _x <= 1; _x++) {
					if ((Math::abs(_x) == 1 && Math::abs(_y) == 1) == false &&
						(x + _x >= 0 && x + _x < textureWidth && y + _y >= 0 && y + _y < textureHeight)) {
						auto pixelOffset = ((y + _y) * textureWidth * textureBytesPerPixel) + ((x + _x) * textureBytesPerPixel);
						red+= textureTextureData.get(pixelOffset + 0) * adjacentSampleWeight;
						green+= textureTextureData.get(pixelOffset + 1) * adjacentSampleWeight;
						blue+= textureTextureData.get(pixelOffset + 2) * adjacentSampleWeight;
						alpha+= (textureBytesPerPixel == 4?textureTextureData.get(pixelOffset + 3):255.0f) * adjacentSampleWeight;
						samples+= adjacentSampleWeight;
					}
				}
			}
			filteredTextureByteBuffer.put(static_cast<uint8_t>(red / samples));
			filteredTextureByteBuffer.put(static_cast<uint8_t>(green / samples));
			filteredTextureByteBuffer.put(static_cast<uint8_t>(blue / samples));
			if (textureBytesPerPixel == 4) filteredTextureByteBuffer.put(static_cast<uint8_t>(alpha / samples));
		}
	}

	//
	auto filteredTexture =
		unique_ptr<
			Texture,
			decltype([](Texture* texture){ texture->releaseReference(); })
		>(
			new Texture(
				texture->getId() + idSuffix,
				textureBytesPerPixel == 4?Texture::TEXTUREDEPTH_RGBA:Texture::TEXTUREDEPTH_RGB,
				textureBytesPerPixel == 4?Texture::TEXTUREFORMAT_RGBA_PNG:Texture::TEXTUREFORMAT_RGB_PNG,
				textureWidth,
				textureHeight,
				textureWidth,
				textureHeight,
				textureBytesPerPixel == 4?Texture::TEXTUREFORMAT_RGBA:Texture::TEXTUREFORMAT_RGB,
				filteredTextureByteBuffer
			)
		);
	filteredTexture->acquireReference();
	return filteredTexture.release();
}
