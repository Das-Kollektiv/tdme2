#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleSystem.h>

#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/tools/editor/misc/Tools.h>

using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::tools::editor::misc::Tools;

using tdme::engine::prototype::PrototypeParticleSystem_PointParticleSystem;

PrototypeParticleSystem_PointParticleSystem::PrototypeParticleSystem_PointParticleSystem()
{
}

void PrototypeParticleSystem_PointParticleSystem::setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName) {
	if (texture != nullptr) texture->releaseReference();;
	texture = nullptr;
	this->textureFileName = textureFileName;
	this->transparencyTextureFileName = transparencyTextureFileName;
	if (this->transparencyTextureFileName.size() > 0) {
		texture = TextureReader::read(
			Tools::getPathName(this->textureFileName),
			Tools::getFileName(this->textureFileName),
			Tools::getPathName(this->transparencyTextureFileName),
			Tools::getFileName(this->transparencyTextureFileName)
		);
	} else {
		texture = TextureReader::read(
			Tools::getPathName(this->textureFileName),
			Tools::getFileName(this->textureFileName)
		);
	}
}

PrototypeParticleSystem_PointParticleSystem::~PrototypeParticleSystem_PointParticleSystem() {
	if (texture != nullptr) texture->releaseReference();;
}
