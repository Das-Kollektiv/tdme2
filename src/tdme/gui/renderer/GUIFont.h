#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/TextureAtlas.h>

#include <tdme/os/filesystem/FileSystemException.h>

using std::string;
using std::unordered_map;

using tdme::engine::fileio::textures::Texture;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUICharacter;
using tdme::gui::renderer::GUIRenderer;
using tdme::os::filesystem::FileSystemException;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;
using tdme::utilities::TextureAtlas;

/**
 * GUI Font
 * A font implementation that will parse the output of the AngelCode font tool available at:
 * @see http://www.angelcode.com/products/bmfont/
 * This implementation copes with both the font display and kerning information allowing nicer
 * looking paragraphs of text. Note that this utility only supports the text format definition
 * file.
 * This was found by google and its origin seems to be Slick2D (http://slick.ninjacave.com) which is under BSD license
 * Copyright (c) 2013, Slick2D
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * * Neither the name of the Slick2D nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS �������AS IS�������� AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * @author kevin, Andreas Drewke
 */
class tdme::gui::renderer::GUIFont final
{
private:
	static bool ftInitialized;
	static FT_Library ftLibrary;
	FT_Face ftFace;
	TextureAtlas textureAtlas;
	int32_t textureId { 0 };
	unordered_map<uint32_t, GUICharacter*> chars;
	float lineHeight { 0.0f };
	float baseLine { 0.0f };

	/**
	 * Public constructor
	 * @param pathName font path name
	 * @param fileName font file name
	 * @param size font pixel size
	 */
	GUIFont(const string& pathName, const string& fileName, int size);

	/**
	 * Add character with given id to texture atlas
	 * @param charId character id
	 * @return GUI character entity
	 */
	GUICharacter* addToTextureAtlas(uint32_t charId);

	/**
	 * Update texture atlas
	 * @param text text chars to be included in atlas
	 */
	inline void addCharactersToFont(const string& text) {
		auto updatedTextureAtlas = false;
		StringTools::UTF8CharacterIterator u8It(text);
		while (u8It.hasNext() == true) {
			auto characterId = u8It.next();
			if (characterId == -1) continue;
			if (getCharacter(characterId) == nullptr) {
				addToTextureAtlas(characterId);
				updatedTextureAtlas = true;
			}
		}
		if (updatedTextureAtlas == true) updateFontInternal();
	}

	/**
	 * Update font texture atlas and character definitions
	 */
	inline void updateFont() {
		if (textureAtlas.isRequiringUpdate() == true) updateFontInternal();
	}

	/**
	 * Do the update work
	 */
	void updateFontInternal();

public:
	/**
	 * Parse the font definition file
	 * @param pathName font path name
	 * @param fileName font file name
	 * @param size font pixel size
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static GUIFont* parse(const string& pathName, const string& fileName, int size = 15);

	/**
	 * Destructor
	 */
	~GUIFont();

	/**
	 * Init
	 */
	void initialize();

	/**
	 * Dispose
	 */
	void dispose();

	/**
	 * @return texture id
	 */
	inline int32_t getTextureId() {
		return textureId;
	}

	/**
	 * Get character defintion
	 * @param charId character id
	 * @return character definition
	 */
	inline GUICharacter* getCharacter(uint32_t charId) {
		// ignore -1 character
		if (charId == -1) return nullptr;
		// try to get char and return it
		auto charIt = chars.find(charId);
		if (charIt != chars.end()) return charIt->second;
		// no yet added, add it
		return addToTextureAtlas(charId);
	}

	/**
	 * @return line height
	 */
	inline float getLineHeight() {
		return lineHeight;
	}

	/**
	 * @return base line
	 */
	inline float getBaseLine() {
		return baseLine;
	}

	/**
	 * Get text index X of given text and index
	 * @param text text
	 * @param offset offset
	 * @param length length or 0 if full length
	 * @param index index
	 * @return text index x
	 */
	int getTextIndexX(const MutableString& text, int offset, int length, int index);

	/**
	 * Get text index by text and X in space of text
	 * @param text text
	 * @param offset offset
	 * @param length length or 0 if full length
	 * @param textX text X
	 * @return text index
	 */
	int getTextIndexByX(const MutableString& text, int offset, int length, int textX);

	/**
	 * Text width
	 * @param text text
	 * @return text width
	 */
	int getTextWidth(const MutableString& text);

	/**
	 * Get text index X at width
	 * @param text text
	 * @return text width
	 */
	int getTextIndexXAtWidth(const MutableString& text, int width);

	/**
	 * Draw character
	 * @param guiRenderer gui renderer
	 * @param character character
	 * @param x x
	 * @param y y
	 * @param color color
	 */
	void drawCharacter(GUIRenderer* guiRenderer, GUICharacter* character, int x, int y, const GUIColor& color = GUIColor::GUICOLOR_WHITE);

	/**
	 * Draw background
	 * @param guiRenderer gui renderer
	 * @param character character
	 * @param x x
	 * @param y y
	 * @param lineHeight line height
	 * @param color color
	 */
	void drawCharacterBackground(GUIRenderer* guiRenderer, GUICharacter* character, int x, int y, int lineHeight, const GUIColor& color);

	/**
	 * Draw string
	 * @param guiRenderer gui renderer
	 * @param x x
	 * @param y y
	 * @param text text
	 * @param offset offset
	 * @param length length or 0 if full length
	 * @param color color
	 * @param selectionStartIndex selection start index
	 * @param selectionEndIndex selection end index
	 * @param backgroundColor background color
	 */
	void drawString(GUIRenderer* guiRenderer, int x, int y, const MutableString& text, int offset, int length, const GUIColor& color, int selectionStartIndex = -1, int selectionEndIndex = -1, const GUIColor& backgroundColor = GUIColor::GUICOLOR_TRANSPARENT);

};
