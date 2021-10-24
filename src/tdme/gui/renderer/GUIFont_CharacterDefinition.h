#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;

/**
 * The definition of a single character as defined in the AngelCode file format
 * @author kevin, Andreas Drewke
 * @version $Id$
 */
class tdme::gui::renderer::GUIFont_CharacterDefinition final
{
	friend class GUIFont;

private:
	GUIFont* font { nullptr };

	/**
	 * Public constructor
	 */
	inline GUIFont_CharacterDefinition(GUIFont* font): font(font) {
		//
	}

	/**
	 * The id of the character
	 */
	int id { -1 };

	/**
	 * The x location on the sprite sheet
	 */
	int x { -1 };

	/**
	 * The y location on the sprite sheet
	 */
	int y { -1 };

	/**
	 * The width of the character image
	 */
	int width { -1 };

	/**
	 * The height of the character image
	 */
	int height { -1 };

	/**
	 * The amount the x position should be offset when drawing the image
	 */
	int xOffset { -1 };

	/**
	 * The amount the y position should be offset when drawing the image
	 */
	int yOffset { -1 };

	/**
	 * The amount to move the current position after drawing the character
	 */
	int xAdvance { -1 };

	/**
	 * Draw character
	 * @param guiRenderer gui renderer
	 * @param x x
	 * @param y y
	 * @param color color
	 */
	void draw(GUIRenderer* guiRenderer, int x, int y, const GUIColor& color = GUIColor::GUICOLOR_WHITE);

	/**
	 * Draw character
	 * @param guiRenderer gui renderer
	 * @param x x
	 * @param y y
	 * @param color color
	 */
	void drawBackground(GUIRenderer* guiRenderer, int x, int y, int lineHeight, const GUIColor& color);

};
