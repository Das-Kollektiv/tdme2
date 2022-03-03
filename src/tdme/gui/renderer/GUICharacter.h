#pragma once

#include <tdme/tdme.h>

/**
 * The definition of a single character as defined in the AngelCode file format
 * @author kevin, Andreas Drewke
 * @version $Id$
 */
class tdme::gui::renderer::GUICharacter final
{
public:
	/**
	 * Public constructor
	 * @param id id
	 * @param x x location on the sprite sheet
	 * @param y y location on the sprite sheet
	 * @param width width of the character image
	 * @param height height of the character image
	 * @param xOffset the amount the x position should be offset when drawing the image
	 * @param yOffset the amount the y position should be offset when drawing the image
	 * @param xAdvance the amount to move the current position after drawing the character
	 */
	inline GUICharacter(
		int id,
		int x,
		int y,
		int width,
		int height,
		int xOffset,
		int yOffset,
		int xAdvance
	):
		id(id),
		x(x),
		y(y),
		width(width),
		height(height),
		xOffset(xOffset),
		yOffset(yOffset),
		xAdvance(xAdvance)
	{
		//
	}

	/**
	 * @return id
	 */
	int getId() {
		return id;
	}

	/**
	 * @return x location on the sprite sheet
	 */
	int getX() {
		return x;
	}

	/**
	 * @return y location on the sprite sheet
	 */
	int getY() {
		return y;
	}

	/**
	 * @return width of the character image
	 */
	int getWidth() {
		return width;
	}

	/**
	 * @return height of the character image
	 */
	int getHeight() {
		return height;
	}

	/**
	 * @return the amount the x position should be offset when drawing the image
	 */
	int getXOffset() {
		return xOffset;
	}

	/**
	 * @return the amount the y position should be offset when drawing the image
	 */
	int getYOffset() {
		return yOffset;
	}

	/**
	 * @return the amount to move the current position after drawing the character
	 */
	int getXAdvance() {
		return xAdvance;
	}

private:
	int id { -1 };
	int x { -1 };
	int y { -1 };
	int width { -1 };
	int height { -1 };
	int xOffset { -1 };
	int yOffset { -1 };
	int xAdvance { -1 };
};
