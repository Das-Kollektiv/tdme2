#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/GUIParserException.h>

using std::array;
using std::string;
using std::vector;

using tdme::engine::Color4;
using tdme::gui::nodes::GUIColor;
using tdme::gui::GUIParserException;

/**
 * GUI color
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUIColor final
	: public Color4
{

public:
	STATIC_DLL_IMPEXT static GUIColor GUICOLOR_WHITE;
	STATIC_DLL_IMPEXT static GUIColor GUICOLOR_BLACK;
	STATIC_DLL_IMPEXT static GUIColor GUICOLOR_RED;
	STATIC_DLL_IMPEXT static GUIColor GUICOLOR_GREEN;
	STATIC_DLL_IMPEXT static GUIColor GUICOLOR_BLUE;
	STATIC_DLL_IMPEXT static GUIColor GUICOLOR_TRANSPARENT;
	STATIC_DLL_IMPEXT static GUIColor GUICOLOR_EFFECT_COLOR_MUL;
	STATIC_DLL_IMPEXT static GUIColor GUICOLOR_EFFECT_COLOR_ADD;

private:
	STATIC_DLL_IMPEXT static vector<GUIColor*> COLOR_INSTANCES;
	STATIC_DLL_IMPEXT static vector<string> COLOR_NAMES;

public:

	/**
	 * Public constructor
	 */
	GUIColor();

	/**
	 * Public constructor
	 * @param color color
	 */
	GUIColor(const Color4& color);

	/**
	 * Public constructor
	 * @param r red
	 * @param g green
	 * @param b blue
	 * @param a alpha
	 */
	GUIColor(float r, float g, float b, float a);

	/**
	 * Public constructor
	 * @param color color as float array
	 */
	GUIColor(const array<float, 4>& color);

	/**
	 * Public constructor
	 * @param colorString color as string
	 * @throws tdme::gui::GUIParserException
	 */
	GUIColor(const string& colorString);
};
