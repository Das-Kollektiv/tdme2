#include <tdme/gui/nodes/GUIColor.h>

#include <array>
#include <cwchar>
#include <string>
#include <vector>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/StringUtils.h>

using std::array;
using std::wstring;
using std::vector;

using tdme::gui::nodes::GUIColor;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::gui::GUIParserException;
using tdme::utils::StringConverter;
using tdme::utils::StringUtils;

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

vector<wstring> GUIColor::COLOR_NAMES = {{
	L"WHITE",
	L"BLACK",
	L"RED",
	L"GREEN",
	L"BLUE",
	L"TRANSPARENT"
}};

GUIColor::GUIColor() : Color4Base()
{
}

GUIColor::GUIColor(const Color4& color) : Color4Base(color)
{
}

GUIColor::GUIColor(float r, float g, float b, float a) : Color4Base(r,g,b,a)
{
}

GUIColor::GUIColor(const array<float, 4>& color): Color4Base(color)
{
}

GUIColor::GUIColor(const wstring& colorString) throw (GUIParserException) : Color4Base()
{
	if (colorString.empty() == true) {
		throw GUIParserException("No color given");
	}
	for (auto i = 0; i < COLOR_NAMES.size(); i++) {
		if (StringUtils::equalsIgnoreCase(COLOR_NAMES[i], colorString) == true) {
			this->data[0] = COLOR_INSTANCES[i]->data[0];
			this->data[1] = COLOR_INSTANCES[i]->data[1];
			this->data[2] = COLOR_INSTANCES[i]->data[2];
			this->data[3] = COLOR_INSTANCES[i]->data[3];
			return;
		}
	}
	if (StringUtils::startsWith(colorString, L"#") == false || (colorString.length() != 7 && colorString.length() != 9)) {
		throw GUIParserException(
			"Invalid color '" +
			StringConverter::toString(colorString) +
			"'"
		);
	}
	int colorValue;
	swscanf(colorString.substr(1, 3).c_str(), L"%02x", &colorValue);
	data[0] = colorValue / 255.0f;
	swscanf(colorString.substr(3, 5).c_str(), L"%02x", &colorValue);
	data[1] = colorValue / 255.0f;
	swscanf(colorString.substr(5, 7).c_str(), L"%02x", &colorValue);
	data[2] = colorValue / 255.0f;
	if (colorString.length() > 7) {
		swscanf(colorString.substr(7, 9).c_str(), L"%02x", &colorValue);
		data[3] = colorValue / 255.0f;
	}
}
