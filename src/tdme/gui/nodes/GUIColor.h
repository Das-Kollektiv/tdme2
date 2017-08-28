// Generated from /tdme/src/tdme/gui/nodes/GUIColor.java

#pragma once

#include <array>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/gui/GUIParserException.h>

using std::array;
using std::vector;

using tdme::engine::model::Color4Base;
using java::lang::String;
using tdme::engine::model::Color4;
using java::lang::Object;
using tdme::gui::nodes::GUIColor;
using tdme::gui::GUIParserException;

struct default_init_tag;

/** 
 * GUI color
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIColor final
	: public Color4Base
{

public:
	static GUIColor* WHITE;
	static GUIColor* BLACK;
	static GUIColor* RED;
	static GUIColor* GREEN;
	static GUIColor* BLUE;
	static GUIColor* TRANSPARENT;
	static GUIColor* EFFECT_COLOR_MUL;
	static GUIColor* EFFECT_COLOR_ADD;

private:
	static vector<GUIColor*> COLOR_INSTANCES;
	static vector<String*> COLOR_NAMES;

public:
	/**
	 * Static class init
	 */
	static void clinit();

	/**
	 * Public constructor
	 */
	GUIColor();

	/**
	 * Public constructor
	 * @param color
	 */
	GUIColor(Color4* color);

	/**
	 * Public constructor
	 * @param red
	 * @param green
	 * @param blue
	 * @param alpha
	 */
	GUIColor(float r, float g, float b, float a);

	/**
	 * Public constructor
	 * @param color as float array
	 */
	GUIColor(array<float, 4>* color);

	/**
	 * Public constructor
	 * @param color as string
	 */
	GUIColor(String* colorString) throw (GUIParserException);
};
