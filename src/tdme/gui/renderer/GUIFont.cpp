#include <tdme/gui/renderer/GUIFont.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/renderer/GUICharacter.h>
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
using tdme::gui::renderer::GUICharacter;
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
			font->chars[def->getId()] = def;
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
	font->yOffsetMin = 10000;
	for (auto& fontIt: font->chars) {
		auto character = fontIt.second;
		if (character->getYOffset() < font->yOffsetMin) font->yOffsetMin = character->getYOffset();
		if (character->getHeight() + character->getYOffset() > font->lineHeight) font->lineHeight = character->getHeight() + character->getYOffset();
	}
	return font;
}

GUICharacter* GUIFont::parseCharacter(const string& line)
{
	StringTokenizer t;
	t.tokenize(line, " =");
	t.nextToken();
	t.nextToken();
	auto id = Integer::parse(t.nextToken());
	t.nextToken();
	auto x = Integer::parse(t.nextToken());
	t.nextToken();
	auto y = Integer::parse(t.nextToken());
	t.nextToken();
	auto width = Integer::parse(t.nextToken());
	t.nextToken();
	auto height = Integer::parse(t.nextToken());
	t.nextToken();
	auto xOffset = Integer::parse(t.nextToken());
	t.nextToken();
	auto yOffset = Integer::parse(t.nextToken());
	t.nextToken();
	auto xAdvance = Integer::parse(t.nextToken());
	if (id != ' ') {
		lineHeight = Math::max(height + yOffset, lineHeight); // TODO
	}
	return new GUICharacter(
		id,
		x,
		y,
		width,
		height,
		xOffset,
		yOffset,
		xAdvance
	);
}

void GUIFont::initialize()
{
	textureId = Engine::getInstance()->getTextureManager()->addTexture(texture, 0);
}

void GUIFont::dispose()
{
	Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
}

void GUIFont::drawString(GUIRenderer* guiRenderer, int x, int y, const MutableString& text, int offset, int length, const GUIColor& color, int selectionStartIndex, int selectionEndIndex, const GUIColor& backgroundColor)
{
	y-= yOffsetMin - 1;
	if (length == 0) length = text.size();
	auto inSelection = false;
	auto currentColor = color;
	auto currentBackgroundColor = backgroundColor;
	if (selectionStartIndex != -1 && selectionEndIndex != -1) {
		auto currentX = x;
		for (auto i = offset; i < text.size() && i < length; i++) {
			auto characterId = text.charAt(i);
			auto character = getCharacter(characterId);
			if (character == nullptr) continue;
			auto currentInSelection = i >= selectionStartIndex && i < selectionEndIndex;
			if (currentInSelection != inSelection) {
				guiRenderer->render();
				inSelection = currentInSelection;
				currentColor = inSelection == true?backgroundColor:color;
				currentBackgroundColor = inSelection == true?color:backgroundColor;
			}
			drawCharacterBackground(guiRenderer, character, currentX, y, lineHeight, currentBackgroundColor);
			currentX += character->getXAdvance();
		}
		guiRenderer->render();
	}
	guiRenderer->render();
	guiRenderer->bindTexture(textureId);
	auto currentX = x;
	for (auto i = offset; i < text.size() && i < length; i++) {
		auto characterId = text.charAt(i);
		auto character = getCharacter(characterId);
		if (character == nullptr) continue;
		auto currentInSelection = i >= selectionStartIndex && i < selectionEndIndex;
		if (currentInSelection != inSelection) {
			guiRenderer->setFontColor(currentColor);
			guiRenderer->render();
			inSelection = currentInSelection;
			currentColor = inSelection == true?backgroundColor:color;
			currentBackgroundColor = inSelection == true?color:backgroundColor;
		}
		drawCharacter(guiRenderer, character, currentX, y);
		currentX += character->getXAdvance();
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
		auto character = getCharacter(characterId);
		if (character == nullptr) continue;
		x += character->getXAdvance();
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
		auto character = getCharacter(characterId);
		if (character == nullptr) continue;
		auto xAdvance = character->getXAdvance();
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
		auto character = getCharacter(characterId);
		if (character == nullptr) continue;
		width += character->getXAdvance();
	}
	return width;
}

int GUIFont::getTextIndexXAtWidth(const MutableString& text, int width) {
	auto x = 0;
	for (auto i = 0; i < text.size(); i++) {
		auto characterId = text.charAt(i);
		auto character = getCharacter(characterId);
		if (character == nullptr) continue;
		x += character->getXAdvance();
		if (x > width) return i;
	}
	return text.size() - 1;
}

int GUIFont::getLineHeight()
{
	return lineHeight;
}

inline void GUIFont::drawCharacter(GUIRenderer* guiRenderer, GUICharacter* character, int x, int y, const GUIColor& color) {
	float screenWidth = guiRenderer->getScreenNode()->getScreenWidth();
	float screenHeight = guiRenderer->getScreenNode()->getScreenHeight();
	float left = x + character->getXOffset();
	float top = y + character->getYOffset();
	float width = character->getWidth();
	float height = character->getHeight();
	float textureWidth = texture->getTextureWidth();
	float textureHeight = texture->getTextureHeight();
	float textureCharLeft = character->getX();
	float textureCharTop = character->getY();
	float textureCharWidth = character->getWidth();
	float textureCharHeight = character->getHeight();
	auto& fontColor = color.getArray();
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		fontColor[0], fontColor[1], fontColor[2], fontColor[3],
		(textureCharLeft) / textureWidth, (textureCharTop) / textureHeight,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		fontColor[0], fontColor[1], fontColor[2], fontColor[3],
		(textureCharLeft + textureCharWidth) / textureWidth, (textureCharTop) / textureHeight,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		fontColor[0], fontColor[1], fontColor[2], fontColor[3],
		(textureCharLeft + textureCharWidth) / textureWidth,
		(textureCharTop + textureCharHeight) / textureHeight,
		((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		fontColor[0], fontColor[1], fontColor[2], fontColor[3],
		(textureCharLeft) / textureWidth,
		(textureCharTop + textureCharHeight) / textureHeight
	);
}

inline void GUIFont::drawCharacterBackground(GUIRenderer* guiRenderer, GUICharacter* character, int x, int y, int lineHeight, const GUIColor& color) {
	float screenWidth = guiRenderer->getScreenNode()->getScreenWidth();
	float screenHeight = guiRenderer->getScreenNode()->getScreenHeight();
	float left = x + character->getXOffset();
	float top = y;
	float width = character->getWidth();
	float height = lineHeight;
	auto& backgroundColor = color.getArray();
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3],
		0.0f,
		1.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3],
		1.0f,
		1.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3],
		1.0f,
		0.0f,
		((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3],
		0.0f,
		0.0f
	);
}
