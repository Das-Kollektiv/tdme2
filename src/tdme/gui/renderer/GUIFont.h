#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/MutableString.h>

#include <tdme/os/filesystem/FileSystemException.h>

using std::map;
using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIFont_CharacterDefinition;
using tdme::gui::renderer::GUIRenderer;
using tdme::os::filesystem::FileSystemException;
using tdme::utils::MutableString;

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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * @author kevin, Andreas Drewke
 * @version $Id$
 */
class tdme::gui::renderer::GUIFont final
{
	friend class GUIFont_CharacterDefinition;

private:
	static MutableString LINEHEIGHT_STRING;

	/** 
	 * The image containing the bitmap font 
	 */
	Texture* texture {  };

	/** 
	 * Texture id 
	 */
	int32_t textureId {  };

	/** 
	 * The characters building up the font 
	 */
	map<int32_t, GUIFont_CharacterDefinition*> chars {  };

	/** 
	 * The height of a line 
	 */
	int32_t lineHeight {  };

public:

	/** 
	 * Parse the font definition file
	 * @param pathName font path name
	 * @param fileName font file name
	 * @throws FileSystemException
	 */
	static GUIFont* parse(const string& pathName, const string& fileName) throw (FileSystemException);

private:

	/** 
	 * Parse a single character line from the definition
	 * @param line line The line to be parsed
	 * @return The character definition from the line
	 */
	GUIFont_CharacterDefinition* parseCharacter(const string& line);

	/**
	 * Get character defintion
	 * @param charId character id
	 * @return character definition
	 */
	GUIFont_CharacterDefinition* getCharacter(int32_t charId);

public:

	/** 
	 * Init
	 */
	void initialize();

	/** 
	 * Dispose
	 */
	void dispose();

	/** 
	 * Draw string
	 * @param guiRenderer gui renderer
	 * @param x x
	 * @param y y
	 * @param text text
	 * @param offset offset
	 * @param length length or 0 if full length
	 * @param color color
	 */
	void drawString(GUIRenderer* guiRenderer, int32_t x, int32_t y, const MutableString& text, int32_t offset, int32_t length, const GUIColor& color);

	/** 
	 * Get text index X of given text and index
	 * @param text text
	 * @param offset offset
	 * @param length length or 0 if full length
	 * @param index index
	 * @return text index x
	 */
	int32_t getTextIndexX(const MutableString& text, int32_t offset, int32_t length, int32_t index);

	/** 
	 * Get text index by text and X in space of text
	 * @param text text
	 * @param offset offset
	 * @param length length or 0 if full length
	 * @param textX text X
	 * @return text index
	 */
	int32_t getTextIndexByX(const MutableString& text, int32_t offset, int32_t length, int32_t textX);

	/** 
	 * Get the offset from the draw location the font will place glyphs
	 * @param text text The text that is to be tested
	 * @return The yoffset from the y draw location at which text will start
	 */
	int32_t getYOffset(const MutableString& text);

	/** 
	 * Text height
	 * @param text text
	 * @return text height
	 */
	int32_t getTextHeight(const MutableString& text);

	/** 
	 * Text width
	 * @param text text
	 * @return text width
	 */
	int32_t getTextWidth(const MutableString& text);

	/** 
	 * @return line height
	 */
	int32_t getLineHeight();

	/**
	 * Public constructor
	 */
	GUIFont();

	/**
	 * Destructor
	 */
	~GUIFont();
};
