#include <tdme/gui/renderer/GUIFont_CharacterDefinition.h>


#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/renderer/GUIRenderer.h>

using tdme::gui::renderer::GUIFont_CharacterDefinition;
using tdme::engine::fileio::textures::Texture;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;

GUIFont_CharacterDefinition::GUIFont_CharacterDefinition(GUIFont *GUIFont_this, const ::default_init_tag&)
	: GUIFont_this(GUIFont_this)
{
}

GUIFont_CharacterDefinition::GUIFont_CharacterDefinition(GUIFont *GUIFont_this)
	: GUIFont_CharacterDefinition(GUIFont_this, *static_cast< ::default_init_tag* >(0))
{
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
	auto fontColor = &GUIColor::WHITE.getArray();
	guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*fontColor)[0], (*fontColor)[1], (*fontColor)[2], (*fontColor)[3], (textureCharLeft) / textureWidth, (textureCharTop) / textureHeight, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*fontColor)[0], (*fontColor)[1], (*fontColor)[2], (*fontColor)[3], (textureCharLeft + textureCharWidth) / textureWidth, (textureCharTop) / textureHeight, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*fontColor)[0], (*fontColor)[1], (*fontColor)[2], (*fontColor)[3], (textureCharLeft + textureCharWidth) / textureWidth, (textureCharTop + textureCharHeight) / textureHeight, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*fontColor)[0], (*fontColor)[1], (*fontColor)[2], (*fontColor)[3], (textureCharLeft) / textureWidth, (textureCharTop + textureCharHeight) / textureHeight);
}

