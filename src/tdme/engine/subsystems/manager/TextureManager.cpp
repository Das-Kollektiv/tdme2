#include <tdme/engine/subsystems/manager/TextureManager.h>

#include <map>
#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager_TextureManaged.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/utils/Console.h>

using std::map;
using std::string;

using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::Console;;

TextureManager::TextureManager(GLRenderer* renderer) 
{
	this->renderer = renderer;
}

TextureManager::~TextureManager() {
	for (auto it = textures.begin(); it != textures.end(); ++it) {
		delete it->second;
	}
}

int32_t TextureManager::addTexture(Texture* texture)
{
	// check if we already manage this texture
	auto textureManagedIt = textures.find(texture->getId());
	if (textureManagedIt != textures.end()) {
		//
		auto textureManaged = textureManagedIt->second;
		textureManaged->incrementReferenceCounter();
		// yep, return open renderer id
		return textureManaged->getRendererId();
	}
	// create texture
	auto textureId = renderer->createTexture();
	// bind texture
	renderer->bindTexture(textureId);
	// upload texture
	renderer->uploadTexture(texture);
	// unbind texture
	renderer->bindTexture(renderer->ID_NONE);
	// create managed texture
	auto textureManaged = new TextureManager_TextureManaged(texture->getId(), textureId);
	// add it to our textures
	textureManaged->incrementReferenceCounter();
	textures[texture->getId()] = textureManaged;
	// return renderer id
	return textureId;
}

void TextureManager::removeTexture(const string& textureId)
{
	auto textureManagedIt = textures.find(textureId);
	if (textureManagedIt != textures.end()) {
		auto textureManaged = textureManagedIt->second;
		if (textureManaged->decrementReferenceCounter()) {
			// delete texture
			renderer->disposeTexture(textureManaged->getRendererId());
			// remove from our list
			textures.erase(textureManagedIt);
			delete textureManaged;
		}
		return;
	}
	Console::println(string("Warning: texture not loaded by texture manager"));
}
