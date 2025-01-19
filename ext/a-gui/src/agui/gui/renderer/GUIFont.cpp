#include <agui/gui/renderer/GUIFont.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <unordered_map>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/fileio/TextureReader.h>
#include <agui/gui/renderer/GUIRendererBackend.h>
#include <agui/gui/renderer/GUICharacter.h>
#include <agui/gui/renderer/GUIRenderer.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Character.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/Float.h>
#include <agui/utilities/Integer.h>
#include <agui/utilities/MutableString.h>
#include <agui/utilities/StringTokenizer.h>
#include <agui/utilities/StringTools.h>
#include <agui/utilities/TextureAtlas.h>

using std::string;
using std::unordered_map;
using std::vector;

using agui::gui::fileio::TextureReader;
using agui::gui::renderer::GUIRendererBackend;
using agui::gui::renderer::GUICharacter;
using agui::gui::renderer::GUIFont;
using agui::gui::renderer::GUIRenderer;
using agui::gui::textures::GUITexture;
using agui::gui::GUI;
using agui::math::Math;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;
using agui::utilities::ByteBuffer;
using agui::utilities::Character;
using agui::utilities::Exception;
using agui::utilities::Float;
using agui::utilities::Integer;
using agui::utilities::MutableString;
using agui::utilities::StringTokenizer;
using agui::utilities::StringTools;
using agui::utilities::TextureAtlas;

bool GUIFont::ftInitialized = false;
FT_Library GUIFont::ftLibrary;

GUIFont::GUIFont(const string& pathName, const string& fileName, int size): textureAtlas("font:" + pathName + "/" + fileName + "@" + to_string(size))
{
	// load ttf data
	FileSystem::getInstance()->getContent(pathName, fileName, ttfData);

	// open face
	ftPathName = pathName + "/" + fileName;
	ftOpenArgs = {
		.flags = FT_OPEN_MEMORY,
		.memory_base = ttfData.data(),
		.memory_size = (int)ttfData.size(),
		.pathname = (char*)ftPathName.c_str(),
		.stream = nullptr,
		.driver = nullptr,
		.num_params = 0,
		.params = nullptr
	};
	if (FT_Open_Face(ftLibrary, &ftOpenArgs, 0, &ftFace) != 0) {
		Console::printLine("GUIFont::parse(): Could not load font: " + pathName + "/" + fileName);
		return;
	}

	//
	FT_Set_Pixel_Sizes(ftFace, 0, size);

	//
	lineHeight = ftFace->size->metrics.height >> 6;
	baseLine = ftFace->size->metrics.ascender >> 6;
}

GUIFont::~GUIFont()
{
	for (const auto& [charId, character]: chars) delete character;
	FT_Done_Face(ftFace);
}

