#include <tdme/engine/subsystems/manager/TextureManager.h>

#include <map>
#include <string>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager_TextureManaged.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/utils/Console.h>

using std::map;
using std::wstring;

using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::Console;;

TextureManager::TextureManager(GLRenderer* renderer) 
{
	this->renderer = renderer;
}

int32_t TextureManager::addTexture(Texture* texture)
{
	auto textureManagedIt = textures.find(texture->getId());
	if (textureManagedIt != textures.end()) {
		auto textureManaged = textureManagedIt->second;
		textureManaged->incrementReferenceCounter();
		return textureManaged->getGlId();
	}
	auto textureId = renderer->createTexture();
	renderer->bindTexture(textureId);
	renderer->uploadTexture(texture);
	renderer->bindTexture(renderer->ID_NONE);
	auto textureManaged = new TextureManager_TextureManaged(texture->getId(), textureId);
	textureManaged->incrementReferenceCounter();
	textures[texture->getId()] = textureManaged;
	return textureId;
}

void TextureManager::removeTexture(const wstring& textureId)
{
	auto textureManagedIt = textures.find(textureId);
	if (textureManagedIt != textures.end()) {
		auto textureManaged = textureManagedIt->second;
		if (textureManaged->decrementReferenceCounter()) {
			renderer->disposeTexture(textureManaged->getGlId());
			textures.erase(textureManagedIt);
		}
		return;
	}
	Console::println(wstring(L"Warning: texture not loaded by texture manager"));
}
