#pragma once

#include <agui/agui.h>

/**
 * GUI character
 * @author Andreas Drewke
 */
class agui::gui::renderer::GUICharacter final
{
	friend class GUIFont;

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
		uint32_t id,
		float x,
		float y,
		float width,
		float height,
		float xOffset,
		float yOffset,
		float xAdvance
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
	uint32_t getId() {
		return id;
	}

	/**
	 * @return x location on the sprite sheet
	 */
	float getX() {
		return x;
	}

	/**
	 * @return y location on the sprite sheet
	 */
	float getY() {
		return y;
	}

	/**
	 * @return width of the character image
	 */
	float getWidth() {
		return width;
	}

	/**
	 * @return height of the character image
	 */
	float getHeight() {
		return height;
	}

	/**
	 * @return the amount the x position should be offset when drawing the image
	 */
	float getXOffset() {
		return xOffset;
	}

	/**
	 * @return the amount the y position should be offset when drawing the image
	 */
	float getYOffset() {
		return yOffset;
	}

	/**
	 * @return the amount to move the current position after drawing the character
	 */
	float getXAdvance() {
		return xAdvance;
	}

	/**
	 * @return if the character is rotated in texture atlas
	 */
	bool isRotated() {
		return rotated;
	}

private:
	uint32_t id;
	float x;
	float y;
	float width;
	float height;
	float xOffset;
	float yOffset;
	float xAdvance;
	bool rotated { false };
};
