#pragma once

#include <array>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/misc/GUIColor4.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/GUIParserException.h>

using std::array;
using std::string;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::gui::misc::GUIColor4;
	using ::agui::gui::GUIParserException;
}
}
}

/**
 * GUI color
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIColor final
	: public GUIColor4
{

public:
	AGUI_STATIC_DLL_IMPEXT static GUIColor GUICOLOR_WHITE;
	AGUI_STATIC_DLL_IMPEXT static GUIColor GUICOLOR_BLACK;
	AGUI_STATIC_DLL_IMPEXT static GUIColor GUICOLOR_RED;
	AGUI_STATIC_DLL_IMPEXT static GUIColor GUICOLOR_GREEN;
	AGUI_STATIC_DLL_IMPEXT static GUIColor GUICOLOR_BLUE;
	AGUI_STATIC_DLL_IMPEXT static GUIColor GUICOLOR_TRANSPARENT;
	AGUI_STATIC_DLL_IMPEXT static GUIColor GUICOLOR_EFFECT_COLOR_MUL;
	AGUI_STATIC_DLL_IMPEXT static GUIColor GUICOLOR_EFFECT_COLOR_ADD;

private:
	AGUI_STATIC_DLL_IMPEXT static vector<GUIColor*> COLOR_INSTANCES;
	AGUI_STATIC_DLL_IMPEXT static vector<string> COLOR_NAMES;

public:

	/**
	 * Public constructor
	 */
	GUIColor();

	/**
	 * Public constructor
	 * @param color color
	 */
	GUIColor(const GUIColor4& color);

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
	 * @throws agui::gui::GUIParserException
	 */
	GUIColor(const string& colorString);
};
