// Generated from /tdme/src/tdme/engine/subsystems/manager/TextureManager.java
#include <tdme/engine/subsystems/manager/TextureManager.h>

#include <map>
#include <string>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager_TextureManaged.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/utils/_Console.h>

using std::map;
using std::wstring;

using tdme::engine::subsystems::manager::TextureManager;
using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::_Console;;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

TextureManager::TextureManager(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TextureManager::TextureManager(GLRenderer* renderer) 
	: TextureManager(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer);
}

void TextureManager::ctor(GLRenderer* renderer)
{
	super::ctor();
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
	auto textureManaged = new TextureManager_TextureManaged(this, texture->getId(), textureId);
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
	_Console::println(static_cast< Object* >(u"Warning: texture not loaded by texture manager"_j));
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TextureManager::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.manager.TextureManager", 45);
    return c;
}

java::lang::Class* TextureManager::getClass0()
{
	return class_();
}

