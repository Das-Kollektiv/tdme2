#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;

/** 
 * The definition of a single character as defined in the AngelCode file format
 * @author kevin, Andreas Drewke
 * @version $Id$
 */
class tdme::gui::renderer::GUIFont_CharacterDefinition final
{

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

public: /* protected */

	/** 
	 * Draw character
	 * @param gui renderer
	 * @param x
	 * @param y
	 */
	void draw(GUIRenderer* guiRenderer, int32_t x, int32_t y);

public:
	GUIFont_CharacterDefinition(GUIFont *GUIFont_this);

public:
	GUIFont *GUIFont_this;

private:
	friend class GUIFont;
};
