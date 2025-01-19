#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

/**
 * GUI node clipping entity
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_Clipping
{

	int left { 0 };
	int top { 0 };
	int right { 0 };
	int bottom { 0 };
};
