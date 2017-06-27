// Generated from /tdme/src/tdme/gui/renderer/GUIFont.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::textures::Texture;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIFont_CharacterDefinition;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::MutableString;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace gui {
namespace renderer {
typedef ::SubArray< ::tdme::gui::renderer::GUIFont_CharacterDefinition, ::java::lang::ObjectArray > GUIFont_CharacterDefinitionArray;
}  // namespace renderer
}  // namespace gui
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::gui::renderer::GUIFont_CharacterDefinitionArray;

struct default_init_tag;

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
	: public Object
{

public:
	typedef Object super;

private:
	static MutableString* LINEHEIGHT_STRING;
	static constexpr int32_t CHARACTERS_MAX { 10000 };

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
	GUIFont_CharacterDefinitionArray* chars {  };

	/** 
	 * The height of a line 
	 */
	int32_t lineHeight {  };

public:

	/** 
	 * Parse the font definition file
	 * @param font file
	 * @throws GUIParserException
	 */
	static GUIFont* parse(String* pathName, String* fileName) /* throws(Exception) */;

private:

	/** 
	 * Parse a single character line from the definition
	 * @param line The line to be parsed
	 * @return The character definition from the line
	 */
	GUIFont_CharacterDefinition* parseCharacter(String* line);

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
	 * @param gui renderer
	 * @param x
	 * @param y
	 * @param text
	 * @param offset
	 * @param length or 0 if full length
	 * @param color
	 */
	void drawString(GUIRenderer* guiRenderer, int32_t x, int32_t y, MutableString* text, int32_t offset, int32_t length, GUIColor* color);

	/** 
	 * Get text index X of given text and index
	 * @param text
	 * @param offset
	 * @param length or 0 if full length
	 * @param index
	 * @return text index x
	 */
	int32_t getTextIndexX(MutableString* text, int32_t offset, int32_t length, int32_t index);

	/** 
	 * Get text index by text and X in space of text
	 * @param text
	 * @param offset
	 * @param length or 0 if full length
	 * @param text X
	 * @return text index
	 */
	int32_t getTextIndexByX(MutableString* text, int32_t offset, int32_t length, int32_t textX);

	/** 
	 * Get the offset from the draw location the font will place glyphs
	 * @param text The text that is to be tested
	 * @return The yoffset from the y draw location at which text will start
	 */
	int32_t getYOffset(MutableString* text);

	/** 
	 * Text height
	 * @param text
	 * @return text height
	 */
	int32_t getTextHeight(MutableString* text);

	/** 
	 * Text width
	 * @param text
	 * @return text width
	 */
	int32_t getTextWidth(MutableString* text);

	/** 
	 * @return line height
	 */
	int32_t getLineHeight();

	// Generated
	GUIFont();
protected:
	void ctor();
	GUIFont(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class GUIFont_CharacterDefinition;
};
