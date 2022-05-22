#include <tdme/gui/renderer/GUIFont.h>

#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
using tdme::engine::fileio::textures::PNGTextureWriter;

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/renderer/GUICharacter.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/TextureAtlas.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::gui::renderer::GUICharacter;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::math::Math;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;
using tdme::utilities::TextureAtlas;

bool GUIFont::ftInitialized = false;
FT_Library GUIFont::ftLibrary;

GUIFont::GUIFont(const string& pathName, const string& fileName, int size): textureAtlas("font:" + pathName + "/" + fileName + "@" + to_string(size))
{
	// TODO: use pathName + fileName
	if (FT_New_Face(ftLibrary, "resources/engine/fonts/Roboto-Regular.ttf", 0, &ftFace) == true) {
		Console::println("GUIFont::parse(): Could not load font: " + pathName + "/" + fileName);
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
	for (auto& charIt: chars) delete charIt.second;
	FT_Done_Face(ftFace);
}

GUIFont* GUIFont::parse(const string& pathName, const string& fileName, int size)
{
	// init freetype library if not yet done
	if (ftInitialized == false) {
		if (FT_Init_FreeType(&ftLibrary) == true) {
			Console::println("GUIFont::parse(): Could not initialize freetype library");
			return nullptr;
		}
		ftInitialized = true;
	}

	// include standard characters in default atlas
	auto font = new GUIFont(pathName, fileName, size);
	// font->updateTextureAtlas("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ^0123456789°!&quot;$%&/()=?+*-<>|#,;.:'\"");
	// Unicode: Not yet: §°!
	font->updateTextureAtlas(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ^0123456789&quot;$%&/()=?+*-<>|#,;.:'\"");

	//
	return font;
}

void GUIFont::addToTextureAtlas(uint32_t charId) {
	Console::println("GUIFont::addToTextureAtlas(): " + (string() + (char)charId));
	//
	if (FT_Load_Char(ftFace, charId, FT_LOAD_RENDER))
	{
		Console::println("GUIFont::addToTextureAtlas(): Could not load glyph");
	    return;
	}

	//
	auto glyphBitmapWidth = ftFace->glyph->bitmap.width;
	auto glyphBitmapHeight = ftFace->glyph->bitmap.rows;
	auto glyphBitmapBuffer = ftFace->glyph->bitmap.buffer;
	auto glyphByteBuffer = ByteBuffer::allocate(glyphBitmapWidth * glyphBitmapHeight * 4);
	for (int y = glyphBitmapHeight - 1; y >= 0; y--) {
	//for (auto y = 0; y < glyphBitmapHeight; y++) {
		for (auto x = 0; x < glyphBitmapWidth; x++) {
			auto v = glyphBitmapBuffer[y * glyphBitmapWidth + x];
			glyphByteBuffer->put(v); // red
			glyphByteBuffer->put(v); // green
			glyphByteBuffer->put(v); // blue
			glyphByteBuffer->put(v); // alpha
		}
	}

	//
	auto glyphTexture = new Texture(
		to_string(charId),
		32,
		glyphBitmapWidth, glyphBitmapHeight,
		glyphBitmapWidth, glyphBitmapHeight,
		glyphByteBuffer
	);
	textureAtlas.addTexture(glyphTexture);

	Console::println(to_string(charId) + ": " + to_string(ftFace->glyph->bitmap.rows) + " / " + to_string(ftFace->glyph->bitmap_top));

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
}

void GUIFont::updateCharacters() {
	if (textureAtlas.isRequiringUpdate() == true) {
		textureAtlas.update();
		// PNGTextureWriter::write(textureAtlas.getAtlasTexture(), ".", "test.png", false, false);
		auto renderer = Engine::getInstance()->renderer;
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
	}
	for (auto i = 0;; i++) {
		auto atlasTexture = textureAtlas.getAtlasTexture(i);
		if (atlasTexture == nullptr) {
			Console::println("GUIFont::updateCharacters(): breaking at " + to_string(i));
			break;
		}
		// TODO: get rid of Integer::parse
		uint32_t charId = 0;
		try {
			charId = Integer::parse(atlasTexture->texture->getId());
		} catch (Exception& e)  {
			Console::println("GUIFont::updateCharacters(): continueing at " + to_string(i));
		}
		if (charId == 0) {
			continue;
		}
		//
		auto character = getCharacter(charId);
		if (character == nullptr) {
			Console::println("GUIFont::updateCharacters(): Could not find character for font character '" + atlasTexture->texture->getId() + "'");
			continue;
		}
		character->x = atlasTexture->left;
		character->y = atlasTexture->top;
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

void GUIFont::drawCharacter(GUIRenderer* guiRenderer, GUICharacter* character, int x, int y, const GUIColor& color) {
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
	float textureCharWidth = character->getWidth();
	float textureCharHeight = character->getHeight();
	auto& fontColor = color.getArray();
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		fontColor[0], fontColor[1], fontColor[2], fontColor[3],
		textureCharLeft / textureWidth, textureCharTop / textureHeight,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		fontColor[0], fontColor[1], fontColor[2], fontColor[3],
		(textureCharLeft + textureCharWidth) / textureWidth, textureCharTop / textureHeight,
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

void GUIFont::drawCharacterBackground(GUIRenderer* guiRenderer, GUICharacter* character, int x, int y, int lineHeight, const GUIColor& color) {
	float screenWidth = guiRenderer->getScreenNode()->getScreenWidth();
	float screenHeight = guiRenderer->getScreenNode()->getScreenHeight();
	float left = x;
	float top = y;
	float width = character->getXAdvance();
	float height = lineHeight;
	auto& backgroundColor = color.getArray();
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3],
		0.0f, 1.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3],
		1.0f, 1.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3],
		1.0f, 0.0f,
		((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3],
		0.0f, 0.0f,
		true
	);
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
