// Generated from /tdme/src/tdme/engine/subsystems/manager/TextureManager.java
#include <tdme/engine/subsystems/manager/TextureManager.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager_TextureManaged.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap.h>

using tdme::engine::subsystems::manager::TextureManager;
using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::_Console;
using tdme::utils::_HashMap;

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
	textures = new _HashMap();
}

int32_t TextureManager::addTexture(Texture* texture)
{
	auto textureManaged = java_cast< TextureManager_TextureManaged* >(textures->get(texture->getId()));
	if (textureManaged != nullptr) {
		textureManaged->incrementReferenceCounter();
		return textureManaged->getGlId();
	}
	auto textureId = renderer->createTexture();
	renderer->bindTexture(textureId);
	renderer->uploadTexture(texture);
	renderer->bindTexture(renderer->ID_NONE);
	textureManaged = new TextureManager_TextureManaged(this, texture->getId(), textureId);
	textureManaged->incrementReferenceCounter();
	textures->put(texture->getId(), textureManaged);
	return textureId;
}

void TextureManager::removeTexture(String* textureId)
{
	auto textureManaged = java_cast< TextureManager_TextureManaged* >(textures->get(textureId));
	if (textureManaged != nullptr) {
		if (textureManaged->decrementReferenceCounter()) {
			renderer->disposeTexture(textureManaged->getGlId());
			textures->remove(textureId);
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

