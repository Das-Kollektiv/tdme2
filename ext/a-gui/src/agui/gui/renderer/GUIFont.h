#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/fileio/fwd-agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/os/filesystem/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/MutableString.h>
#include <agui/utilities/StringTools.h>
#include <agui/utilities/TextureAtlas.h>
#include <agui/utilities/UTF8CharacterIterator.h>

#include <agui/os/filesystem/FileSystemException.h>

using std::string;
using std::unordered_map;

// namespaces
namespace agui {
namespace gui {
namespace renderer {
	using ::agui::gui::textures::GUITexture;
	using ::agui::gui::nodes::GUIColor;
	using ::agui::gui::nodes::GUIScreenNode;
	using ::agui::os::filesystem::FileSystemException;
	using ::agui::utilities::MutableString;
	using ::agui::utilities::StringTools;
	using ::agui::utilities::TextureAtlas;
	using ::agui::utilities::UTF8CharacterIterator;
}
}
}

/**
 * GUI font class
 * @author Andreas Drewke
 */
class agui::gui::renderer::GUIFont final
{
private:
	static bool ftInitialized;
	static FT_Library ftLibrary;
	string ftPathName;
	vector<uint8_t> ttfData;
	FT_Open_Args ftOpenArgs;
	FT_Face ftFace;
	TextureAtlas textureAtlas;
	int32_t textureId { 0 };
	unordered_map<uint32_t, GUICharacter*> chars;
	float lineHeight { 0.0f };
	float baseLine { 0.0f };

	// forbid class copy
	FORBID_CLASS_COPY(GUIFont)

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
		UTF8CharacterIterator u8It(text);
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
	 * @throws agui::os::filesystem::FileSystemException
	 */
	static GUIFont* parse(const string& pathName, const string& fileName, int size);

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
