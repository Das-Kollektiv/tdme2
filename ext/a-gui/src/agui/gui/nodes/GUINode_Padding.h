#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

/**
 * GUI node padding entity
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_Padding
{
	int left { 0 };
	int top { 0 };
	int right { 0 };
	int bottom { 0 };
};
