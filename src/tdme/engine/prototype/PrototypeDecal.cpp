#include <tdme/engine/prototype/PrototypeDecal.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/tools/editor/misc/Tools.h>

using std::string;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::tools::editor::misc::Tools;

using tdme::engine::prototype::PrototypeDecal;

PrototypeDecal::PrototypeDecal()
{
}

void PrototypeDecal::setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName) {
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

PrototypeDecal::~PrototypeDecal() {
	if (texture != nullptr) texture->releaseReference();;
}

Texture* PrototypeDecal::getTextureReference() {
	if (texture != nullptr) texture->acquireReference();
	return texture;
}
