#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

/**
 * GUI screen node size constraints entity
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUIScreenNode_SizeConstraints
{
	int minWidth { -1 };
	int minHeight { -1 };
	int maxWidth { -1 };
	int maxHeight { -1 };
};
