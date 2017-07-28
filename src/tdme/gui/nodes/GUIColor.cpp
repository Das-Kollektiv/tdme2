// Generated from /tdme/src/tdme/gui/nodes/GUIColor.java
#include <tdme/gui/nodes/GUIColor.h>

#include <cwchar>
#include <vector>

#include <Array.h>
#include <java/lang/Integer.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/utils/StringConverter.h>

using std::vector;

using tdme::gui::nodes::GUIColor;
using java::lang::Integer;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::gui::GUIParserException;
using tdme::utils::StringConverter;

GUIColor::GUIColor() : Color4Base()
{
}

GUIColor::GUIColor(Color4* color) : Color4Base(color)
{
}

GUIColor::GUIColor(float r, float g, float b, float a) : Color4Base(r,g,b,a)
{
}

GUIColor::GUIColor(floatArray* color): Color4Base(color)
{
}

GUIColor::GUIColor(String* colorString) throw (GUIParserException) : Color4Base()
{
	clinit();
	if (colorString == nullptr) {
			throw GUIParserException("No color given");
	}
	for (auto i = 0; i < COLOR_NAMES.size(); i++) {
		if (COLOR_NAMES[i]->equalsIgnoreCase(colorString) == true) {
			this->data[0] = COLOR_INSTANCES[i]->data[0];
			this->data[1] = COLOR_INSTANCES[i]->data[1];
			this->data[2] = COLOR_INSTANCES[i]->data[2];
			this->data[3] = COLOR_INSTANCES[i]->data[3];
			return;
		}
	}
	if (colorString->startsWith(u"#"_j) == false || (colorString->length() != 7 && colorString->length() != 9)) {
		throw GUIParserException(
			"Invalid color '" +
			StringConverter::toString(colorString->getCPPWString()) +
			"'"
		);
	}
	int colorValue;
	swscanf(colorString->substring(1, 3)->getCPPWString().c_str(), L"%02x", &colorValue);
	data[0] = colorValue / 255.0f;
	swscanf(colorString->substring(3, 5)->getCPPWString().c_str(), L"%02x", &colorValue);
	data[1] = colorValue / 255.0f;
	swscanf(colorString->substring(5, 7)->getCPPWString().c_str(), L"%02x", &colorValue);
	data[2] = colorValue / 255.0f;
	if (colorString->length() > 7) {
		swscanf(colorString->substring(7, 9)->getCPPWString().c_str(), L"%02x", &colorValue);
		data[3] = colorValue / 255.0f;
	}
}

GUIColor* GUIColor::WHITE;

GUIColor* GUIColor::BLACK;

GUIColor* GUIColor::RED;

GUIColor* GUIColor::GREEN;

GUIColor* GUIColor::BLUE;

GUIColor* GUIColor::TRANSPARENT;

GUIColor* GUIColor::EFFECT_COLOR_MUL;

GUIColor* GUIColor::EFFECT_COLOR_ADD;

vector<GUIColor*> GUIColor::COLOR_INSTANCES;

vector<String*> GUIColor::COLOR_NAMES;

void GUIColor::clinit()
{
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
			WHITE = new GUIColor(new floatArray({
				1.0f,
				1.0f,
				1.0f,
				1.0f
			}));
			BLACK = new GUIColor(new floatArray({
				0.0f,
				0.0f,
				0.0f,
				1.0f
			}));
			RED = new GUIColor(new floatArray({
				1.0f,
				0.0f,
				0.0f,
				1.0f
			}));
			GREEN = new GUIColor(new floatArray({
				0.0f,
				1.0f,
				0.0f,
				1.0f
			}));
			BLUE = new GUIColor(new floatArray({
				0.0f,
				0.0f,
				1.0f,
				1.0f
			}));
			TRANSPARENT = new GUIColor(new floatArray({
				0.0f,
				0.0f,
				0.0f,
				0.0f
			}));
			EFFECT_COLOR_MUL = new GUIColor(new floatArray({
				1.0f,
				1.0f,
				1.0f,
				1.0f
			}));
			EFFECT_COLOR_ADD = new GUIColor(new floatArray({
				0.0f,
				0.0f,
				0.0f,
				0.0f
			}));
			COLOR_INSTANCES.push_back(WHITE),
			COLOR_INSTANCES.push_back(BLACK),
			COLOR_INSTANCES.push_back(RED),
			COLOR_INSTANCES.push_back(GREEN),
			COLOR_INSTANCES.push_back(BLUE),
			COLOR_INSTANCES.push_back(TRANSPARENT);
			COLOR_NAMES.push_back(u"WHITE"_j);
			COLOR_NAMES.push_back(u"BLACK"_j);
			COLOR_NAMES.push_back(u"RED"_j);
			COLOR_NAMES.push_back(u"GREEN"_j);
			COLOR_NAMES.push_back(u"BLUE"_j);
			COLOR_NAMES.push_back(u"TRANSPARENT"_j);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

