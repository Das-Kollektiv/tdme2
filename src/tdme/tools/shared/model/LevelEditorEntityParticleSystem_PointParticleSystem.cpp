#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleSystem.h>

#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/tools/shared/tools/Tools.h>

using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::tools::shared::tools::Tools;

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;

LevelEditorEntityParticleSystem_PointParticleSystem::LevelEditorEntityParticleSystem_PointParticleSystem() 
{
	maxPoints = 4000;
	pointSize = 10.0f;
	textureFileName = "";
	texture = nullptr;
	autoEmit = true;
}

void LevelEditorEntityParticleSystem_PointParticleSystem::setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName) {
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

LevelEditorEntityParticleSystem_PointParticleSystem::~LevelEditorEntityParticleSystem_PointParticleSystem() {
	if (texture != nullptr) texture->releaseReference();;
}
