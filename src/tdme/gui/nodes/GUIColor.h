#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/gui/GUIParserException.h>

using std::array;
using std::wstring;
using std::vector;

using tdme::engine::model::Color4Base;
using tdme::engine::model::Color4;
using tdme::gui::nodes::GUIColor;
using tdme::gui::GUIParserException;

/** 
 * GUI color
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIColor final
	: public Color4Base
{

public:
	static GUIColor WHITE;
	static GUIColor BLACK;
	static GUIColor RED;
	static GUIColor GREEN;
	static GUIColor BLUE;
	static GUIColor TRANSPARENT;
	static GUIColor EFFECT_COLOR_MUL;
	static GUIColor EFFECT_COLOR_ADD;

private:
	static vector<GUIColor*> COLOR_INSTANCES;
	static vector<wstring> COLOR_NAMES;

public:

	/**
	 * Public constructor
	 */
	GUIColor();

	/**
	 * Public constructor
	 * @param color
	 */
	GUIColor(const Color4& color);

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
	GUIColor(const array<float, 4>& color);

	/**
	 * Public constructor
	 * @param color as string
	 */
	GUIColor(const wstring& colorString) throw (GUIParserException);
};
