// Generated from /tdme/src/tdme/gui/renderer/GUIFont.java
#include <tdme/gui/renderer/GUIFont.h>

#include <java/lang/Integer.h>
#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/util/StringTokenizer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/gui/renderer/GUIFont_CharacterDefinition.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/MutableString.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::gui::renderer::GUIFont;
using java::lang::Integer;
using java::lang::Math;
using java::lang::String;
using java::util::StringTokenizer;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::gui::renderer::GUIFont_CharacterDefinition;
using tdme::gui::renderer::GUIRenderer;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::MutableString;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace gui {
namespace renderer {
typedef ::SubArray< ::tdme::gui::renderer::GUIFont_CharacterDefinition, ::java::lang::ObjectArray > GUIFont_CharacterDefinitionArray;
}  // namespace renderer
}  // namespace gui
}  // namespace tdme

GUIFont::GUIFont(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIFont::GUIFont()
	: GUIFont(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void GUIFont::ctor()
{
	super::ctor();
	init();
}

void GUIFont::init()
{
	chars = new GUIFont_CharacterDefinitionArray(CHARACTERS_MAX);
}

MutableString* GUIFont::LINEHEIGHT_STRING;

constexpr int32_t GUIFont::CHARACTERS_MAX;

GUIFont* GUIFont::parse(String* pathName, String* fileName) throw (_FileSystemException)
{
	clinit();
	int lineIdx = 0;
	auto font = new GUIFont();
	auto in = _FileSystem::getInstance()->getContentAsStringArray(pathName, fileName);
	auto info = in->get(lineIdx++);
	auto common = in->get(lineIdx++);
	auto page = in->get(lineIdx++);
	font->texture = TextureLoader::loadTexture(pathName, page->substring(page->indexOf(u"file="_j) + u"file=\""_j->length(), page->lastIndexOf(u"\""_j)));
	auto done = false;
	while (lineIdx < in->length) {
		String* line = in->get(lineIdx++);
		if (line->startsWith(u"chars c"_j)) {
		} else if (line->startsWith(u"char"_j)) {
			auto def = font->parseCharacter(line);
			font->chars->set(def->id, def);
		}
		if (line->startsWith(u"kernings c"_j)) {
		} else if (line->startsWith(u"kerning"_j)) {
			auto tokens = new StringTokenizer(line, u" ="_j);
			tokens->nextToken();
			tokens->nextToken();
			auto first = Integer::parseInt(tokens->nextToken());
			tokens->nextToken();
			auto second = Integer::parseInt(tokens->nextToken());
			tokens->nextToken();
			auto offset = Integer::parseInt(tokens->nextToken());
		}
	}
	font->lineHeight = font->getTextHeight(LINEHEIGHT_STRING);
	return font;
}

GUIFont_CharacterDefinition* GUIFont::parseCharacter(String* line)
{
	auto characterDefinition = new GUIFont_CharacterDefinition(this);
	auto tokens = new StringTokenizer(line, u" ="_j);
	tokens->nextToken();
	tokens->nextToken();
	characterDefinition->id = Integer::parseInt(tokens->nextToken());
	tokens->nextToken();
	characterDefinition->x = Integer::parseInt(tokens->nextToken());
	tokens->nextToken();
	characterDefinition->y = Integer::parseInt(tokens->nextToken());
	tokens->nextToken();
	characterDefinition->width = Integer::parseInt(tokens->nextToken());
	tokens->nextToken();
	characterDefinition->height = Integer::parseInt(tokens->nextToken());
	tokens->nextToken();
	characterDefinition->xOffset = Integer::parseInt(tokens->nextToken());
	tokens->nextToken();
	characterDefinition->yOffset = Integer::parseInt(tokens->nextToken());
	tokens->nextToken();
	characterDefinition->xAdvance = Integer::parseInt(tokens->nextToken());
	if (characterDefinition->id != u' ') {
		lineHeight = Math::max(characterDefinition->height + characterDefinition->yOffset, lineHeight);
	}
	return characterDefinition;
}

void GUIFont::initialize()
{
	textureId = Engine::getInstance()->getTextureManager()->addTexture(texture);
}

void GUIFont::dispose()
{
	Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
}

void GUIFont::drawString(GUIRenderer* guiRenderer, int32_t x, int32_t y, MutableString* text, int32_t offset, int32_t length, GUIColor* color)
{
	guiRenderer->bindTexture(textureId);
	guiRenderer->setFontColor(color);
	y -= getYOffset(text) / 2;
	if (length == 0)
		length = text->length();

	for (auto i = offset; i < text->length() && i < length; i++) {
		int32_t id = text->charAt(i);
		if (id >= chars->length) {
			continue;
		}
		if ((*chars)[id] == nullptr) {
			continue;
		}
		(*chars)[id]->draw(guiRenderer, x, y);
		auto xAdvance = (*chars)[id]->xAdvance;
		x += xAdvance;
	}
	guiRenderer->render();
}

int32_t GUIFont::getTextIndexX(MutableString* text, int32_t offset, int32_t length, int32_t index)
{
	if (length == 0)
		length = text->length();

	auto x = 0;
	for (auto i = offset; i < index && i < text->length() && i < length; i++) {
		int32_t id = text->charAt(i);
		if (id >= chars->length) {
			continue;
		}
		if ((*chars)[id] == nullptr) {
			continue;
		}
		auto xAdvance = (*chars)[id]->xAdvance;
		x += xAdvance;
	}
	return x;
}

int32_t GUIFont::getTextIndexByX(MutableString* text, int32_t offset, int32_t length, int32_t textX)
{
	auto x = 0;
	auto index = offset;
	if (length == 0)
		length = text->length();

	for (; index < text->length() && index < length; index++) {
		int32_t id = text->charAt(index);
		if (id >= chars->length) {
			continue;
		}
		if ((*chars)[id] == nullptr) {
			continue;
		}
		auto xAdvance = (*chars)[id]->xAdvance;
		x += xAdvance;
		if (x - xAdvance / 2 > textX) {
			return index;
		}
	}
	return index;
}

int32_t GUIFont::getYOffset(MutableString* text)
{
	auto minYOffset = 10000;
	for (auto i = 0; i < text->length(); i++) {
		int32_t id = text->charAt(i);
		if ((*chars)[id] == nullptr) {
			continue;
		}
		minYOffset = Math::min((*chars)[id]->yOffset, minYOffset);
	}
	return minYOffset;
}

int32_t GUIFont::getTextHeight(MutableString* text)
{
	auto maxHeight = 0;
	for (auto i = 0; i < text->length(); i++) {
		int32_t id = text->charAt(i);
		if ((*chars)[id] == nullptr) {
			continue;
		}
		if (id == u' ') {
			continue;
		}
		maxHeight = Math::max((*chars)[id]->height + (*chars)[id]->yOffset, maxHeight);
	}
	return maxHeight;
}

int32_t GUIFont::getTextWidth(MutableString* text)
{
	auto width = 0;
	for (auto i = 0; i < text->length(); i++) {
		int32_t id = text->charAt(i);
		if ((*chars)[id] == nullptr) {
			continue;
		}
		auto xAdvance = (*chars)[id]->xAdvance;
		width += xAdvance;
	}
	return width;
}

int32_t GUIFont::getLineHeight()
{
	return lineHeight;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIFont::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.renderer.GUIFont", 25);
    return c;
}

void GUIFont::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		LINEHEIGHT_STRING = new MutableString(u"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUV0123456789"_j);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* GUIFont::getClass0()
{
	return class_();
}

