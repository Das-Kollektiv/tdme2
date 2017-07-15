// Generated from /tdme/src/tdme/gui/nodes/GUIColor.java
#include <tdme/gui/nodes/GUIColor.h>

#include <cwchar>

#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/Integer.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/utils/StringConverter.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::gui::nodes::GUIColor;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::Integer;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::gui::GUIParserException;
using tdme::utils::StringConverter;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Color4Base, ::java::lang::ObjectArray > Color4BaseArray;
}  // namespace model
}  // namespace engine

namespace gui {
namespace nodes {
typedef ::SubArray< ::tdme::gui::nodes::GUIColor, ::tdme::engine::model::Color4BaseArray > GUIColorArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUIColor::GUIColor(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIColor::GUIColor() 
	: GUIColor(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

GUIColor::GUIColor(Color4* color) 
	: GUIColor(*static_cast< ::default_init_tag* >(0))
{
	ctor(color);
}

GUIColor::GUIColor(float r, float g, float b, float a) 
	: GUIColor(*static_cast< ::default_init_tag* >(0))
{
	ctor(r,g,b,a);
}

GUIColor::GUIColor(floatArray* color) 
	: GUIColor(*static_cast< ::default_init_tag* >(0))
{
	ctor(color);
}

GUIColor::GUIColor(String* colorString)  /* throws(GUIParserException) */
	: GUIColor(*static_cast< ::default_init_tag* >(0))
{
	ctor(colorString);
}

GUIColor* GUIColor::WHITE;

GUIColor* GUIColor::BLACK;

GUIColor* GUIColor::RED;

GUIColor* GUIColor::GREEN;

GUIColor* GUIColor::BLUE;

GUIColor* GUIColor::TRANSPARENT;

GUIColor* GUIColor::EFFECT_COLOR_MUL;

GUIColor* GUIColor::EFFECT_COLOR_ADD;

GUIColorArray* GUIColor::COLOR_INSTANCES;

StringArray* GUIColor::COLOR_NAMES;

void GUIColor::ctor()
{
	super::ctor();
	set(0.0f, 0.0f, 0.0f, 1.0f);
}

void GUIColor::ctor(Color4* color)
{
	super::ctor(static_cast< Color4Base* >(color));
}

void GUIColor::ctor(float r, float g, float b, float a)
{
	super::ctor(r, g, b, a);
}

void GUIColor::ctor(floatArray* color)
{
	super::ctor(color);
}

void GUIColor::ctor(String* colorString) throw (GUIParserException)
{
	super::ctor();
	if (colorString == nullptr) {
		throw GUIParserException("No color given");
	}
	for (auto i = 0; i < COLOR_NAMES->length; i++) {
		if ((*COLOR_NAMES)[i]->equalsIgnoreCase(colorString) == true) {
			this->data = new floatArray({
				(*(*COLOR_INSTANCES)[i]->data)[0],
				(*(*COLOR_INSTANCES)[i]->data)[1],
				(*(*COLOR_INSTANCES)[i]->data)[2],
				(*(*COLOR_INSTANCES)[i]->data)[3]
			});
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
	data = new floatArray({
		0.0f,
		0.0f,
		0.0f,
		1.0f
	});

	int colorValue;
	swscanf(colorString->substring(1, 3)->getCPPWString().c_str(), L"%02x", &colorValue);
	(*data)[0] = colorValue / 255.0f;
	swscanf(colorString->substring(3, 5)->getCPPWString().c_str(), L"%02x", &colorValue);
	(*data)[1] = colorValue / 255.0f;
	swscanf(colorString->substring(5, 7)->getCPPWString().c_str(), L"%02x", &colorValue);
	(*data)[2] = colorValue / 255.0f;
	if (colorString->length() > 7) {
		swscanf(colorString->substring(7, 9)->getCPPWString().c_str(), L"%02x", &colorValue);
		(*data)[3] = colorValue / 255.0f;
	}
}

String* GUIColor::toString()
{
	return ::java::lang::StringBuilder().append(u"GUIColor [data="_j)->append(Arrays::toString(data))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIColor::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIColor", 23);
    return c;
}

void GUIColor::clinit()
{
	super::clinit();
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
		COLOR_INSTANCES = (new GUIColorArray({
			WHITE,
			BLACK,
			RED,
			GREEN,
			BLUE,
			TRANSPARENT
		}));
		COLOR_NAMES = (new StringArray({
			u"WHITE"_j,
			u"BLACK"_j,
			u"RED"_j,
			u"GREEN"_j,
			u"BLUE"_j,
			u"TRANSPARENT"_j
		}));
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* GUIColor::getClass0()
{
	return class_();
}

