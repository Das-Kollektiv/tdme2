#include <tdme/engine/subsystems/manager/TextureManager.h>

#include <map>
#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager_TextureManaged.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utils/Console.h>

using std::map;
using std::string;

using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::threading::Mutex;
using tdme::utils::Console;;

TextureManager::TextureManager(Renderer* renderer): mutex("texturemanager-mutex") {
	this->renderer = renderer;
}

TextureManager::~TextureManager() {
	for (auto it = textures.begin(); it != textures.end(); ++it) {
		delete it->second;
	}
}

TextureManager_TextureManaged* TextureManager::addTexture(const string& id)
{
	// check if we already manage this texture
	mutex.lock();
	auto textureManagedIt = textures.find(id);
	if (textureManagedIt != textures.end()) {
		//
		auto textureManaged = textureManagedIt->second;
		textureManaged->incrementReferenceCounter();
		auto textureId = textureManaged->getRendererId();
		mutex.unlock();
		// yep, return renderer texture id
		return textureManaged;
	}
	// create texture
	auto textureId = renderer->createTexture();
	// create managed texture
	auto textureManaged = new TextureManager_TextureManaged(id, textureId);
	// add it to our textures
	textureManaged->incrementReferenceCounter();
	textures[id] = textureManaged;
	//
	mutex.unlock();
	//
	return textureManaged;
}

int32_t TextureManager::addTexture(Texture* texture)
{
	auto textureManaged = addTexture(texture->getId());
	auto rendererId = textureManaged->getRendererId();
	auto context = renderer->getDefaultContext();

	// bind texture
	renderer->bindTexture(context, rendererId);
	// upload texture
	renderer->uploadTexture(context, texture);
	// unbind texture
	renderer->bindTexture(context, renderer->ID_NONE);

	// return renderer id
	return rendererId;
}

void TextureManager::removeTexture(const string& textureId)
{
	mutex.lock();
	auto textureManagedIt = textures.find(textureId);
	if (textureManagedIt != textures.end()) {
		auto textureManaged = textureManagedIt->second;
		if (textureManaged->decrementReferenceCounter()) {
			// delete texture
			auto textureRendererId = textureManaged->getRendererId();
			// remove from our list
			textures.erase(textureManagedIt);
			//
			mutex.unlock();
			// remove from renderer
			renderer->disposeTexture(textureRendererId);
			delete textureManaged;
		}
		//
		mutex.unlock();
		return;
	}
	mutex.unlock();
	Console::println(string("Warning: texture not loaded by texture manager"));
}