GUIFont* GUIFont::parse(const string& pathName, const string& fileName, int size)
{
	// init freetype library if not yet done
	if (ftInitialized == false) {
		if (FT_Init_FreeType(&ftLibrary) != 0) {
			Console::printLine("GUIFont::parse(): Could not initialize freetype library");
			return nullptr;
		}
		ftInitialized = true;
	}

	// include standard characters in default atlas
	auto font = new GUIFont(pathName, fileName, size);
	font->addCharactersToFont(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ^0123456789°!&quot;$%&/()=?+*-<>|#,;.:'\"");

	//
	return font;
}

GUICharacter* GUIFont::addToTextureAtlas(uint32_t charId) {
	//
	if (FT_Load_Char(ftFace, charId, FT_LOAD_RENDER))
	{
		Console::printLine("GUIFont::addToTextureAtlas(): Could not load glyph: " + Character::toString(charId) + "(" + to_string(charId) + ")");
	    return nullptr;
	}

	//
	auto glyphBitmapWidth = ftFace->glyph->bitmap.width;
	auto glyphBitmapHeight = ftFace->glyph->bitmap.rows;
	auto glyphBitmapBuffer = ftFace->glyph->bitmap.buffer;
	auto glyphByteBuffer = ByteBuffer(glyphBitmapWidth * glyphBitmapHeight * 4);
	for (int y = glyphBitmapHeight - 1; y >= 0; y--) {
		for (auto x = 0; x < glyphBitmapWidth; x++) {
			auto v = glyphBitmapBuffer[y * glyphBitmapWidth + x];
			glyphByteBuffer.put(v); // red
			glyphByteBuffer.put(v); // green
			glyphByteBuffer.put(v); // blue
			glyphByteBuffer.put(v == 0?0:(v < 0xff / 2?v * 2:0xff)); // alpha
		}
	}

	//
	auto glyphTexture = new GUITexture(
		Character::toString(charId),
		GUITexture::TEXTUREDEPTH_RGBA,
		GUITexture::TEXTUREFORMAT_RGBA,
		glyphBitmapWidth, glyphBitmapHeight,
		glyphBitmapWidth, glyphBitmapHeight,
		GUITexture::TEXTUREFORMAT_RGBA,
		glyphByteBuffer
	);
	glyphTexture->acquireReference();

	//
	auto glyphTextureSmoothed = TextureReader::smooth(glyphTexture, string());
	glyphTexture->releaseReference();

	//
	textureAtlas.addTexture(glyphTextureSmoothed);

	//
	glyphTextureSmoothed->releaseReference();

	//
	auto character = new GUICharacter(
		charId,
		-1,
		-1,
		glyphBitmapWidth,
		glyphBitmapHeight,
		ftFace->glyph->bitmap_left,
		(lineHeight - ftFace->glyph->bitmap_top) - (lineHeight - baseLine),
		ftFace->glyph->advance.x >> 6
	);
	chars[charId] = character;

	//
	return character;
}

void GUIFont::updateFontInternal() {
	textureAtlas.update();
	auto renderer = GUI::getRendererBackend();
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;
	if (textureAtlas.getAtlasTexture() != nullptr) {
		if (textureId == renderer->ID_NONE) textureId = renderer->createTexture();
		renderer->bindTexture(contextIdx, textureId);
		renderer->uploadTexture(contextIdx, textureAtlas.getAtlasTexture());
	} else
	if (textureId != renderer->ID_NONE) {
		renderer->disposeTexture(textureId);
		textureId = renderer->ID_NONE;
	}
	for (auto i = 0;; i++) {
		auto atlasTexture = textureAtlas.getAtlasTexture(i);
		if (atlasTexture == nullptr) {
			break;
		}
		//
		UTF8CharacterIterator u8It(atlasTexture->texture->getId());
		auto character = getCharacter(u8It.next());
		if (character == nullptr) {
			Console::printLine("GUIFont::updateCharacters(): Could not find character for font character '" + atlasTexture->texture->getId() + "'");
			continue;
		}
		character->x = atlasTexture->left;
		character->y = atlasTexture->top;
		character->rotated = atlasTexture->orientation == TextureAtlas::AtlasTexture::ORIENTATION_ROTATED;
	}
}

void GUIFont::initialize()
{
}

void GUIFont::dispose()
{
}

int GUIFont::getTextIndexX(const MutableString& text, int offset, int length, int index)
{
	auto u8It = text.getUTF8CharacterIterator();
	u8It.seekCharacterPosition(offset);
	if (length == 0) length = text.length();
	auto x = 0;
	auto i = offset;
	for (; u8It.hasNext() == true && i < index && i < length; i++) {
		auto characterId = u8It.next();
		auto character = getCharacter(characterId);
		if (character == nullptr) continue;
		x += character->getXAdvance();
	}
	return x;
}

int GUIFont::getTextIndexByX(const MutableString& text, int offset, int length, int textX)
{
	auto u8It = text.getUTF8CharacterIterator();
	u8It.seekCharacterPosition(offset);
	if (length == 0) length = text.length();
	auto x = 0;
	auto index = offset;
	for (; u8It.hasNext() == true && index < length; index++) {
		auto characterId = u8It.next();
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
	auto u8It = text.getUTF8CharacterIterator();
	auto width = 0;
	for (auto i = 0; u8It.hasNext() == true; i++) {
		auto characterId = u8It.next();
		auto character = getCharacter(characterId);
		if (character == nullptr) continue;
		width += character->getXAdvance();
	}
	return width;
}

int GUIFont::getTextIndexXAtWidth(const MutableString& text, int width) {
	auto u8It = text.getUTF8CharacterIterator();
	auto x = 0;
	for (auto i = 0; u8It.hasNext() == true; i++) {
		auto characterId = u8It.next();
		auto character = getCharacter(characterId);
		if (character == nullptr) continue;
		x += character->getXAdvance();
		if (x > width) return i;
	}
	return text.length() - 1;
}

void GUIFont::drawCharacter(GUIRenderer* guiRenderer, GUICharacter* character, int x, int y, const GUIColor& color) {
	//
	updateFont();
	//
	float screenWidth = guiRenderer->getScreenNode()->getScreenWidth();
	float screenHeight = guiRenderer->getScreenNode()->getScreenHeight();
	float left = x + character->getXOffset();
	float top = y + character->getYOffset();
	float width = character->getWidth();
	float height = character->getHeight();
	float textureWidth = textureAtlas.getAtlasTexture()->getTextureWidth();
	float textureHeight = textureAtlas.getAtlasTexture()->getTextureHeight();
	float textureCharLeft = character->getX();
	float textureCharTop = character->getY();
	float textureCharWidth = character->rotated == true?character->getHeight():character->getWidth();
	float textureCharHeight = character->rotated == true?character->getWidth():character->getHeight();
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		color[0], color[1], color[2], color[3],
		textureCharLeft / textureWidth, textureCharTop / textureHeight,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		color[0], color[1], color[2], color[3],
		(textureCharLeft + textureCharWidth) / textureWidth, textureCharTop / textureHeight,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		color[0], color[1], color[2], color[3],
		(textureCharLeft + textureCharWidth) / textureWidth,
		(textureCharTop + textureCharHeight) / textureHeight,
		((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		color[0], color[1], color[2], color[3],
		(textureCharLeft) / textureWidth,
		(textureCharTop + textureCharHeight) / textureHeight,
		false,
		character->rotated
	);
}

void GUIFont::drawCharacterBackground(GUIRenderer* guiRenderer, GUICharacter* character, int x, int y, int lineHeight, const GUIColor& color) {
	//
	updateFont();
	//
	float screenWidth = guiRenderer->getScreenNode()->getScreenWidth();
	float screenHeight = guiRenderer->getScreenNode()->getScreenHeight();
	float left = x;
	float top = y;
	float width = character->getXAdvance();
	float height = lineHeight;
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		color[0], color[1], color[2], color[3],
		0.0f, 1.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		color[0], color[1], color[2], color[3],
		1.0f, 1.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		color[0], color[1], color[2], color[3],
		1.0f, 0.0f,
		((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		color[0], color[1], color[2], color[3],
		0.0f, 0.0f,
		true
	);
}

void GUIFont::drawString(GUIRenderer* guiRenderer, int x, int y, const MutableString& text, int offset, int length, const GUIColor& color, int selectionStartIndex, int selectionEndIndex, const GUIColor& backgroundColor)
{
	//
	updateFont();
	//
	auto inSelection = false;
	auto currentColor = color;
	auto currentBackgroundColor = backgroundColor;
	if (selectionStartIndex != -1 && selectionEndIndex != -1) {
		auto currentX = x;
		auto u8It = text.getUTF8CharacterIterator();
		u8It.seekCharacterPosition(offset);
		for (auto i = offset; u8It.hasNext() == true && (length == 0 || i < length); i++) {
			auto characterId = u8It.next();
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
	auto u8It = text.getUTF8CharacterIterator();
	u8It.seekCharacterPosition(offset);
	for (auto i = offset; u8It.hasNext() == true && (length == 0 || i < length); i++) {
		auto characterId = u8It.next();
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
