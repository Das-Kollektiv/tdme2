#include <tdme/engine/subsystems/manager/TextureManager.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::unordered_map;

using tdme::engine::Texture;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::os::threading::Mutex;
using tdme::utilities::Console;;

TextureManager::TextureManager(RendererBackend* rendererBackend): mutex("texturemanager-mutex") {
	this->rendererBackend = rendererBackend;
}

TextureManager::~TextureManager() {
	for (const auto& [textureManagedId, textureManaged]: textures) delete textureManaged;
}

TextureManager::ManagedTexture* TextureManager::addTexture(const string& id, bool& created)
{
	// check if we already manage this texture
	mutex.lock();
	auto textureManagedIt = textures.find(id);
	if (textureManagedIt != textures.end()) {
		//
		auto textureManaged = textureManagedIt->second;
		textureManaged->incrementReferenceCounter();
		mutex.unlock();
		// yep, return renderer backend texture id
		created = false;
		return textureManaged;
	}
	// create texture
	auto textureId = rendererBackend->createTexture();
	// create managed texture
	auto managedTexture = new ManagedTexture(id, textureId);
	// add it to our textures
	managedTexture->incrementReferenceCounter();
	textures[id] = managedTexture;
	//
	mutex.unlock();
	//
	created = true;
	return managedTexture;
}

int32_t TextureManager::addTexture(Texture* texture, int contextIdx)
{
	bool created;
	auto textureManaged = addTexture(texture->getId(), created);
	auto rendererId = textureManaged->getRendererId();

	// upload if it was created
	if (created == true) {
		// bind texture
		rendererBackend->bindTexture(contextIdx, rendererId);
		// upload texture
		rendererBackend->uploadTexture(contextIdx, texture);
		// unbind texture
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		//
		textureManaged->setUploaded(true);
	}

	// return renderer id
	return rendererId;
}

int32_t TextureManager::addCubeMapTexture(const string& id, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack, int contextIdx)
{
	bool created;
	auto textureManaged = addTexture(id, created);
	auto rendererId = textureManaged->getRendererId();

	// upload if it was created
	if (created == true) {
		// bind texture
		rendererBackend->bindCubeMapTexture(contextIdx, rendererId);
		// upload texture
		rendererBackend->uploadCubeMapTexture(contextIdx, textureLeft, textureRight, textureTop, textureBottom, textureFront, textureBack);
		// unbind texture
		rendererBackend->bindCubeMapTexture(contextIdx, rendererBackend->ID_NONE);
		//
		textureManaged->setUploaded(true);
	}

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
			rendererBackend->disposeTexture(textureRendererId);
			delete textureManaged;
			//
			return;
		}
		//
		mutex.unlock();
		return;
	}
	mutex.unlock();
	Console::printLine(string("Warning: texture not loaded by texture manager: " + textureId));
}
