#include <tdme/engine/prototype/PrototypeParticleSystem_FogParticleSystem.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/tools/editor/misc/Tools.h>

using std::string;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::tools::editor::misc::Tools;

using tdme::engine::prototype::PrototypeParticleSystem_FogParticleSystem;

PrototypeParticleSystem_FogParticleSystem::PrototypeParticleSystem_FogParticleSystem()
{
}

void PrototypeParticleSystem_FogParticleSystem::setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName) {
	if (texture != nullptr) texture->releaseReference();
	texture = nullptr;
	this->textureFileName = textureFileName;
	this->transparencyTextureFileName = transparencyTextureFileName;
	if (this->transparencyTextureFileName.empty() == false && this->textureFileName.empty() == false) {
		texture = TextureReader::read2(
			Tools::getPathName(this->textureFileName),
			Tools::getFileName(this->textureFileName),
			Tools::getPathName(this->transparencyTextureFileName),
			Tools::getFileName(this->transparencyTextureFileName)
		);
	} else
	if (this->textureFileName.empty() == false) {
		texture = TextureReader::read(
			Tools::getPathName(this->textureFileName),
			Tools::getFileName(this->textureFileName)
		);
	}
}

PrototypeParticleSystem_FogParticleSystem::~PrototypeParticleSystem_FogParticleSystem() {
	if (texture != nullptr) texture->releaseReference();
}

Texture* PrototypeParticleSystem_FogParticleSystem::getTextureReference() {
	if (texture != nullptr) texture->acquireReference();
	return texture;
}
