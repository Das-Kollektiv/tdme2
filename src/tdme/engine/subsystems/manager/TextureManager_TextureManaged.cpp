// Generated from /tdme/src/tdme/engine/subsystems/manager/TextureManager.java
#include <tdme/engine/subsystems/manager/TextureManager_TextureManaged.h>

#include <java/lang/String.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>

using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using java::lang::String;
using tdme::engine::subsystems::manager::TextureManager;

TextureManager_TextureManaged::TextureManager_TextureManaged(TextureManager *TextureManager_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, TextureManager_this(TextureManager_this)
{
	clinit();
}

TextureManager_TextureManaged::TextureManager_TextureManaged(TextureManager *TextureManager_this, const wstring& id, int32_t glId)
	: TextureManager_TextureManaged(TextureManager_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(id,glId);
}

void TextureManager_TextureManaged::ctor(const wstring& id, int32_t glId)
{
	super::ctor();
	this->id = id;
	this->glId = glId;
	this->referenceCounter = 0;
}

const wstring& TextureManager_TextureManaged::getId()
{
	return id;
}

int32_t TextureManager_TextureManaged::getGlId()
{
	return glId;
}

int32_t TextureManager_TextureManaged::getReferenceCounter()
{
	return referenceCounter;
}

bool TextureManager_TextureManaged::decrementReferenceCounter()
{
	referenceCounter--;
	return referenceCounter == 0;
}

void TextureManager_TextureManaged::incrementReferenceCounter()
{
	referenceCounter++;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TextureManager_TextureManaged::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.manager.TextureManager.TextureManaged", 60);
    return c;
}

java::lang::Class* TextureManager_TextureManaged::getClass0()
{
	return class_();
}

