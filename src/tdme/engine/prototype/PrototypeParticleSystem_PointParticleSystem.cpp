#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleSystem.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/tools/FileSystemTools.h>
#include <tdme/engine/Texture.h>

using std::string;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::tools::FileSystemTools;
using tdme::engine::Texture;

using tdme::engine::prototype::PrototypeParticleSystem_PointParticleSystem;

PrototypeParticleSystem_PointParticleSystem::PrototypeParticleSystem_PointParticleSystem()
{
}

void PrototypeParticleSystem_PointParticleSystem::setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName) {
	if (texture != nullptr) texture->releaseReference();
	texture = nullptr;
	this->textureFileName = textureFileName;
	this->transparencyTextureFileName = transparencyTextureFileName;
	if (this->transparencyTextureFileName.empty() == false && this->textureFileName.empty() == false) {
		texture = TextureReader::read2(
			FileSystemTools::getPathName(this->textureFileName),
			FileSystemTools::getFileName(this->textureFileName),
			FileSystemTools::getPathName(this->transparencyTextureFileName),
			FileSystemTools::getFileName(this->transparencyTextureFileName)
		);
	} else
	if (this->textureFileName.empty() == false) {
		texture = TextureReader::read(
			FileSystemTools::getPathName(this->textureFileName),
			FileSystemTools::getFileName(this->textureFileName)
		);
	}
}

PrototypeParticleSystem_PointParticleSystem::~PrototypeParticleSystem_PointParticleSystem() {
	if (texture != nullptr) texture->releaseReference();;
}

Texture* PrototypeParticleSystem_PointParticleSystem::getTextureReference() {
	if (texture != nullptr) texture->acquireReference();
	return texture;
}
