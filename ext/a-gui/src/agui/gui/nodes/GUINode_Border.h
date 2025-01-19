#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>

/**
 * GUI node border entity
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_Border
{

	GUIColor leftColor;
	GUIColor topColor;
	GUIColor rightColor;
	GUIColor bottomColor;
	int left { 0 };
	int top { 0 };
	int right { 0 };
	int bottom { 0 };
};
