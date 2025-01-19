#include <agui/gui/textures/GUITextureManager.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/renderer/GUIRendererBackend.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/os/threading/Mutex.h>
#include <agui/utilities/Console.h>

using std::string;
using std::unordered_map;

using agui::gui::renderer::GUIRendererBackend;
using agui::gui::textures::GUITexture;
using agui::gui::textures::GUITextureManager;
using agui::os::threading::Mutex;
using agui::utilities::Console;

GUITextureManager::GUITextureManager(GUIRendererBackend* renderer): mutex("texturemanager-mutex") {
	this->renderer = renderer;
}

GUITextureManager::~GUITextureManager() {
	for (const auto& [textureManagedId, textureManaged]: textures) delete textureManaged;
}

GUITextureManager::GUIManagedTexture* GUITextureManager::addTexture(const string& id, bool& created)
{
	// check if we already manage this texture
	mutex.lock();
	auto textureManagedIt = textures.find(id);
	if (textureManagedIt != textures.end()) {
		//
		auto textureManaged = textureManagedIt->second;
		textureManaged->incrementReferenceCounter();
		mutex.unlock();
		// yep, return renderer texture id
		created = false;
		return textureManaged;
	}
	// create texture
	auto textureId = renderer->createTexture();
	// create managed texture
	auto textureManaged = new GUIManagedTexture(id, textureId);
	// add it to our textures
	textureManaged->incrementReferenceCounter();
	textures[id] = textureManaged;
	//
	mutex.unlock();
	//
	created = true;
	return textureManaged;
}

int32_t GUITextureManager::addTexture(GUITexture* texture, int contextIdx)
{
	bool created;
	auto textureManaged = addTexture(texture->getId(), created);
	auto rendererId = textureManaged->getRendererId();

	// upload if it was created
	if (created == true) {
		// bind texture
		renderer->bindTexture(contextIdx, rendererId);
		// upload texture
		renderer->uploadTexture(contextIdx, texture);
		// unbind texture
		renderer->bindTexture(contextIdx, renderer->ID_NONE);
		//
		textureManaged->setUploaded(true);
	}

	// return renderer id
	return rendererId;
}

void GUITextureManager::removeTexture(const string& textureId)
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
