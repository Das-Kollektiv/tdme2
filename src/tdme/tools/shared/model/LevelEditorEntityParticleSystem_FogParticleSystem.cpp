#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_FogParticleSystem.h>

#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/tools/shared/tools/Tools.h>

using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::tools::shared::tools::Tools;

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_FogParticleSystem;

LevelEditorEntityParticleSystem_FogParticleSystem::LevelEditorEntityParticleSystem_FogParticleSystem()
{
}

void LevelEditorEntityParticleSystem_FogParticleSystem::setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName) {
	if (texture != nullptr) texture->releaseReference();;
	texture = nullptr;
	this->textureFileName = textureFileName;
	this->transparencyTextureFileName = transparencyTextureFileName;
	if (this->transparencyTextureFileName.size() > 0) {
		texture = TextureReader::read(
			Tools::getPath(this->textureFileName),
			Tools::getFileName(this->textureFileName),
			Tools::getPath(this->transparencyTextureFileName),
			Tools::getFileName(this->transparencyTextureFileName)
		);
	} else {
		texture = TextureReader::read(
			Tools::getPath(this->textureFileName),
			Tools::getFileName(this->textureFileName)
		);
	}
}

LevelEditorEntityParticleSystem_FogParticleSystem::~LevelEditorEntityParticleSystem_FogParticleSystem() {
	if (texture != nullptr) texture->releaseReference();;
}
