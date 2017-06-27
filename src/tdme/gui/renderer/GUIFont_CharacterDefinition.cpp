// Generated from /tdme/src/tdme/gui/renderer/GUIFont.java
#include <tdme/gui/renderer/GUIFont_CharacterDefinition.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <Array.h>

using tdme::gui::renderer::GUIFont_CharacterDefinition;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::fileio::textures::Texture;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;

GUIFont_CharacterDefinition::GUIFont_CharacterDefinition(GUIFont *GUIFont_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, GUIFont_this(GUIFont_this)
{
	clinit();
}

GUIFont_CharacterDefinition::GUIFont_CharacterDefinition(GUIFont *GUIFont_this)
	: GUIFont_CharacterDefinition(GUIFont_this, *static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIFont_CharacterDefinition::toString()
{
	return ::java::lang::StringBuilder().append(u"[CharDef id="_j)->append(id)
		->append(u" x="_j)
		->append(x)
		->append(u" y="_j)
		->append(y)
		->append(u"]"_j)->toString();
}

void GUIFont_CharacterDefinition::draw(GUIRenderer* guiRenderer, int32_t x, int32_t y)
{
	float screenWidth = guiRenderer->gui->getWidth();
	float screenHeight = guiRenderer->gui->getHeight();
	float left = x + xOffset;
	float top = y + yOffset;
	float width = this->width;
	float height = this->height;
	float textureWidth = GUIFont_this->texture->getTextureWidth();
	float textureHeight = GUIFont_this->texture->getTextureHeight();
	float textureCharLeft = this->x;
	float textureCharTop = this->y;
	float textureCharWidth = this->width;
	float textureCharHeight = this->height;
	auto fontColor = GUIColor::WHITE->getArray();
	guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*fontColor)[0], (*fontColor)[1], (*fontColor)[2], (*fontColor)[3], (textureCharLeft) / textureWidth, (textureCharTop) / textureHeight, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*fontColor)[0], (*fontColor)[1], (*fontColor)[2], (*fontColor)[3], (textureCharLeft + textureCharWidth) / textureWidth, (textureCharTop) / textureHeight, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*fontColor)[0], (*fontColor)[1], (*fontColor)[2], (*fontColor)[3], (textureCharLeft + textureCharWidth) / textureWidth, (textureCharTop + textureCharHeight) / textureHeight, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*fontColor)[0], (*fontColor)[1], (*fontColor)[2], (*fontColor)[3], (textureCharLeft) / textureWidth, (textureCharTop + textureCharHeight) / textureHeight);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIFont_CharacterDefinition::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.renderer.GUIFont.CharacterDefinition", 45);
    return c;
}

java::lang::Class* GUIFont_CharacterDefinition::getClass0()
{
	return class_();
}

