// Generated from /tdme/src/tdme/gui/renderer/GUIFont.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;


struct default_init_tag;

/** 
 * The definition of a single character as defined in the AngelCode file format
 * @author kevin, Andreas Drewke
 * @version $Id$
 */
class tdme::gui::renderer::GUIFont_CharacterDefinition final
	: public Object
{

public:
	typedef Object super;

public: /* protected */

	/** 
	 * The id of the character 
	 */
	int32_t id {  };

	/** 
	 * The x location on the sprite sheet 
	 */
	int32_t x {  };

	/** 
	 * The y location on the sprite sheet 
	 */
	int32_t y {  };

	/** 
	 * The width of the character image 
	 */
	int32_t width {  };

	/** 
	 * The height of the character image 
	 */
	int32_t height {  };

	/** 
	 * The amount the x position should be offset when drawing the image 
	 */
	int32_t xOffset {  };

	/** 
	 * The amount the y position should be offset when drawing the image 
	 */
	int32_t yOffset {  };

	/** 
	 * The amount to move the current position after drawing the character 
	 */
	int32_t xAdvance {  };
public:

	/** 
	 * @see toString
	 */
	String* toString() override;

public: /* protected */

	/** 
	 * Draw character
	 * @param gui renderer
	 * @param x
	 * @param y
	 */
	void draw(GUIRenderer* guiRenderer, int32_t x, int32_t y);

	// Generated

public:
	GUIFont_CharacterDefinition(GUIFont *GUIFont_this);
protected:
	GUIFont_CharacterDefinition(GUIFont *GUIFont_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	GUIFont *GUIFont_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIFont;
};
