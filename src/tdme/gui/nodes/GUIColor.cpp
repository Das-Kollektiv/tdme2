#include <tdme/gui/nodes/GUIColor.h>

#include <array>
#include <cstdio>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using std::array;
using std::string;
using std::vector;

using tdme::engine::Color4;
using tdme::gui::nodes::GUIColor;
using tdme::gui::GUIParserException;
using tdme::utilities::Console;
using tdme::utilities::StringTools;

GUIColor GUIColor::GUICOLOR_WHITE(1.0f, 1.0f, 1.0f, 1.0f);
GUIColor GUIColor::GUICOLOR_BLACK(0.0f, 0.0f, 0.0f, 1.0f);
GUIColor GUIColor::GUICOLOR_RED(1.0f, 0.0f, 0.0f, 1.0f);
GUIColor GUIColor::GUICOLOR_GREEN(0.0f, 1.0f, 0.0f, 1.0f);
GUIColor GUIColor::GUICOLOR_BLUE(0.0f, 0.0f, 1.0f, 1.0f);
GUIColor GUIColor::GUICOLOR_TRANSPARENT(0.0f, 0.0f, 0.0f, 0.0f);
GUIColor GUIColor::GUICOLOR_EFFECT_COLOR_MUL(1.0f, 1.0f, 1.0f, 1.0f);
GUIColor GUIColor::GUICOLOR_EFFECT_COLOR_ADD(0.0f, 0.0f, 0.0f, 0.0f);

vector<GUIColor*> GUIColor::COLOR_INSTANCES = {{
	&GUICOLOR_WHITE,
	&GUICOLOR_BLACK,
	&GUICOLOR_RED,
	&GUICOLOR_GREEN,
	&GUICOLOR_BLUE,
	&GUICOLOR_TRANSPARENT
}};

vector<string> GUIColor::COLOR_NAMES = {{
	"WHITE",
	"BLACK",
	"RED",
	"GREEN",
	"BLUE",
	"TRANSPARENT"
}};

GUIColor::GUIColor() : Color4()
{
}

GUIColor::GUIColor(const Color4& color) : Color4(color)
{
}

GUIColor::GUIColor(float r, float g, float b, float a) : Color4(r,g,b,a)
{
}

GUIColor::GUIColor(const array<float, 4>& color): Color4(color)
{
}

GUIColor::GUIColor(const string& colorString) : Color4()
{
	if (colorString.empty() == true) {
		Console::println("GUI: Warning: No color given");
		this->data = GUIColor::GUICOLOR_TRANSPARENT.getArray();
		return;
	}
	for (auto i = 0; i < COLOR_NAMES.size(); i++) {
		if (StringTools::equalsIgnoreCase(COLOR_NAMES[i], colorString) == true) {
			this->data[0] = COLOR_INSTANCES[i]->data[0];
			this->data[1] = COLOR_INSTANCES[i]->data[1];
			this->data[2] = COLOR_INSTANCES[i]->data[2];
			this->data[3] = COLOR_INSTANCES[i]->data[3];
			return;
		}
	}
	if (StringTools::startsWith(colorString, "#") == false || (colorString.length() != 7 && colorString.length() != 9)) {
		Console::println("GUI: Warning: Invalid color '" + (colorString) + "'");
		this->data = GUIColor::GUICOLOR_TRANSPARENT.getArray();
		return;
	}
	int colorValue;
	sscanf(colorString.substr(1, 3).c_str(), "%02x", &colorValue);
	data[0] = colorValue / 255.0f;
	sscanf(colorString.substr(3, 5).c_str(), "%02x", &colorValue);
	data[1] = colorValue / 255.0f;
	sscanf(colorString.substr(5, 7).c_str(), "%02x", &colorValue);
	data[2] = colorValue / 255.0f;
	if (colorString.length() > 7) {
		sscanf(colorString.substr(7, 9).c_str(), "%02x", &colorValue);
		data[3] = colorValue / 255.0f;
	}
}
