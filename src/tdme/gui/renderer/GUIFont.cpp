#include <tdme/gui/renderer/GUIFont.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/renderer/GUIFont_CharacterDefinition.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::Engine;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIFont_CharacterDefinition;
using tdme::gui::renderer::GUIRenderer;
using tdme::math::Math;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

GUIFont::GUIFont()
{
}

GUIFont::~GUIFont()
{
	for (auto& charIt: chars) delete charIt.second;
	if (texture != nullptr) texture->releaseReference();
}

GUIFont* GUIFont::parse(const string& pathName, const string& fileName)
{
	int lineIdx = 0;
	auto font = new GUIFont();
	vector<string> lines;
	FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, lines);
	auto info = lines[lineIdx++];
	auto common = lines[lineIdx++];
	auto page = lines[lineIdx++];
	font->texture = TextureReader::read(
		pathName,
		StringTools::substring(page, page.find("file=") + string("file=\"").length(), page.find_last_of("\"")),
		false,
		false
	);
	auto done = false;
	while (lineIdx < lines.size()) {
		auto line = lines[lineIdx++];
		if (StringTools::startsWith(line, "chars c")) {
		} else
		if (StringTools::startsWith(line, "char")) {
			auto def = font->parseCharacter(line);
			font->chars[def->id] = def;
		}
		if (StringTools::startsWith(line, "kernings c")) {
		} else
		if (StringTools::startsWith(line, "kerning")) {
			/*
			// TODO: not yet supported in the moment
			StringTokenizer t;
			t.tokenize(line, " =");
			t.nextToken();
			t.nextToken();
			auto first = Integer::parseInt(t.nextToken());
			t.nextToken();
			auto second = Integer::parseInt(t.nextToken());
			t.nextToken();
			auto offset = Integer::parseInt(t.nextToken());
			*/
		}
	}
	for (auto& fontIt: font->chars) {
		auto characterDefinition = fontIt.second;
		if (characterDefinition->height + characterDefinition->yOffset > font->lineHeight) font->lineHeight = characterDefinition->height + characterDefinition->yOffset;
	}
	return font;
}

GUIFont_CharacterDefinition* GUIFont::parseCharacter(const string& line)
{
	auto characterDefinition = new GUIFont_CharacterDefinition(this);
	StringTokenizer t;
	t.tokenize(line, " =");
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

void GUIFont::initialize()
{
	textureId = Engine::getInstance()->getTextureManager()->addTexture(texture, nullptr);
}

void GUIFont::dispose()
{
	Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
}

void GUIFont::drawString(GUIRenderer* guiRenderer, int x, int y, const MutableString& text, int offset, int length, const GUIColor& color, int selectionStartIndex, int selectionEndIndex, const GUIColor& backgroundColor)
{
	if (length == 0) length = text.size();
	auto inSelection = false;
	auto currentColor = color;
	auto currentBackgroundColor = backgroundColor;
	if (selectionStartIndex != -1 && selectionEndIndex != -1) {
		auto currentX = x;
		for (auto i = offset; i < text.size() && i < length; i++) {
			auto characterId = text.charAt(i);
			auto characterDefinition = getCharacter(characterId);
			if (characterDefinition == nullptr) continue;
			auto currentInSelection = i >= selectionStartIndex && i < selectionEndIndex;
			if (currentInSelection != inSelection) {
				guiRenderer->render();
				inSelection = currentInSelection;
				currentColor = inSelection == true?backgroundColor:color;
				currentBackgroundColor = inSelection == true?color:backgroundColor;
			}
			characterDefinition->drawBackground(guiRenderer, currentX, y, lineHeight, currentBackgroundColor);
			currentX += characterDefinition->xAdvance;
		}
		guiRenderer->render();
	}
	guiRenderer->render();
	guiRenderer->bindTexture(textureId);
	auto currentX = x;
	for (auto i = offset; i < text.size() && i < length; i++) {
		auto characterId = text.charAt(i);
		auto characterDefinitions = getCharacter(characterId);
		if (characterDefinitions == nullptr) continue;
		auto currentInSelection = i >= selectionStartIndex && i < selectionEndIndex;
		if (currentInSelection != inSelection) {
			guiRenderer->setFontColor(currentColor);
			guiRenderer->render();
			inSelection = currentInSelection;
			currentColor = inSelection == true?backgroundColor:color;
			currentBackgroundColor = inSelection == true?color:backgroundColor;
		}
		characterDefinitions->draw(guiRenderer, currentX, y);
		currentX += characterDefinitions->xAdvance;
	}
	guiRenderer->setFontColor(currentColor);
	guiRenderer->render();
	guiRenderer->bindTexture(0);
}

int GUIFont::getTextIndexX(const MutableString& text, int offset, int length, int index)
{
	if (length == 0) length = text.size();
	auto x = 0;
	for (auto i = offset; i < index && i < text.size() && i < length; i++) {
		auto characterId = text.charAt(i);
		auto characterDefinition = getCharacter(characterId);
		if (characterDefinition == nullptr) continue;
		x += characterDefinition->xAdvance;
	}
	return x;
}

int GUIFont::getTextIndexByX(const MutableString& text, int offset, int length, int textX)
{
	auto x = 0;
	auto index = offset;
	if (length == 0) length = text.size();
	for (; index < text.size() && index < length; index++) {
		auto characterId = text.charAt(index);
		auto characterDefinition = getCharacter(characterId);
		if (characterDefinition == nullptr) continue;
		auto xAdvance = characterDefinition->xAdvance;
		x += xAdvance;
		if (x - xAdvance / 2 > textX) {
			return index;
		}
	}
	return index;
}

int GUIFont::getTextWidth(const MutableString& text)
{
	auto width = 0;
	for (auto i = 0; i < text.size(); i++) {
		auto characterId = text.charAt(i);
		auto characterDefinition = getCharacter(characterId);
		if (characterDefinition == nullptr) continue;
		width += characterDefinition->xAdvance;
	}
	return width;
}

int GUIFont::getTextIndexXAtWidth(const MutableString& text, int width) {
	auto x = 0;
	for (auto i = 0; i < text.size(); i++) {
		auto characterId = text.charAt(i);
		auto characterDefinition = getCharacter(characterId);
		if (characterDefinition == nullptr) continue;
		x += characterDefinition->xAdvance;
		if (x > width) return i;
	}
	return text.size() - 1;
}

int GUIFont::getLineHeight()
{
	return lineHeight;
}
