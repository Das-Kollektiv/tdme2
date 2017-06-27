// Generated from /tdme/src/tdme/engine/fileio/textures/TextureLoader.java
#include <tdme/engine/fileio/textures/TextureLoader.h>

using tdme::engine::fileio::textures::TextureLoader;
TextureLoader::TextureLoader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TextureLoader::TextureLoader()
	: TextureLoader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Texture* TextureLoader::loadTexture(String* path, String* fileName)
{
	clinit();
	return nullptr;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TextureLoader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.textures.TextureLoader", 41);
    return c;
}

java::lang::Class* TextureLoader::getClass0()
{
	return class_();
}

