// Generated from /tdme/src/tdme/gui/renderer/GUIFont.java
#include <tdme/gui/renderer/GUIFont.h>

#include <map>
#include <vector>
#include <string>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/gui/renderer/GUIFont_CharacterDefinition.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::gui::renderer::GUIFont;
using java::lang::Math;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::gui::renderer::GUIFont_CharacterDefinition;
using tdme::gui::renderer::GUIRenderer;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::Integer;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;
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
}

MutableString* GUIFont::LINEHEIGHT_STRING;

constexpr int32_t GUIFont::CHARACTERS_MAX;

GUIFont* GUIFont::parse(String* pathName, String* fileName) throw (_FileSystemException)
{
	clinit();
	int lineIdx = 0;
	auto font = new GUIFont();
	vector<wstring> lines;
	_FileSystem::getInstance()->getContentAsStringArray(pathName->getCPPWString(), fileName->getCPPWString(), &lines);
	auto info = lines[lineIdx++];
	auto common = lines[lineIdx++];
	auto page = lines[lineIdx++];
	font->texture = TextureLoader::loadTexture(
		pathName->getCPPWString(),
		StringUtils::substring(page, page.find(L"file=") + wstring(L"file=\"").length(), page.find_last_of(L"\""))
	);
	auto done = false;
	while (lineIdx < lines.size()) {
		auto line = lines[lineIdx++];
		if (StringUtils::startsWith(line, L"chars c")) {
		} else
		if (StringUtils::startsWith(line, L"char")) {
			auto def = font->parseCharacter(line);
			font->chars[def->id] = def;
		}
		if (StringUtils::startsWith(line, L"kernings c")) {
		} else
		if (StringUtils::startsWith(line, L"kerning")) {
			StringTokenizer t;
			t.tokenize(line, L" =");
			t.nextToken();
			t.nextToken();
			auto first = Integer::parseInt(t.nextToken());
			t.nextToken();
			auto second = Integer::parseInt(t.nextToken());
			t.nextToken();
			auto offset = Integer::parseInt(t.nextToken());
		}
	}
	font->lineHeight = font->getTextHeight(LINEHEIGHT_STRING);
	return font;
}

GUIFont_CharacterDefinition* GUIFont::parseCharacter(const wstring& line)
{
	auto characterDefinition = new GUIFont_CharacterDefinition(this);
	StringTokenizer t;
	t.tokenize(line, L" =");
	t.nextToken();
	t.nextToken();
	characterDefinition->id = Integer::parseInt(t.nextToken());
	t.nextToken();
	characterDefinition->x = Integer::parseInt(t.nextToken());
	t.nextToken();
	characterDefinition->y = Integer::parseInt(t.nextToken());
	t.nextToken();
	characterDefinition->width = Integer::parseInt(t.nextToken());
	t.nextToken();
	characterDefinition->height = Integer::parseInt(t.nextToken());
	t.nextToken();
	characterDefinition->xOffset = Integer::parseInt(t.nextToken());
	t.nextToken();
	characterDefinition->yOffset = Integer::parseInt(t.nextToken());
	t.nextToken();
	characterDefinition->xAdvance = Integer::parseInt(t.nextToken());
	if (characterDefinition->id != u' ') {
		lineHeight = Math::max(characterDefinition->height + characterDefinition->yOffset, lineHeight);
	}
	return characterDefinition;
}

GUIFont_CharacterDefinition* GUIFont::getCharacter(int32_t charId) {
	auto charIt = chars.find(charId);
	if (charIt != chars.end()) return charIt->second;
	return nullptr;
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
		GUIFont_CharacterDefinition* charDef = getCharacter(id);
		if (charDef == nullptr) continue;
		charDef->draw(guiRenderer, x, y);
		auto xAdvance = charDef->xAdvance;
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
		GUIFont_CharacterDefinition* charDef = getCharacter(id);
		if (charDef == nullptr) continue;
		auto xAdvance = charDef->xAdvance;
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
		GUIFont_CharacterDefinition* charDef = getCharacter(id);
		if (charDef == nullptr) continue;
		auto xAdvance = charDef->xAdvance;
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
		GUIFont_CharacterDefinition* charDef = getCharacter(id);
		if (charDef == nullptr) continue;
		minYOffset = Math::min(charDef->yOffset, minYOffset);
	}
	return minYOffset;
}

int32_t GUIFont::getTextHeight(MutableString* text)
{
	auto maxHeight = 0;
	for (auto i = 0; i < text->length(); i++) {
		int32_t id = text->charAt(i);
		GUIFont_CharacterDefinition* charDef = getCharacter(id);
		if (charDef == nullptr) continue;
		if (id == L' ') {
			continue;
		}
		maxHeight = Math::max(charDef->height + charDef->yOffset, maxHeight);
	}
	return maxHeight;
}

int32_t GUIFont::getTextWidth(MutableString* text)
{
	auto width = 0;
	for (auto i = 0; i < text->length(); i++) {
		int32_t id = text->charAt(i);
		GUIFont_CharacterDefinition* charDef = getCharacter(id);
		if (charDef == nullptr) continue;
		auto xAdvance = charDef->xAdvance;
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

